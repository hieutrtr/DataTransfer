#include "DBUtilities.h"
#include "../Common/DBCommon.h"
#include "../Config/ConfigFile.h"


/*
 * Constructor - Assign a file name
 */
CDBUtilities::CDBUtilities()
{

}

/*
 * Destructor -
 */
CDBUtilities::~CDBUtilities()
{

}

/*
* Get Connect Info -
*/
ConnectInfo CDBUtilities::GetConnectInfo()
{
	ConnectInfo CInfo;
	/*
	CInfo.strHost = pConfigFile->GetHost();
	CInfo.strUser = pConfigFile->GetUser();
	CInfo.strPass = pConfigFile->GetPassword();
	CInfo.strSource = pConfigFile->GetSource();
	CInfo.bIsReplicateSetUsed = pConfigFile->IsReplicateSetUsed();	
	CInfo.strReadReferenceOption = pConfigFile->GetReadReference();

	if(pConfigFile->GetPort().compare("") != 0)
	{
	CInfo.strHost = CInfo.strHost + ":" + pConfigFile->GetPort();
	}
	*/
	CInfo.strDBType = CConfigFile::GetInstance()->GetDBType();
	CInfo.strHost = CConfigFile::GetInstance()->GetHost();
	CInfo.strUser = CConfigFile::GetInstance()->GetUser();
	CInfo.strPass = CConfigFile::GetInstance()->GetPassword();
	CInfo.strSource = CConfigFile::GetInstance()->GetSource();
	CInfo.bIsReplicateSetUsed = CConfigFile::GetInstance()->IsReplicateSetUsed();
	CInfo.strReadReferenceOption = CConfigFile::GetInstance()->GetReadReference();
	
	if (CConfigFile::GetInstance()->GetPort().compare("") != 0)
	{
		CInfo.strHost = CInfo.strHost + ":" + CConfigFile::GetInstance()->GetPort();
	}

	return CInfo;
}
