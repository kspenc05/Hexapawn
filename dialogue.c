#include <stdio.h>
#include "dialogue.h"

//PURPOSE:: prints out the author and the company that designed the 
//original version of this game in BASIC.
void printAuthor()
{
    printf("\tHexapawn\n");
    printf("by Creative Computing Morristown, New Jersey\n\n");
}

//PURPOSE:: tells the user how to play the game, if they wanted a tutorial
void printTutorial()
{
    printf("This program plays the game of Hexapawn.\n");
    printf("Hexapawn is played with pawns on a 3 by 3 board.\n\n");
    
    printf("The pawns (or game pieces) are moved as in chess (in two ways):\n");
    printf("1. One space forward.\n");
    printf("2. One space diagonally to capture an oponent's piece.\n\n");
    
    printf("On the board:\n");
    printf("Your pawns are '0',\n");
    printf("the computer's pawns are 'X',\n");
    printf("and empty squares are '.' .\n\n");
    
    printf("In order to move:\n");
    printf("Type the number of the square you are moving from,\n");
    printf("followed by the number of the square you will move to.\n");
    printf("The numbers must be separated by a comma.\n");
    printf("eg., 4,5 , to move from square 4 to 5\n\n");
    
    printf("The computer starts a series of games knowing only \n");
    printf("when the game is won (draws are impossible) and how to move.\n");
    printf("It has no strategy at first and moves randomly.\n\n");
    
    printf("However, it learns from each game, so winning becomes \n");
    printf("progressively more difficult.\n\n");
    
    printf("To help offset your initial advantage of going first,\n");
    printf("you will not be told how to win the game,\n");
    printf("you must learn this by playing.\n\n");
    
    printf("The numbering of the board is as follows:\n");
    printf("with the real game board directly beside it for reference:\n\n");
    
    printf("\t123\tXXX\n\t456\t...\n\t789\t000\n\t\n\n");

    printf("For example, to move your rightmost pawn forward,\n");
    printf("You would type \"9,6\" in response to the question\n");
    printf("\"Your move?\".\n");
    printf("Since I'm a good sport, you'll always\n");
    printf("go first\n\n");
}

//PURPOSE:: asks the user if they would like a tutorial
//return 1 if they do, 0 if they would not.
void promptTutorial()
{
    char response [50];
    printAuthor();
    
    printf("Instructions (Y or N)?");
    fgets(response, 50, stdin);
    
    switch(response[0])
    {
        case 'y': case 'Y': printTutorial(); break;
    }
}

void gameStats(int CpuWins, int plyrWins, char * board)
{
    printf("I have won %d ", CpuWins);
    printf("and you have won %d ", plyrWins);
    printf("out of %d games\n", CpuWins + plyrWins);
}

