#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<string.h>
#include <math.h>

// for normal case
// #define MAXPV 4
// #define MAXProcPerPC 5
// int ProcPerPC[]={2,5,1,1,1};

void ExecuteBSchedule(int *ProcPerPC, int **wait, char *filename, int MAXPV, int f_flag, int t_flag);
void ComputeWait(int **wait, int *ProcPerPC,int MAXPV);
void ExecuteBSchedule_analysis_only(int *ProcPerPC, int **wait, char *filename, int MAXPV, int f_flag, int t_flag);
void ExecuteBSchedule_plot_only(int *ProcPerPC, int **wait, char *filename, int MAXPV, int f_flag, int t_flag);
int ReverseBinary(int k, int d);


int main (int argc, char *argv[])
{
    int opt;
    int f_flag=0;
    int t_flag=0;
    int o_flag=0;
    int a_flag=0;
    int p_flag=0;

    int MAXPV;
    int MAXProcPerPC;

    char *filename= malloc(50);

    while((opt=getopt(argc,argv,"fo:tap"))!=-1)
    {
        switch(opt)
        {
            case 'f':
                f_flag=1;
                break;
            case 'o':
                o_flag=1;
                strcpy(filename,optarg);
                break;
            case 't':
                t_flag=1;
                break;
            case 'a':
                a_flag=1;
                break;
            case 'p':
                p_flag=1;
                break;
            default:
                fprintf(stderr, "usage: [-f] [-o filename] [-t] [-p]\n");
                exit(EXIT_FAILURE);
        }
    }

    if(!o_flag){
        strcpy(filename,"output.txt");
    }

    if(p_flag){
        int MAXPV_array[]={2,4,5,6,9}; //hard coded values for plotting
        int MAXProcPerPC_array[]={5,5,5,5,5};
        int ProcPerPC_array[5][10]={{2,1,0,0,0},{2,5,1,1,1},{2,5,1,1,1,3},{2,5,1,1,1,3,4},{2,5,1,1,1,0,0,0,0,1}};
        int i;
        
        int k=0;

        int length = sizeof(MAXPV_array)/sizeof(MAXPV_array[0]);
        while(k<length){
            MAXPV=MAXPV_array[k];
            MAXProcPerPC=MAXProcPerPC_array[k];
            printf("k = %d %d %d\n",k,MAXPV,MAXProcPerPC);
            int **wait = (int**)malloc((MAXPV+1) * sizeof(int*));
            for (i = 0; i <= MAXPV; i++){
                wait[i] = (int*)malloc(MAXProcPerPC * sizeof(int));
            }

            int *ProcPerPC = (int*)malloc((MAXPV+1) * sizeof(int*));

            ProcPerPC=ProcPerPC_array[k];

            for (i=0;i<=MAXPV;i++){
                printf("%d ",ProcPerPC[i]);
            }   
            printf("\n");

            ComputeWait(wait,ProcPerPC,MAXPV);
            ExecuteBSchedule_plot_only(ProcPerPC,wait,filename,MAXPV, f_flag,t_flag);

            for (i = 0; i <= MAXPV; i++) { 
                free(wait[i]);
            }
            free(wait);
            k++;
        }
    }    
    else{
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

        if (a_flag){
            ExecuteBSchedule_analysis_only(ProcPerPC,wait,filename,MAXPV, f_flag,t_flag);
        }
        else{
            ExecuteBSchedule(ProcPerPC,wait,filename,MAXPV, f_flag,t_flag);
        }
    }
	return EXIT_SUCCESS;
}

void ExecuteBSchedule_plot_only(int *ProcPerPC, int **wait, char *filename, int MAXPV, int f_flag, int t_flag){
    int nmic, round; 
	int i,j;
    int count=0;
    printf("Called\n");

    FILE *filePointer;
    filePointer = fopen(filename, "a") ; 

	// compute the number of minor cycles
	nmic = (1<<MAXPV);
	// execute major cycle
	for(round=0; round < nmic; round++) {
		// execute minor cycle
		for(i=0; i<=MAXPV; i++){
			for(j=0; j<ProcPerPC[i]; j++){
				if(wait[i][j]==0) {		
					wait[i][j] = 1<<i;
                    count++;
				}
				wait[i][j]--;
			}
		}
	}
    double av = (double)count/(double)nmic;
    int perfect,dirty;
    perfect=ceil(av);
    dirty=floor(av); 
    fputs("\n\n----------------------------------\nAnalysis of the schedule:\n\n",filePointer);
    fprintf(filePointer, "Workload (WL) = %d\n",count);
    fprintf(filePointer,"Average processes per minor cycle (av) = %lf\n",av);
    fprintf(filePointer,"Perfect = %d\n",perfect);
    fprintf(filePointer,"Dirty = %d\n",dirty);
    fclose(filePointer);
}

/*executes the bscheduling algorithm to get the required schedule*/
void ExecuteBSchedule_analysis_only(int *ProcPerPC, int **wait, char *filename, int MAXPV, int f_flag, int t_flag) {
	int nmic, round; 
	int i,j;
    int count=0;

    FILE *filePointer;
    filePointer = fopen(filename, "w") ; 

	// compute the number of minor cycles
	nmic = (1<<MAXPV);

    printf("\n\n----------------------------------\n\n");

	// execute major cycle
	for(round=0; round < nmic; round++) {
		// execute minor cycle
		for(i=0; i<=MAXPV; i++){
			for(j=0; j<ProcPerPC[i]; j++){
				if(wait[i][j]==0) {		
					wait[i][j] = 1<<i;
                    count++;
				}
				wait[i][j]--;
			}
		}
	}
    printf("Analysis of the schedule:\n\n");
    printf("Workload (WL) = %d\n",count);
    double av = (double)count/(double)nmic;
    printf("Average processes per minor cycle (av) = %lf \n",av);
    int perfect,dirty;
    perfect=ceil(av);
    dirty=floor(av);

    printf("Perfect = %d\n",perfect);
    printf("Dirty = %d\n",dirty);
    
    if (f_flag){
        fputs("\n\n----------------------------------\nAnalysis of the schedule:\n\n",filePointer);
        fprintf(filePointer, "Workload (WL) = %d\n",count);
        fprintf(filePointer,"Average processes per minor cycle (av) = %lf\n",av);
        fprintf(filePointer,"Perfect = %d\n",perfect);
        fprintf(filePointer,"Dirty = %d\n",dirty);
        fclose(filePointer);
    }
}

/*executes the bscheduling algorithm to get the required schedule*/
void ExecuteBSchedule(int *ProcPerPC, int **wait, char *filename, int MAXPV, int f_flag, int t_flag) {
	int nmic, round; 
	int i,j;
    int count=0;

    FILE *filePointer;
    filePointer = fopen(filename, "w") ; 

	// compute the number of minor cycles
	nmic = (1<<MAXPV);

    printf("\n\n----------------------------------\n\n");

	// execute major cycle
	for(round=0; round < nmic; round++) {
		// execute minor cycle
		for(i=0; i<=MAXPV; i++){
			for(j=0; j<ProcPerPC[i]; j++){
				if(wait[i][j]==0) {
					printf ("p%d.%d ", i, j);
                    if (f_flag){
                        fprintf(filePointer, "p%d.%d ", i, j);
                    }		
					wait[i][j] = 1<<i;
                    count++;
				}
				wait[i][j]--;
			}
		}
		printf ("\n");		
        if (f_flag){
            fputs("\n", filePointer);
        }
	}
    printf("Analysis of the schedule:\n\n");
    printf("Workload (WL) = %d\n",count);
    double av = (double)count/(double)nmic;
    printf("Average processes per minor cycle (av) = %lf \n",av);
    int perfect,dirty;
    perfect=ceil(av);
    dirty=floor(av);

    printf("Perfect = %d\n",perfect);
    printf("Dirty = %d\n",dirty);
    
    if (f_flag){
        fputs("\n\n----------------------------------\nAnalysis of the schedule:\n\n",filePointer);
        fprintf(filePointer, "Workload (WL) = %d\n",count);
        fprintf(filePointer,"Average processes per minor cycle (av) = %lf\n",av);
        fprintf(filePointer,"Perfect = %d\n",perfect);
        fprintf(filePointer,"Dirty = %d\n",dirty);
        fclose(filePointer);
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