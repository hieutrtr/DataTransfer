#include "SO6AlertController.h"
#include "../Common/DBCommon.h"

CSO6AlertController::CSO6AlertController(void)
{
}

CSO6AlertController::~CSO6AlertController(void)
{
}

bool CSO6AlertController::Find()
{
	string strQuery;
	strQuery = "SELECT * FROM `alert`";
	return SelectQuery(strQuery.c_str());
}

bool CSO6AlertController::Insert()
{

}