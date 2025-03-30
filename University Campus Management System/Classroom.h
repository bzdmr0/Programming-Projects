/** Muhammet Sait Bozdemir -- 2584738
I read and accept the submission rules and the extra rules specified in each
question. This is my own work that is done by myself only**/

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
