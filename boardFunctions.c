#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "moveCheckingFunctions.h"
#include "boardFunctions.h"

#define BoardSize 9

//PURPOSE:: prints out the board
//ARGUMENTS:: the board
void printBoard(char * board)
{
    int i;
    printf("\n\t");
    for(i=0; i < BoardSize; i++)
    {
        printf("%c", board[i]);
        if( (i+1) % 3 == 0 && i != 0)
        {
            printf("\n\t");
        }
    }
    printf("\n");
}

//PURPOSE:: initializes board
//Arguments:: the game board
void initBoard(char * board)
{
    strcpy(board, "XXX...000");
}


//PURPOSE:: the standard move function, moves the char token to the space
//specified by next, from the position of prev.
//ARGUMENTS:: the char array for the hexapawn board, the (int) previous position,
//int next position, and the character token to put at next.
void move(char * board, int prev, int next, char token)
{
    if(board[prev-1] == token)
    {
        board[prev-1] = '.';
        board[next-1] = token;
    }
}


//PURPOSE:: takes in the prev and next positions, and then checks if the move is valid.
//
//ARGUMENTS:: the char * game board, the previous position, the next position,
//and the int type.
//
//NOTE:: the int type arg is to differentiate between CPU and player moves.
//returns an integer below 0 if move is invalid, and 0 if valid.
int isValidPlayerMove(char * board, int prev, int next, int type)
{
    char enemyToken;
    
    switch(type)
    {
        case Player: enemyToken = 'X'; break;
        case CPU: enemyToken = '0'; break;
    }
    return checkIfForward(prev, next, board, type) +
            checkIfSideways(prev, next, type) +
            checkDiagonals(prev, next, board, type, enemyToken) +
            checkMoveBounds(prev, next, type) +
            checkIfTokenExists(board, prev, enemyToken);
}

//PURPOSE:: checks if there is a tie or not, 1. by checking how many X's and 0's 
//2. if they are all lined up vertically, and 3. checks if there are any
//horizontally next to each other that could attack diagonally, and then 4. if there
//are either player still has pieces left.
//ARGUMENTS:: the char array hex board.
//returns 1 if there is a tie, 0 if there is not.
int tie (char * board)
{
    int i, X[3], Xnum, O[3], Onum, blockedPieces, total;
    Xnum = Onum = blockedPieces = 0;
    for(i=0; i < BoardSize; i++)
    {
        switch(board[i])
        {
            case '0': O[Onum++] = i; break;
            case 'X': X[Xnum++] = i; break;
        }
    }
    if(Onum == 0 || Xnum == 0)
        return 1;
    
    if(Onum >= Xnum)
       total = Onum;
       
    else if(Onum < Xnum)
       total = Xnum;
    
    for(i=0; i < total; i++)
    {
        if(O[i] - X[i] == 3)
        {
            if(board[O[i] + 1] != 'O' && board[X[i] + 1] != 'X')
            {
                if(board[O[i] - 1] != 'O' && board[X[i] - 1] != 'X')
                {
                    blockedPieces++;
                }
            }
        }
    }
    
    //if deadlock occurs
    if(blockedPieces == total)
        return 1;
    else
        return 0;
}

//PURPOSE:: checks if game is won yet or not
//ARGUMENTS:: the character array for the hexapawn board.
//returns 1 if human player has won, 2 if CPU player won,
//and 0 if neither side has won yet.
int gameWon(char * board)
{
    if(board[0] == '0' || board[1] == '0' || board[2] == '0')
    {
        return 1;
    }
    if(board[6] == 'X' || board[7] == 'X' || board[8] == 'X')
    {
        return 2;
    }

    return 0;
}

//PURPOSE:: moves the player (includes prompt to get where the player wants to move)
//ARGUMENTS:: char array hexapawn board
//NOTE:: returns -1, if bad input, 7 if human player won the game, 5 if the human
//player caused a tie, otherwise it returns 0.
int playerMove(char * board)
{
    char buffer[50], garbage;
    int prev, next;

    printf("Your move?: ");
    
    fgets(buffer, 50, stdin);
    sscanf(buffer, "%d%c%d", &prev, &garbage, &next);
    printf("\n");
    
    
    if(isValidPlayerMove(board, prev, next, Player) != 0)
        return -1;

    else
        move(board, prev, next, '0');
    
    if(gameWon(board) == 1 || tie(board) == 1)
    {
        printBoard(board);
        
        if(gameWon(board) == 1) 
        {
            return 7;
        }
        else if(tie(board) == 1)
        {
            return 5;
        }
    }
    return 0;
}

//PURPOSE:: goes through hexapawn board, and counts how many pawns the CPU has
//ARGUMENTS:: the character array hexapawn board, and a pointer to an int array of 3
//to store the values of where the X's are located.
//Returns:: the number of X's/pawns the CPU still has.
int getNumXs(char * board, int * X)
{
    int i, num; //there are a maximum of 3 X's on the board
    num = 0;
    for(i=0; i < BoardSize; i++)
    {
        if(board[i] == 'X')
        {
            X[num] = i;
            num++;
        }
    }
    return num;
}

//PURPOSE:: moves the CPU, as well as helps it determine a move,
//it does this by picking a random piece on the board, and attempting to move it,
//left, center and then right if possible.
//Returns:: 7 if the computer won, 5 if the computer caused a tie to happen (losing)
//otherwise 0 if nothing significant happened.
int cpuMove(char * board)
{
    //X[3] = array for all possble X's on board
    int prev, next, status, i, X[3];
    status = -1;

    //let the user know the computer is doing something
    printf("\nI'm thinking...\n");
    
    
    //loop will keep exeucting until it generates a randomized move that is legal
    do
    {
        srand(time(NULL));
        prev = X[ rand() % getNumXs(board, X) ] + 1;
        
        if(prev >= 0 && prev < 4)
        {
            next = 4; 
        }
        else if (prev >= 4 && prev < 7)
        {
            next = 7;
        }
        
        for(i=0; i < 3; i++)
        {
            status = isValidPlayerMove(board, prev, next, CPU);
            
            if(status == 0)
                break;
                
            next++;
        }
    } while(status < 0);
    
    move(board, prev, next, 'X');
    
    printf("I moved from %d to %d\n", prev, next);
    
    if(gameWon(board) == 2 || tie(board) == 1)
    {
        printBoard(board);
        
        if(gameWon(board) == 2)
        {
            return 7;
        }
        if(tie(board) == 1)
        { 
            return 5;
        }
    }
    return 0;
}

//PURPOSE:: determines if it should print "I" or "You"
//ARGUMENTS:: the type (is it the CPU or the player)
void determinePronoun(int type)
{
    switch(type)
    {
        case Player: printf("You "); break;
        case CPU: printf("I "); break;
    }
}

//PURPOSE:: displauys proper text for a win, and updates wins
//ARGUMENTS:: type (whether it is cpu or player, and address for number
//of wins.
void victoryConditionWin(int type, int * wins)
{
    determinePronoun(type);
    printf("win!\n");
    *wins = *wins + 1;
}

//PURPOSE:: swaps the value of the type to the other type
void swapTypes (int * type)
{
    switch(*type)
    {
        case Player: *type = CPU; break;
        case CPU: *type = Player; break;
    }
}

//PURPOSE:: displays proper text for a tie, and updates wins
//ARGUMENTS:: the type (whether it's CPU or player), and the address for
//number of wins.
void victoryConditionTie(int type, int * wins)
{
    swapTypes(&type);
    determinePronoun(type);
    printf("can't move so ");
    
    swapTypes(&type);
    determinePronoun(type);
    printf("win!\n");
    
    *wins = *wins + 1;
}

//PURPOSE:: if gameCondition is 7 or 5, will determine whether or
//not it is a tie or a win.
//ARGUMENTS:: current game condition, the player type,
//the address of the player's wins, and the address of the cpu's wins.
void determineGameCondition(int gameCondition, int type, 
    int * plyrWins, int * CpuWins)
{
    if(gameCondition == 7) // If there is a tie
    {
        if(type == Player)
            victoryConditionWin(type, plyrWins);
        
        else if(type == CPU)
            victoryConditionWin(type, CpuWins);
    }
    else if(gameCondition == 5) //if there is a win
    {
        if(type == CPU) //if cpu caused
            victoryConditionTie(type, CpuWins);
        
        else if(type == Player) //if player caused 
            victoryConditionTie(type, plyrWins);
    }
}

void runGame(int * CpuWins, int * plyrWins, char * board)
{
    int gameCondition;
    
    initBoard(board);
    printBoard(board);
    
    while(gameCondition != 7 && gameCondition != 5)
    {
        //keeps prompting user for move, until move is valid
        while((gameCondition = playerMove(board)) < 0);
        
        if(gameCondition != 0)
            determineGameCondition(gameCondition, Player, plyrWins, CpuWins);
        else  
            printBoard(board);
        
        if(gameCondition == 7 || gameCondition == 5)
            break;
        
        if( (gameCondition = cpuMove(board)) != 0)
            determineGameCondition(gameCondition, CPU, plyrWins, CpuWins);
        else
            printBoard(board);
    }
}