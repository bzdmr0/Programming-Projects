

#ifndef ASSGN2_UNIVERSITY_H
#define ASSGN2_UNIVERSITY_H
#include "Building.h"

class University{
private:
    char *uniName;
    Building *buildinglist[20];
    int buildingNum;
public:
    University();
    University(char*);
    int getBuildingNum() const;
    void addBuilding(char*,int);
    char *getUniName() const;
    void setUniName(char *uniName);
    void printBuildings();
    void addRoom(int,char*,int,int,int,int,int);
    void printRooms();
    void printRoomsByType(int);
    void printRoomTypeStatistics();
    void printAvailableOffices();
    void printTotalCapacityOfOffices();
    void printSuitableClassrooms(int);
    University(const University&);
    University& operator=(const University&);
    ~University();
};
#endif //ASSGN2_UNIVERSITY_H
