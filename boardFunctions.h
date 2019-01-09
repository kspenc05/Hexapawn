/*
boardFunctions.h
Author: Kent Spence
087280
In order to run hexapawn, call runGame(), and this will run through 1 game of 
hexapawn. The other functions in boardFunctions.h, are helper functions for
runGame().
*/


//PURPOSE:: Runs 1 game of hexapawn, calls all the required functions in boardFunctions.c
//ARGUMENTS:: the current number of CPU wins, the current number of
//player wins, and the char array hexapawn board to play on.
void runGame(int * CpuWins, int * plyrWins, char * board);