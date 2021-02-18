// biblereader.cpp
// main function for Project 1

#include "Ref.h"
#include "Verse.h"
#include "Bible.h"
#include <iostream>
#include <fstream>
#include <string> 
#include <stdio.h>
#include <stdlib.h>
using namespace std;

main (int argc, char **argv) {
	// Create Bible object to process the raw text file
	Bible webBible("/home/class/csc3004/Bibles/web-complete");
	
	Verse verse;
	int b, c, v;
	int n = 1;						//number of verses to be displayed
	LookupResult result;
	cout << "Using Bible from: ";
	webBible.display();
	// Prompt for input: get reference to lookup
	// This is good for testing your classes quickly for the first milestone.
	// TODO: your final program should get input from command line arguments instead.
	//cout << "Enter 3 integers for book, chapter and verse to find: " << flush;
	//cin >> b >> c >> v;	

	if (argc < 4)
	{
		cerr << "Error: include book, chapter, and verse as arguments (example: ./biblereader 1 1 1 = Genesis:1:1)" << endl;
		exit(2);
	}
	else
	{
		b = atoi(argv[1]);
		c = atoi(argv[2]);
		v = atoi(argv[3]);
		if (argc == 5)
		{
			n = atoi(argv[4]);
		}
	}
 
	// Create a reference from the numbers
	Ref ref(b, c, v);

	
	// Use the Bible object to retrieve the verse by reference
	cout << "Looking up reference: ";
	ref.display();
	
	cout << endl;

	verse = webBible.lookup(ref, result, true);					//display the first verse
	
	//debugging code
	//cout << "first verse result status: " << result << endl;

	if (result == SUCCESS)										//if the refernce provided by the user was valid
	{
		verse.display();										//dispaly all remaining references
		n--;
	}
	else
	{
		n = 0;
	}

	while (n > 0)
	{
		verse = webBible.lookup(ref, result, false);
		verse.display();
		n--;
	}
}
