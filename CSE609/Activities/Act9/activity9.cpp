#include <iostream>
#include <string>

using namespace std;

int main()
{
    int vowels;
    string line;
    while ( getline(cin, line) ) {
	for( int i=0; i< line.length(); i++)
	{ 
	    char ch = line.at(i);
	    if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'y' ) {
		vowels ++;
	    }
	}
    }
    cout << "total vowels: " << vowels << endl;
}

