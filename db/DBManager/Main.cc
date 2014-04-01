#include <iostream>
#include <cstdio>
#include "DBManager.h"

using namespace std;

int main(int argc, char **argv)
{
	const char *host   = "localhost";
	const char *user   = "zhang";
	const char *passwd = "justice";
	const char *db     = "mydb";

	DBManager *dbm = new DBManager(host, user, passwd, db);

	if(!dbm->ExecuteSql("drop table testtbl"))
		cout<<"Failed to drop table testtbl."<<endl;

	if(!dbm->ExecuteSql("create table testtbl(id int, name char(20))"))
		cout<<"Failed to create new table testtbl."<<endl;

	if(!dbm->ExecuteSql("insert into testtbl(id, name) values('1991', 'user1')"))
		cout<<"Failed to insert new entries into testtbl."<<endl;
	if(!dbm->ExecuteSql("insert into testtbl(id, name) values('1992', 'user2')"))
		cout<<"Failed to insert new entries into testtbl."<<endl;
	if(!dbm->ExecuteSql("insert into testtbl(id, name) values('1993', 'user3')"))
		cout<<"Failed to insert new entries into testtbl."<<endl;
	if(!dbm->ExecuteSql("insert into testtbl(id, name) values('1994', 'user4')"))
		cout<<"Failed to insert new entries into testtbl."<<endl;

	MYSQL_RES *res = NULL;
	MYSQL_ROW row;

	res = dbm->OpenRecordset("select * from testtbl");

	if(res)
	{
		cout<<"Content in table: "<<endl;
		while(row = mysql_fetch_row(res))
		{
			for(int i=0; i<mysql_num_fields(res); i++)
				printf("%s ", row[i]);
			printf("\n");
		}
	}

	dbm->FreeResult(res);
	delete dbm;
	dbm = NULL;

	return 0;
}
