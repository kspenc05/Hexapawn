#include <stdio.h>
#include "dialogue.h"
#include "boardFunctions.h"

int main()
{
    char board[9], buffer[10];
    int CpuWins, plyrWins;
    
    CpuWins = plyrWins = 0;

    promptTutorial();
    
    while(buffer[0] != 'N' && buffer[0] != 'n')
    {
        runGame(&CpuWins, &plyrWins, board);
        gameStats(CpuWins, plyrWins, board);
        
        printf("Would you like to play again? (Y or N)?\n");
        fgets(buffer, 10, stdin);
    }
    return 0;
}