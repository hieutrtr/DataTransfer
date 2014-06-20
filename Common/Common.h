#pragma once

#include "../Utilities/Utilities.h"
#include "../Utilities/DBUtilities.h"
#include "../Utilities/APIUtilities.h"
#include <vector>
#include <queue>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>
#include <map>
#include <set>
#include <iterator> // for ostream_iterator

using namespace std;

typedef vector<string> StringArray;
typedef vector<int> IntArray;
typedef set<string> StringSet;

struct InterfaceInfo
{
	string strJson;
	string strMac;
	IP_TYPE eType;
};

//======Time define===========
#define SEC_PER_MIN		60
#define SEC_PER_HOUR	3600
#define SEC_PER_DAY		86400
#define SEC_PER_WEEK		(7 * SEC_PER_DAY)
#define SEC_PER_MONTH		(30 * SEC_PER_DAY)
#define SEC_PER_YEAR		(365 * SEC_PER_DAY)
//===Interval Define (by secs)===
#define DB_CONNECT_RETRY_INTERVAL 1
#define DB_RECONNECT_TIME 3
#define INVALID_IP_ADDRESS "127.0.0.1"
#define PARSE_LOG_INTERVAL 3
#define ETL_DEFAULT_INTERVAL 3600
#define CENTRALIZE_INTERVAL 1


#define RAW_ALERT_STATUS_INIT        	0
#define RAW_ALERT_STATUS_CENTRALIZED    1
#define RAW_ALERT_STATUS_ITSM_OPENNED   2
#define RAW_ALERT_STATUS_ITSM_CLOSED    3
#define RAW_ALERT_STATUS_ITSM_REOPEN    4
#define RAW_ALERT_STATUS_ITSM_REJECTED  5
#define RAW_ALERT_STATUS_ITSM_RESOLVED  6

#define JSON_ROOT 0
