#include "APIUtilities.h"
#include "Utilities.h"
#include "../Common/DBCommon.h"
#include "../Config/ConfigFile.h"

typedef string(*UpdateINCStatus)(char*, short*, char*, char*, char*, char*);

/*
* Constructor - Assign a file name
*/
CAPIUtilities::CAPIUtilities()
{

}

/*
* Destructor -
*/
CAPIUtilities::~CAPIUtilities()
{

}

int CAPIUtilities::CallUpdateINCStatusAPI(char *pINCCode, short *pINCStatusID, char *pITSMCode, char *pCreatedBy, char *pComment, char *pITSMCloseDate, string &strResponse)
{
	stringstream strErrorMess;
	string strLog, strData;
	string strLibName = "libCSService-3.0.so";
	string strAPIName = "CallUpdateStatusCSINC";
	try{
		// open the library
		void* handle = dlopen(strLibName.c_str(), RTLD_LAZY);
		if (!handle)
		{
			strErrorMess << "Cannot open library: " << dlerror() << __FILE__ << "|" << __LINE__;
			strLog = CUtilities::FormatLog(ERROR_MSG, "CAPIUtilities", "CallUpdateINCStatusAPI", "error:" + strErrorMess.str());
			CUtilities::WriteErrorLog(ERROR_MSG, strLog);
			return API_ACTION_ERROR;
		}

		// reset errors
		dlerror();
		UpdateINCStatus apiFunction = (UpdateINCStatus)dlsym(handle, strAPIName.c_str());
		const char *dlsym_error = dlerror();
		if (dlsym_error) {
			strErrorMess << "Cannot load symbol " << strAPIName.c_str() << ":" << dlsym_error;
			strLog = CUtilities::FormatLog(ERROR_MSG, "CAPIUtilities", "CallUpdateINCStatusAPI", "error:" + strErrorMess.str());
			CUtilities::WriteErrorLog(ERROR_MSG, strLog);
			// close the library
			dlclose(handle);
			return API_ACTION_ERROR;
		}
		strResponse = apiFunction(pINCCode, pINCStatusID, pITSMCode, pCreatedBy, pComment, pITSMCloseDate);
		cout << "strResponse: " << strResponse << endl << endl;
		// close the library
		dlclose(handle);
	}
	catch (exception &ex)
	{
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CAPIUtilities", "CallUpdateINCStatusAPI", "exception:" + strErrorMess.str() + "|strData" + strData + "|Response:" + strResponse);
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
	return API_ACTION_SUCCESS;
}