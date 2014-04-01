/* usage: g++ mysql.cc -o mysql -I /usr/include/mysql -lmysqlclient */

#include <iostream>
#include <mysql.h>
#include <cstdio>
#include <errno.h>

using namespace std;

int main(int argc, char **argv)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	const char *server   = "localhost";
	const char *user     = "zhang";
	const char *passwd   = "justice";
	const char *database = "employees";

	conn = mysql_init(NULL);

	if(!mysql_real_connect(conn, server, user, passwd, database, 0, NULL, 0))
	{
		perror("Error\n");
		cout<<"Cannot real connect to the database"<<endl;
		return 1;
	}

	if(mysql_query(conn, "select * from departments"))
	{
		cout<<"Failed to query database"<<endl;
		return 1;
	}

	res = mysql_use_result(conn);

	printf("Department List:\n");

	while((row=mysql_fetch_row(res)) != NULL)
		printf("%s, %s\n", row[0], row[1]);

	mysql_free_result(res);
	mysql_close(conn);
	return 0;
}
