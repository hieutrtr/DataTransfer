INCPATH1=/usr/local/include
LIB1=/usr/local/lib -lmongoclient 
LIB2=/usr/lib64 -lboost_thread-mt -lboost_filesystem -lboost_system -lboost_regex -ljson_linux-gcc-4.4.7_libmt -ldl -lcurl
LIB3=-I/usr/include/mysql -g -pipe -m64 -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -fno-strict-aliasing
LIB4=-L/usr/lib64/mysql -lmysqlclient -lz -lcrypt 
CC=g++
CFLAGS=-L$(LIB1) -L$(LIB2) $(LIB3) $(LIB4) -I$(INCPATH1)

# === Centrallize Zbx Alert === #
CENTRALIZE_ZBX_ALERT_MAIN=CentralizeZbxAlertMain.cpp
CENTRALIZE_ZBX_ALERT_FILE=CentralizeZbxAlertMain.o \
./Model/MongodbModel.o ./Model/CentralizeModel.o ./Model/CentralizeZbxAlertModel.o\
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CentrolizeMySQLController.o \
./Controller/MAAlertController.o ./Controller/ZbxAlertController.o ./Controller/UpdateItemLogController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o \
./Processor/Processor.o \
./Processor/CentralizeProcessor.o ./Processor/CentralizeZbxAlertProcessor.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o \
./Utilities/ZabbixParser.o ./Utilities/TextParser.o \
./Utilities/Thread.o ./Utilities/FileMapping.o

# === Centrallize G8 Alert === #
CENTRALIZE_G8_ALERT_MAIN=CentralizeG8AlertMain.cpp
CENTRALIZE_G8_ALERT_FILE=CentralizeG8AlertMain.o \
./Model/MongodbModel.o ./Model/CentralizeModel.o ./Model/CentralizeG8AlertModel.o\
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CentrolizeMySQLController.o \
./Controller/MAAlertController.o ./Controller/MapProductController.o ./Controller/G8AlertController.o ./Controller/AlertController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o \
./Processor/Processor.o \
./Processor/CentralizeProcessor.o ./Processor/CentralizeG8AlertProcessor.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o \
./Utilities/ZabbixParser.o ./Utilities/TextParser.o \
./Utilities/Thread.o ./Utilities/FileMapping.o

# === Centrallize DC Alert === #
CENTRALIZE_DC_ALERT_MAIN=CentralizeDCAlertMain.cpp
CENTRALIZE_DC_ALERT_FILE=CentralizeDCAlertMain.o \
./Model/MongodbModel.o ./Model/CentralizeModel.o ./Model/CentralizeDCAlertModel.o\
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CentrolizeMySQLController.o \
./Controller/MAAlertController.o ./Controller/DCAlertController.o ./Controller/AlertController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o \
./Processor/Processor.o \
./Processor/CentralizeProcessor.o ./Processor/CentralizeDCAlertProcessor.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o \
./Utilities/ZabbixParser.o ./Utilities/TextParser.o \
./Utilities/Thread.o ./Utilities/FileMapping.o

# === Centrallize SO6 Alert === #
CENTRALIZE_SO6_ALERT_MAIN=CentralizeSO6AlertMain.cpp
CENTRALIZE_SO6_ALERT_FILE=CentralizeSO6AlertMain.o \
./Model/MongodbModel.o ./Model/CentralizeModel.o ./Model/CentralizeSO6AlertModel.o\
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CentrolizeMySQLController.o \
./Controller/MAAlertController.o ./Controller/SO6AlertController.o ./Controller/MapProductController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o \
./Processor/Processor.o \
./Processor/CentralizeProcessor.o ./Processor/CentralizeSO6AlertProcessor.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o \
./Utilities/ZabbixParser.o ./Utilities/TextParser.o \
./Utilities/Thread.o ./Utilities/FileMapping.o

# === Centrallize Zbx Event === #
CENTRALIZE_ZBX_EVENT_MAIN=CentralizeZbxEventMain.cpp
CENTRALIZE_ZBX_EVENT_FILE=CentralizeZbxEventMain.o \
./Model/MongodbModel.o ./Model/CentralizeModel.o ./Model/CentralizeEventModel.o\
./Controller/MongodbController.o ./Controller/MySQLController.o ./Controller/CentrolizeMySQLController.o \
./Controller/MAAlertController.o ./Controller/EventController.o ./Controller/TriggerController.o ./Controller/ServerController.o ./Controller/ZbxAlertController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o \
./Processor/Processor.o \
./Processor/CentralizeProcessor.o ./Processor/CentralizeZbxEventProcessor.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o \
./Utilities/ZabbixParser.o ./Utilities/TextParser.o \
./Utilities/Thread.o ./Utilities/FileMapping.o

# === Update Incident Status === #
UPDATE_INC_STATUS_MAIN=UpdateAlertSttMain.cpp
UPDATE_INC_STATUS_FILE=UpdateAlertSttMain.o \
./Model/MongodbModel.o ./Model/CSAlertModel.o ./Model/JsonModel.o ./Model/AlertModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o  ./Controller/AlertController.o \
./Controller/CSAlertController.o ./Controller/IncidentFollowController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o \
./Processor/Processor.o \
./Processor/UpdateAlertSttProcessor.o ./Processor/CSUpdateAlertSttProcessor.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o ./Utilities/APIUtilities.o \
./Utilities/ZabbixParser.o ./Utilities/TextParser.o \
./Utilities/Thread.o ./Utilities/FileMapping.o

# === Trigger Log Parser === #
TRIGGER_LOG_PARSER_MAIN=TriggerLogParserMain.cpp
TRIGGER_LOG_PARSER_FILE=TriggerLogParserMain.o \
./Model/MongodbModel.o ./Model/TriggerModel.o ./Model/JsonModel.o ./Model/LogModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o  ./Controller/TriggerController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Config/ConfigMarkFile.o \
./Processor/Processor.o \
./Processor/LogParser.o ./Processor/TriggerLogParser.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o ./Utilities/APIUtilities.o \
./Utilities/ZabbixParser.o ./Utilities/TextParser.o \
./Utilities/Thread.o ./Utilities/FileMapping.o

# === Event Log Parser === #
EVENT_LOG_PARSER_MAIN=EventLogParserMain.cpp
EVENT_LOG_PARSER_FILE=EventLogParserMain.o \
./Model/MongodbModel.o ./Model/EventModel.o ./Model/JsonModel.o ./Model/LogModel.o \
./Controller/MongodbController.o ./Controller/MySQLController.o  ./Controller/EventController.o \
./Config/ConfigFile.o ./Config/ConfigReader.o ./Config/ConfigMarkFile.o \
./Processor/Processor.o \
./Processor/LogParser.o ./Processor/EventLogParser.o \
./Utilities/Utilities.o ./Utilities/DBUtilities.o ./Utilities/APIUtilities.o \
./Utilities/ZabbixParser.o ./Utilities/TextParser.o \
./Utilities/Thread.o ./Utilities/FileMapping.o

all: main file 
main: CentralizeZbxAlertMain.o UpdateAlertSttMain.o TriggerLogParserMain.o EventLogParserMain.o CentralizeZbxEventMain.o CentralizeG8AlertMain.o CentralizeDCAlertMain.o \
CentralizeSO6AlertMain.o

CentralizeZbxAlertMain.o: $(CENTRALIZE_ZBX_ALERT_MAIN)
	$(CC) -c $(CENTRALIZE_ZBX_ALERT_MAIN)
UpdateAlertSttMain.o: $(UPDATE_INC_STATUS_MAIN)
	$(CC) -c $(UPDATE_INC_STATUS_MAIN)
TriggerLogParserMain.o: $(TRIGGER_LOG_PARSER_MAIN)
	$(CC) -c $(TRIGGER_LOG_PARSER_MAIN)
EventLogParserMain.o: $(EVENT_LOG_PARSER_MAIN)
	$(CC) -c $(EVENT_LOG_PARSER_MAIN)
CentralizeZbxEventMain.o: $(CENTRALIZE_ZBX_EVENT_MAIN)
	$(CC) -c $(CENTRALIZE_ZBX_EVENT_MAIN)
CentralizeG8AlertMain.o: $(CENTRALIZE_G8_ALERT_MAIN)
	$(CC) -c $(CENTRALIZE_G8_ALERT_MAIN)
CentralizeDCAlertMain.o: $(CENTRALIZE_DC_ALERT_MAIN)
	$(CC) -c $(CENTRALIZE_DC_ALERT_MAIN)
CentralizeSO6AlertMain: $(CENTRALIZE_SO6_ALERT_MAIN)
	$(CC) -c $(CENTRALIZE_SO6_ALERT_MAIN)
	
file:
	cd Model; make
	cd Controller; make
	cd Config; make
	cd Utilities; make		
	cd Processor; make

	$(CC) $(CENTRALIZE_ZBX_ALERT_FILE) $(CFLAGS) -o ./bin/maCenZbxAlert
	$(CC) $(UPDATE_INC_STATUS_FILE) $(CFLAGS) -o ./bin/maUpdateIncStt
	$(CC) $(TRIGGER_LOG_PARSER_FILE) $(CFLAGS) -o ./bin/maTriggerParser
	$(CC) $(EVENT_LOG_PARSER_FILE) $(CFLAGS) -o ./bin/maEventParser
	$(CC) $(CENTRALIZE_ZBX_EVENT_FILE) $(CFLAGS) -o ./bin/maCenZbxEvent
	$(CC) $(CENTRALIZE_G8_ALERT_FILE) $(CFLAGS) -o ./bin/maCenG8Alert
	$(CC) $(CENTRALIZE_DC_ALERT_FILE) $(CFLAGS) -o ./bin/maCenDCAlert
	$(CC) $(CENTRALIZE_SO6_ALERT_FILE) $(CFLAGS) -o ./bin/maCenSO6Alert
	
clean:
	cd Model; make clean
	cd Controller; make clean
	cd Config; make clean
	cd Utilities; make clean
	cd Processor; make clean
	rm -rf *o
