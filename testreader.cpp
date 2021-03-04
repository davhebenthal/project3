#include "Ref.h"
#include "Verse.h"
#include "Bible.h"
#include <iostream>
#include <fstream>
#include <string> 
#include <stdio.h>
#include <stdlib.h>
using namespace std;

main (int argc, char **argv)
{
	Bible webBible("/home/class/csc3004/Bibles/web-complete");
	
	Verse verse;
	int b, c, v, n = 1;
	LookupResult result;
	
	cout << "Using Bible from: ";
	webBible.display();
	
	cout << "Enter 3 integers for book, chapter and verse to find: " << flush;
	cin >> b >> c >> v;	
	
	cout << "Enter the number of verses to look up: " << flush;
	cin >> n;
	
	Ref ref(b, c, v);
	
	cout << "Looking up reference: ";
	ref.display();
	cout << " and the following " << n << " verses.";
	cout << endl;
	
	verse = webBible.lookup(ref, result, true);
	
	cout << "Result status: " << result << endl;
	
	if (result == SUCCESS)
	{	
		verse.display();
		n--;
		
		while ( n > 0)
		{
			ref = webBible.next(ref, result);
			verse = webBible.lookup(ref, result, false);
			
			if(result == SUCCESS)
			{
				
				verse.display();
				n--;
			}
		}
	}
	
	cout << endl;
}