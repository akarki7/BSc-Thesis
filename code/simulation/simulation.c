#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h> /* for pid_t */
#include <signal.h>
#include <string.h>

volatile sig_atomic_t exitRequested = 0;

#define MAXPV 3
#define MAXProcPerPC 2 
int ProcPerPC[]={2,1,1};

float X, Y;
int SPEED=0, current_battery=100;

int wait[MAXPV][MAXProcPerPC];
void ExecuteBSchedule();
void ComputeWait();
int ReverseBinary(int k, int d);
void  INThandler(int sig);

void horizontal_alignment();
void forward();
void obstacle_avoidance();
void battery_check();

float left_meter_reading();
float right_meter_reading();
float forward_reading();
void battery_decrease();


int main (int argc, char *argv[])
{
	X = 0;
	Y= 0;
    signal(SIGINT,INThandler);
	
    ComputeWait();
	
    while(!exitRequested){
        ExecuteBSchedule();
        sleep(5);
    }

	return (0);
}

/*executes the bscheduling algorithm to get the required schedule*/
void ExecuteBSchedule() {
	int nmic, round; 
	int i,j;

	// compute the number of minor cycles
	nmic = (1<<MAXPV);

	// execute major cycle
	for(round=0; round < nmic; round++) {
		// execute minor cycle
		for(i=0; i<=MAXPV; i++){
			for(j=0; j<ProcPerPC[i]; j++){
				if(wait[i][j]==0) {
					printf ("p%d.%d ", i, j);		
					wait[i][j] = 1<<i;
				}
				wait[i][j]--;
			}
		}
		printf ("\n");		

	}
}

/*computes initial wait values for all the processes*/
void ComputeWait() {
	int start = 0; 
	int slots = 1;

	int i,j;

	for(i=0;  i<=MAXPV; i++) {
		for(j=0; j<ProcPerPC[i]; j++){
			wait[i][j] = ReverseBinary((start + j) % slots, i);
		}
		start = (start + ProcPerPC[i]) % slots;
		start = 2 * start;
		slots = 2 * slots;
	}
	
}

/*computes Reverse Binary of number k with d digits*/
int ReverseBinary(int k, int d){
	int tmp = 0;
	int i;

	if(d<1) return(0);

	for(i=0;i<d;i++){
		tmp = tmp<<1;
		tmp += k & 1;
		k = k>>1;
	}
	return(tmp);
}

void  INThandler(int sig)
{
    printf("\nExiting...\n");
    exitRequested=1;
}

void horizontal_alignment(){
	float h1= left_meter_reading();
	float h2 = right_meter_reading();

	float position;

	position = (h1+h2)/2;


}

void forward(){
	X= X + SPEED;
}

void obstacle_avoidance(){
	float reading = forward_reading();
	if (reading <=5){
		SPEED--;
	}
}

void battery_check(){
	if (current_battery <=30){
		printf("Need to charge or else battery will run out soon\n");
	}
}

float left_meter_reading(){
	// return a fake meter reading
	return 1;
}

float right_meter_reading(){
	return 1;
}

float forward_reading()
{
	return 5;
}

void battery_decrease(){
	current_battery--;
}