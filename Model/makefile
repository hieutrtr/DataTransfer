CC=g++
ModelFolder: MongodbModel.o LogModel.o \
			UpdateItemLogModel.o CentralizeModel.o CentralizeZbxAlertModel.o CentralizeEventModel.o CentralizeG8AlertModel.o CentralizeDCAlertModel.o \
			JsonModel.o AlertModel.o CSAlertModel.o TriggerModel.o EventModel.o CentralizeSO6AlertModel.o
			
MongodbModel.o : MongodbModel.cpp MongodbModel.h
	$(CC) -c MongodbModel.cpp 
LogModel.o : LogModel.cpp LogModel.h
	$(CC) -c LogModel.cpp
UpdateItemLogModel.o : UpdateItemLogModel.cpp UpdateItemLogModel.h
	$(CC) -c UpdateItemLogModel.cpp
CentralizeModel.o : CentralizeModel.cpp CentralizeModel.h
	$(CC) -c CentralizeModel.cpp
CentralizeZbxAlertModel.o : CentralizeZbxAlertModel.cpp CentralizeZbxAlertModel.h
	$(CC) -c CentralizeZbxAlertModel.cpp
CentralizeEventModel.o : CentralizeEventModel.cpp CentralizeEventModel.h
	$(CC) -c CentralizeEventModel.cpp
CentralizeG8AlertModel.o : CentralizeG8AlertModel.cpp CentralizeG8AlertModel.h
	$(CC) -c CentralizeG8AlertModel.cpp
CentralizeDCAlertModel.o : CentralizeDCAlertModel.cpp CentralizeDCAlertModel.h
	$(CC) -c CentralizeDCAlertModel.cpp
JsonModel.o : JsonModel.cpp JsonModel.h
	$(CC) -c JsonModel.cpp
AlertModel.o : AlertModel.cpp AlertModel.h
	$(CC) -c AlertModel.cpp
CSAlertModel.o : CSAlertModel.cpp CSAlertModel.h
	$(CC) -c CSAlertModel.cpp
TriggerModel.o : TriggerModel.cpp TriggerModel.h
	$(CC) -c TriggerModel.cpp
EventModel.o : EventModel.cpp EventModel.h
	$(CC) -c EventModel.cpp
CentralizeSO6AlertModel.o : CentralizeSO6AlertModel.cpp CentralizeSO6AlertModel.h
	$(CC) -c CentralizeSO6AlertModel.cpp

clean:
	rm -rf *o ModelFolder
