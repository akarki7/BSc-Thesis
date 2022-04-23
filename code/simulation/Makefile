all: simulation.out

#main file
simulation.out: simulation.c
	gcc -Wall -g -o simulation.out simulation.c


deleteofiles:
	rm -f *.o
	
deleteexec:
	rm -f simulation.out

deleteall: deleteexec deleteofiles