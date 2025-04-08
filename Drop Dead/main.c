
/**MUHAMMET SAIT BOZDEMIR-2584738**/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int roll_a_dice();
int play_computer(int);
int play_user(int);
void scoresheet(int,int,int);

int main() {
    int raundnum,firstuser,firstcomp,tot1=0,tot2=0;
    printf("Welcome to the Drop Dead game.\nLet's get started!\n");
    printf("How many rounds would you like to play?");
    scanf("%d",&raundnum);
    srand(time(NULL));
    do {
        firstuser = roll_a_dice();
        printf("\nI have rolled the dice for you and you got %d!\n", firstuser);
        firstcomp = roll_a_dice();
        printf("I have rolled the dice and got %d!", firstcomp);
        if(firstuser==firstcomp)
            printf("\nDraw,I will start again");
        else {
            if (firstcomp < firstuser) {
                for (int i = 1; i <= raundnum; ++i) {
                    tot1+= play_user(i);//total score of one round for user
                    tot2+= play_computer(i);// total score of one round for computer
                    scoresheet(tot1, tot2,i);
                }
                if(tot1<tot2)
                    printf("\nI AM THE WINNER!");
                else if(tot1>tot2)
                    printf("\nYOU ARE THE WINNER!");
                else
                    printf("\nDRAW!");// I assume that they are draw when their total score are equal
            }

            else {
                for (int i = 1; i <= raundnum; ++i){
                    tot1+= play_computer(i);
                    tot2+= play_user(i);
                    scoresheet(tot2, tot1,i);
                }
                //Conditions are different from above because of sequence of score_sheet function
                if(tot1>tot2)
                    printf("\nI AM THE WINNER!");
                else if(tot1<tot2)
                    printf("\nYOU ARE THE WINNER!");
                else
                    printf("\nDRAW!");
            }

        }
    }while(firstuser==firstcomp);// I assume computer rolls the dice again if they are draw at start.



    return 0;
}
int roll_a_dice(){
    return 1+rand()%6;
}
int play_user(int i)
{
    int dice1,dice2,dice3,dice4,dice5,x=0,score,totalscore=0,cntrl1=1,cntrl2=1,cntrl3=1,cntrl4=1,cntrl5=1;//cntrl's control case of dices 2 or 5
    printf("\n\nRaund %d -- Your turn\n", i);
    printf("Are you ready to play!\nI rolled them for you and you got\n");
    do {
        score=0;
        if(cntrl1==1)
        {
            dice1= roll_a_dice();
            printf("[Dice 1]: %d  ",dice1);
            if(dice1==2||dice1==5)
                cntrl1=0;
        }

        if(cntrl2==1)
        {
            dice2= roll_a_dice();
            printf("[Dice 2]: %d  ",dice2);
            if(dice2==2||dice2==5)
                cntrl2=0;
        }

        if(cntrl3==1){
            dice3= roll_a_dice();
            printf("[Dice 3]: %d  ",dice3);
            if(dice3==2||dice3==5)
                cntrl3=0;}

        if(cntrl4==1){
            dice4= roll_a_dice();
            printf("[Dice 4]: %d  ",dice4);
            if(dice4==2||dice4==5)
                cntrl4=0;}

        if(cntrl5==1){
            dice5= roll_a_dice();
            printf("[Dice 5]: %d  ",dice5);
            if(dice5==2||dice5==5)
                cntrl5=0;}

        if((((cntrl1==0 || cntrl2==0 )|| cntrl3==0) || (cntrl4==0)) || cntrl5==0){//if dices are 2 or 5 their "cntrl"s change
            score=0;
            totalscore+=score;
            printf("\nYour score: %d Total score: %d\n",score,totalscore);

            if(cntrl1==0){
                printf("Dice 1 ");
                cntrl1=2;
                dice1=0;}
            if(cntrl2==0){
                printf("Dice 2 ");
                cntrl2=2;
                dice2=0;}
            if(cntrl3==0){
                printf("Dice 3 ");
                cntrl3=2;
                dice3=0;}
            if(cntrl4==0){
                printf("Dice 4 ");
                cntrl4=2;
                dice4=0;}
            if(cntrl5==0){
                printf("Dice 5 ");
                cntrl5=2;
                dice5=0;}
            printf("are excluded\n\n");
            if((cntrl1==2 && cntrl2==2) && (cntrl3==2 && cntrl4==2) && cntrl5 == 2)
                printf("Drop Dead\n");
            else
                printf("I rolled and you got\n");

        }

        else{
            score=dice1+dice2+dice3+dice4+dice5;
            totalscore+=score;
            printf("\nYour score: %d Total score: %d\n\n",score,totalscore);
            printf("I rolled and you got\n");}


    }while((cntrl3==1 || cntrl2==1) || (cntrl1==1 || cntrl4==1) || cntrl5==1);
    return totalscore;
}
int play_computer(int i)
{
    int dice1,dice2,dice3,dice4,dice5,x=0,score,totalscore=0,cntrl1=1,cntrl2=1,cntrl3=1,cntrl4=1,cntrl5=1;//"cntrl"s control case of dices 2 or 5
    printf("\n\nRaund %d -- My turn\n", i);
    printf("I got\n");
    do {
        score=0;
        if(cntrl1==1)
        {
            dice1= roll_a_dice();
            printf("[Dice 1]: %d  ",dice1);
            if(dice1==2||dice1==5)
                cntrl1=0;
        }

        if(cntrl2==1)
        {
            dice2= roll_a_dice();
            printf("[Dice 2]: %d  ",dice2);
            if(dice2==2||dice2==5)
                cntrl2=0;
        }

        if(cntrl3==1){
            dice3= roll_a_dice();
            printf("[Dice 3]: %d  ",dice3);
            if(dice3==2||dice3==5)
                cntrl3=0;}

        if(cntrl4==1){
            dice4= roll_a_dice();
            printf("[Dice 4]: %d  ",dice4);
            if(dice4==2||dice4==5)
                cntrl4=0;}

        if(cntrl5==1){
            dice5= roll_a_dice();
            printf("[Dice 5]: %d  ",dice5);
            if(dice5==2||dice5==5)
                cntrl5=0;}

        if((((cntrl1==0 || cntrl2==0 )|| cntrl3==0) || (cntrl4==0)) || cntrl5==0){//if dices are 2 or 5 their "cntrl"s change
            score=0;
            totalscore+=score;
            printf("\nMy score: %d Total score: %d\n",score,totalscore);

            if(cntrl1==0){
                printf("Dice 1 ");
                cntrl1=2;
                dice1=0;}
            if(cntrl2==0){
                printf("Dice 2 ");
                cntrl2=2;
                dice2=0;}
            if(cntrl3==0){
                printf("Dice 3 ");
                cntrl3=2;
                dice3=0;}
            if(cntrl4==0){
                printf("Dice 4 ");
                cntrl4=2;
                dice4=0;}
            if(cntrl5==0){
                printf("Dice 5 ");
                cntrl5=2;
                dice5=0;}
            printf("are excluded\n\n");
            if((cntrl1==2 && cntrl2==2) && (cntrl3==2 && cntrl4==2) && cntrl5 == 2)
                printf("Drop Dead\n");
            else
                printf("I got\n");

        }

        else{
            score=dice1+dice2+dice3+dice4+dice5;
            totalscore+=score;
            printf("\nMy score: %d Total score: %d\n\n",score,totalscore);
            printf("I got\n");}


    }while((cntrl3==1 || cntrl2==1) || (cntrl1==1 || cntrl4==1) || cntrl5==1);
    return totalscore;

}
void scoresheet(int user,int comp,int i){
    printf("Our scoresheet after round %d:\n",i);
    printf("=============================\n");
    printf("My score        Your score\n");
    printf("   %d               %d",comp,user);
}


