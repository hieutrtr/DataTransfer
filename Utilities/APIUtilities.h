#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <iconv.h>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <iterator> // for ostream_iterator
#include <vector>
#include <map>
#include <boost/regex.hpp>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <dlfcn.h>
using namespace std;

//===API RESULT===//
#define API_ACTION_ERROR 0
#define API_ACTION_SUCCESS 1
#define API_ACTION_FAIL 2
#define API_RETRY_TIME 3

class CAPIUtilities
{

public:
	CAPIUtilities();
	virtual ~CAPIUtilities();

	static int CallUpdateINCStatusAPI(char *pINCCode, short *pINCStatusID, char *pITSMCode, char *pCreatedBy, char *pComment, char *pITSMCloseDate, string &strResponse);
};
