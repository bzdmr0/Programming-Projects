

#ifndef ASSGN2_ROOMS_H
#define ASSGN2_ROOMS_H
#include <cstring>
#include <iostream>

using namespace std;

class Rooms{
protected:
    char *roomName;
    int floorNo;
public:
    Rooms();
    Rooms(char *, int );
    char *getRoomName() const;
    void setRoomName(char *);
    int getFloorNo() const;
    void setFloorNo(int);
    virtual void printRoom();
    Rooms(const Rooms&);
    Rooms& operator=(const Rooms&);
    ~Rooms();
    virtual  int getPeople() const{};
    virtual char whichRoom(){};
    virtual int getCapacity(){};
    virtual bool isFull(){};
    virtual bool checkSuitability(int){};
    virtual int getType(){};
};
#endif //ASSGN2_ROOMS_H
