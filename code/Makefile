all: main.out scheduling.out output.out

#main file
main.out: main.c
	gcc -Wall -g -o main.out main.c

#bscheduling file
scheduling.out: b_scheduling.c
	gcc -Wall -g -o scheduling.out b_scheduling.c

#bscheduling file
output.out: output_only.c
	gcc -Wall -g -o output.out output_only.c -lm

deleteofiles:
	rm -f *.o
	rm -f *.txt
	
deleteexec:
	rm -f scheduling.out main.out output.out

deleteall: deleteexec deleteofiles