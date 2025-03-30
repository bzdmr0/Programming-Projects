/** Arda Menşur – 2585214 , Muhammet Sait Bozdemir – 2584738
We read and accept the submission rules and the extra rules specified in each question. This is our own work that is done by us only **/
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
    //created by Arda
    void deploy_elements();
    //created by Sait
    void movement(int V, int H,int turn);
    // created by Arda
    bool isavailable(int V,int H);
    //Created by Sait
    bool isEnd(int totalTurn,int turn);
    //Created by Arda
    void behind(int V,int H);
    //Created by Sait
    void printBoard(int turn,int totalturn);
    //We created together.
    bool isEmpty(int posH, int posV);

};


#endif
