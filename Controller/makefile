CC=g++
MYSQLFLAGS=-I/usr/include/mysql -L/usr/lib64/mysql -lmysqlclient -lz -lcrypt -lnsl -lm -lssl -lcrypto
ControllerFolder: MongodbController.o MySQLController.o \
				UpdateItemLogController.o MAAlertController.o ZbxAlertController.o G8AlertController.o DCAlertController.o \
				AlertController.o CSAlertController.o IncidentFollowController.o TriggerController.o EventController.o \
				ServerController.o MapProductController.o \
				CentrolizeMySQLController.o SO6AlertController.o

MongodbController.o : MongodbController.cpp MongodbController.h
	$(CC) -c MongodbController.cpp
MySQLController.o : MySQLController.cpp MySQLController.h
	$(CC) -c MySQLController.cpp $(MYSQLFLAGS)
UpdateItemLogController.o: UpdateItemLogController.cpp UpdateItemLogController.h
	$(CC) -c UpdateItemLogController.cpp
MAAlertController.o: MAAlertController.cpp MAAlertController.h
	$(CC) -c MAAlertController.cpp
ZbxAlertController.o: ZbxAlertController.cpp ZbxAlertController.h
	$(CC) -c ZbxAlertController.cpp
G8AlertController.o: G8AlertController.cpp G8AlertController.h
	$(CC) -c G8AlertController.cpp
DCAlertController.o: DCAlertController.cpp DCAlertController.h
	$(CC) -c DCAlertController.cpp
AlertController.o: AlertController.cpp AlertController.h
	$(CC) -c AlertController.cpp
CSAlertController.o: CSAlertController.cpp CSAlertController.h
	$(CC) -c CSAlertController.cpp
IncidentFollowController.o: IncidentFollowController.cpp IncidentFollowController.h
	$(CC) -c IncidentFollowController.cpp $(MYSQLFLAGS)
TriggerController.o: TriggerController.cpp TriggerController.h
	$(CC) -c TriggerController.cpp
EventController.o: EventController.cpp EventController.h
	$(CC) -c EventController.cpp
ServerController.o: ServerController.cpp ServerController.h
	$(CC) -c ServerController.cpp
MapProductController.o: MapProductController.cpp MapProductController.h
	$(CC) -c MapProductController.cpp
CentrolizeMySQLController.o: CentrolizeMySQLController.cpp CentrolizeMySQLController.h
	$(CC) -c CentrolizeMySQLController.cpp $(MYSQLFLAGS)
SO6AlertController.o: SO6AlertController.cpp SO6AlertController.h
	$(CC) -c SO6AlertController.cpp $(MYSQLFLAGS)
clean:
	rm -rf *o ControllerFolder
