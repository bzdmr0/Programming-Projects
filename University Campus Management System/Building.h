
#ifndef ASSGN2_BUILDING_H
#define ASSGN2_BUILDING_H
#include "Office.h"
#include "Classroom.h"

class Building {
private:
    char *buildingName;
    int size;
    int roomNum;
    Rooms *roomsList[100];
public:
    Building();
    Building(char *,int);
    char *getBuildingName() const;
    void setBuildingName(char *);
    int getSize() const ;
    void setSize(int ) ;
    int getRoomNum() const;
    void addRoom(char*,int,int,int,int,int);
    void printBuilding();
    void printRooms();
    void printRoomsByType(int);
    int getNumberOfClassrooms();
    int getNumberOfOffices();
    int getTotalCapacity();
    void printAvailableOffices();
    void printSuitableClassrooms(int);
    Building(const Building&);
    Building& operator=(const Building&);
    ~Building();



};
#endif //ASSGN2_BUILDING_H
