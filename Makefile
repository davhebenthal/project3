# Bibleajax program
# Bob Kasper, MVNU Computer Science
# updated January 2020 to use
# c++11 compiler option, current paths on cs.mvnu.edu

# This is a Makefile for the Bible web app demo program.
# Copy this directory to a location within your home directory. 
# Change the USER name value below to your own user name.
# Then use "make" to build the server program,
# and deploy it to the live web server directory.
# To test the program, go to http://cs.mvnu.edu/class/csc3004/USER/
# and open the bibleajax.html link.

# TO DO: Must replace "username" by your username
USER= davhebenthal

# Use GNU C++ compiler with C++11 standard
CC= g++
CFLAGS= -g -std=c++11

#all: testreader
all: bibleajax3.cgi sslookupserver PutCGI PutHTML

# Ref Object
Ref.o : Ref.h Ref.cpp
	$(CC) $(CFLAGS) -c Ref.cpp

# Verse Object
Verse.o : Ref.h Verse.h Verse.cpp
	$(CC) $(CFLAGS) -c Verse.cpp

# Bible Object
Bible.o : Ref.h Verse.h Bible.h Bible.cpp
	$(CC) $(CFLAGS) -c Bible.cpp

# TO DO: For bibleajax.cgi, add dependencies to include
# compiled classes from Project 1 to be linked into the executable program
bibleajax3.cgi:	bibleajax3.o Bible.o Ref.o Verse.o fifo.o
		$(CC) $(CFLAGS) -o bibleajax3.cgi bibleajax3.o Ref.o Verse.o Bible.o fifo.o -l cgicc
		# -l option is necessary to link with cgicc library

# main program to handle AJAX/CGI requests for Bible references
bibleajax3.o:	bibleajax3.cpp
		$(CC) $(CFLAGS) -c bibleajax3.cpp

# TO DO: copy targets to build classes from Project 1:
# Bible.o, Ref.o, Verse.o

# testreader program
testreader.o : Ref.h Verse.h Bible.h
	$(CC) $(CFLAGS) -c testreader.cpp
	
#sslookupclient and sslookupserver programs
sslokupclient.o : sslookupclient.cpp fifo.h
	$(CC) $(CFLAGS) -c sslookupclient.cpp
	
sslookupserver.o : sslookupserver.cpp fifo.h Ref.h Verse.h Bible.h
	$(CC) $(CFLAGS) -c sslookupserver.cpp

sslookupclient : sslookupclient.o fifo.o
	$(CC) $(CFLAGS) -o sslookupclient sslookupclient.o fifo.o -L/usr/local/lib –lcgicc

sslookupserver : sslookupserver.o fifo.o Ref.h Verse.h Bible.h
	$(CC) $(CFLAGS) -o sslookupserver sslookupserver.o fifo.o Ref.o Verse.o Bible.o
	
#fifo code
fifo.o : fifo.cpp fifo.h
	$(CC) $(CFLAGS) -c fifo.cpp
	
	
#testreader executable
testreader: Ref.o Verse.o Bible.o testreader.o
	$(CC) $(CFLAGS) -o testreader Ref.o Verse.o Bible.o testreader.o
			
PutCGI:	bibleajax3.cgi
		chmod 755 bibleajax3.cgi
		cp bibleajax3.cgi /var/www/html/class/csc3004/$(USER)/cgi-bin

		echo "Current contents of your cgi-bin directory: "
		ls -l /var/www/html/class/csc3004/$(USER)/cgi-bin/

PutHTML:
		cp bibleajax3.html /var/www/html/class/csc3004/$(USER)

		echo "Current contents of your HTML directory: "
		ls -l /var/www/html/class/csc3004/$(USER)

clean:		
		rm *.o core bibleajax3.cgi
