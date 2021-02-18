// Verse class function definitions
// Computer Science, MVNU

#include "Verse.h"
#include <iostream>
#define DELIM  ".,;:'\" ?"  // characters that separate tokens
using namespace std;

Verse::Verse() {  	// Default constructor
    verseText = "Uninitialized Verse!";
    verseRef = Ref();
} 

// REQUIRED: Parse constructor - pass verse string from file
Verse::Verse(const string s) {
	// use Ref constructor to create verseRef
	// store the remainder of the string in verseText
	
	string input = s;
	
	int bookNum = atoi(GetNextToken(input, DELIM).c_str());
	int chapNum = atoi(GetNextToken(input, DELIM).c_str());
	int verseNum = atoi(GetNextToken(input, DELIM).c_str());
	
	
	//int bookNum = atoi(GetNextToken(s));
	//int chapNum = atoi(GetNextToken(s));
	//int verseNum = atoi(GetNextToken(s));
	
	Ref thisVerseRef (bookNum, chapNum, verseNum);
	
	this->verseRef = thisVerseRef;
	this->verseText = input;
}



// REQUIRED: Accessors
string Verse::getVerse() {
	return this->verseText;
}

Ref Verse::getRef() {
	return this->verseRef;
}

// display reference and verse
void Verse::display() {
    verseRef.display();
    cout << " " << verseText << endl;
 }
 
 void Verse::displayText()
 {
	 cout << verseText << endl;
 }
