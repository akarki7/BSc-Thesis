#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h> /* for pid_t */
#include <signal.h>
#include <string.h>

struct stack
{
    int maxsize;    // define max capacity of the stack
    int top;
    int *items;
};

// Utility function to initialize the stack
struct stack* newStack(int capacity)
{
    struct stack *pt = (struct stack*)malloc(sizeof(struct stack));
 
    pt->maxsize = capacity;
    pt->top = -1;
    pt->items = (int*)malloc(sizeof(int) * capacity);
 
    return pt;
}

// in another file create structure for stack
// then create stacks for left_reading, right_reading and each time the function is called pop one and return the popped data
struct stack *obstacles_x;
struct stack *obstacles_y;
struct stack *left_readings; //h1
struct stack *right_readings; //h2
struct stack *forward_readings_data;

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

//for stacks
// Utility function to return the size of the stack
int size(struct stack *pt);
// Utility function to check if the stack is empty or not
int isEmpty(struct stack *pt);
// Utility function to add an element `x` to the stack
void push(struct stack *pt, int x);
// Utility function to check if the stack is full or not
int isFull(struct stack *pt);
// Utility function to pop a top element from the stack
int pop(struct stack *pt);


int main (int argc, char *argv[])
{
	X = 0;
	Y= 5;
    signal(SIGINT,INThandler);
	
	//create simulation environment
	left_readings = newStack(100);
	right_readings = newStack(100);
	forward_readings_data = newStack(200);

	int h1=5, h2=5,i=0, f=15;

	while(i<100){
		if (i==93){
			h2=15;
			h1=5;
		}
		else if(i==84){
			h1=9;
			h2=1;
		}
		else if (i==85){
			h2=10;
			h1=10;
		}
		else if (i==94)
		{
			h2=5;
		}
		// printf("Left:");
		push(left_readings,h1);
		// printf("Rightt:");
		push(right_readings,h2);
		i++;
	}

	i=0;
	while(i<200){
		if (i==171){ //in 28th call of forward readings it should return 4
			f=4;
		}
		else if(i==170 || i==169){
			f=3;
		}
		else if (i==172){
			f=15;
		}
		push(forward_readings_data,f);
		i++;
	}
	
	if (remove("robot.txt") != 0)
	{
		printf("Unable to delete the file");
	}

	//execution starts from here
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
	printf("H1= %f, H2= %f\n",h1,h2);

	float position;
	float final_h1, final_h2;

	final_h2 = Y-h2;
	final_h1=Y + h1;

	position = (final_h1+final_h2)/2;
	// if(Y!=position){

	// }
	Y=position;
}

void forward(){
	X= X + SPEED;
}

void obstacle_avoidance(){
	float reading = forward_reading();
	// float reading_second;
	printf("Forward reading = %f\n",reading);
	if ((reading <5) && (SPEED > 0)){
		SPEED--;
	}
	else if (SPEED == 0){
		Y=Y+1; //might need to change this logic
		SPEED=2;
		X=X+reading;
	}
	else{
		SPEED=2;
	}
}

void battery_check(){
	if (current_battery <=30 && current_battery > 10){
		printf("Need to charge or else battery will run out soon\n");
	}
	else if (current_battery <= 10)
	{
		printf("Warning!!!Battery Too Low!!\n");
		// move to side of a road and stop-> then charge battery to 100 and start moving
	}
}

float left_meter_reading(){
	// return a fake meter reading
	return pop(left_readings);
}

float right_meter_reading(){
	return pop(right_readings);
}

float forward_reading()
{
	// need to send a value if the robot reads something within 6 else just send
	return pop(forward_readings_data);
	// return 15;
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

int size(struct stack *pt) {
    return pt->top + 1;
}
 
int isEmpty(struct stack *pt) {
    return pt->top == -1;                   // or return size(pt) == 0;
}
 
int isFull(struct stack *pt) {
    return pt->top == pt->maxsize - 1;      // or return size(pt) == pt->maxsize;
}
 
void push(struct stack *pt, int x)
{
    // check if the stack is already full. Then inserting an element would
    // lead to stack overflow
    if (isFull(pt))
    {
        printf("Overflow\nProgram Terminated\n");
        exit(EXIT_FAILURE);
    }
 
    // printf("Inserting %d\n", x);
 
    // add an element and increment the top's index
    pt->items[++pt->top] = x;
}
 
int pop(struct stack *pt)
{
    // check for stack underflow
    if (isEmpty(pt))
    {
        printf("Underflow\nProgram Terminated\n");
        exit(EXIT_FAILURE);
    }
    // printf("Removing %d\n", peek(pt));
    // decrement stack size by 1 and (optionally) return the popped element
    return pt->items[pt->top--];
}