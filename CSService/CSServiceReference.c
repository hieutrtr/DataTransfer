#include "stdio.h"
#include <iostream>
#include <string.h>
#include <string>
#include <unistd.h>		/* defines _POSIX_THREADS if pthreads are available */
#if defined(_POSIX_THREADS) || defined(_SC_THREADS)
#include <pthread.h>
#endif
#include <signal.h>		/* defines SIGPIPE */
#include "soapH.h"
#include "BasicHttpBinding_USCOREISDKSuportSerivces.nsmap"
using namespace std;

#define CODE_ERROR_SSL_INIT "1"
#define MSG_ERROR_SSL_INIT "Cannot init ssl to dc service"

#define CODE_ERROR_CRYPTO_THREAD_SETUP "2"
#define MSG_ERROR_CRYPTO_THREAD_SETUP "Cannot setup thread mutex for OpenSSL"

#define CODE_ERROR_INIT "3"
#define MSG_ERROR_INIT "Cannot access to CS service"

#define CODE_ERROR_SSL_CLIENT_CONTEXT "4"
#define MSG_ERROR_SSL_CLIENT_CONTEXT "SSL client authentication fail"

#define CODE_ERROR_UPDATE_STATUS_INC "5"
#define MSG_ERROR_UPDATE_STATUS_INC "Cannot call update status inc to CS"

#define SECKEY "V34qG36hWwRxbff2ZeGH"
// #define SECKEY "sdk123"

int CRYPTO_thread_setup();
void CRYPTO_thread_cleanup();
void sigpipe_handle(int);

extern "C" std::string CallUpdateStatusCSINC(char *pINCCode, short *pINCStatusID, char *pITSMCode, char *pCreatedBy, char *pComment, char *pITSMCloseDate)
{
	string strResult;
	struct soap soap;
	struct _ns1__UpdateStatusINC tagUpdateStatusINCRequest;
	struct _ns1__UpdateStatusINCResponse tagUpdateStatusINCResponse;

	//Assign parameter to UpdateStatusINC Request
	tagUpdateStatusINCRequest.INCCode = pINCCode;
	tagUpdateStatusINCRequest.INCStatusID = pINCStatusID;
	tagUpdateStatusINCRequest.ITSMCode = pITSMCode;
	tagUpdateStatusINCRequest.CreatedBy = pCreatedBy;
	tagUpdateStatusINCRequest.Comment = pComment;
	tagUpdateStatusINCRequest.ITSMCloseDate = pITSMCloseDate;
	tagUpdateStatusINCRequest.sigkey = (char*)SECKEY;
	
	//****************************
	//soap_init
	//****************************
	try
	{
		// soap_init(&soap);
		soap_init1(&soap, SOAP_C_UTFSTRING);
		// soap_set_imode( &soap  , SOAP_C_MBSTRING);
		// soap_set_omode( &soap  , SOAP_C_MBSTRING);
		// soap_imode( &soap  , SOAP_C_MBSTRING);
		// soap_omode( &soap  , SOAP_C_MBSTRING);
	}
	catch(exception& ex)
	{	
		return CODE_ERROR_INIT;
	}
	//****************************
	soap.connect_timeout = 60;	/* try to connect for 1 minute */
	soap.send_timeout = soap.recv_timeout = 90;	/* if I/O stalls, then timeout after 30 seconds */
	//****************************
	
	
	if(soap_call___ns1__UpdateStatusINC(&soap, 
								NULL  /*endpoint address*/, 
								NULL  /*soapAction*/, 
								&tagUpdateStatusINCRequest,
								&tagUpdateStatusINCResponse
							   )== SOAP_OK)
	{
		strResult = tagUpdateStatusINCResponse.UpdateStatusINCResult;
	}
	else
	{   
		return CODE_ERROR_UPDATE_STATUS_INC;
	}  
    //*****************************
	//Destroy
	//*****************************
	soap_destroy(&soap); 
	soap_end(&soap); 
	soap_done(&soap);			
	//*****************************
	return strResult;
}

#ifdef WITH_OPENSSL

#if defined(WIN32)
# define MUTEX_TYPE		HANDLE
# define MUTEX_SETUP(x)		(x) = CreateMutex(NULL, FALSE, NULL)
# define MUTEX_CLEANUP(x)	CloseHandle(x)
# define MUTEX_LOCK(x)		WaitForSingleObject((x), INFINITE)
# define MUTEX_UNLOCK(x)	ReleaseMutex(x)
# define THREAD_ID		GetCurrentThreadId()
#elif defined(_POSIX_THREADS) || defined(_SC_THREADS)
# define MUTEX_TYPE		pthread_mutex_t
# define MUTEX_SETUP(x)		pthread_mutex_init(&(x), NULL)
# define MUTEX_CLEANUP(x)	pthread_mutex_destroy(&(x))
# define MUTEX_LOCK(x)		pthread_mutex_lock(&(x))
# define MUTEX_UNLOCK(x)	pthread_mutex_unlock(&(x))
# define THREAD_ID		pthread_self()
#else
# error "You must define mutex operations appropriate for your platform"
# error	"See OpenSSL /threads/th-lock.c on how to implement mutex on your platform"
#endif

struct CRYPTO_dynlock_value
{ MUTEX_TYPE mutex;
};

static MUTEX_TYPE *mutex_buf;

static struct CRYPTO_dynlock_value *dyn_create_function(const char *file, int line)
{ struct CRYPTO_dynlock_value *value;
  value = (struct CRYPTO_dynlock_value*)malloc(sizeof(struct CRYPTO_dynlock_value));
  if (value)
    MUTEX_SETUP(value->mutex);
  return value;
}

static void dyn_lock_function(int mode, struct CRYPTO_dynlock_value *l, const char *file, int line)
{ if (mode & CRYPTO_LOCK)
    MUTEX_LOCK(l->mutex);
  else
    MUTEX_UNLOCK(l->mutex);
}

static void dyn_destroy_function(struct CRYPTO_dynlock_value *l, const char *file, int line)
{ MUTEX_CLEANUP(l->mutex);
  free(l);
}

void locking_function(int mode, int n, const char *file, int line)
{ if (mode & CRYPTO_LOCK)
    MUTEX_LOCK(mutex_buf[n]);
  else
    MUTEX_UNLOCK(mutex_buf[n]);
}

unsigned long id_function()
{ return (unsigned long)THREAD_ID;
}

int CRYPTO_thread_setup()
{ int i;
  mutex_buf = (MUTEX_TYPE*)malloc(CRYPTO_num_locks() * sizeof(pthread_mutex_t));
  if (!mutex_buf)
    return SOAP_EOM;
  for (i = 0; i < CRYPTO_num_locks(); i++)
    MUTEX_SETUP(mutex_buf[i]);
  CRYPTO_set_id_callback(id_function);
  CRYPTO_set_locking_callback(locking_function);
  CRYPTO_set_dynlock_create_callback(dyn_create_function);
  CRYPTO_set_dynlock_lock_callback(dyn_lock_function);
  CRYPTO_set_dynlock_destroy_callback(dyn_destroy_function);
  return SOAP_OK;
}

void CRYPTO_thread_cleanup()
{ int i;
  if (!mutex_buf)
    return;
  CRYPTO_set_id_callback(NULL);
  CRYPTO_set_locking_callback(NULL);
  CRYPTO_set_dynlock_create_callback(NULL);
  CRYPTO_set_dynlock_lock_callback(NULL);
  CRYPTO_set_dynlock_destroy_callback(NULL);
  for (i = 0; i < CRYPTO_num_locks(); i++)
    MUTEX_CLEANUP(mutex_buf[i]);
  free(mutex_buf);
  mutex_buf = NULL;
}

#else

/* OpenSSL not used, e.g. GNUTLS is used */

int CRYPTO_thread_setup()
{ return SOAP_OK;
}

void CRYPTO_thread_cleanup()
{ }

#endif

/******************************************************************************\
 *
 *	SIGPIPE
 *
\******************************************************************************/

void sigpipe_handle(int x) { }
