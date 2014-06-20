CC=g++
MYSQLFLAGS=-I/usr/include/mysql -L/usr/lib64/mysql -lmysqlclient -lz -lcrypt -lnsl -lm -lssl -lcrypto
ProcessorFolder: Processor.o LogParser.o \
	CentralizeProcessor.o CentralizeZbxAlertProcessor.o CentralizeZbxEventProcessor.o CentralizeG8AlertProcessor.o CentralizeDCAlertProcessor.o \
	UpdateAlertSttProcessor.o CSUpdateAlertSttProcessor.o TriggerLogParser.o EventLogParser.o \
	CentralizeSO6AlertProcessor.o
	
Processor.o: Processor.cpp Processor.h
	$(CC) -c Processor.cpp $(MYSQLFLAGS)
LogParser.o: LogParser.cpp LogParser.h
	$(CC) -c LogParser.cpp
CentralizeProcessor.o: CentralizeProcessor.cpp CentralizeProcessor.h
	$(CC) -c CentralizeProcessor.cpp $(MYSQLFLAGS)
CentralizeZbxAlertProcessor.o: CentralizeZbxAlertProcessor.cpp CentralizeZbxAlertProcessor.h
	$(CC) -c CentralizeZbxAlertProcessor.cpp $(MYSQLFLAGS)
CentralizeZbxEventProcessor.o: CentralizeZbxEventProcessor.cpp CentralizeZbxEventProcessor.h
	$(CC) -c CentralizeZbxEventProcessor.cpp $(MYSQLFLAGS)
CentralizeG8AlertProcessor.o: CentralizeG8AlertProcessor.cpp CentralizeG8AlertProcessor.h
	$(CC) -c CentralizeG8AlertProcessor.cpp $(MYSQLFLAGS)
CentralizeDCAlertProcessor.o: CentralizeDCAlertProcessor.cpp CentralizeDCAlertProcessor.h
	$(CC) -c CentralizeDCAlertProcessor.cpp $(MYSQLFLAGS)
UpdateAlertSttProcessor.o: UpdateAlertSttProcessor.cpp UpdateAlertSttProcessor.h
	$(CC) -c UpdateAlertSttProcessor.cpp $(MYSQLFLAGS)
CSUpdateAlertSttProcessor.o: CSUpdateAlertSttProcessor.cpp CSUpdateAlertSttProcessor.h
	$(CC) -c CSUpdateAlertSttProcessor.cpp $(MYSQLFLAGS)
TriggerLogParser.o: TriggerLogParser.cpp TriggerLogParser.h
	$(CC) -c TriggerLogParser.cpp
EventLogParser.o: EventLogParser.cpp EventLogParser.h
	$(CC) -c EventLogParser.cpp
CentralizeSO6AlertProcessor.o: CentralizeSO6AlertProcessor.cpp CentralizeSO6AlertProcessor.h
	$(CC) -c CentralizeSO6AlertProcessor.cpp $(MYSQLFLAGS)
				
clean:
	rm -rf *o ProcessorFolder
