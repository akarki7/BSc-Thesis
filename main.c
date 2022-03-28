#include <stdio.h>

// EXAMPLE LECTURE
//#define MAXPV 4
//#define MAXProcPerPC 5
//
// EXAMPLE HW
#define MAXPV 3
#define MAXProcPerPC 3     
int wait[MAXPV][MAXProcPerPC];


// EXAMPLE LECTURE
// int ProcPerPC[]={2,5,1,1,1};
//
// EXAMPLE HW
int ProcPerPC[]={1,3,2,1};


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

void ShowWait() {
	int start = 0; 
	int slots = 1;

	int i,j;

	for(i=0;  i<=MAXPV; i++) {
		for(j=0; j< ProcPerPC[i]; j++){
			printf ("wait p%d.%d = %d  \n", i, j,wait[i][j]);		
		}
	}	
}


//
// computes Reverse Binary  
// of number k with d digits
//
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


void DemoReverseBinary(int d){
	int i,j,h;

	for(i=1;i<=d;i++){
		for(j=0;j<(1<<i);j++){
			h = ReverseBinary(j,i);
			printf ("Rev.Bin.(%d,%d) = %d  \n", j, i,h);
		}
		printf ("\n");
	}
}


int main (int argc, char *argv[])
{
//	DemoReverseBinary(4);

	ComputeWait();
	ShowWait();

	ExecuteBSchedule();

	return (0);
}

