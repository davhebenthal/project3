// Ref class function definitions
// Computer Science, MVNU

#include "Ref.h"
#include <iostream>
#include <string>
#define DELIM  ".,;:'\" ?"  // characters that separate tokens
using namespace std;

// GetNextToken - general routine for getting next token from a string
// Parameters
//    str - string to search. search is destructive, i.e., token is removed.
//    delimiters - string, a list of characters to use a delimiters between tokens
// Returns: string token (removed from str)



string GetNextToken(string& str, const string& delimiters = " ") {
  // Skip delimiters at beginning                                          
  string::size_type startPos = str.find_first_not_of(delimiters, 0);
  // Find position of delimiter at end of token                                           
  string::size_type endPos = str.find_first_of(delimiters, startPos);

  // Found a token, remove it from string, and return it                       
  string next = str.substr(startPos, endPos - startPos);
  string rest = str.substr(endPos - startPos + 1, string::npos);
  str = rest;
  return(next);
}

// Ref member functions

Ref::Ref() {book = 0; chap = 0; verse = 0;}  	// Default constructor

Ref::Ref(const string s) { // Parse constructor - receives a line "34:5:7 text"
    string rtext = s; // make local copy of string to avoid modifying parameter
    // parse the reference - notice, currently there is no error checking!
    // Get book number
    string strbook = GetNextToken(rtext,":");
    book = atoi(strbook.c_str());
    // Get the chapter number
    string strchap = GetNextToken(rtext,":");
    chap = atoi(strchap.c_str());
    // Get the verse number
    string strverse = GetNextToken(rtext," ");
    verse = atoi(strverse.c_str());
}

Ref::Ref(const int b, const int c, const int v) { 	// Construct Ref from three integers
	book = b;
	chap = c;
	verse = v;
}

// Accessors
int Ref::getBook() {return book;}	 // Access book number
int Ref::getChap() {return chap;}	 // Access chapter number
int Ref::getVerse() {return verse;}; // Access verse number

// TO DO: implement comparison functions
// REQUIRED: == comparison
bool Ref::operator==(const Ref r) 
{
	bool same = true;
	   
	if(this->book != r.book)
	{
	same = false;
	}
	   
	if(this->chap != r.chap)
	{
	same = false;
	}
	   
	if(this->verse != r.verse)
	{
	   same = false;
	}
	   
	return same;
}

// OPTIONAL: define < and > comparisons

bool Ref::operator>(const Ref r)
{
	bool greaterThan;
	
	if(this->book > r.book)
	{
		greaterThan = true;
	}
	else if (this->book < r.book)
	{
		greaterThan = false;
	}
	else if (this->book == r.book)
	{
		if(this->chap > r.chap)
		{
			greaterThan = true;
		}
		else if(this->chap < r.chap)
		{
			greaterThan = false;
		}
		else if (this->chap == r.chap)
		{
			if(this->verse > r.verse)
			{
				greaterThan = true;
			}
			else if (this->verse < r.verse)
			{
				greaterThan = false;
			}
			else if (this->verse == r.verse)
			{
				greaterThan = false;
			}
		}
	}
	
	return greaterThan;
}

bool Ref::operator<(const Ref r)
{
	bool lessThan;
	
	if(this->book < r.book)
	{
		lessThan = true;
	}
	else if (this->book > r.book)
	{
		lessThan = false;
	}
	else if (this->book == r.book)
	{
		if(this->chap < r.chap)
		{
			lessThan = true;
		}
		else if(this->chap > r.chap)
		{
			lessThan = false;
		}
		else if (this->chap == r.chap)
		{
			if(this->verse < r.verse)
			{
				lessThan = true;
			}
			else if (this->verse > r.verse)
			{
				lessThan = false;
			}
			else if (this->verse == r.verse)
			{
				lessThan = false;
			}
		}
	}
	
	return lessThan;
}

// TO DO: modify display function to show book name instead of book number
void Ref::display() { 	// Display Reference

bookNames[0] = "Error";
bookNames[1] = "Genesis";
bookNames[2] = "Exodus";
bookNames[3] = "Leviticus";
bookNames[4] = "Numbers";
bookNames[5] = "Deutoronomy";
bookNames[6] = "Joshua";
bookNames[7] = "Judges";
bookNames[8] = "Ruth";
bookNames[9] = "1 Samuel";
bookNames[10] = "2 Samuel";
bookNames[11] = "1 Kings";
bookNames[12] = "2 Kings";
bookNames[13] = "1 Chronicles";
bookNames[14] = "2 Chronicles";
bookNames[15] = "Ezra";
bookNames[16] = "Nehemiah";
bookNames[17] = "Esther";
bookNames[18] = "Job";
bookNames[19] = "Psalms";
bookNames[20] = "Proverbs";
bookNames[21] = "Ecclesiastes";
bookNames[22] = "Song of Solomon";
bookNames[23] = "Isaiah";
bookNames[24] = "Jeremiah";
bookNames[25] = "Lamentations";
bookNames[26] = "Ezekiel";
bookNames[27] = "Daniel";
bookNames[28] = "Hosea";
bookNames[29] = "Joel";
bookNames[30] = "Amos";
bookNames[31] = "Obadiah";
bookNames[32] = "Jonah";
bookNames[33] = "Micah";
bookNames[34] = "Nahum";
bookNames[35] = "Habakkuk";
bookNames[36] = "Zephaniah";
bookNames[37] = "Haggai";
bookNames[38] = "Zecariah";
bookNames[39] = "Malachi";
bookNames[39] = "Matthew";
bookNames[41] = "Mark";
bookNames[42] = "Luke";
bookNames[43] = "John";
bookNames[44] = "Acts";
bookNames[45] = "Romans";
bookNames[46] = "1 Corinthians";
bookNames[47] = "2 Corinthians";
bookNames[48] = "Galatians";
bookNames[49] = "Ephesians";
bookNames[50] = "Phillipians";
bookNames[51] = "Colossians";
bookNames[52] = "1 Thessalonians";
bookNames[53] = "2 Thessalonians";
bookNames[54] = "1 Timothy";
bookNames[55] = "2 Timothy";
bookNames[56] = "Titius";
bookNames[57] = "Philemon";
bookNames[58] = "Hebrews";
bookNames[59] = "James";
bookNames[60] = "1 Peter";
bookNames[61] = "2 Peter";
bookNames[62] = "1 John";
bookNames[63] = "2 John";
bookNames[64] = "3 John";
bookNames[65] = "Jude";
bookNames[66] = "Revelations";
     cout << "<b>" << bookNames[book] << ":" << chap << ":" << verse << "</b>";
}
