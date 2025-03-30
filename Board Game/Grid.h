
#ifndef INC_242ASSIGNMENT3_GRID_H
#define INC_242ASSIGNMENT3_GRID_H
#include "Elements.h"
#include "Player.h"
#include <ctime>
#include <cstdlib>
#include <cstring>

class Grid{
private:
    Elements ***board;//the board which using for player interactions with elements.
    Player *p1,*p2;
    int n; //Length of one side of the board
    string **visibleBoard;// the board which player see like game map
public:
    Grid();
    Grid(const string& playerName1,const string& playerName2, int n);
    Grid(const Grid& rhs);

    Grid & operator=(Grid& rhs);
    ~Grid();
    //getters of player objectives.
    string getNameP1();
    string getNameP2();
    int getHealthP1();
    int getHealthP2();
    int getScoreP1();
    int getScoreP2();
    void deploy_elements();
    void movement(int V, int H,int turn);
    bool isavailable(int V,int H);
    bool isEnd(int totalTurn,int turn);
    void behind(int V,int H);
    void printBoard(int turn,int totalturn);
    bool isEmpty(int posH, int posV);

};


#endif
