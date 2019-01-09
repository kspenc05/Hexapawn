hexapawn: dialogue.o board.o
	gcc -Wall -pedantic -std=c99 hexapawn.c dialogue.o moveCheckingFunctions.c board.o -o hexapawn

dialogue.o:
	gcc -c -Wall -pedantic -std=c99 dialogue.c

board.o: 
	gcc -c -Wall -pedantic -std=c99 boardFunctions.c -o board.o

clean:
	rm hexapawn *.o
    