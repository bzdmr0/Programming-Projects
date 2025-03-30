

#ifndef ASSGN2_CLASSROOM_H
#define ASSGN2_CLASSROOM_H
#include "Rooms.h"

class Classroom : public Rooms{
private:
    int capacity;
public:
    Classroom();
    Classroom(char *, int, int);
    int getCapacity();
    void setCapacity(int );
    bool checkSuitability(int);
    void printRoom();
    char whichRoom();
};
#endif //ASSGN2_CLASSROOM_H
