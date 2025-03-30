/** Muhammet Sait Bozdemir -- 2584738
I read and accept the submission rules and the extra rules specified in each
question. This is my own work that is done by myself only**/

#include "Office.h"

Office::Office() :Rooms(){
    people=0;
    type=None;
}
Office::Office(char *name, int floor,int people, int type) : Rooms(name,floor){
    this->people=people;
    this->type = officeType(type);
}

void Office::setType(int type) {
    this->type = officeType(type);
}
int Office::getType() {
    return type;
}

int Office::getPeople() const {
    return people;
}

void Office::setPeople(int people) {
    this->people = people;
}


int Office:: getCapacity(){
    switch (type) {
        case None:
            return 0;
        case CoordinatorOffice:
            return 1;
        case StandardOffice:
            return 1;
        case SharedOfficeFor2People:
            return 2;
        case SharedOfficeFor3People:
            return 3;
        case SharedOfficeFor10People:
            return 10;
    }
}
bool Office::isFull(){
    if(people>=getCapacity())
        return true;
    else
        return false;
}
void Office::printRoom(){
    cout << "Office name = " << roomName << endl;
    cout << "Office floor number = " << floorNo << endl;
    cout << "Office type: ";
    switch (type) {
        case None:
            cout << "None" << endl;
            break;
        case CoordinatorOffice:
            cout << "Coordinator Office" << endl;
            break;
        case StandardOffice:
            cout << "Standard Office" << endl;
            break;
        case SharedOfficeFor2People:
            cout << "Shared office for 2 people" << endl;
            break;
        case SharedOfficeFor3People:
            cout << "Shared office for 3 people" << endl;
            break;
        case SharedOfficeFor10People:
            cout << "Shared office for 10 people" << endl;
            break;
        default:
            cout << "Wrong input";
    }
    cout << "Number of people in office = " << people << endl;
    cout << "Office capacity = " << Office::getCapacity() << endl;
    if(Office::isFull())
        cout << "Office is full" << endl;
    else
        cout << "Office is not full" << endl;
}

//for checking is the room office.
char Office::whichRoom(){
    return 'o';
}
