all: simulation.out simulation2.out

#main file
simulation.out: simulation.c
	gcc -Wall -g -o simulation.out simulation.c

simulation2.out: simulation_complex.c
	gcc -Wall -g -o simulation2.out simulation_complex.c	


deleteofiles:
	rm -f *.o
	rm -f *.txt
	
deleteexec:
	rm -f simulation.out simulation2.out

deleteall: deleteexec deleteofiles