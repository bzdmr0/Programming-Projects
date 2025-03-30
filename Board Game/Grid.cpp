/** Arda Menşur – 2585214 , Muhammet Sait Bozdemir – 2584738
We read and accept the submission rules and the extra rules specified in each question. This is our own work that is done by us only **/
#include "Grid.h"


Grid::Grid(){
    n=0;
    board = nullptr;
    visibleBoard = nullptr;
    p1= nullptr;
    p2= nullptr;
}
Grid::Grid(const string& playerName1,const string& playerName2, int n){
    this->n = n;
    p1= new Player(playerName1,2*n);
    p2= new Player(playerName2,2*n);
    board= new Elements** [n];
    for (int i = 0; i < n; ++i) {
        board[i]=new Elements* [n];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            board[i][j]=nullptr;
        }
    }
    visibleBoard = new string *[n];
    for (int i = 0; i < n; ++i) {
        visibleBoard[i]=new string [n];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if(i==0 && j==0)
                visibleBoard[i][j] = " [P1] ";
            else if(i==n-1 && j==n-1)
                visibleBoard[i][j] = " [P2] ";
            else
                visibleBoard[i][j] = " [  ] ";

        }
    }
}
Grid::Grid(const Grid& rhs) {
    n = rhs.n;

    p1 = new Player(*rhs.p1);
    p2 = new Player(*rhs.p2);

    board = new Elements**[n];
    for (int i = 0; i < n; i++) {
        board[i] = new Elements*[n];
        for (int j = 0; j < n; j++) {
            if (rhs.board[i][j] != nullptr) {
                board[i][j] = rhs.board[i][j];
            } else {
                board[i][j] = nullptr;
            }
        }
    }

    visibleBoard = new string*[n];
    for (int i = 0; i < n; i++) {
        visibleBoard[i] = new string[n];
        for (int j = 0; j < n; j++) {
            visibleBoard[i][j] = rhs.visibleBoard[i][j];
        }
    }
}

Grid & Grid::operator=(Grid& rhs){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(board[i][j]!= nullptr)
                delete board[i][j];
        }
        delete[] board[i];
        delete[] visibleBoard[i];
    }
    delete p1;
    delete p2;
    delete [] board;
    delete [] visibleBoard;

    n = rhs.n;

    p1 = new Player(*rhs.p1);
    p2 = new Player(*rhs.p2);

    board = new Elements**[n];
    for (int i = 0; i < n; i++) {
        board[i] = new Elements*[n];
        for (int j = 0; j < n; j++) {
            if (rhs.board[i][j] != nullptr) {
                board[i][j] = rhs.board[i][j];
            } else {
                board[i][j] = nullptr;
            }
        }
    }

    visibleBoard = new string*[n];
    for (int i = 0; i < n; i++) {
        visibleBoard[i] = new string[n];
        for (int j = 0; j < n; j++) {
            visibleBoard[i][j] = rhs.visibleBoard[i][j];
        }
    }
    return *this;
}
Grid::~Grid(){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(board[i][j]!= nullptr)
                delete board[i][j];
        }
        delete[] board[i];
        delete[] visibleBoard[i];
    }
    delete p1;
    delete p2;
    delete [] board;
    delete [] visibleBoard;
}
//getters of player objectives.
string Grid::getNameP1(){ return p1->getName();}
string Grid::getNameP2(){ return p2->getName();}
int Grid::getHealthP1(){ return p1->getHealth();}
int Grid::getHealthP2(){ return p2->getHealth();}
int Grid::getScoreP1(){ return p1->getGoldCount()*100;}
int Grid::getScoreP2(){ return p2->getGoldCount()*100;}
//created by Arda
void Grid::deploy_elements(){ // Hocam, instead of deleting the visible board parts, we deliberately put them in the comment line. We think it's useful for checking and editing.
    srand(time(nullptr));
    int shape,posV,posH; // posV= Vertical coordinates, posH= Horizontal coordinates
    //for bear
    for (int i = 0; i < (n*n)/25; ++i) {
        shape= rand()%4; // for choosing randomly shapes for the deployments.
        int loop=1;
        if(shape==0){ //horizontal
            do {
                posV= rand()%n;
                posH = rand()%(n-2);
                if(isEmpty(posH,posV) && isEmpty(posH+1,posV) && isEmpty(posH+2,posV)){
                    board[posV][posH] = new Bear(n);
                    //visibleBoard[posV][posH] = " [b] ";
                    board[posV][posH+1] = new Bear(n);
                    //visibleBoard[posV][posH+1] = " [b] ";
                    board[posV][posH+2] = new Bear(n);
                    //visibleBoard[posV][posH+2] = " [b] ";
                    loop=0;
                }
            } while (loop==1);
        } else if(shape==1){ //vertical
            do {
                posV= rand()%(n-2);
                posH = rand()%n;
                if(isEmpty(posH,posV) && isEmpty(posH,posV+1) && isEmpty(posH,posV+2)){
                    board[posV][posH] = new Bear(n);
                    //visibleBoard[posV][posH] = " [b] ";
                    board[posV+1][posH] = new Bear(n);
                    //visibleBoard[posV+1][posH] = " [b] ";
                    board[posV+2][posH] = new Bear(n);
                    //visibleBoard[posV+2][posH+2] = " [b] ";
                    loop=0;
                }
            } while (loop==1);
        } else if(shape==2){ // '/' shape
            do {
                posV = (rand()%(n-2))+2;
                posH = rand()%(n-2);
                if(isEmpty(posH,posV) && isEmpty(posH+1,posV-1) && isEmpty(posH+2,posV-2)){
                    board[posV][posH] = new Bear(n);
                    //visibleBoard[posV][posH] = " [b] ";
                    board[posV-1][posH+1] = new Bear(n);
                    //visibleBoard[posV-1][posH+1] = " [b] ";
                    board[posV-2][posH+2] = new Bear(n);
                    //visibleBoard[posV-2][posH+2] = " [b] ";
                    loop=0;
                }
            } while (loop==1);
        } else{  // '\' shape
            do {
                posV = (rand()%(n-2))+2;
                posH = (rand()%(n-2))+2;
                if(isEmpty(posH,posV) && isEmpty(posH-1,posV-1) && isEmpty(posH-2,posV-2)){
                    board[posV][posH] = new Bear(n);
                    //visibleBoard[posV][posH] = " [b] ";
                    board[posV-1][posH-1] = new Bear(n);
                    //visibleBoard[posV-1][posH-1] = " [b] ";
                    board[posV-2][posH-2] = new Bear(n);
                    //visibleBoard[posV-2][posH-2] = " [b] ";
                    loop=0;
                }
            } while (loop==1);
        }
    }
    //for wood
    for (int i = 0; i < 2*((n*n)/25); ++i) {
        shape= rand()%4;
        int loop=1;
        if(shape==0){//horizontal
            do {
                posV= rand()%n;
                posH = rand()%(n-2);
                if(isEmpty(posH,posV) && isEmpty(posH+1,posV)){
                    board[posV][posH] = new Wood(n);
                    //visibleBoard[posV][posH] = " [i] ";
                    board[posV][posH+1] = new Wood(n);
                    //visibleBoard[posV][posH+1] = " [i] ";
                    loop=0;
                }
            } while (loop==1);
        } else if(shape==1){//vertical
            do {
                posV= rand()%(n-2);
                posH = rand()%n;
                if(isEmpty(posH,posV) && isEmpty(posH,posV+1)){
                    board[posV][posH] = new Wood(n);
                    //visibleBoard[posV][posH] = " [i] ";
                    board[posV+1][posH] = new Wood(n);
                    //visibleBoard[posV+1][posH] = " [i] ";
                    loop=0;
                }
            } while (loop==1);
        } else if(shape==2){    // '/' shape
            do {
                posV = (rand()%(n-2))+2;
                posH = rand()%(n-2);
                if(isEmpty(posH,posV) && isEmpty(posH+1,posV-1)){
                    board[posV][posH] = new Wood(n);
                    //visibleBoard[posV][posH] = " [i] ";
                    board[posV-1][posH+1] = new Wood(n);
                    //visibleBoard[posV-1][posH+1] = " [i] ";
                    loop=0;
                }
            } while (loop==1);
        } else{       // '\' shape
            do {
                posV = (rand()%(n-2))+2;
                posH = (rand()%(n-2))+2;
                if(isEmpty(posH,posV) && isEmpty(posH+1,posV-1)){
                    board[posV][posH] = new Wood(n);
                    //visibleBoard[posV][posH] = " [i] ";
                    board[posV-1][posH-1] = new Wood(n);
                    //visibleBoard[posV-1][posH-1] = " [i] ";
                    loop=0;
                }
            } while (loop==1);
        }
    }
    //for Wolf
    for (int i = 0; i < 2*((n*n)/25); ++i) {
        int loop =1;
        do {
            posV = rand()%n;
            posH = rand()%n;
            if(isEmpty(posH,posV)){
                board[posV][posH] = new Wolf(n);
                //visibleBoard[posV][posH] = " [w] ";
                loop=0;
            }
        } while (loop==1);
    }
    //for Food
    for (int i = 0; i < 2*((n*n)/25); ++i) {
        int loop =1;
        do {
            posV = rand()%n;
            posH = rand()%n;
            if(isEmpty(posH,posV)){
                board[posV][posH] = new Food(n);
                //visibleBoard[posV][posH] = " [f] ";
                loop=0;
            }
        } while (loop==1);
    }
    //for Medical supplies
    for (int i = 0; i < 2*((n*n)/25); ++i) {
        int loop =1;
        do {
            posV = rand()%n;
            posH = rand()%n;
            if(isEmpty(posH,posV)){
                board[posV][posH] = new MedicalSupplies(n);
                //visibleBoard[posV][posH] = " [s] ";
                loop=0;
            }
        } while (loop==1);
    }
    //for Gold
    for (int i = 0; i < 2*((n*n)/25); ++i) {
        int loop =1;
        do {
            posV = rand()%n;
            posH = rand()%n;
            if(isEmpty(posH,posV)){
                board[posV][posH] = new Gold();
                //visibleBoard[posV][posH] = " [g] ";
                loop=0;
            }
        } while (loop==1);
    }
}
//created by Sait
void Grid::movement(int V, int H,int turn){ //The movement function that contains all player movements and facings.
    char choice;
    srand(time(nullptr));
    int dice,check=1;

    if (turn % 2 == 1) {  //movement for Player 1
        visibleBoard[V][H] = " [P1] ";

        if (board[V][H] != nullptr) {
            if (V == 0 && H == 0)  //if player1 spawn in a cell which has an element
                cout << p1->getName() << ", at initial you interact with something"
                     << endl;
            if (board[V][H]->isAnimal()) { // facing with a wild animal
                cout << "You faced with a "<<board[V][H]->getName()<<" !" << endl;
                cout << "If you find the number is odd or even you can escape." << endl;
                do {
                    cout << "Your choice ('E' for even 'O' for odd) : ";
                    cin >> choice;
                    dice = rand();
                    if (choice == 'E') {
                        check = 0;
                        if (dice % 2 != 0) {
                            cout << "You could not escape!" << endl;
                            p1->applyEffect(board[V][H]->getHealthEffect());
                        } else
                            cout << "You managed to escape!" << endl;
                    } else if (choice == 'O') {
                        check = 0;
                        if (dice % 2 == 0) {
                            cout << "You could not escape!" << endl;
                            p1->applyEffect(board[V][H]->getHealthEffect());
                        } else
                            cout << "You managed to escape!" << endl;
                    } else
                        cout << "Please enter correct input." << endl;
                } while (check == 1);
            } else { // finding an element
                cout << "You found " << board[V][H]->getName() << endl;
                p1->applyEffect(board[V][H]->getHealthEffect());
                if (board[V][H]->getSymbol() == 'G') {
                    p1->addGold();
                    if (p1->getGoldCount() % 3 == 0) {  //Bonus by gold
                        cout << "You reached " << p2->getGoldCount()
                             << " amount of gold. Your health increased "
                             << n / 4 << endl;
                        p1->setHealth(p1->getHealth() + (n / 4));
                    }   //Bonus health effect
                }
                if (board[V][H]->getSymbol() == 'I') {
                    p1->addWood();
                    if (p1->getWoodCount() % 2 == 0) {//Bonus by wood
                        cout << "You reached " << p1->getWoodCount()
                             << " amount of wood. Your health increased "
                             << n / 4 << endl;
                        p1->setHealth(p1->getHealth() + (n / 8));
                    }  //Bonus health effect
                }
            }
        } else if (V == 0 && H == 0) { cout << p1->getName() << ", you spawned an empty cell." << endl; }
        else
            cout << "There is nothing here." << endl;
    } else { // movement for Player 2
        visibleBoard[V][H] = " [P2] ";
        if (board[V][H] != nullptr) {
            if (V == n - 1 && H == n - 1)  //if  player2 spawn in a cell which has an element
                cout << p2->getName() << ", at initial you interact with something" << endl;
            if (board[V][H]->isAnimal()) {
                cout << "You faced with a "<<board[V][H]->getName()<<" !" << endl;
                cout << "If you find the number is odd or even you can escape." << endl;
                do {
                    cout << "Your choice ('E' for even 'O' for odd) :";
                    cin >> choice;
                    dice = rand();
                    if (choice == 'E') {
                        check = 0;
                        if (dice % 2 != 0) {
                            cout << "You could not escape!" << endl;
                            p2->applyEffect(board[V][H]->getHealthEffect());
                        } else
                            cout << "You managed to escape!" << endl;
                    } else if (choice == 'O') {
                        check = 0;
                        if (dice % 2 == 0) {
                            cout << "You could not escape!" << endl;
                            p2->applyEffect(board[V][H]->getHealthEffect());
                        } else
                            cout << "You managed to escape!" << endl;
                    } else
                        cout << "Please enter correct input." << endl;
                } while (check == 1);
            } else {
                cout << "You found " << board[V][H]->getName() << endl;
                p2->applyEffect(board[V][H]->getHealthEffect());
                if (board[V][H]->getSymbol() == 'G') {
                    p2->addGold();
                    if (p2->getGoldCount() % 3 == 0) {  //Bonus by gold
                        cout << "You reached " << p2->getGoldCount()
                             << " amount of gold. Your health increased "
                             << n / 4 << endl;
                        p2->setHealth(p2->getHealth() + (n / 4));  //Bonus health effect
                    }
                }
                if (board[V][H]->getSymbol() == 'I') {
                    p2->addWood();
                    if (p2->getWoodCount() % 2 == 0) {//Bonus by wood
                        cout << "You reached " << p2->getWoodCount()
                             << " amount of wood. Your health increased "
                             << n / 4 << endl;
                        p2->setHealth(p2->getHealth() + (n / 8));  //Bonus health effect
                    }
                }
            }
        } else if (V == (n - 1) && H == (n - 1)) {
            cout << p2->getName() << ", you spawned an empty cell." << endl;
        }
        else
            cout << "There is nothing here." << endl;
    }
}
// created by Arda
bool Grid::isavailable(int V,int H){ // To check whether a position of movement was visited or not. Player can only visit once for all positions.
    if(visibleBoard[V][H]==" [  ] ") return true;
    else return false;
}
//Created by Sait
bool Grid::isEnd(int totalTurn,int turn){ // To check game is over or not for given scenarios.

    if(totalTurn==turn)//Number of turn over
        return true;
    if(p1->getGoldCount()+p2->getGoldCount()==2*((n*n)/25)) // all golds collected
        return true;
    if(p1->getHealth()==0 && p2->getHealth()==0)//Both players died
        return true;
    return false;
}
//Created by Arda
void Grid::behind(int V,int H){ // After a move we put a sign to previous position.
    if(board[V][H]== nullptr)
        visibleBoard[V][H] = " [X] "; // Visited position was empty
    else if(board[V][H]->getSymbol()=='G') // Visited position had an element. It is matching with their symbols.
        visibleBoard[V][H] = " [G] ";
    else if (board[V][H]->getSymbol()=='I')
        visibleBoard[V][H] = " [I] ";
    else if (board[V][H]->getSymbol()=='W')
        visibleBoard[V][H] = " [W] ";
    else if (board[V][H]->getSymbol()=='F')
        visibleBoard[V][H] = " [F] ";
    else if (board[V][H]->getSymbol()=='B')
        visibleBoard[V][H] = " [B] ";
    else
        visibleBoard[V][H] = " [S] ";
}
//Created by Sait
void Grid::printBoard(int turn,int totalturn){ //Game map & stats
    cout<<"-------------------------------------------------------------------"<<endl;
    cout<<"Turn -> "<<turn<<"/"<<totalturn<<endl;
    cout << p1->getName() << " (P1)" << "'s health: " << p1->getHealth() <<"\t\t"<<p2->getName() << " (P2)" << "'s health: " << p2->getHealth() << endl;
    cout << p1->getName() << " (P1)" << "'s point: " << p1->getGoldCount()*100 <<"\t\t"<< p2->getName() << " (P2)" << "'s point: " << p2->getGoldCount()*100 << endl<<endl;

    for (int num =0;num<n;num++ ){ printf("%6d", num); }
    cout<<endl;
    for (int i = 0; i < n; ++i) {
        printf("%d ",i);
        for (int j = 0; j < n; ++j) {
            printf("%6s", visibleBoard[i][j].c_str());
        }
        cout << endl;
    }
    cout<<"-------------------------------------------------------------------"<<endl;
}
//We created together.
bool Grid::isEmpty(int posH, int posV){ // To check whether a position of an element is empty or not before deploying it
    if(board[posV][posH] == nullptr)
        return true;
    else
        return false;
}