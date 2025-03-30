/** Muhammet Sait Bozdemir -- 2584738
I read and accept the submission rules and the extra rules specified in each
question. This is my own work that is done by myself only**/

#include "University.h"

University::University() {
    uniName = new char [strlen("Undefined")+1];
    strcpy(uniName,"Undefined");
    buildingNum=0;
}
University::University(char *name) {
    this->uniName = new char [strlen("Undefined")+1];
    strcpy(uniName,name);
    buildingNum=0;
}

char *University::getUniName() const {
    return uniName;
}

void University::setUniName(char *uniName) {
    this->uniName = uniName;
}

int University::getBuildingNum() const {
    return buildingNum;
}

//in order to reach addRoom function of building in the main, I add extra addRoom function to University.
void University::addRoom(int number,char* name,int roomType,int floor,int cap,int offType,int people) {
    buildinglist[number]->addRoom(name,roomType,floor,cap,offType,people);
}

void University::addBuilding(char * name, int size) {
    buildinglist[buildingNum++]=new Building(name,size);
}
void University::printBuildings() {
    cout << "Buildings in " << uniName << " university:" << endl;
    for (int i = 0; i < buildingNum; ++i) {
        cout << "[" << i+1 << "] ";
        buildinglist[i]->printBuilding();
    }
}
void University::printRooms() {
    cout << "Rooms in " << uniName << " university:" << endl;
    for (int i = 0; i < buildingNum; ++i) {
        buildinglist[i]->printRooms();
    }
}
void University::printRoomsByType(int type) {
    if(type==1)
        cout << "Classrooms in "<< uniName <<" university:" << endl;
    else
        cout << "Offices in "<< uniName <<" university:" << endl;
    for (int i = 0; i < buildingNum; ++i) {
        buildinglist[i]->printRoomsByType(type);
    }
}
void University::printRoomTypeStatistics() {
    int clas=0,off=0;
    for (int i = 0; i < buildingNum; ++i) {
        clas+=buildinglist[i]->getNumberOfClassrooms();
        off+=buildinglist[i]->getNumberOfOffices();
    }
    cout << "Room Type statistics for " << uniName << " university:" << endl;
    cout << "Number of offices = " << off << endl;
    cout << "Number of classrooms = " << clas << endl;
}

void University::printAvailableOffices() {
    cout << "Available offices in " << uniName <<" university:" << endl;
    for (int i = 0; i < buildingNum; ++i) {
        buildinglist[i]->printAvailableOffices();
    }
}

void University::printTotalCapacityOfOffices() {
    cout << "Office capacity in " << uniName << " university:" << endl;
    for (int i = 0; i < buildingNum; ++i) {
        cout << "Office capacity in " << buildinglist[i]->getBuildingName() << " building = " << buildinglist[i]->getTotalCapacity() << endl;
    }
}
void University::printSuitableClassrooms(int students) {
    cout << "Suitable classes in " << uniName << " university for " << students << " students:" << endl;
    for (int i = 0; i < buildingNum; ++i) {
        buildinglist[i]->printSuitableClassrooms(students);
    }
}
University::University(const University& uni){
    uniName = new char [strlen(uni.uniName)+1];
    strcpy(uniName,uni.uniName);
    buildingNum=uni.buildingNum;
    for (int i = 0; i < uni.buildingNum; ++i) {
        buildinglist[i] = new Building(*uni.buildinglist[i]);
    }
}

University& University::operator=(const University& uni){
    if(this == &uni)
        return *this;
    else{
        delete[] uniName;
        uniName = new char [strlen(uni.uniName)+1];
        strcpy(uniName,uni.uniName);
        buildingNum=uni.buildingNum;
        for (int i = 0; i < uni.buildingNum; ++i) {
            buildinglist[i] = new Building(*uni.buildinglist[i]);
        }
        return *this;
    }
}
University::~University(){
    delete [] uniName;
    for (int i = 0; i < buildingNum; ++i) {
        delete buildinglist[i];
    }
}
