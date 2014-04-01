#include <mysql/mysql.h>
#include <cstdio>
#include <iostream>
#include <iomanip>

using namespace std;

/*
void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  return;    
}

int main(int argc, char **argv)
{
  	MYSQL *con;
	const char *server = "webdev.fit.cvut.cz";
	const char *user = "chudoja3";
	const char *password = "81l2i7kd";  // got tot keep my data secret
	const char *database = "test";
	con = mysql_init(NULL);
	//GGG
	// connect to database

  
  if (con == NULL) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      return 1;
  }  

  	

  if (!(mysql_real_connect(con, server, user, password, database, 0, NULL, 0))) 
  {
      finish_with_error(con);
  }    
  
  if (mysql_query(con, "DROP TABLE IF EXISTS Cars")) {
      finish_with_error(con);
  }
  
  if (mysql_query(con, "CREATE TABLE Cars(Id INT, Name TEXT, Price INT)")) {      
      finish_with_error(con);
  }
  
  if (mysql_query(con, "INSERT INTO Cars VALUES(1,'Audi',52642)")) {
      finish_with_error(con);
  }
  
  if (mysql_query(con, "INSERT INTO Cars VALUES(2,'Mercedes',57127)")) {
      finish_with_error(con);
  }
  
  if (mysql_query(con, "INSERT INTO Cars VALUES(3,'Skoda',9000)")) {
      finish_with_error(con);
  }
  
  if (mysql_query(con, "INSERT INTO Cars VALUES(4,'Volvo',29000)")) {
      finish_with_error(con);
  }
  
  if (mysql_query(con, "INSERT INTO Cars VALUES(5,'Bentley',350000)")) {
      finish_with_error(con);
  }
  
  if (mysql_query(con, "INSERT INTO Cars VALUES(6,'Citroen',21000)")) {
      finish_with_error(con);
  }
  
  if (mysql_query(con, "INSERT INTO Cars VALUES(7,'Hummer',41400)")) {
      finish_with_error(con);
  }
  
  if (mysql_query(con, "INSERT INTO Cars VALUES(8,'Volkswagen',21600)")) {
      finish_with_error(con);
  }

  mysql_close(con);
  return 0;
}

*/





























  //vypis dat z DB 
int main()
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	const char *server = "webdev.fit.cvut.cz";
	const char *user = "chudoja3";
	const char *password = "81l2i7kd";  // got tot keep my data secret
	const char *database = "test";
	conn = mysql_init(NULL);
	//GGG
	// connect to database
	if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		return -1;
	}
	
	// send SQL query
	//SELECT TABLE_NAME FROM Information_Schema.Tables where Table_Type = 'BASE TABLE'
	//select * from Item
	/*
	if(mysql_query(conn, "SELECT TABLE_NAME FROM Information_Schema.Tables where Table_Type = 'BASE TABLE'"))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		return -1;
	}
	*/
	if(mysql_query(conn,"select * from SH_PAGE") != 0) // 0 pro uspech
	{
		cout<<"chyba"<<endl;
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
