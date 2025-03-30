

#include "Classroom.h"

Classroom::Classroom(): Rooms(){
    roomName=new char [100];
    floorNo=0;
    capacity = -1;
}
Classroom::Classroom(char *name, int floor, int cap): Rooms(name,floor){
    roomName=new char [100];
    strcpy(roomName,name);
    floorNo=floor;
    capacity=cap;
}

int Classroom::getCapacity() {
    return capacity;
}

void Classroom::setCapacity(int capacity) {
    this->capacity = capacity;
}
bool Classroom::checkSuitability(int students){
    if(capacity>=students)
        return true;
    else
        return false;
}
void Classroom::printRoom(){
    cout << "Classroom name = " << roomName << endl;
    cout << "Classroom floor number = " << floorNo << endl;
    cout << "Classroom capacity = " << capacity << endl;
}

//for checking is the room classroom.
char Classroom::whichRoom(){
    return 'c';
}
