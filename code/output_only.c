#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<string.h>

// for normal case
// #define MAXPV 4
// #define MAXProcPerPC 5
// int ProcPerPC[]={2,5,1,1,1};

void ExecuteBSchedule(int *ProcPerPC, int **wait, char *filename, int MAXPV);
void ComputeWait(int **wait, int *ProcPerPC,int MAXPV);
int ReverseBinary(int k, int d);


int main (int argc, char *argv[])
{
    int opt;
    int f_flag=0;
    int t_flag=0;
    int o_flag=0;

    int MAXPV;
    int MAXProcPerPC;

    char *filename="output.txt";

    while((opt=getopt(argc,argv,"fot"))!=-1)
    {
        switch(opt)
        {
            case 'f':
                printf("Print to file\n");
                f_flag=1;
                break;
            case 'o':
                printf("Output file specific name\n");
                o_flag=1;
                break;
            case 't':
                printf("print in terminal\n");
                t_flag=1;
                break;
            default:
                fprintf(stderr, "usage: [-f] [-o] [-b] [filename]");
                exit(EXIT_FAILURE);
        }
    }

    if(o_flag){
        strcpy(filename,argv[optind]);
    }

    printf("Enter value for MAXPV: ");
    scanf("%d", &MAXPV);

    printf("Enter value for MAXProcPerPC: ");
    scanf("%d", &MAXProcPerPC);

    int i;
    int **wait = (int**)malloc((MAXPV+1) * sizeof(int*));
    for (i = 0; i <= MAXPV; i++){
        wait[i] = (int*)malloc(MAXProcPerPC * sizeof(int));
    }

    int *ProcPerPC = (int*)malloc((MAXPV+1) * sizeof(int*));

    printf("Enter values for ProcPerPC:\n");
    for (i=0; i<=MAXPV; i++){
        scanf("%d",&ProcPerPC[i]);
    }
        

	ComputeWait(wait,ProcPerPC,MAXPV);
	ExecuteBSchedule(ProcPerPC,wait,filename,MAXPV);

	return EXIT_SUCCESS;
}

/*executes the bscheduling algorithm to get the required schedule*/
void ExecuteBSchedule(int *ProcPerPC, int **wait, char *filename, int MAXPV) {
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
void ComputeWait(int **wait, int *ProcPerPC,int MAXPV) {
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