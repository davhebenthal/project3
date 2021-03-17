/* Demo server program for Bible lookup using AJAX/CGI interface
 * By James Skon, Febrary 10, 2011
 * updated by Bob Kasper, January 2020
 * Mount Vernon Nazarene University
 * 
 * This sample program works using the cgicc AJAX library to
 * allow live communication between a web page and a program running on the
 * same server that hosts the web server.
 *
 * This program is run by a request from the associated html web document.
 * A Javascript client function invokes an AJAX request,
 * passing the input form data as the standard input string.
 *
 * The cgi.getElement function parses the input string, searching for the matching 
 * field name, and returing a "form_iterator" oject, which contains the actual
 * string the user entered into the corresponding field. The actual values can be
 * accessed by dereferencing the form iterator twice, e.g. **verse
 *     refers to the actual string entered in the form's "verse" field.
 */


#include "Ref.h"
#include "Verse.h"
#include "Bible.h"
#include <iostream>
#include <fstream>
#include <string> 
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sstream>
#include <map>
#include <vector>
#include "fifo.h"
#define logging
#define LOG_FILENAME "/tmp/davhebenthal-bibleajax3.log"
#include "logfile.h"
using namespace std;

/* Required libraries for AJAX to function */
#include "/home/class/csc3004/cgicc/Cgicc.h"
#include "/home/class/csc3004/cgicc/HTTPHTMLHeader.h"
#include "/home/class/csc3004/cgicc/HTMLClasses.h"
using namespace cgicc;

int main() {
  cout << "Content-Type: text/plain\n\n";

  #ifdef logging 
  logFile.open(LOG_FILENAME, ios::out); 
  #endif

  /* A CGI program must send a response header with content type
   * back to the web client before any other output.
   * For an AJAX request, our response is not a complete HTML document,
   * so the response type is just plain text to insert into the web page.
   */
  
  Cgicc cgi;  // create object used to access CGI request data

  // GET THE INPUT DATA
  // browser sends us a string of field name/value pairs from HTML form
  // retrieve the value for each appropriate field name
  form_iterator st = cgi.getElement("search_type");
  form_iterator book = cgi.getElement("book");
  form_iterator chapter = cgi.getElement("chapter");
  form_iterator verse = cgi.getElement("verse");
  form_iterator nv = cgi.getElement("num_verse");

  int bookNum;
  int chapterNum;
  int verseNum;
  int numOfVerses;

  // Convert and check input data
  bool validInput = false;
  if (chapter != cgi.getElements().end()) {
	 chapterNum = chapter->getIntegerValue();
	 if (chapterNum > 150) {
		 cout << "<p>The chapter number (" << chapterNum << ") is too high.</p>" << endl;
	 }
	 else if (chapterNum <= 0) {
		 cout << "<p>The chapter must be a positive number.</p>" << endl;
	 }
	 else
		 validInput = true;
  }
  
  /* TO DO: OTHER INPUT VALUE CHECKS ARE NEEDED ... but that's up to you! */
	
  if (book != cgi.getElements().end() && validInput == true) {
	 bookNum = book->getIntegerValue();
	 if (bookNum > 66) {
		 cout << "<p>The book number (" << bookNum << ") is too high.</p>" << endl;
		 validInput = false;
	 }
	 else if (bookNum <= 0) {
		 cout << "<p>The book must be a positive number.</p>" << endl;
		 validInput = false;
	 }
	 else
		 validInput = true;
  }
  
  if (verse != cgi.getElements().end() && validInput == true) {
	 verseNum = verse->getIntegerValue();
	 if (verseNum > 176) {
		 cout << "<p>The verse number (" << verseNum << ") is too high.</p>" << endl;
		 validInput = false;
	 }
	 else if (verseNum <= 0) {
		 cout << "<p>The verse must be a positive number.</p>" << endl;
		 validInput = false;
	 }
	 else
		 validInput = true;
  }
	
  if (verse != cgi.getElements().end() && validInput == true) {
	 numOfVerses = nv->getIntegerValue();
     if (numOfVerses <= 0) {
		 cout << "<p>The number of verses must be a positive number.</p>" << endl;
		 validInput = false;
	 }
	 else
		 validInput = true;
  }

  log("Input received from user: " + to_string(bookNum) + " " + to_string(chapterNum) + " " + to_string(verseNum) + "\n");

  if (validInput == true)
  {
	//send a string in the format "bookNum:chapterNum:verseNum:numOfVerses\n"
  
	string searchString;
  
	searchString = to_string(bookNum);
	searchString = searchString + ":";
	searchString = searchString + to_string(chapterNum);
	searchString = searchString + ":";
	searchString = searchString + to_string(verseNum);
	searchString = searchString + ":";
	searchString = searchString + to_string(numOfVerses);
	searchString = searchString + "\n";
	
	log("assembled string to be sent: " + searchString);
  
	string receive_pipe = "ssreply";
	string send_pipe = "ssrequest";
  
	Fifo recfifo(receive_pipe);
	Fifo sendfifo(send_pipe);
  
	sendfifo.openwrite();
	
	log("sending pipe " + send_pipe + " open" + "\n");
	
	sendfifo.send(searchString);
  
    log("searchString sent\n");
  
	recfifo.openread();
	
	log("receiving pipe " + receive_pipe + " open" + "\n");
	
	//receive the resultStatus
	string outputString = recfifo.recv();
	
	//recfifo.recv stops at newline characters, so it needs to be run once to receive every requested verse
	int n = numOfVerses;
	while (n > 0)
	{
		outputString = outputString + "\n" + recfifo.recv();
		n--;
	}
	
	log("outputString received: " + outputString + "\n");
  
	//should receive a string consisting of "result\n" once, followed by "bookNumber:chapterNumber:verseNumber:verse text\n" for as many verses as are requested*/

	//first check the result
	string strResult;
	int outputResult;
  
	strResult = GetNextToken(outputString,"\n");
	outputResult = atoi(strResult.c_str());
	
	log("first section of output string (should contain an integer indicating the result status): " + strResult + "\n");
  
	//if the result is good, then split and output the rest of the string
	if (outputResult == 0)
	{
  
		string strBook;
		int outputBook;
		string strChapter;
		int outputChapter;
		string strVerse;
		int outputVerse;
		string verseText;
		
		log("outputting verse to the client.\n");
  
		while(numOfVerses > 0)
		{
				/* Split the message into parts*/
				strBook = GetNextToken(outputString,":");
				outputBook = atoi(strBook.c_str());
				// Get the chapter number
				strChapter = GetNextToken(outputString,":");
				outputChapter = atoi(strChapter.c_str());
				// Get the verse number
				strVerse = GetNextToken(outputString,":");
				outputVerse = atoi(strVerse.c_str());
				// Get the verse text
				verseText = GetNextToken(outputString,"\n");
				
				log("verse reference being output: " + to_string(outputBook) + ":" + to_string(outputChapter) + ":" + to_string(outputVerse) + "\n");
				log("verse text being output: " + verseText + "\n");
		
				Ref outputRef(outputBook, outputChapter, outputVerse);
				outputRef.display();
				cout << " " << verseText << endl;
				
				numOfVerses--;
		}
	}
	else
	{
		//otherwise output the error
		
		log("Error status. outputting error message to the client.\n");
		
		switch (outputResult)
		{
			case 1 :
				cout << "Error: book not found";
				break;
			case 2 :
				cout << "Error: chapter not found";
				break;
			case 3 :
				cout << "Error: verse not found";
				break;
		}
	}
  
	recfifo.fifoclose();
	sendfifo.fifoclose();
  }
  return 0;
}
