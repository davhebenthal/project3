/***************************************************************************
 * sslookupserver.cpp  -  Program to serve Shakespeare search results
 *
 * copyright : (C) 2009 by Jim Skon
 ***************************************************************************/
 
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "fifo.h"
#include "Ref.h"
#include "Verse.h"
#include "Bible.h"
using namespace std;

string receive_pipe = "ssrequest";
string send_pipe = "ssreply";

string convertInt(int number)
{
  stringstream ss;//create a stringstream
  ss << number;//add number to the stream
  return ss.str();//return a string with the contents of the stream
}

/* Server main line,create name MAP, wait for and serve requests */
int main() 
{
	/* create Bible object, build map*/
	Bible webBible("/home/class/csc3004/Bibles/web-complete");
	
	/* Create the communication fifos */
	Fifo recfifo(receive_pipe);
	Fifo sendfifo(send_pipe);

	recfifo.openread(); // only open once
  
	while (1) // "infinite loop" for server: repeat each time a request is received
	{ 

		/* Get a message from a client */
		string inputString = recfifo.recv();	//inputString should be "bookNum:chapterNum:verseNum:numOfVerses\n"
		
		/* Split the message into parts*/
		string strbook = GetNextToken(inputString,":");
		int bookNum = atoi(strbook.c_str());
		// Get the chapter number
		string strchap = GetNextToken(inputString,":");
		int chapterNum = atoi(strchap.c_str());
		// Get the verse number
		string strverse = GetNextToken(inputString,":");
		int verseNum = atoi(strverse.c_str());
		// Get the number of verses
		string strnumverses = GetNextToken(inputString,"\n");
		int numOfVerses = atoi(strnumverses.c_str());

		LookupResult result;
		Verse lookupVerse;
	
		cout << "Looking up ref for: " << bookNum << " " << chapterNum << " " << verseNum << endl;
		Ref ref(bookNum, chapterNum, verseNum);
		bool firstVerse = true;
   
		lookupVerse = webBible.lookup(ref, result, firstVerse);

		/* SEND BACK THE RESULTS
		* Finally we send the result back to the client on the standard output stream
		* in HTML text format.
		* This string will be inserted as is inside a container on the web page, 
		* so we must include HTML formatting commands to make things look presentable!
		*/
		
		string outputString;
		
		if (result == SUCCESS) 
		{
			//cout << "Search Type: <b>" << **st << "</b>" << "</br>";							//debugging code
			//cout << "Your result: " << **book << " " << **chapter << ":" << **verse << " ";	//debugging code
			outputString = to_string(result) + "\n";
			outputString = outputString + lookupVerse.giveString();
			numOfVerses--;
			firstVerse = false;
			
			/*if there are still more verses to display, then move to the next verse unless the end of the Bible is reached*/
			while (numOfVerses > 0 && result == SUCCESS)
			{
				cout << "</br>"; 
				cout << " ";
				ref = webBible.next(ref, result);
				lookupVerse = webBible.lookup(ref, result, firstVerse);
				
				/*result for all verses after the first will only ever != SUCCESS if the end of the Bible has been reached*/
				if (result == SUCCESS)									
				{
					//outputRef.display();
					//cout << " " << endl;
					//lookupVerse.displayText();
					outputString = outputString + lookupVerse.giveString();
					numOfVerses--;
				}
			}
		}
		else
		{
			outputString = to_string(result) + "\n";
		}
	
		/*send ouputString, which should consist of "result\n" once, followed by "bookNumber:chapterNumber:verseNumber:verse text\n" for as many verses as are requested*/
		
		cout << "sending " << outputString;
		
		sendfifo.openwrite();

		sendfifo.send(outputString);
		
		while (numOfVerses > 0)
		{
			sendfifo.send(outputString);
			numOfVerses--;
		}

		sendfifo.fifoclose();
	}
	
}
