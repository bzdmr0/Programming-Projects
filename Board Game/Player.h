
#ifndef INC_242ASSIGNMENT3_PLAYER_H
#define INC_242ASSIGNMENT3_PLAYER_H

using namespace std;
#include <iostream>
#include "Elements.h"
struct node { //this structure holds the player stats
    int goldCount;
    int woodCount;
};

class Player {
private:
    int health;
    string name;
    node stats;

public:
    Player();

    Player(const string& playerName,int health);

    void applyEffect(int effect);

    void addGold();
    void addWood();


    int getHealth() const ;
    int getGoldCount() const ;
    void setHealth(int health);
    int getWoodCount() const ;
    string getName() const ;
};


#endif
