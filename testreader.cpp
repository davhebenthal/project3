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
	int b, c, v;
	LookupResult result;
	
	cout << "Using Bible from: ";
	webBible.display();
	
	cout << "Enter 3 integers for book, chapter and verse to find: " << flush;
	cin >> b >> c >> v;	
	
	Ref ref(b, c, v);
	
	Ref notUsed(1, 1, 1);
	
	cout << "Looking up reference: ";
	ref.display();
	cout << endl;
	
	verse = webBible.lookup(ref, notUsed, result, true);
	
	cout << "Result status: " << result << endl;
	
	if (result == SUCCESS)
	{
		verse.display();
	}
	
	cout << endl;
}