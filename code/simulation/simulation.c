#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h> /* for pid_t */
#include <signal.h>
#include <string.h>

int obstacles_x [] = {5,20,40};
int obstacles_y [] = {5,20,40};
// means the obstacles are at coordinates 5,5 20,20 and 40,40

volatile sig_atomic_t exitRequested = 0;

#define MAXPV 2
#define MAXProcPerPC 2 
int ProcPerPC[]={2,1,1};

float X, Y;
int SPEED=2, current_battery=100;

int wait[MAXPV][MAXProcPerPC];
void ExecuteBSchedule();
void ComputeWait();
int ReverseBinary(int k, int d);
void INThandler(int sig);

void horizontal_alignment();
void forward();
void obstacle_avoidance();
void battery_check();

float left_meter_reading();
float right_meter_reading();
float forward_reading();
void battery_decrease();
void execute_function(int i, int j);


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

	FILE *filePointer;
    filePointer = fopen("robot.txt", "a") ; 

	// compute the number of minor cycles
	nmic = (1<<MAXPV);

	// execute major cycle
	for(round=0; round < nmic; round++) {
		// execute minor cycle
		for(i=0; i<=MAXPV; i++){
			for(j=0; j<ProcPerPC[i]; j++){
				if(wait[i][j]==0) {
					// printf ("p%d.%d ", i, j);
					execute_function(i,j);
					printf("Speed = %d, X=%f, Y= %f, Battery=%d\n",SPEED,X,Y,current_battery);
					fprintf(filePointer,"%d %f %f %d\n",SPEED,X,Y,current_battery);	
					wait[i][j] = 1<<i;
				}
				wait[i][j]--;
			}
		}
		// printf ("\n");		
	}
	battery_decrease();
	fclose(filePointer);
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

void INThandler(int sig)
{
    printf("\nExiting...\n");
    exitRequested=1;
}

void horizontal_alignment(){
	float h1= left_meter_reading();
	float h2 = right_meter_reading();

	float position;

	position = (h1+h2)/2;
	Y=position;
}

void forward(){
	X= X + SPEED;
}

void obstacle_avoidance(){
	float reading = forward_reading();
	if ((reading <=5) && (SPEED > 0)){
		SPEED--;
	}
	if (SPEED == 0){
		Y=Y+1;
		obstacle_avoidance();
	}
}

void battery_check(){
	if (current_battery <=30){
		printf("Need to charge or else battery will run out soon\n");
	}
}

float left_meter_reading(){
	// return a fake meter reading
	return 4;
}

float right_meter_reading(){
	return 4;
}

float forward_reading()
{
	return 15;
}

void battery_decrease(){
	current_battery--;
}

void execute_function(int i, int j){
	//execute a function based on the value of i and j
	if (i==0){
		if(j==0){
			forward();
		}
		else{ // j==1 so this means only two processes are in PC=0
			obstacle_avoidance();
		}
	}
	else if (i==1)
	{
		if(j==0){
			horizontal_alignment();
		}	
	}
	else if (i==2){
		if(j==0){
			battery_check();
		}
	}
}