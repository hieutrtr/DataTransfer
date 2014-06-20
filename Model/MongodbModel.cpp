#include "MongodbModel.h"
#include "../Common/DBCommon.h"
CMongodbModel::CMongodbModel(void)
{
	m_pBSONBuilder = new BSONObjBuilder();
}

CMongodbModel::CMongodbModel(const BSONObj& objBSON)
{
	m_objBSON = objBSON;
}

CMongodbModel::~CMongodbModel(void)
{
}

void CMongodbModel::UpdateBSONObj(const BSONObj& objBSON)
{
	m_objBSON = objBSON.copy(); 
}

BSONObj CMongodbModel::MergeBSONObj(BSONObj *pOldRecord, BSONObj *pNewRecord)
{
	BSONObjBuilder bobMergedRecord;
	StringSet setFieldNames;
	StringSet::iterator it;
	string strFieldName;

	try
	{
		pOldRecord->getFieldNames(setFieldNames);
		bobMergedRecord.appendElements(*pNewRecord);
		for (it = setFieldNames.begin(); it != setFieldNames.end(); it++)
		{
			strFieldName = *it;
			if (strFieldName.compare("_id") == 0)
			{
				continue;
			}
			if (!pNewRecord->hasField(strFieldName))
			{
				bobMergedRecord.append(pOldRecord->getField(strFieldName));
			}
		}
	}
	catch (exception &ex)
	{
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CMongodbModel", "MergeBSONObj", "exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
	return bobMergedRecord.obj();
}

BSONObj CMongodbModel::MergeBSONObj(BSONObj *pOldRecord, BSONObj *pNewRecord, BSONObj &pboChangedFields)
{
	BSONObjBuilder bobMergedRecord;
	BSONObjBuilder bobChangedFields;
	StringSet setFieldNames;
	StringSet::iterator it;
	string strFieldName;
	try
	{
		bobMergedRecord.appendElements(*pNewRecord);
		if (pOldRecord->isEmpty()){
			pNewRecord->getFieldNames(setFieldNames);
		}
		else{
			pOldRecord->getFieldNames(setFieldNames);
		}
		for (it = setFieldNames.begin(); it != setFieldNames.end(); it++)
		{
			strFieldName = *it;
			if (strFieldName.compare("_id") == 0)
			{
				continue;
			}
			if (!pNewRecord->hasField(strFieldName))
			{
				bobMergedRecord.append(pOldRecord->getField(strFieldName));
			}
			else if (!pOldRecord->hasField(strFieldName))
			{
				bobChangedFields.append(strFieldName, 1);
			}
			else if ((*pNewRecord)[strFieldName] != (*pOldRecord)[strFieldName])
			{
				bobChangedFields.append(strFieldName, 1);
			}
		}
		pboChangedFields = bobChangedFields.obj();
	}
	catch (exception &ex)
	{
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CMongodbModel", "MergeBSONObj", "exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
	return bobMergedRecord.obj();
}

BSONObj CMongodbModel::ConvertBSONObj(BSONObj boRecord, map<string, string> mapField)
{
	BSONObjBuilder bobCenRecord;
	map<string, string>::iterator mit;
	int iFieldType;
	try{
		for (mit = mapField.begin(); mit != mapField.end(); mit++)
		{
			if (boRecord.hasField(mit->second)){
				iFieldType = boRecord[mit->second].type();
				switch (iFieldType)
				{
				case BSON_STRING_TYPE:
					bobCenRecord.append(mit->first, boRecord.getStringField(mit->second.c_str()));
					break;
				case BSON_INT_TYPE:
					bobCenRecord.append(mit->first, boRecord[mit->second]._numberInt());
					break;
				case BSON_TIMESTAMP_TYPE:
					bobCenRecord.append(mit->first, boRecord[mit->second]._numberLong());
					break;
				case BSON_LONG_LONG_TYPE:
					bobCenRecord.append(mit->first, boRecord[mit->second]._numberLong());
					break;
				default:
					bobCenRecord.append(mit->first, boRecord[mit->second].toString(false));
				}
			}
			else{
				bobCenRecord.append(mit->first, "");
			}
		}
	}
	catch (exception &ex)
	{
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CMongodbModel", "ConvertBSONObj", "exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
	return bobCenRecord.obj();
}

Query CMongodbModel::GetObjectIdQuery()
{
	Query queryOID = QUERY("_id" << m_beOID);
	return queryOID;
}

//template<class TYPE>
void CMongodbModel::Append(string strFieldName, int tValue)
{
	try{
		m_pBSONBuilder->append(strFieldName, tValue);
	}
	catch (exception &ex)
	{
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CMongodbModel", "int Append", "exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
}

void CMongodbModel::Append(string strFieldName, string tValue)
{
	try{
		m_pBSONBuilder->append(strFieldName, tValue);
	}
	catch (exception &ex)
	{
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CMongodbModel", "string Append", "exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
}

void CMongodbModel::Append(string strFieldName, long long tValue)
{
	try{
		m_pBSONBuilder->append(strFieldName, tValue);
	}
	catch (exception &ex)
	{
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CMongodbModel", "long long Append", "exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
}
void CMongodbModel::Append(BSONObj boAdd)
{
	try
	{
		m_pBSONBuilder->appendElements(boAdd);
	}
	catch (exception &ex)
	{
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CMongodbModel", "BSONObj Append", "exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
}

BSONObj CMongodbModel::LoadObj()
{
	BSONObj boResult = m_pBSONBuilder->obj();
	return boResult.copy();
}

BSONObj CMongodbModel::RemoveFields(BSONObj *pRecord, StringArray &arrFieldName) {
	BSONObjBuilder b;
	BSONObjIterator i(*pRecord);
	try{
		while (i.more()) {
			BSONElement e = i.next();
			const char *fname = e.fieldName();
			StringArray::iterator it = find(arrFieldName.begin(), arrFieldName.end(), fname);
			if (it == arrFieldName.end())
				b.append(e);
		}
	}
	catch (exception &ex)
	{
		stringstream strErrorMess;
		string strLog;
		strErrorMess << ex.what() << "][" << __FILE__ << "|" << __LINE__;
		strLog = CUtilities::FormatLog(ERROR_MSG, "CMongodbModel", "RemoveFields", "exception:" + strErrorMess.str());
		CUtilities::WriteErrorLog(ERROR_MSG, strLog);
	}
	return b.obj();
}