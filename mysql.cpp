#include <mysql/mysql.h>
#include <cstdio>
#include <iostream>
#include <iomanip>

using namespace std;
int main()
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	const char *server = "webdev.fit.cvut.cz";
	const char *user = "chudoja3";
	const char *password = "81l2i7kd";  // got tot keep my data secret
	const char *database = "chudoja3";
	conn = mysql_init(NULL);
	
	// connect to database
	if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		return -1;
	}
	
	// send SQL query
	//SELECT TABLE_NAME FROM Information_Schema.Tables where Table_Type = 'BASE TABLE'
	//select * from Item
	if(mysql_query(conn, "SELECT TABLE_NAME FROM Information_Schema.Tables where Table_Type = 'BASE TABLE'"))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		return -1;
	}
	
	res = mysql_use_result(conn);
	// output table name
	cout<<"MySQL Tables in mysql database: "<<endl;
	while ((row = mysql_fetch_row(res)) != NULL)
	{
		//printf("%s %s %s %s %s\n", row[0], row[1], row[2], row[3], row[4]);
		printf("%s\n",row[0] );
		
	}
	
	// close connection
	mysql_free_result(res);
	mysql_close(conn);
	
	return 0;
}