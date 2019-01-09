#include <stdio.h>
#include "moveCheckingFunctions.h"

//PURPOSE:: displays appropriate warnings
//NOTE:: currently there are only two error messages it displays, but this function
//is where any future warnings or error messages for the user will go
void warning(int warning)
{
    switch(warning)
    {
        case 1:
        {
            printf("error: there is ");
            printf("error: no piece at previous position\n"); 
            break;
        }
        default: printf("Invalid move\n"); break;
    }
}


int checkIfForward(int prev, int next, char * board, int type)
{
    //if there is an enemy in front cannot perform move, both pawns are stuck
    if(prev - next == 3 * type && board[next-1] != '.')
    {
        if(type != CPU)
            warning(0);
        return -1;
    }
    return 0;
}


int checkIfSideways(int prev, int next, int type)
{
    //cannot move sideways
    if(prev - next == -1 || prev - next == 1)
    {
        if(type != CPU)
            warning(0);
        return 1;
    }
    return 0;
}

int checkDiagonals (int prev, int next, char * board, int type, char enemyToken)
{
    switch(type)
    {
        case Player:
        {
            if(  (prev - next == 4 || prev - next == 2) 
                && board[next-1] != enemyToken)
            {
                warning(0);
            
                return -1;
            }
        }
        case CPU:
        {
            if(  (prev - next == -4 || prev - next == -2 ) 
                && board[next-1] != enemyToken)
            {
                return -1;
            }
        }
    }
    return 0;
}

int checkMoveBounds(int prev, int next, int type)
{
    if(prev < 0 || prev > 10 || next < 0 || next > 10 || prev == next)
    {
        warning(0);
        return -1;
    }
    if(prev - next < -4 && type == CPU)
        return -1;
    
    if(prev - next > 4 && type == 1)
        return -1;
    
    return 0;
}

int checkIfTokenExists(char * board, int prev, char enemyToken)
{
    if(enemyToken == 'X' && board[prev-1] != '0')
    {
        warning(1);
        return -1;
    }
    else if(enemyToken == '0' && board[prev-1] != 'X')
    {
        return -1;
    }
    return 0;
}