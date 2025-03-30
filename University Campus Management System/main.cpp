/** Muhammet Sait Bozdemir -- 2584738
I read and accept the submission rules and the extra rules specified in each
question. This is my own work that is done by myself only**/


#include <iostream>
#include "University.h"

int main() {
    /*Building b1("T",100);
    Rooms *r1;
    Office *o1 = new Office("TZ-11",1,1,1);
    r1=o1;
    //r1->printRoom();
    b1.printBuilding();
    b1.addRoom();
    b1.printRooms();*/


    University U = University("METU NCC");
    int selection;
    char *name = new char;
    do {
        cout << "\n[1] Add a new building to the university\n"
                "[2] Add a new room to a selected building\n"
                "[3] Print the buildings in the university\n"
                "[4] Print the rooms in each building in the university\n"
                "[5] Print the rooms in each building in the university based on type\n"
                "[6] Print the total number of classrooms and offices in the university\n"
                "[7] Print the available offices in each building in the university\n"
                "[8] Print the total capacity of all the offices\n"
                "[9] Print the suitable classrooms in the university based on the given number\n"
                "of students\n"
                "[10] Exit" << endl;
        cout << "Please enter your choice:";
        cin >> selection;
        switch (selection) {
            case 1:
                int size;
                cout << "Please enter name of building:";
                cin >> name;
                cout << "Please enter size of building:";
                cin >> size;
                U.addBuilding(name,size);
                break;
            case 2:
                int number;
                U.printBuildings();
                if (U.getBuildingNum()==0)
                    cout << "There is no building, please add a building."<< endl;
                else{
                    cout << "Please enter the number of building to which the room should be added:";
                    cin >> number;
                    if(number>U.getBuildingNum() || number<=0)
                        cout << "Your input is not suitable";
                    else{
                        int roomType;
                        int floor;
                        cout << "Please enter the type of room(1: Classroom/ 2: Office): ";
                        cin >> roomType;
                        if(roomType==1){
                            int cap;
                            cout << "Please enter the name of the new classroom: ";
                            cin >> name;
                            cout << "Please enter the floor number of the new classroom: ";
                            cin >> floor;
                            cout << "Please enter capacity of classroom: ";
                            cin >> cap;
                            U.addRoom(number-1,name,roomType,floor,cap,0,0);
                        } else{
                            int offtype,people;
                            cout << "Please enter the name of the new office:";
                            cin >> name;
                            cout << "Please enter the floor number of the new office: ";
                            cin >> floor;
                            cout << "[1] Coordinator Office\n[2] Standard Office\n[3] Shared Office for 2 people\n"
                                    "[4] Shared Office for 3 people\n"
                                    "[5] Shared Office for 10 people\n";
                            cout << "Please enter type of office: ";
                            cin >> offtype;
                            cout << "Please enter number of people in the office: ";
                            cin >> people;
                            U.addRoom(number-1,name,roomType,floor,0,offtype,people);
                        }
                    }
                }
                break;
            case 3:
                U.printBuildings();
                break;
            case 4:
                U.printRooms();
                break;
            case 5:
                int type;
                cout << "Please enter type of room to display:" << endl;
                cout << "[1] Classrooms\n"
                        "[2] Offices" << endl;
                cin >> type;
                if(type==1 || type==2)
                    U.printRoomsByType(type);
                else
                    cout << "Your input is not suitable";
                break;
            case 6:
                U.printRoomTypeStatistics();
                break;
            case 7:
                U.printAvailableOffices();
                break;
            case 8:
                U.printTotalCapacityOfOffices();
                break;
            case 9:
                int students;
                cout << "Please enter number of students:";
                cin >> students;
                if(students<0)
                    cout << "Your input is not suitable";
                else
                    U.printSuitableClassrooms(students);
            case 10:
                break;
            default:
                cout << "Please enter a suitable number" << endl;
                break;
        }
    } while (selection!=10);
    cout << "Thank you for using the university campus management system";
    return 0;
}
