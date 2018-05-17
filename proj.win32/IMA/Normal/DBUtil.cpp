#include "DBUtil.h"

sqlite3* DBUtil::pDB = NULL;
sqlite3_stmt* DBUtil::m_stmt = NULL;
char* errMsg = NULL;//错误指令
std::string sqlstr;//SQL指令
int result;//sqlite3_exec返回值
DBUtil::DBUtil()
{
}


DBUtil::~DBUtil()
{
}

void DBUtil::initDB(const char * db)
{
	result = sqlite3_open(db, &pDB);
	if (result != SQLITE_OK)
	{
		log(u8"打开数据库失败，错误码：%d,错误原因:%s\n", result, errMsg);
	}
	else
	{
		log(u8"打开数据库成功");
	}
}
sqlite3_stmt * DBUtil::GetSTMTByString(const string & additionstring)
{
	if (m_stmt)
	{
		sqlite3_reset(m_stmt);
	}
	const char *zTail;
	if (sqlite3_prepare_v2(pDB, ("select * from " + additionstring).c_str(), -1, &m_stmt, &zTail) == SQLITE_OK)
	{
		if (sqlite3_step(m_stmt) == SQLITE_ROW)
			return m_stmt;
	}
	else
	{
		log("%s", zTail);
	}
	return nullptr;
}
sqlite3_stmt * DBUtil::GetSTMTDataByName(const string & table, const string& name)
{
	return GetSTMTByString(table + " where name='" + name +"'");
}
sqlite3_stmt * DBUtil::GetSTMTDataByID(const string& table, int ID)
{
	return GetSTMTByString(table + " where id = " + StringUtils::toString(ID));
}
int isExisted(void* para, int n_column, char** column_value, char** column_name)
{
	bool *isExisted_ = (bool*)para;
	*isExisted_ = (**column_value) != '0';
	return 0;
}

bool DBUtil::tableIsExist(const string& name)
{
	if (pDB != NULL)
	{
		bool tableIsExited;
		sqlstr = "select count(type) from sqlite_master where type = 'table' and name = " + name;
		result = sqlite3_exec(pDB, sqlstr.c_str(), isExisted, &tableIsExited, &errMsg);
		return tableIsExited;
	}
	return false;
}
//"create table xxx(xx xx,xx xx,xx, xx)"
void DBUtil::createTable(const string& name)
{
	if (!tableIsExist(name))
	{
		result = sqlite3_exec(pDB, sqlstr.c_str(), NULL, NULL, &errMsg);
		if (result != SQLITE_OK)
			log("创建表失败，错误码：%d, 错误原因：%s\n", result, errMsg);
	}
}
//"drop table name"
void DBUtil::deleteTable(const string& name)
{
	if (tableIsExist(name))
	{
		result = sqlite3_exec(pDB, sqlstr.c_str(), NULL, NULL, &errMsg);
		if (result != SQLITE_OK)
			log("删除表失败，错误码:%d，错误原因：%s\n", result, errMsg);
	}
}

void DBUtil::insertData()
{
	sqlstr.clear();
	sqlstr = "insert into MyTable_1( name ) values ( '擎天柱' ) ";
	result = sqlite3_exec(pDB, sqlstr.c_str(), NULL, NULL, &errMsg);
	if (result != SQLITE_OK)
		log(u8"插入数据失败，错误码:%d，错误原因：%s\n", result, errMsg);
}

void DBUtil::insertString(const string& table, const string& name, const string& value)
{
	sqlstr.clear();
	//sqlstr = " insert into MyTable_1( name ) values ( '擎天柱' ) ";
	sqlstr = StringUtils::format("insert into %s (%s) values ('%s')", table.c_str(), name.c_str(), value.c_str());
	//sqlstr = "insert into " + table + "(" + name + ") values " + "('" + value + "')";
	result = sqlite3_exec(pDB, sqlstr.c_str(), NULL, NULL, &errMsg);
	if (result != SQLITE_OK)
		log(u8"插入数据失败，错误码:%d，错误原因：%s\n", result, errMsg);
	else
	{
		log(u8"插入数据成功");
	}
}

void DBUtil::insertInt(const string& table, const string& name, int value)
{
	sqlstr.clear();
	//sqlstr = " insert into MyTable_1( name ) values ( '擎天柱' ) ";
	sqlstr = StringUtils::format("insert into %s (%s) values ('%d')", table.c_str(), name.c_str(), value);
	//sqlstr = "insert into " + table + "(" + name + ") values " + "('" + StringUtils::format("%d",value) + "')";
	result = sqlite3_exec(pDB, sqlstr.c_str(), NULL, NULL, &errMsg);
	if (result != SQLITE_OK)
		log(u8"插入数据失败，错误码:%d，错误原因：%s\n", result, errMsg);
	else
	{
		log(u8"插入数据成功");
	}
}

void DBUtil::insertDouble(const string& table, const string& name, double value)
{
	sqlstr.clear();
	//sqlstr = " insert into MyTable_1( name ) values ( '擎天柱' ) ";
	sqlstr = StringUtils::format("insert into %s (%s) values ('%lf')", table.c_str(), name.c_str(), value);
	//sqlstr = "insert into " + table + "(" + name + ") values " + "('" + StringUtils::format("%lf", value) + "')";
	result = sqlite3_exec(pDB, sqlstr.c_str(), NULL, NULL, &errMsg);
	if (result != SQLITE_OK)
		log(u8"插入数据失败，错误码:%d，错误原因：%s\n", result, errMsg);
	else
	{
		log(u8"插入数据成功");
	}
}

void DBUtil::deleteData(const string& table, const string& key, const string& keyValue)
{
	char s[100];
	memset(s, 0, 100);
	sprintf_s(s, 100, "delete from %s where %s = '%s'", table.c_str(), key.c_str(), keyValue.c_str());
	//sqlstr = StringUtils::format("delete from %s where %s = '%s'", table.c_str(), key.c_str(), keyValue.c_str());
	result = sqlite3_exec(pDB, s, NULL, NULL, &errMsg);
	if (result != SQLITE_OK)
		log(u8"删除数据失败，错误码:%d，错误原因：%s\n", result, errMsg);
	else
	{
		log(u8"删除数据成功");
	}
}

void DBUtil::updateData()
{
	sqlstr.clear();
	//sqlstr = StringUtils::format("update ")
	
	result = sqlite3_exec(pDB, sqlstr.c_str(), NULL, NULL, &errMsg);
	if (result != SQLITE_OK)
		log("插入记录失败，错误码:%d，错误原因：%s\n", result, errMsg);
}
void DBUtil::updateDataForInt(const string& table, const string& tagetname, int tagetvalue, const string& key, const string& keyValue)
{
	sqlstr.clear();
	char s[100];
	memset(s, 0, 100);
	sprintf_s(s,100, "update %s set %s=%d where %s = '%s'", table.c_str(), tagetname.c_str(), tagetvalue, key.c_str(), keyValue.c_str());
	//sqlstr = StringUtils::format("update %s set %s=%d where %s = '%s'", table.c_str(), tagetname.c_str(), tagetvalue, key.c_str(), keyValue.c_str());
		result = sqlite3_exec(pDB, s, NULL, NULL, &errMsg);
	if (result != SQLITE_OK)
		log("插入记录失败，错误码:%d，错误原因：%s\n", result, errMsg);
	else
	{
		log(u8"插入记录成功");
	}
}
void DBUtil::updateDataForDouble(const string& table, const string& tagetname, double tagetvalue, const string& key, const string& keyValue)
{
	sqlstr.clear();
	char s[100];
	memset(s, 0, 100);
	sprintf_s(s, 100, "update %s set %s=%lf where %s = '%s'", table.c_str(), tagetname.c_str(), tagetvalue, key.c_str(), keyValue.c_str());
	//sqlstr = StringUtils::format("update %s set %s=%lf where %s = '%s'", table.c_str(), tagetname.c_str(), tagetvalue, key.c_str(), keyValue.c_str());
	result = sqlite3_exec(pDB, s, NULL, NULL, &errMsg);
	if (result != SQLITE_OK)
		log("插入记录失败，错误码:%d，错误原因：%s\n", result, errMsg);
	else
	{
		log(u8"插入记录成功");
	}
}
void DBUtil::updateDataForString(const string& table, const string& targetname, const string& targetvalue, const string& key, const string& keyValue)
{
	char s[100];
	memset(s, 0, 100);
	sprintf_s(s, sizeof(s), "update %s set %s='%s' where %s = '%s'", table.c_str(), targetname.c_str(), targetvalue.c_str(), key.c_str(), keyValue.c_str());
	result = sqlite3_exec(pDB, s, NULL, NULL, &errMsg);
	if (result != SQLITE_OK)
		log(u8"插入记录失败，错误码:%d，错误原因：%s\n", result, errMsg);
	else
	{
		log(u8"插入记录成功");
	}
}

int DBUtil::getDataCount()
{
	
	return 0;
}

int DBUtil::getIntDataByName(const string & table, const string & name, int field)
{
	return sqlite3_column_int(GetSTMTDataByName(table, name),field);
}

int DBUtil::getIntDataByID(const string & table, int ID, int field)
{
	return 0;
}

double DBUtil::getDoubleDataByName(const string & table, const string & name, int field)
{
	return sqlite3_column_double(GetSTMTDataByName(table, name), field);
}

double DBUtil::getDoubleDataByID(const string & table, int ID, int field)
{
	return 0.0;
}

string DBUtil::getStringDataByName(const string & table, const string & name, int field)
{
	return string((char*)sqlite3_column_text(GetSTMTDataByName(table, name), field));
}

string DBUtil::getStringDataID(const string & table, int ID, int field)
{
	return string();
}

void DBUtil::closeDB()
{
	sqlite3_close(pDB);
}
