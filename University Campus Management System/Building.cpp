

#include "Building.h"

Building::Building(){
    buildingName = new char [strlen("Undefined")+1];
    strcpy(buildingName,"Undefined");
    size=-1;
    roomNum=-0;
}
Building::Building(char *name,int size){
    buildingName = new char [strlen(name)+1];
    strcpy(buildingName,name);
    this->size=size;
    roomNum=0;
}


char* Building:: getBuildingName() const{
    return buildingName;
}

void Building:: setBuildingName(char *buildingName) {
    this->buildingName = buildingName;
}

int Building::getSize() const {
    return size;
}

void Building::setSize(int size) {
    this->size = size;
}

int Building::getRoomNum() const {
    return roomNum;
}

void Building::addRoom(char* name,int roomType,int floor,int cap,int offType,int people){
    if(roomType==1){
        roomsList[roomNum++] = new Classroom(name,floor,cap);
    } else{
        switch (offType) {
            case 1:
                if(people<=1)
                    roomsList[roomNum++] = new Office(name,floor,people,offType);
                else
                    cout << "Office capacity is not sufficient" << endl;
                break;
            case 2:
                if(people<=1)
                    roomsList[roomNum++] = new Office(name,floor,people,offType);
                else
                    cout << "Office capacity is not sufficient" << endl;
                break;
            case 3:
                if(people<=2)
                    roomsList[roomNum++] = new Office(name,floor,people,offType);
                else
                    cout << "Office capacity is not sufficient" << endl;
                break;
            case 4:
                if(people<=3)
                    roomsList[roomNum++] = new Office(name,floor,people,offType);
                else
                    cout << "Office capacity is not sufficient" << endl;
                break;
            case 5:
                if(people<=10)
                    roomsList[roomNum++] = new Office(name,floor,people,offType);
                else
                    cout << "Office capacity is not sufficient" << endl;
                break;
            default:
                cout << "Wrong input";
        }
    }
}
void Building::printBuilding(){
    cout << "Building name = " << buildingName << endl;
    cout << "Building size = " << size << endl;
    cout << "Building number of rooms = " << roomNum << endl;
}
void Building::printRooms(){
    cout << "All rooms in " << buildingName << " building:" << endl;
    for (int i = 0; i < roomNum; ++i) {
        roomsList[i]->printRoom();
        cout << endl;
    }
}
void Building::printRoomsByType(int inpt){
    if(inpt==1){
        cout << "All classrooms in " << buildingName << " building:" << endl;
        for (int i = 0; i < roomNum; ++i) {
            if(roomsList[i]->whichRoom() == 'c'){
                roomsList[i]->printRoom();
                cout << endl;
            }
        }
    } else{
        cout << "All offices in " << buildingName << " building:" << endl;
        for (int i = 0; i < roomNum; ++i) {
            if(roomsList[i]->whichRoom() == 'o'){
                roomsList[i]->printRoom();
                cout << endl;
            }
        }
    }
}
int Building::getNumberOfClassrooms() {
    int num=0;
    for (int i = 0; i < roomNum; ++i) {
        if(roomsList[i]->whichRoom() == 'c')
            num++;
    }
    return num;
}

int Building::getNumberOfOffices() {
    int num=0;
    for (int i = 0; i < roomNum; ++i) {
        if(roomsList[i]->whichRoom() == 'o')
            num++;
    }
    return num;
}
int Building::getTotalCapacity(){
    int num=0;
    for (int i = 0; i < roomNum; ++i) {
        if(roomsList[i]->whichRoom() == 'o')
            num+=roomsList[i]->getCapacity();
    }
    return num;
}

void Building::printAvailableOffices(){
    cout << "Available offices in " << buildingName << " building:" << endl;
    for (int i = 0; i < roomNum; ++i) {
        if(roomsList[i]->whichRoom()=='o'){
            if(!roomsList[i]->isFull()){
                roomsList[i]->printRoom();
                cout << endl;
            }
        }
    }
}

void Building::printSuitableClassrooms(int students){
    cout << "Classrooms which are suitable for "<< students <<" students in "<< buildingName <<" building:" << endl;
    for (int i = 0; i < roomNum; ++i) {
        if(roomsList[i]->whichRoom()=='c')
            if(roomsList[i]->checkSuitability(students))
                roomsList[i]->printRoom();
    }
}
Building::Building(const Building& building){
    buildingName = new char [strlen(building.buildingName)+1];
    strcpy(buildingName,building.buildingName);
    size=building.size;
    for (int i = 0; i < building.roomNum; ++i) {
        if(building.roomsList[i]->whichRoom()=='c')
            roomsList[i]= new Classroom(building.roomsList[i]->getRoomName(),building.roomsList[i]->getFloorNo(),building.roomsList[i]->getCapacity());
        else if(building.roomsList[i]->whichRoom()=='o')
            roomsList[i]= new Office(building.roomsList[i]->getRoomName(),building.roomsList[i]->getFloorNo(),building.roomsList[i]->getPeople(),building.roomsList[i]->getType());
    }
}

Building& Building::operator=(const Building& building){
    if(this == &building)
        return *this;
    else{
        delete[] buildingName;
        buildingName = new char [strlen(building.buildingName)+1];
        strcpy(buildingName,building.buildingName);
        size=building.size;
        for (int i = 0; i < building.roomNum; ++i) {
            if(building.roomsList[i]->whichRoom()=='c')
                roomsList[i]= new Classroom(building.roomsList[i]->getRoomName(),building.roomsList[i]->getFloorNo(),building.roomsList[i]->getCapacity());
            else if(building.roomsList[i]->whichRoom()=='o')
                roomsList[i]= new Office(building.roomsList[i]->getRoomName(),building.roomsList[i]->getFloorNo(),building.roomsList[i]->getPeople(),building.roomsList[i]->getType());
        }
        return *this;
    }
}
Building::~Building(){
    delete [] buildingName;
    for (int i = 0; i < roomNum; ++i) {
        delete roomsList[i];
    }
}

