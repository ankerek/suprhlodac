#include <mysql/mysql.h>
#include <cstdio>
#include <iostream>
#include <iomanip>

using namespace std;


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
	
	if (con == NULL) 
	{
	  fprintf(stderr, "%s\n", mysql_error(con));
	  return 1;
	}  
	// connect to database
	if (!(mysql_real_connect(con, server, user, password, database, 0, NULL, 0))) 
	{
	  finish_with_error(con);
	}    


	//check tables
	if (mysql_query(con, "DROP TABLE IF EXISTS SH_PAGE")) {
	  finish_with_error(con);
	}
	/*
	if (mysql_query(con, "DROP TABLE IF EXISTS SH_LINK")) {
	finish_with_error(con);
	}
	*/
	//create tables
	if (mysql_query(con, "CREATE TABLE SH_PAGE(Name TEXT, PageRank INT)")) {      
	  finish_with_error(con);
	}
	/*
	if (mysql_query(con, "CREATE TABLE SH_LINK(Id INT, Name TEXT, Price INT)")) {      
	  finish_with_error(con);
	}
	*/
  /*
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
	*/
  mysql_close(con);
  return 0;
}
