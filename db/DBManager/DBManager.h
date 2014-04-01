#ifndef __DBMANAGER_H__
#define __DBMANAGER_H__

#include <mysql.h>

class DBManager
{
public:
	DBManager(const char *host, const char *user, const char *passwd, const char
			*db);
	~DBManager();
	bool ExecuteSql(const char *sql);           // execute any sql command
	MYSQL_RES *OpenRecordset(const char *sql);  // only execute sql query
	void FreeResult(MYSQL_RES *result);

private:
	bool Open();		// open a new connection to MySQL
	void Close();		// close the connection to MySQL
	bool GetConnState();// check if there is already a connection established 

private:
	MYSQL conn;
	bool is_open;

	const char *host;   // address of MySQL
	const char *user;   // user name of MySQL
	const char *passwd; // password for username
	const char *db;     // which db to use? equal to "use dbname" in mysql
};

#endif
