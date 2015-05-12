//============================================================================
// Name        : LeGrep.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "kmp.h"

int main(int argc, char * argv[]) {

	argc=2;
	bool continuar=true;
	string phrase="";
	string search="";
	string read="";
	// Check number of user arguments.

	if(argc > 4 || argc < 2)  { // arg needs to be 2 or 3
		cerr << "Invalid command line parameters.\n"
			<<	"\nToo many arguments.  "
			<<	"\nUsage:  	//	grep word_to_find [replacement_word] directory\n";
	}

	// instantiate variables.


	// Check number of user arguments.
	if(argc == 3)  {  // no replacement

		//user_output (search only)
		cout <<"GREP - SEARCH ONLY\n";
		cout <<"------------------\n\n";
		cout <<"Search directory:\n";
		cout <<"-----------------\n";

	}
	else if(argc == 2)
	{
		//user_output (without files)
		cout <<"GREP - SEARCH\n";
		cout <<"-------------------------\n\n";
		getline(cin, search);
		getline(cin, phrase);
		if(kmp(phrase, search))
			cout << phrase << endl;
	}


	do{
		cout<< "Note: You can stop a search in progress by typing 'y' and return.\n";
		cout<<"Continue?  y/n  > ";
		getline(cin,read);
		if(read == "n")
			continuar = false;
	}
	while(continuar);

	return 0; // done
}
