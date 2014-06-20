#include "LogParser.h"
#include "../Model/LogModel.h"
#include "../Utilities/FileMapping.h"
#include "../Config/ConfigFile.h"
#include "../Config/ConfigMarkFile.h"

CLogParser::CLogParser(const string& strConfigFileName, const string& strLocationGroup)
:CProcessor(strConfigFileName)
{
	CConfigFile::GetInstance()->SetActiveLocationGroup(strLocationGroup);
	string strMarkingLog = CConfigFile::GetInstance()->GetMarkingLogPath();
	cout << "[MARKING_LOG_PATH] " << strMarkingLog << endl;
	CConfigMarkFile::GetInstance(strMarkingLog);
}

CLogParser::~CLogParser(void)
{
}

void CLogParser::Proceed()
{
	if (!Connect()) // Connecting all controllers 
	{
		return;
	}
	
	while (true)
	{
		ParseLog();
	}
}

bool CLogParser::Connect()
{
	cout << "CLogParser\n";
	return CProcessor::Connect();
}

void CLogParser::ParseLog()
{
	map<string, long> map_FileName2Position;
	map<string, long>::iterator it;
	vector<CLogModel*> v_LogModelPtr;
	CFileMapping objFileMapping;
	string strFileName;
	long lPosition, lLength;
	char *cBuffer;

	map_FileName2Position = CollectFile();
	it = map_FileName2Position.begin();
	while (it != map_FileName2Position.end())
	{
		strFileName = it->first;
		cout << strFileName << endl;
		lPosition = it->second;
		cBuffer = (char*)objFileMapping.Map(strFileName);
		lLength = objFileMapping.GetLength();
		cout << "after:ReadBuffer\n";
		cout << "lPosition:" << lPosition << endl;
		cout << "lLength:" << lLength << endl;
		v_LogModelPtr = ParseLog(lLength, lPosition, cBuffer);
		ProceedData(v_LogModelPtr);
		objFileMapping.UnMap();
		it++;
	}
}


