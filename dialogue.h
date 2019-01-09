/*
performs all introductory text prompts
dialogue.h
Author: Kent Spence
0872780
*/

//PURRPOSE:: asks if the user would want a tutorial, if yes, displays
//the tutorial.
void promptTutorial();

//PURPOSE:: prints how many games have been won by the CPU and the player.
//ARGUMENTS:: the number of computer wins, player wins, char * hexapawn board.
void gameStats(int CpuWins, int plyrWins, char * board);