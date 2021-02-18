// Bible class function definitions
// Computer Science, MVNU

#include "Ref.h"
#include "Verse.h"
#include "Bible.h" 
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

Bible::Bible() { // Default constructor
	infile = "/home/class/csc3004/Bibles/web-complete";
}

// Constructor – pass bible filename
Bible::Bible(const string s) { infile = s; }

// REQUIRED: lookup finds a given verse in this Bible
const Verse Bible::lookup(Ref ref, Ref &outputRef, LookupResult& status, bool firstVerse) { 
    // TODO: scan the file to retrieve the line with ref ...
	
	
	string verseText;
	bool searchDone = false;
	bool verseFound = false;
	Verse currentVerse;
	
	if (instream.is_open() == false)
	{
		instream.open(infile.c_str(), ios::in);							//open the file contained in Bible.infile
		instream.unsetf(ios::skipws);
	}
	
	if (!instream) {
	cerr << "Error - can't open input file: " << infile << endl;
	exit(2);
	}
	
	//debugging code:
	//cout << "lookup function checking verse " << ref.getBook() << " " << ref.getChap() << " " << ref.getVerse() << endl;
	//cin.ignore();
	
	if (firstVerse == true)												//if this is the first verse to be displayed, it is necessary to check whether the reference given by the user for that verse is valid
	{
		if (ref.getBook() < 1 || ref.getBook() > 66)					//if the book number is not valid (1-66), don't bother searching
		{
			status = NO_BOOK;
			searchDone = true;
			cout << this->error(status);
		}
		
		if (ref.getBook() == 66 && ref.getChap() == 22 && ref.getVerse() > 21)	//the last verse in the Bible is Revlation 22:21, if a higher verse than this is called for then return an error
		{
			status = NO_VERSE;
			searchDone = true;
			cout << this->error(status);
		}
	
		status = OTHER;
	
		while (searchDone == false)										//while we still haven't found the appropriate verse
		{
			getline(instream, verseText);								//read the next line of text in the Bible object (starting with the first line in the file)
		
			//cout<< "get line " << verseText << endl;
	
			currentVerse = Verse(verseText);							//create new verse based on that line
		
			//debugging code:
			//cout << "verse scanned in by lookup function: " << currentVerse.getRef().getBook() << " " << currentVerse.getRef().getChap() << " " << currentVerse.getRef().getVerse() << endl;
			//cin.ignore();
	
			if(currentVerse.getRef() == ref)							//if this is the verse we're looking for (checked by ref), end the loop, if not, then loop again (check the next verse)
			{
				searchDone = true;
				verseFound = true;
				status = SUCCESS;
			}
			else if(ref.getBook() < currentVerse.getRef().getBook())	//if this funciton has scanned through to a higher book number, then that means the specified chapter must not exist
			{
				searchDone = true;
				status = NO_CHAPTER;
				cout << this->error(status);
			}
			else if(ref.getChap() < currentVerse.getRef().getChap() && ref.getBook() <= currentVerse.getRef().getBook())	//if this function has scanned through to a higher book and chapter number, the specified verse must not exist
			{
				searchDone = true;
				status = NO_VERSE;
				cout << this->error(status);
			}
			else if (instream.eof() == true)
			{
				status = NO_VERSE;
				cout << this->error(status);
			}
		}
	}
	else																//if the first verse has been successfully found, then simply display the next one
	{
		getline(instream, verseText);
		
		if( instream.eof() == false)
		{
			currentVerse = Verse(verseText);
			outputRef = currentVerse.getRef();							//set outputRef equal to the reference of the verse being returned so that it can be displayed
		}
		else
		{
			status = NO_VERSE;
			cout << this->error(status);
		}
	}
	return(currentVerse);
}

// REQUIRED: Return the reference after the given ref
Ref Bible::next( Ref ref, LookupResult& status) 
{
	//debugging code:
	//cout << "running next ref function" << endl;
	//cout << "next ref function received " << ref.getBook() << " " << ref.getChap() << " " << ref.getVerse() << endl;
	if (status == NO_VERSE)
	{
		Ref newRef(ref.getBook(), ref.getChap() + 1, 1);
		return newRef;
	}
	else if (status == NO_CHAPTER)
	{
		Ref newRef(ref.getBook() + 1, 1, 1);
		return newRef;
	}
	else if (status == NO_BOOK)
	{
		cerr << "Error: end of Bible reached." << endl;
		exit (2);
	}
	else
	{
		//debugging code
		//cout << "next ref function received OTHER or SUCCESS code, adding 1 to verse value" << endl;
		Ref newRef(ref.getBook(), ref.getChap(), ref.getVerse() +1);
		//debugging code
		//cout << "next ref function returning " << newRef.getBook() << " " << newRef.getChap() << " " << newRef.getVerse() << endl;
		return newRef;
	}
};

// OPTIONAL: Return the reference before the given ref
const Ref prev(const Ref ref, LookupResult& status) {};

// Return an error message string to describe status
const string Bible::error(LookupResult status) {
	if (status == NO_BOOK)
	{
		return "<b>Error</b>: Book not found.\n";
	}
	else if (status == NO_CHAPTER)
	{
		return "<b>Error</b>: Chapter not found\n";
	}
	else if (status == NO_VERSE)
	{
		return "<b>Error</b>: Verse not found\n";
	}
	else
	{
		return "<b>Error</b>: Unknown error\n";
	}
};

void Bible::display() {
	cout << "Bible file: " << infile << endl;
}
