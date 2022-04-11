all: main.out scheduling.out

#main file
main.out: main.c
	gcc -Wall -g -o main.out main.c

#bscheduling file
scheduling.out: b_scheduling.c
	gcc -Wall -g -o scheduling.out b_scheduling.c

deleteofiles:
	rm -f *.o
	
deleteexec:
	rm -f scheduling.out main.out

deleteall: deleteexec deleteofiles