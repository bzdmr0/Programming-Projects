/**
We read and accept the submission rules and the extra rules specified in each question. This is our own work that is done by us only **/
#include <iostream>
#include <ctime>
#include "Grid.h"

using namespace std;
int main() {
    char exit = 'N';
    do{
        int n, loop = 0, totalTurn, turn = 1, VforP1, HforP1, VforP2, HforP2, skip = 0;
        string p1Name, p2Name;
        srand(time(nullptr));

        cout << "Welcome to Gold Rush Alaska! Let's start the game! " << endl;
        cout << "Oh! It looks frigid outside. Let's collect some gold without getting caught by wild animals." << endl;
        cout << "Please, enter the name of Player 1:";
        cin >> p1Name;
        cout << "Please, enter the name of Player 2:";
        cin >> p2Name;
        cout << "Please enter the board size n x n (It should be at least 5):";
        cin >> n;
        if (n < 5) {
            cout << "The n value you entered is less than 5. 5x5 board created automatically." << endl;
            n = 5;
        }
        //Vertical and horizontal coordinates of each player.
        VforP2 = n - 1;
        HforP2 = n - 1;
        HforP1 = 0;
        VforP1 = 0;
        totalTurn=4;
        //totalTurn=20+(rand()%((n*n)-19)); // as stated in assignment PDF the game select the turns randomly between 20 - (n*n)
        cout << "The total number of turns you will play:" << totalTurn << endl << endl;
        Grid g1 = Grid(p1Name, p2Name, n);
        g1.deploy_elements();// placing the elements to board
        do {
            if (g1.getHealthP1() != 0) { // if player1 dies game will continue with only player2
                if (turn == 1)
                    g1.movement(HforP1, VforP1, 1); //initial place of Player1
                cout << endl << g1.getNameP1() << " (P1)" << "'s turn" << endl;
                g1.printBoard(turn, totalTurn);
                g1.behind(VforP1, HforP1);
                cout << g1.getNameP1() << ", please enter the coordinates you want to move ([x][y]):";
                cin >> HforP1 >> VforP1;
                while (!g1.isavailable(VforP1, HforP1)) { //To prevent players from revisiting visited coordinates.
                    cout<< "You can not visit same position more than one time! Please enter the new coordinates you want to move ([x][y]):";
                    cin >> HforP1 >> VforP1;
                }
                g1.movement(VforP1, HforP1, turn);
                g1.printBoard(turn, totalTurn);
                if (g1.isEnd(totalTurn, turn)) {
                    loop = 1;
                    skip = 1; // if game ends in player1's turn game will skip the player2's turn.
                }
                turn++;
            }
            if (skip != 1 && g1.getHealthP2() != 0) { // if player2 dies game will continue with only player1 OR game ends in player1's turn.
                if (turn == 2)
                    g1.movement(VforP2, HforP2, 2);//initial place of Player2
                cout << endl << g1.getNameP2() << " (P2)" << "'s turn" << endl;
                g1.printBoard(turn, totalTurn);
                g1.behind(VforP2, HforP2);
                cout << g1.getNameP2() << ", please enter the coordinates you want to move ([x][y]):";
                cin >> HforP2 >> VforP2;
                while (!g1.isavailable(VforP2, HforP2)) {//To prevent players from revisiting visited coordinates.
                    cout<< "You can not visit same position more than one time! Please enter the new coordinates you want to move ([x][y]):";
                    cin >> HforP2 >> VforP2;
                }
                g1.movement(VforP2, HforP2, turn);
                g1.printBoard(turn, totalTurn);
                if (g1.isEnd(totalTurn, turn)) {
                    loop = 1;
                }
                turn++;
            }
        } while (loop != 1);
        // result part of the game.
        if (g1.getScoreP1() > g1.getScoreP2())
            cout << g1.getNameP1() << "<< won the game. Congratulations!!!" << endl;
        else if (g1.getScoreP1() < g1.getScoreP2())
            cout << g1.getNameP2() << "<< won the game. Congratulations!!!" << endl;
        else
            cout << "The draw won. I think, you should play again." << endl;
        cout<<"Do you want to play again ?(Y/N)";
        cin>>exit;
    } while (exit !='N');

    return 0;
}
