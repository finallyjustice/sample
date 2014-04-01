#include <iostream>
#include <cstring>
#include "DBManager.h"

using namespace std;

DBManager::DBManager(const char *_host, const char *_user, const char *_passwd,
		const char *_db)
{
	host   = _host;
	user   = _user;
	passwd = _passwd;
	db     = _db;

	is_open = false;
	this->Open();
}

DBManager::~DBManager()
{
	this->Close();
}

bool DBManager::GetConnState()
{
	return is_open;
}

bool DBManager::Open()
{
	if(!mysql_init(&conn))
	{
		cout<<"Failed to initialize MySQL Connection"<<endl;
		return false;
	}

	if(!mysql_real_connect(&conn, host, user, passwd, db, 0, NULL, 0))
	{
		cout<<"Failed to connect to MySQL"<<endl;
		return false;
	}

	cout<<"Login succesfully!"<<endl;
	is_open = true;
	return is_open;
}

void DBManager::Close()
{
	if(is_open)
	{
		mysql_close(&conn);
		is_open = false;
	}
}

bool DBManager::ExecuteSql(const char *sql)
{
	if(!this->GetConnState())
		return false;
	if(mysql_real_query(&conn, sql, strlen(sql)) == 0)
		return true;
}

MYSQL_RES* DBManager::OpenRecordset(const char *sql)
{
	MYSQL_RES *rs = NULL;
	if(ExecuteSql(sql))
	{
		rs = mysql_store_result(&conn);
	}
	return rs;
}

void DBManager::FreeResult(MYSQL_RES *result)
{
	if(result)
	{
		mysql_free_result(result);
	}
}
