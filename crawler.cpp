#include <vector>
#include <iostream>
#include <sstream>      // std::istringstream
#include <string> 
#include <fstream>
#include <string>
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <cstdlib>



using namespace std;

vector<string> ListFolder()
{
	vector<string> listOfFiles;
	string line;
	string prefix = "data/";
	//cout<<listOfFiles.size()<<endl;
	FILE * pFile;
	//cout<<"Opening config.cfg for writing"<<endl;
	pFile = fopen ("config.cfg","w");

	if ( pFile == 0 ) {
		fprintf( stderr, "File was not created\n" );
		return listOfFiles;
	}
	//cout<<"Executing ls -l | tr -s ' ' | cut -d ' ' -f9 | tail -n +2"<<endl;
	FILE * f = popen( "ls -l ./data | tr -s ' ' | cut -d ' ' -f9 | tail -n +2", "r" );
	//system("ls -l data");
	if ( f == 0 ) {
		fprintf( stderr, "Could not execute\n" );
		return listOfFiles;
	}
		const int BUFSIZE = 1000;
		char buf[ BUFSIZE ];
		
		while( fgets( buf, BUFSIZE,  f ) ) {
			fprintf( pFile, "%s", buf  );
		}
	pclose( f );
	fclose (pFile);
	
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
	cout<< "Data from config.cfg has been read successfully"<<endl;
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
char* ConvertStrToChar(string str)
{	
	char *c_char =(char*)malloc(sizeof(char) * (str.length() + 1));
	for(unsigned int i = 0; i < str.length(); i++)
	{
		c_char[i] = str[i];
	}
	return c_char;
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
 * Function reads file and counts outgoing links
 *
 */
void PageRanker(string str)
{
	string wholeFile;
	ifstream is (ConvertStrToChar(str));

	if (is) {
	    // get length of file:
	    is.seekg (0, is.end);
	    int length = is.tellg();
	    is.seekg (0, is.beg);

	    char * buffer = new char [length];
	    is.read (buffer,length);
	    wholeFile = buffer;
	    /*
	    if (is)
	      std::cout << "all characters read successfully.";
	    else
	      std::cout << "error: only " << is.gcount() << " could be read";
		*/
    	is.close();
    	delete[] buffer;
	}

	//parsovani
	//TODO
	istringstream iss(wholeFile);
	string line;
	while(!(iss.eof()))
	{
		getline(iss,line);
		if (line.find("<a ") != std::string::npos) {
			unsigned pos = line.find("<a href");
	 		std::cout << "found!" <<pos << " "<<line<< '\n';
		}	
	}
	//vytáhnout název stránky
	//spočítat odkazy
	//nacpat do db
		// jmeno: index.html -> aaa.html, bb.html
		// pagerank: 1
		//	

  
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
   
   vector<string> listOfFiles;
   listOfFiles = ListFolder();
   if(listOfFiles.size() == 0)
   {
	cout<< "Error reading config.cfg" << endl;
   }
   PageRankerCompleter(listOfFiles);

   
  


	return 0;
  }