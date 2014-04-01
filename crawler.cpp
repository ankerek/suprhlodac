#include <vector>
#include <iostream>
#include <sstream>      // std::istringstream
#include <string> 
#include <fstream>
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <mysql/mysql.h>


using namespace std;

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  return;    
}

void createConfig()
{
	
	//cout<<listOfFiles.size()<<endl;
	
	FILE * pFile;
	//cout<<"Opening config.cfg for writing"<<endl;
	pFile = fopen ("config.cfg","w");

	if ( pFile == 0 ) {
		fprintf( stderr, "File was not created\n" );
		return;
	}
	//cout<<"Executing ls -l | tr -s ' ' | cut -d ' ' -f9 | tail -n +2"<<endl;
	
	//system("ls -l ./data | tr -s ' ' | cut -d ' ' -f9 | tail -n +2 > config.cfg");
	
	FILE * f = popen( "ls -l ./data | tr -s ' ' | cut -d ' ' -f9 | tail -n +2", "r" );
	//system("ls -l data");
	if ( f == 0 ) {
		fprintf( stderr, "Could not execute\n" );
		return;
	}
		const int BUFSIZE = 1000;
		char buf[ BUFSIZE ];
		
		while( fgets( buf, BUFSIZE,  f ) ) {
			fprintf( pFile, "%s", buf  );
		}
	pclose( f );

	fclose (pFile);

}
vector<string> getListOfFiles()
{
	vector<string> listOfFiles;
	string prefix = "data/";
	string line;
	ifstream myfile ("config.cfg");

	if (myfile.is_open())
	{	
		
		while ( getline (myfile,line) )
		{
			line = prefix + line;
		  	listOfFiles.push_back(line);
		}
		myfile.close();
	}
	else cout << "Unable to open file";
	cout<< "Data from config.cfg have been read successfully"<<endl;
	return listOfFiles;
}
//=========================================================================
void PrintList(vector<string> list)
{
	for(unsigned int i = 0; i< list.size(); i++)
	{
		cout<<list[i]<<endl;
	}
}

//=========================================================================
int LineChecker(string check_str, string line)
{
	if (line.find(check_str) != std::string::npos) {
    std::cout << "found!" << '\n';
	}
}
//=========================================================================
/**
 * The most important function. Function reads file, counts outgoing links and pushes page name and pagerank to database
 * @param str is the name of the file
 */
void PageRanker(string str)
{
	string wholeFile;
	
	ifstream is (str.c_str());
	if (is) {
	    // get length of file:
	    is.seekg (0, is.end);
	    int length = is.tellg();
	    is.seekg (0, is.beg);

	    char * buffer = new char [length];
	    is.read (buffer,length);
	  	wholeFile = buffer;

	    if (is){}
	      //std::cout << "all characters read successfully."
	    else
	      std::cout << "error: only " << is.gcount() << " could be read";
		
    	is.close();
    	delete[] buffer;
	}
	is.clear();
	string pagename = str.substr(5);

	//parsovani + pocitani pageranku
	//TODO
	int pagerank = 0;
	istringstream iss(wholeFile);
	string line;
	while(!(iss.eof()))
	{
		getline(iss,line);
		//cout<<line<<endl;
		
		unsigned pos = line.find("<a href");
		if ( pos != std::string::npos) {
	 		//std::cout << "found! " <<pos << " "<<line<<endl;
		}	
		
	}
	
	//vytáhnout název stránky
	//spočítat odkazy
	//nacpat do db
		// jmeno: index.html -> aaa.html, bb.html
		// pagerank: 1
		//

	//inicializace databáze
	MYSQL *con;
	const char *server = "webdev.fit.cvut.cz";
	const char *user = "chudoja3";
	const char *password = "81l2i7kd";  
	const char *database = "test";
	con = mysql_init(NULL);
	
	if (con == NULL) 
	{
	  fprintf(stderr, "%s\n", mysql_error(con));
	  return ;
	}  
	// connect to database
	if (!(mysql_real_connect(con, server, user, password, database, 0, NULL, 0))) 
	{
	  finish_with_error(con);
	}    
	//insert webpages
	string pagerank_str = to_string(pagerank);
	string name = "'" + pagename + "'";
	string command = "INSERT INTO SH_PAGE VALUES(" + name + ","+ pagerank_str +")";
	//cout<<command;
	
	if (mysql_query(con, command.c_str())) {
      finish_with_error(con);
  	}
	
	//cout<<"Crawling done: "<<str<<endl;
  
}
//=========================================================================
void PageRankerCompleter(vector<string> urls)
{
	
	for(unsigned int i = 0; i< urls.size();i++)
	{
		PageRanker(urls[i]);
		//cout<<urls[i]<<endl;
	}
	
	
}
//=========================================================================
//=========================================================================

int main() {
   createConfig();
   vector<string> listOfFiles;
   listOfFiles = getListOfFiles();
   if(listOfFiles.size() == 0)
   {
	cout<< "Error reading config.cfg" << endl;
   }
   PageRankerCompleter(listOfFiles);
   //PrintList(listOfFiles);
   	
 


	return 0;
  }