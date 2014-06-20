#pragma once
#include "../Common/Common.h"

class CTextParser
{
public:
	CTextParser(void);
	~CTextParser(void);

	int SkipSpecialChars(const char* chBuffer, long nCurPosition, long iLength);
	int GoToNewLine(const char* chBuffer, long nPosition, long iLength);
	
	string GetToken(const char* chBuffer, long &nCurPosition, long iLength);
	string GetBlock(const char* chBuffer, long &nCurPosition, long iLength);
	long ParseLong(const char* chBuffer, long &nCurPosition, long iLength);
	int ParseInt(const char* chBuffer, long &nCurPosition, long iLength);
};
