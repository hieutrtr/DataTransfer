#include "TextParser.h"
#include "../Utilities/Utilities.h"

CTextParser::CTextParser(void)
{
}

CTextParser::~CTextParser(void)
{
}

int CTextParser::SkipSpecialChars(const char* chBuffer, long nCurPosition, long iLength)
{
	while (nCurPosition < iLength)
	{
		switch (chBuffer[nCurPosition])
		{
		case ' ':
		case '\t':
		case '\n':
			nCurPosition++;
			continue;
		default:
			break;
		}	

		break;
	}

	return nCurPosition;
}

int CTextParser::GoToNewLine(const char* chBuffer, long nPosition, long iLength)
{
	int nCurPosition = nPosition;	

	while (nCurPosition < iLength){
		switch (chBuffer[nCurPosition])
		{
		case '\n':
			nCurPosition++;
			return nCurPosition;			
		case '\r':
			nCurPosition++;
			continue;
		}		

		nCurPosition++;
	}

	return nCurPosition;
}

string CTextParser::GetToken(const char* chBuffer, long &nCurPosition, long iLength)
{
	string strToken;
	bool bOpenBrace = false;
	bool bBreak = false;
	nCurPosition = SkipSpecialChars(chBuffer, nCurPosition, iLength);
	while(nCurPosition < iLength)
	{
		switch (chBuffer[nCurPosition])
		{
		case '{':
			bOpenBrace = true;
			break;
		case ' ':
			if (bOpenBrace == false)
			{
				nCurPosition++;
				bBreak = true;
			}
			break;
		case '\n':
			if (bOpenBrace == false)
			{
				nCurPosition++;
				bBreak = true;
			}
			break;
		case '}':
			strToken = strToken + chBuffer[nCurPosition];
			nCurPosition++;
			bBreak = true;
			break;
		}								

		if (bBreak)
		{
			break;
		}

		if (chBuffer[nCurPosition] != '\n')
		{
			strToken = strToken + chBuffer[nCurPosition];			
		}

		nCurPosition++;
	}

	return strToken;
}

long CTextParser::ParseLong(const char* chBuffer, long &nCurPosition, long lLength)
{	
	string strValue = GetToken(chBuffer, nCurPosition, lLength);
	long lValue = 0;
	try
	{									
		lValue = atol(strValue.c_str());
	}
	catch(exception& ex)
	{
		stringstream strErrorMess;
		strErrorMess << ex.what() << " " << __FILE__ << " " << __LINE__;
		string strFormatLog = CUtilities::FormatLog(ERROR_MSG, "CTextParser", "ParseLong", strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strFormatLog);
	}

	return lValue;
}

int CTextParser::ParseInt(const char* chBuffer, long &nCurPosition, long lLength)
{
	string strValue = GetToken(chBuffer, nCurPosition, lLength);
	long iValue = 0;
	try
	{									
		iValue = atoi(strValue.c_str());
	}
	catch(exception& ex)
	{
		stringstream strErrorMess;
		strErrorMess << ex.what() << " " << __FILE__ << " " << __LINE__;
		string strFormatLog = CUtilities::FormatLog(ERROR_MSG, "CTextParser", "ParseLong", strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strFormatLog);
	}

	return iValue;
}

string CTextParser::GetBlock(const char* chBuffer, long &nCurPosition, long iLength)
{
	string strToken;
	nCurPosition = SkipSpecialChars(chBuffer, nCurPosition, iLength);
	bool bOpenBrace = false;
	while (nCurPosition < iLength)
	{
		if (chBuffer[nCurPosition] == '{')
		{
			strToken = strToken + chBuffer[nCurPosition];
			nCurPosition += 1;
			bOpenBrace = true;
			continue;
		}
		else if (chBuffer[nCurPosition] == '\r')
		{
			nCurPosition += 1;
			continue;
		}
		else if (chBuffer[nCurPosition] == '}')
		{
			strToken = strToken + chBuffer[nCurPosition];
			nCurPosition += 1;
			break;
		}
		if (chBuffer[nCurPosition] != '\n')
		{
			if (bOpenBrace == true)
				strToken = strToken + chBuffer[nCurPosition];
		}
		nCurPosition = nCurPosition + 1;
	}
	return strToken;
}