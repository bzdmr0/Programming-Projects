
#ifndef ASSGN2_OFFICE_H
#define ASSGN2_OFFICE_H
#include "Rooms.h"

class Office : public Rooms{
private:
    int people;
    enum officeType{None, CoordinatorOffice, StandardOffice,
        SharedOfficeFor2People, SharedOfficeFor3People, SharedOfficeFor10People}type;
public:
    Office();
    Office(char *, int, int, int);
    int getPeople() const;
    void setPeople(int);
    int getType();
    int getCapacity();
    bool isFull();
    void printRoom();
    char whichRoom();
    void setType(int);
};
#endif //ASSGN2_OFFICE_H
