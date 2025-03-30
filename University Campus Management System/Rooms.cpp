

#include "Rooms.h"

Rooms::Rooms(){
    roomName = new char [strlen("Undefined")+1];
    strcpy(roomName,"Undefined");
    floorNo = -1;
}
Rooms::Rooms(char *name, int no){
    roomName = new char [strlen(name)+1];
    strcpy(roomName,name);
    floorNo = no;
}

char * Rooms::getRoomName() const {
    return roomName;
}

void Rooms::setRoomName(char *roomName) {
    this->roomName = roomName;
}

int Rooms::getFloorNo() const {
    return floorNo;
}

void Rooms::setFloorNo(int floorNo) {
    this->floorNo = floorNo;
}
void Rooms::printRoom(){
    cout << "Room name = " << roomName << endl;
    cout << "Room floor number = " << floorNo << endl;
}

Rooms::Rooms(const Rooms& room){
    roomName = new char [strlen(room.roomName)+1];
    strcpy(roomName,room.roomName);
    floorNo=room.floorNo;
}

Rooms& Rooms::operator=(const Rooms& room){
    if(this == &room)
        return *this;
    else{
        delete[] roomName;
        roomName = new char [strlen(room.roomName)+1];
        strcpy(roomName,room.roomName);
        floorNo=room.floorNo;
        return *this;
    }
}
Rooms::~Rooms(){
    delete[] roomName;
}

