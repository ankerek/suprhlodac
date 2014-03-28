#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h> 

using namespace std;
//=========================================================================
vector<string> ReadFromCfg(const char* filename)
{	
	vector<string> listOfFiles;
	string line;
	ifstream myfile (filename);
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
		  listOfFiles.push_back(line);
		}
		myfile.close();
	}
	else cout << "Unable to open file";
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
char* ConverStrToChar(string str)
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
int PageRanker(string str)
{
	char *filename =(char*) malloc(sizeof(char) * (str.length() + 1));

	string line;
	ifstream myfile (filename);
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
		  LineChecker(str,line);
		}
		myfile.close();
	}
	else cout << "Unable to open file: " << str << endl;
	return 0;
}
//=========================================================================
void PageRankerCompleter(vector<string> urls)
{
	for(unsigned int i = 0; i< urls.size();i++)
	{
		PageRanker(urls[i]);
	}
}
//=========================================================================
//=========================================================================
int main(void)
{	
	vector<string> list;
	string str;
	
	cout<<"Insert name of file, where the urls are specified: ";
	cin>>str;

	char *filename =(char*) malloc(sizeof(char) * (str.length() + 1));
	filename = ConverStrToChar(str);
	
	list = ReadFromCfg(filename);
	//PrintList(list);
	PageRankerCompleter(list);

	free(filename);
	return 0;
}