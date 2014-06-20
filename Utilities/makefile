CC=g++
UtilitiesFolder: Utilities.o DBUtilities.o FileMapping.o \
	Thread.o TextParser.o ZabbixParser.o APIUtilities.o
Utilities.o: Utilities.cpp Utilities.h
	$(CC) -c Utilities.cpp
DBUtilities.o: DBUtilities.cpp DBUtilities.h
	$(CC) -c DBUtilities.cpp
FileMapping.o : FileMapping.cpp FileMapping.h
	$(CC) -c FileMapping.cpp 
Thread.o: Thread.cpp Thread.h	
	$(CC) -c Thread.cpp
TextParser.o: TextParser.cpp TextParser.h	
	$(CC) -c TextParser.cpp	
ZabbixParser.o: ZabbixParser.cpp ZabbixParser.h	
	$(CC) -c ZabbixParser.cpp
APIUtilities.o: APIUtilities.cpp APIUtilities.h	
	$(CC) -c APIUtilities.cpp		
clean:
	rm -rf *o UtilitiesFolder
