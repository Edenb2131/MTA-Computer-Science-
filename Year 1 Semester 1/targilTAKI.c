//
// Created by Eden Bar on 21/12/2021.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h> // in order to use the "rand" and "srand" functions
#include <time.h>	// in order to use "time" function

#define MAX_NAME 21
#define MAX_PLAYERS 10
#define NUM_OF_FIRST_WITHDRAW 4
#define RAND_COLOR 4
#define MAX_CARDS 50
#define NUM_OF_ALL_CARDS 14
#define PLUS_CARD 10
#define STOP_CARD 11
#define TAKI_CARD 12
#define COLOR_CARD 13
#define CHANGE_CARD 14
#define RED_COLOR 1
#define RED_COLOR_NAME 'R'
#define BLUE_COLOR 2
#define BLUE_COLOR_NAME 'B'
#define YELLOW_COLOR 3
#define YELLOW_COLOR_NAME 'Y'
#define GREEN_COLOR 4
#define GREEN_COLOR_NAME 'G'

//Declaring the struct Cards
struct Card{
    int card;  // Card num or symbol
    char color; // Color of cards(if he has any)
};
typedef struct Card Card;

//Declaring the struct Player
struct Player{
    char name[MAX_NAME]; // name of player
    Card* cards; // Cards array
    int numberOfCards; // how much cards are there
};
typedef struct Player Player;

//Declaring the struct Stats
struct Stats{
    int c; // Card number
    int rep; // repetition
};
typedef struct Stats Stats;

//printing welcome massage
void welcomeMassage();

//Getting players names
void gettingPlayerNames(Player* players, int numOfPlayers);

//Allocating new memory for another card
Player* pReAlloc(Card* cards ,int size ,int newSize, Player* player);

//Print Card
void printCard(int num, char color);

//print Player Cards
void printPlayerCards(Player* player);

//Withdraw Card
void withdrawCard(Player* player, Stats stats[]);

//Withdraw first UpperCard
void withdrawUpperCard(Card* c);

//Giving all the players 4 cards to start with
void withdrawFourCards(Player player[], int numOfPlayers,Stats stats[]);

//Updating upper card
void updateUpperCard(Card* c, int newNum, char newColor);

//Players decision to play
void playerMove(Player* player, int* currentTurn, Card* c,bool* direction, Stats stats[],int numOfPlayers);

//If player chose color card
void choseColorCard(Card* c, int PlayersChoiceOfColor);

//If player chose Taki Card
void choseTakiCard(Player* player, int choice, Card* c,int* newNum,char* newColor);

//Who's turn is it now ?
int whosTurn(int numOfPlayers, int currentTurn, bool direction);

//Remove Card for player's deck
void removerCard(Player* player, int place);

//initialize Stats
void iniStats(Stats stats[]);

//Sorting stats
Stats* merge(Stats stats1[],int size1, Stats stats2[], int size2);

//The merge sort algorithm
void mergeSort(Stats stats[], int size);

//copy Stats Array
void copyStatsArr(Stats statsDest[], Stats statsSrc[], int size);

//Someone won the game
bool winTheGame(Player player[], int numOfPlayers, char* nameOfWinner);

void main(){
    //Player players[] = {};
    Card upperCard = {};
    int numOfPlayers ,currentTurn = 0, i;
    char nameOfWinner[] = {};
    Stats stats[NUM_OF_ALL_CARDS] = {};

    //initializing stats
    iniStats(stats);

    //direction = ture -> the game is from player 1 to the last player
    //direction = false -> the game is from the last player to the first
    bool direction = true;

    //printing welcome massage
    welcomeMassage();

    printf("Please enter the number of players:\n");
    scanf("%d",&numOfPlayers);

    //allocating memory for the amount of player the play the game
    Player* players = (Player*) malloc(numOfPlayers * sizeof(Player));

    //Getting input for player names
    gettingPlayerNames(players, numOfPlayers);

    //Withdrawing 4 cards for each player
    withdrawFourCards(players, numOfPlayers,stats);

    //Withdrawing UpperCard for the deck
    withdrawUpperCard(&upperCard);

    //GameLoop
    while(!(winTheGame(players, numOfPlayers, nameOfWinner))){


        printf("Upper card:");
        printCard(upperCard.card, upperCard.color);

        printf("\n");

        printf("%s's turn:\n", players[currentTurn].name);
        printPlayerCards(&players[currentTurn]);

        playerMove(&players[currentTurn],&currentTurn, &upperCard, &direction,stats,numOfPlayers);



        currentTurn = whosTurn(numOfPlayers,currentTurn, direction);


    }

    //winner statement
    printf("The winner is... %s! Congratulations!\n",nameOfWinner);

    //sorting stats array to the display the most used cards
    //sortStats(stats);
    mergeSort(stats,NUM_OF_ALL_CARDS);

    //stats statement
    printf("************ Game Statistics ************\n");
    printf("Card # | Frequency\n");
    printf("__________________\n");

    //printing the stats
    for(i = 0; i < NUM_OF_ALL_CARDS; i ++){
        switch (stats[i].c) {
            case PLUS_CARD:
                printf("   +   ");
                break;
            case STOP_CARD:
                printf(" STOP  ");
                break;
            case TAKI_CARD:
                printf(" TAKI  ");
                break;
            case COLOR_CARD:
                printf(" COLOR ");
                break;
            case CHANGE_CARD:
                printf("  <->  ");
                break;
            default:
                printf("   %d   ",stats[i].c);
                break;

        }

        printf("|    %d\n",stats[i].rep);
    }

    //end of main
}


//printing welcome massage
void welcomeMassage(){

    printf("************  Welcome to TAKI game !!! ***********\n");

    //initializing time and random
    srand(time(NULL));

}

//Getting players names
void gettingPlayerNames(Player* players, int numOfPlayers){

    int i;

    //used code when didn't use dynamic memory
//    printf("Please enter the number of players:\n");
//    scanf("%d",&numOfPlayers);

//    players = (Player*) malloc(numOfPlayers * sizeof (Player));

    for(i = 0; i<numOfPlayers; i++){
        printf("Please enter the first name of player #%d:",(i+1));
        scanf("%s",players[i].name);
        printf("\n");
    }

}

//Allocating new memory for another card
Card* cReAlloc(Card* cards, int size ,int newSize, Player* players) {

    Card* newCards = (Card*)malloc(newSize * sizeof(Card));
    int i;

    //Check if memory allocation succeed
    if (newCards) {

        //copy cards into newCards
        for(i = 0; i<size && i< newSize; i++) {
            newCards[i].card = cards[i].card;
            newCards[i].color = cards[i].color;
        }

        free(cards);
        return newCards;
    }
    else {
        exit(1);
    }

}

//Print Card
void printCard(int num, char color){

    printf("\n*********\n");
    printf("*       *\n");

    switch (num) {
        case PLUS_CARD:
            printf("*   +   *\n");
            break;
        case STOP_CARD:
            printf("*  STOP *\n");
            break;
        case TAKI_CARD:
            printf("*  TAKI *\n");
            break;
        case COLOR_CARD:
            printf("* COLOR *\n");
            break;
        case CHANGE_CARD:
            printf("*  <->  *\n");
            break;
        default:
            printf("*   %d   *\n",num);
            break;

    }

    printf("*   %c   *\n",color);

   // printf("*       *\n");

    printf("*       *\n");
    printf("*********\n");


}

//print Player Cards
void printPlayerCards(Player* player){
    int i;
    for(i = 0; i< (*player).numberOfCards ;i++ ) {
        printf("Card #%d",i+1);
        printCard((*player).cards[i].card, (*player).cards[i].color);
    }
}

//Withdraw Card
void withdrawCard(Player* player,Stats stats[]){

    //reallocating new memory for another card
     player->cards = cReAlloc(player->cards,player->numberOfCards,player->numberOfCards+1,player);

     //rolling random numbers
     int num = 1 + (rand() % NUM_OF_ALL_CARDS); // random card number or special card
     int color = 1 + (rand() % RAND_COLOR); // random color

     player->cards[player->numberOfCards].card = num; // assigning the random card to the player's deck

     stats[num-1].rep++; // updating stats

     //assigning color to the player's new card
    if(num != COLOR_CARD) {
        switch (color) {
            case RED_COLOR:
                player->cards[player->numberOfCards].color = RED_COLOR_NAME;
                break;
            case BLUE_COLOR:
                player->cards[player->numberOfCards].color = BLUE_COLOR_NAME;
                break;
            case YELLOW_COLOR:
                player->cards[player->numberOfCards].color = YELLOW_COLOR_NAME;
                break;
            case GREEN_COLOR:
                player->cards[player->numberOfCards].color = GREEN_COLOR_NAME;
                break;
            default:
                break;
        }
    }

    else
        player->cards[player->numberOfCards].color = ' ';

    (*player).numberOfCards++; //updating player's new number of cards in the deck
}

//Withdraw first UpperCard
void withdrawUpperCard(Card* c){

    int num = 1 + (rand() % NUM_OF_ALL_CARDS);

    while(num > 9)
        num = 1 + (rand() % NUM_OF_ALL_CARDS);

    int color = 1 + rand() % RAND_COLOR;

    (*c).card = num;

    switch (color) {
        case RED_COLOR:
            (*c).color = RED_COLOR_NAME;
            break;
        case BLUE_COLOR:
            (*c).color = BLUE_COLOR_NAME;
            break;
        case YELLOW_COLOR:
            (*c).color = YELLOW_COLOR_NAME;
            break;
        case GREEN_COLOR:
            (*c).color = GREEN_COLOR_NAME;
            break;
        default:
            break;
    }
}

//Giving all the players 4 cards
void withdrawFourCards(Player player[], int numOfPlayers, Stats stats[]){

    int i,j;
    for(i = 0; i< numOfPlayers ; i++)
        for(j = 0; j < NUM_OF_FIRST_WITHDRAW ; j++){
            withdrawCard(&player[i], stats);
        }

//    for(i = 0; i< numOfPlayers ; i++)
//        for(j = 0; j < NUM_OF_FIRST_WITHDRAW ; j++)
//            printCard(player[i].cards[j].card,player[i].cards[j].color);



}

//Updating upper card
void updateUpperCard(Card* c, int newNum, char newColor){

    c->card = newNum;
    c->color = newColor;
}

//Players decision to play
void playerMove( Player* player, int* currentTurn, Card* c,bool* direction,Stats stats[] ,int numOfPlayers){

    int playerPress;
    int choice = -1;
    bool canContinue = false;

    while(!canContinue) {

        printf("Please enter 0 if you want to take a card from the deck\n");
        printf("or 1-%d if you want to put one of your cards in the middle:\n", (player)->numberOfCards);
        scanf("%d", &playerPress);

        if (playerPress == 0) {
            withdrawCard(player,stats);
            canContinue = true;
        }

        else if ((*player).cards[playerPress-1].card == COLOR_CARD) {

            printf("Please enter your color choice:\n");
            printf("1 - Yellow\n");
            printf("2 - Red\n");
            printf("3 - Blue\n");
            printf("4 - Green\n");
            scanf("%d", &choice);

            choseColorCard(c,choice);
            removerCard(player,playerPress-1);

            canContinue = true;

        }

        else if ((*player).cards[playerPress-1].card == TAKI_CARD && (*player).cards[playerPress-1].color == (*c).color) {

            printf("Please enter 0 if you want to finish your turn\n");
            printf("or 1-%d if you want to put one of your cards in the middle:\n", (*player).numberOfCards);
            scanf("%d", &choice);
            int newNum;
            char newColor;
            while(choice != 0){

                choseTakiCard(player, choice, c,&newNum, &newColor);
                printf("Please enter 0 if you want to finish your turn\n");
                printf("or 1-%d if you want to put one of your cards in the middle:\n", (*player).numberOfCards);
                scanf("%d", &choice);

            }

            updateUpperCard(c,newNum,newColor);
            canContinue = true;
        }

        else if ((*player).cards[playerPress-1].card == PLUS_CARD && (*player).cards[playerPress-1].color == (*c).color) {

            *currentTurn = *currentTurn - 1;
            updateUpperCard(c,(*player).cards[playerPress-1].card,(*player).cards[playerPress-1].color);
            removerCard(player,playerPress-1);

            //if PLUS was last card, withdrawing another card
            if(player->numberOfCards== 0)
                withdrawCard(player,stats);

            canContinue = true;

        }

        else if((*player).cards[playerPress-1].card == CHANGE_CARD && (*player).cards[playerPress-1].color == (*c).color){

            if(*direction)
                *direction = false;
            else
                *direction = true;

            removerCard(player,playerPress-1);
            canContinue= true;

        }

        else if((*player).cards[playerPress-1].card == STOP_CARD && (*player).cards[playerPress-1].color == (*c).color){

            if(numOfPlayers != 1)
                *currentTurn = *currentTurn + 1;
            updateUpperCard(c,(*player).cards[playerPress-1].card,(*player).cards[playerPress-1].color);
            removerCard(player,playerPress-1);

            //if STOP was last card, withdrawing another card
            if(player->numberOfCards== 0)
                withdrawCard(player,stats);


            canContinue = true;
        }

        else if((*player).cards[playerPress-1].card == (*c).card || (*player).cards[playerPress-1].color == (*c).color){

            updateUpperCard(c,player[*currentTurn].cards[playerPress - 1].card,player[*currentTurn].cards[playerPress - 1].color);
            //printf("Card was updated!\n");
            removerCard(player,playerPress-1);
            canContinue = true;
        }

        else
            printf("Invalid choice! Try again.\n");
    }

}

//If player chose color card
void choseColorCard(Card* c, int playersChoiceOfColor){

    c->card = COLOR_CARD;
    switch (playersChoiceOfColor) {
        case 1:
            c->color = YELLOW_COLOR_NAME;
            break;
        case 2:
            c->color = RED_COLOR_NAME;
            break;
        case 3:
            c->color = BLUE_COLOR_NAME;
            break;
        case 4:
            c->color = GREEN_COLOR_NAME;
            break;
        default:
            printf("Invalid choice! Try again.");
    }

}

//Remove Card for player's deck
void removerCard(Player* player, int place){
    //Card temp = {};
    int i;
    for( i = place; i < player->numberOfCards - 1; i++){
        player->cards[i].card = player->cards[i+1].card;
        player->cards[i].color = player->cards[i+1].color;
    }

    player->cards[player->numberOfCards].card = ' ';
    player->cards[player->numberOfCards].color = ' ';

    player->numberOfCards--;
}

//If player chose TAKI Card
void choseTakiCard(Player* player, int choice, Card* c,int* newNum,char* newColor){

    if((*player).cards[choice-1].color == c->color) {
        *newNum = player->cards[choice-1].card;
        *newColor = player->cards[choice-1].color;
        removerCard(player, choice);

    }
}

//Who's turn is it now ?
int whosTurn(int numOfPlayers, int currentTurn, bool direction){

    if(direction) {

        if (currentTurn == numOfPlayers - 1)
            return 0;
        else
            return (currentTurn + 1);
    }

    else{
        if (currentTurn == 0)
            return numOfPlayers-1;
        else
            return (currentTurn - 1);

    }
}

//initialize Stats
void iniStats(Stats stats[]){

    int i;
    for(i = 0; i < NUM_OF_ALL_CARDS; i ++){
        stats[i].c = i+1;
        stats[i].rep = 0;
    }

}

//Sorting stats - merge sort
//void sortStats(Stats stats[]){
//
//    int i, j;
//    Stats temp;
//    for (i = 0; i < NUM_OF_ALL_CARDS - 1; i++)
//        for (j = 0; j < NUM_OF_ALL_CARDS - i - 1; j++){
//         if(stats[j].rep < stats[j+1].rep) {
//             temp = stats[j];
//             stats[j] = stats[j + 1];
//             stats[j+1] = temp;
//         }
//        }
//}

//Sorting stats
Stats* merge(Stats stats1[],int size1, Stats stats2[], int size2){

    int ind1, ind2,resInd;
    Stats* res = (Stats*) malloc((size1+size2) * sizeof(Stats));

    if(res){

        ind1 = ind2 = resInd = 0;

        while( (ind1 < size1) && (ind2 < size2)){
            if(stats1[ind1].rep >= stats2[ind2].rep){
                res[resInd].rep = stats1[ind1].rep;
                res[resInd].c = stats1[ind1].c;
                ind1++;
            }
            else{
                res[resInd].rep = stats2[ind2].rep;
                res[resInd].c = stats2[ind2].c;
                ind2++;
            }
            resInd++;
        }
        while(ind1 < size1){
            res[resInd].rep = stats1[ind1].rep;
            res[resInd].c = stats1[ind1].c;
            ind1++;
            resInd++;
        }

        while(ind2 < size2){
            res[resInd].rep = stats2[ind2].rep;
            res[resInd].c = stats2[ind2].c;
            ind2++;
            resInd++;
        }

    }

    else{
        printf("Memory allocation failure !");
        exit(1);
    }
    return res;
}

//The merge sort algorithm
void mergeSort(Stats stats[], int size){
    Stats* tempStats = NULL;
    if(size <= 1)
        return;

    mergeSort(stats, (size/2));
    mergeSort(stats + (size/2), size - (size/2));
    tempStats = merge(stats,size/2,stats + (size/2),size - (size/2));

    if (tempStats){

        copyStatsArr(stats,tempStats,size);
        free(tempStats);
    }
    else{

        printf("Memory allocation failure !\n");
        exit(1);
    }

}

//copy Stats Array
void copyStatsArr(Stats statsDest[], Stats statsSrc[], int size){

    int i;

    for(i = 0; i <size; i++) {
        (statsDest + i)->c = (statsSrc + i)->c;
        (statsDest + i)->rep = (statsSrc + i)->rep;
    }
}

//Someone won the game
bool winTheGame(Player* player, int numOfPlayers, char nameOfWinner[]){


    int i;
    for(i = 0; i<numOfPlayers; i++)
        if(player[i].numberOfCards == 0){
            strcpy(nameOfWinner,player[i].name);
            return true;
        }

    return false;

}
