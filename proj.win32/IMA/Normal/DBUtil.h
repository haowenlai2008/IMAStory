#pragma once
#include "cocos2d.h"
#include "sqlite3\include\sqlite3.h"
USING_NS_CC;
using std::string;
class DBUtil
{
public:
	static void initDB(const char *db);	//�������ݿ�
	static sqlite3_stmt* GetSTMTByString(const string& additionstring);
	static sqlite3_stmt* GetSTMTDataByName(const string& table, const string& name);
	static sqlite3_stmt* GetSTMTDataByID(const string& table, int ID);
	static bool tableIsExist(const string& name);//�жϱ���Ƿ����
	static void createTable(const string& name);//����һ������name�ı��
	static void deleteTable(const string& name);//ɾ��һ������name�ı��
	static void insertData();//����һ������
	static void insertString(const string& table, const string& name, const string& value);
	static void insertInt(const string& table, const string& name, int value);
	static void insertDouble(const string& table, const string& name, double value);
	static void deleteData(const string& table, const string& key, const string& keyValue);//ɾ��һ������
	static void updateData();//�޸�һ������
	static void updateDataForInt(const string& table, const string& tagetname, int tagetvalue, const string& key, const string& keyValue);
	static void updateDataForDouble(const string& table, const string& tagetname, double tagetvalue, const string& key, const string& keyValue);
	static void updateDataForString(const string& table, const string& tagetname, const string& tagetvalue, const string& key, const string& keyValue);
	static int getDataCount();//��ü�¼������
	static int getIntDataByName(const string& table, const string& name, int field);
	static int getIntDataByID(const string& table, int ID, int field);
	static double getDoubleDataByName(const string& table, const string& name, int field);
	static double getDoubleDataByID(const string& table, int ID, int field);
	static string getStringDataByName(const string& table, const string& name, int field);
	static string getStringDataID(const string& table, int ID, int field);
	static void closeDB();//�ر����ݿ�
	DBUtil();
	~DBUtil();
	static sqlite3 *pDB;
	static sqlite3_stmt* m_stmt;
};

