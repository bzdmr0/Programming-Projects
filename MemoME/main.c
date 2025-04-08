
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int boardSize();
int initializeBoard(char **,int);
void charactersarray(char *,int);
void getCoordinates(int*,int*,int*,int*,int,char**);
void displayBoard(int,char **,char **,int*,int,int,int,int,int *,int*,int*,int);
int checkCharacters(char **,int,int,int,int);


int main() {
    int size, row1 = 0, row2 = 0, column1 = 0, column2 = 0, start, finish, score1 = 0, totscore1 = 0, c = 0, score2 = 0, totscore2 = 0;//I control score in displayboard
    char **board, **board2, yesno;
do{
    start=1;
    srand(time(NULL));
    printf("Welcome to MemoMe!\n");
    size = boardSize();
    finish = size * size;
    board2 = (char **) malloc(sizeof(char *) * size);
    if (board2 == NULL) {
        printf("Failed to do memory allocation!\n");
        exit(1);
    } else {
        for (int i = 0; i < size; i++) {
            board2[i] = (char *) malloc(sizeof(char) * size);
            if (board2[i] == NULL) {
                printf("Failed to do memory allocation!\n");
                exit(1);
            }
        }
    }
    board = (char **) malloc(sizeof(char *) * size);
    if (board == NULL) {
        printf("Failed to do memory allocation!\n");
        exit(1);
    } else {
        for (int i = 0; i < size; i++) {
            board[i] = (char *) malloc(sizeof(char) * size);
            if (board[i] == NULL) {
                printf("Failed to do memory allocation!\n");
                exit(1);
            }
        }
    }
    printf("A Board is created for you with the size of %dx%d!\n", size, size);
    initializeBoard(board, size);
    while (finish != 0) {// finish changes in displayboard for controlling ending moment of game
        if (c % 2 == 0) {
            printf("\n--Player 1 Turn:--\n");
            displayBoard(size, board2, board, &start, row1, row2, column1, column2, &finish, &score1, &totscore1,
                         1);
            getCoordinates(&row1, &row2, &column1, &column2, size, board2);
            displayBoard(size, board2, board, &start, row1, row2, column1, column2, &finish, &score1, &totscore1,
                         2);
        } else {
            printf("\n--Player 2 Turn:--\n");
            displayBoard(size, board2, board, &start, row1, row2, column1, column2, &finish, &score2, &totscore2,
                         1);
            getCoordinates(&row1, &row2, &column1, &column2, size, board2);
            displayBoard(size, board2, board, &start, row1, row2, column1, column2, &finish, &score2, &totscore2,
                         2);
        }
        c++;
    }
    if (totscore1 < totscore2)
        printf("\n***Winner is Player 2!***");
    else if (totscore2 < totscore1)
        printf("\n***Winner is Player 1!***");
    else
        printf("***Draw!***");//I assume user gets "Draw" message when total scores of both Player 1 and Payer 2 are equal.
    printf("\nWould you like to play again (Y/N)?");
    scanf(" %c",&yesno);
    for (int i = 0; i < size; ++i) {
        free(board[i]);
    }
    free(board);
}while(yesno=='Y');
    return 0;
}
int boardSize(){
    int size;
    do {
        printf("Please specify the board size (2-30):");
        scanf("%d",&size);
        if(size>30 || size<2)
            printf("Board size can only be between 2-32!\n");
        else if(size%2==1)
            printf("Board size can only be a multiple of two!\n");
    } while (size%2==1 || size>30 || size<2);
    return size;
}
int initializeBoard(char **board,int size){
    int chr,rtrn=1;
    char *values;//array for all possible symbols
    values=(char*)malloc(sizeof(char)*(size*size));
    if(values==NULL){
        printf("Failed to do memory allocation!\n");
        rtrn=0;
        exit(1);
    }
    charactersarray(values,size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            do {
                chr=rand()%(size*size);
            }while(values[chr]==0);
            board[i][j]=values[chr];// I send randomly the symbols from "values" to board
            values[chr]=0;
        }
    }
    free(values);
    return rtrn;
}
void charactersarray(char *values,int size){//in this function I create array for all possible symbols in order to send the board randomly
    for (int i =0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            values[(i*size)+j]=33+i;
        }
    }
}
void getCoordinates(int *row1,int *row2,int *column1,int *column2,int size,char **board2){
    int chck;
    do {
        fflush(stdin);
        chck=1;
        printf("\nEnter the coordinates of doors to open:");
        scanf("(%d,%d) (%d,%d)", row1, column1, row2, column2);//Player only enter coordinates in the format of (row1,column1) (row2,column2)
        *row1=(*row1)-1;
        *row2=(*row2)-1;
        *column2=(*column2)-1;
        *column1=(*column1)-1;
        if ((*row1)+1 > size || (*row2)+1 > size || (*column1)+1 > size || (*column2)+1 > size) {
            printf("Sorry, wrong coordinates!");
            chck = 0;
        }
        else if(board2[*row1][*column1]!=64 || board2[*row2][*column2]!=64){// I control the position of doors if they are not "@" they already opened
            if(board2[*row1][*column1]!=64)
                printf("(%d,%d) already opened!",(*row1)+1,(*column1)+1);
            if(*row1==*row2 && *column1==*column2){
            }
            else if(board2[*row2][*column2]!=64)
                printf("\n(%d,%d) already opened!",(*row2)+1,(*column2)+1);
            chck = 0;
        }
        else if (*row2 == *row1 && *column2 == *column1) {
            printf("Sorry, two door coordinates are same!");
            chck = 0;
        }
    } while (chck==0);
}
void displayBoard(int size,char **board2,char **board,int *start,int row1,int row2,int clmn1,int clmn2,int *finish,int *score,int *totscore,int sequence){
    if(*start==1){// I create another board that contains "@"s. With "start" I create only one time.
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                board2[i][j]=64;
            }
        }
    }
    if(sequence==1){//"sequence" controls whether function displays the status of the board or to show the doors entered by the user
        printf(" ");
        for (int i = 0; i < size; ++i) {
            printf("%3.d",i+1);
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            if(i!=0)
                printf("\n");
            printf("%d",i+1);
            for (int j = 0; j < size; j++) {
                printf("%3.c",board2[i][j]);
            }
        }
    }
    else {
        board2[row1][clmn1] = board[row1][clmn1];//"board2" is '@' board, and "board" is the board that contains symbols
        board2[row2][clmn2] = board[row2][clmn2];
        printf(" ");
        for (int i = 0; i < size; ++i) {
            printf("%3.d",i+1);
        }
        printf("\n");
        for (int i = 0; i < size; i++) {
            if (i != 0)
                printf("\n");
            printf("%d",i+1);
            for (int j = 0; j < size; j++) {
                printf("%3.c", board2[i][j]);
            }
        }
        if(checkCharacters(board,row1,row2,clmn1,clmn2)==0){
            *score=-1;
            printf("\nUnlucky! Your score: %d, ",*score);
            board2[row1][clmn1]=64;//if coordinates are not same symbols I close the doors
            board2[row2][clmn2]=64;
        }
        else{
            *score=2;
            printf("\nLucky you! Your score: %d, ",*score);
            *finish=(*finish)-2;
        }
        (*totscore)+=(*score);
        printf("total score: %d",*totscore);
    }
    *start=0;
}
int checkCharacters(char **board,int row1,int row2,int clmn1,int clmn2){
    if(board[row1][clmn1]==board[row2][clmn2])
        return 1;
    else
        return 0;
}

