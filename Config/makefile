CC=g++
ConfigFolder: ConfigReader.o ConfigFile.o ConfigHistoryFile.o ConfigUpdateFile.o ConfigMarkFile.o
ConfigReader.o: ConfigReader.cpp ConfigReader.h
	$(CC) -c ConfigReader.cpp
ConfigFile.o: ConfigFile.cpp ConfigFile.h ConfigReader.o
	$(CC) -c ConfigFile.cpp
ConfigHistoryFile.o: ConfigHistoryFile.cpp ConfigHistoryFile.h
	$(CC) -c ConfigHistoryFile.cpp	
ConfigUpdateFile.o: ConfigUpdateFile.cpp ConfigUpdateFile.h
	$(CC) -c ConfigUpdateFile.cpp
ConfigMarkFile.o: ConfigMarkFile.cpp ConfigMarkFile.h
	$(CC) -c ConfigMarkFile.cpp		
clean:
	rm -rf *o ConfigFolder
