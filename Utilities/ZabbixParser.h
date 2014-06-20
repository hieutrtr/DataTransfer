#pragma once
#include "TextParser.h"
#include "../Common/Common.h"

class CZabbixParser :
	public CTextParser
{
public:
	CZabbixParser(void);
	~CZabbixParser(void);

	string GetBlock(const char* chBuffer, long &nCurPosition, long iLength);
	string GetValueBlock(const char* chBuffer, long &nCurPosition, long iLength);
	string GetExpression(const char* chBuffer, long &nCurPosition, long iLength);
	string GetDescription(const char* chBuffer, long &nCurPosition, long iLength);
	string GetParameter(const char* chBuffer, long &nCurPosition, long iLength);
	string GetItemKey(const char* chBuffer, long &nCurPosition, long iLength);
	string GetItemValue(const char* chBuffer, long &nCurPosition, long iLength);
};
