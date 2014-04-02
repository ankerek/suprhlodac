#include <vector>
#include <set>
#include <iostream>
#include <sstream>
#include <string> 
#include <fstream>
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <cstdlib>

using namespace std;

#define DOMAIN "edna.cz"


string eraseS ( string &link ) {
	if ( link.back() == '/' ) link = link.substr(0, link.size()-1);

	vector<string> prefix = {"https://www.","http://www.","https://","http://"};
	for( int i =0; i < prefix.size(); i++ ) {
		if ( link.find(prefix[i]) == 0 ) {
			link.erase(0,prefix[i].size());
			break;
		}
	}
	

	return link;
}

int main() {

	string line, tag, link;
	char c, s;
	int count = 0;

	set<string> links;

	ifstream myfile("data/edna.html");

	while(getline(myfile,line)) {
		//cout << line << endl;

		istringstream iss(line);

		while(iss.good()) {
			if (iss.peek() ==  char_traits<char>::eof()) continue;
			
      		c = iss.get();

      		if( c == '<' ) {

      			c = iss.get();
      			if( c == 'a' ) {
      				
      				c = iss.get(); // vezmu mezeru

      				tag = "";

      				while( c != '>' && iss.good() ) {

      					c = iss.get();

      					if( c == 'h' ) {

	      					while( c != '=' && iss.good() ) {
	      						tag += c;
	      						c = iss.get();
	      					}
	      					
	      					if( tag == "href" ) {
	      						count++;

	      						s = iss.get();
	      						c = iss.get();

	      						while( c != '"' && iss.good() ) {	
	      							link += c;
	      							c = iss.get();
	     							     							
	      						}
	      						eraseS(link);
	      						
	      						links.insert(link);
	      						//cout << link << endl;
	      						
	      						link = "";   						
	      					}
	      					tag = "";
	      				}
      				}

      			}
      			else iss.unget();
      		}


		}

	}


	for(set<string>::const_iterator it = links.begin(); it != links.end(); it++) {
        cout << *it << endl;
    }

	cout << "Pocet odkazu: " << links.size() << endl;



	return 0;

}