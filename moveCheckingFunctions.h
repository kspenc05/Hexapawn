//"moveCheckingFunctions.h"
//Author:: Kent Spence
//0872780
//All functions that have to do with checking the user and CPU's moves.
//All functions (except warning()) return 0 if the input is correct, and -1 if 
//the inputted move is incorrect.

#define Player 1
#define CPU -1


//PURPOSE:: checks if forward move is legal. If there is another pawn in 
//the way, this move is not legal, and -1 is returned.
//ARGUMENTS:: previous position, next position, hexapawn board, and the type of player.
//-1 for CPU because CPU moves UP the board, eg. prev is 4, next is 7, so difference
//is -3, whereas if it is the player the difference is 3, not -3, since they move down.
int checkIfForward(int prev, int next, char * board, int type);


//PURPOSE:: checks if the move is sideways. No one is allowed to move sideways,
//CPU or human
//ARGUMENTS:: previous position, next position, and the type of player
int checkIfSideways(int prev, int next, int type);


//PURPOSE:: checks if diagonal moves are correct. 
//ARGUMENTS:: previous position, next position, character array for hex board,
//player type, and character symbol of enemy, eg. '0' for human, 'X' for CPU.
int checkDiagonals (int prev, int next, char * board, int type, char enemyToken);


//PURPOSE:: checks for illegal moves that are within array boundaries, but should
//not ever happen. 
//NOTE:: only made this for the AI, it would occasionally do game-breaking moves like
//4,9, which should not ever be possible, simply because the enemy was not on the square.
int checkMoveBounds(int prev, int next, int type);


//PURPOSE:: makes sure the previous position does have the proper character on it
//ARGUMENTS:: char array for hex board, previous position, and enemy character token.
//NOTE:: meant to prevent moves entered in which the player is not actually located.
int checkIfTokenExists(char * board, int prev, char enemyToken);