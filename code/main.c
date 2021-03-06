#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include<errno.h>
#include <unistd.h>
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */
#include <signal.h>
#include <string.h>

volatile sig_atomic_t exitRequested = 0;

void execute_bschedule();
void  INThandler(int sig);

int main(){
    float frequency;
    float input_in_seconds;
    int i,choice;
    long double time_in_seconds;
    long double time_in_nanoseconds;
    bool nsecs=true;

    struct timespec tim;
    tim.tv_sec=0;

    signal(SIGINT,INThandler);

    printf("Enter your choice for input:\n1-Input in Seconds\n2-Input in Hz\n\n");
    scanf("%d", &choice);

    switch (choice){
        case 1:
            printf("Enter time in seconds (>=1) = ");
            scanf("%f", &input_in_seconds);
            if (input_in_seconds <1){
                printf("Invalid input.Exiting....\n");
                exit(EXIT_FAILURE);
            }
            nsecs=false;
            break;
        case 2:
            printf("Enter frequency in Hz (>=1) = ");
            scanf("%f", &frequency);
            if (frequency <1){
                printf("Invalid input.Exiting....\n");
                exit(EXIT_FAILURE);
            }
            time_in_seconds= (long double)1/(long double)frequency;
            time_in_nanoseconds=time_in_seconds*1000000000;
            tim.tv_nsec=time_in_nanoseconds;
            printf("\nTime in seconds = %.20Lf\n",time_in_seconds); 
            printf("\nTime in nanoseconds = %.20Lf\n",time_in_nanoseconds); 
            if(time_in_nanoseconds>= 1000000000)
            {
                nsecs=false;
            }
            break;
        default:
            printf("Invalid choice inputted.Exiting....\n");
            exit(EXIT_FAILURE);
    }
    i=0;

    /*Spawn a child to run the program.*/
    pid_t pid=fork();

    if (pid==0){
        while(!exitRequested)
        {
            if(nsecs)
            {
                execute_bschedule();
                if(nanosleep(&tim,NULL)==-1)
                {
                    switch (errno) {
                            case EINTR:
                                printf("interrupted by a signal handler\n");
                                exit(EXIT_FAILURE);
                            case EINVAL:
                                printf("tv_nsec - not in range or tv_sec is negative\n");
                                exit(EXIT_FAILURE);
                            default:
                                perror("nanosleep");
                                exit(EXIT_FAILURE);
                        }
                }
            }
            else{
                execute_bschedule();
                sleep(input_in_seconds);
            }
            i++;
        }
    }
    else{
        waitpid(pid,0,0);/*wait for child to exit*/
        printf("\nExiting...\n");
    }
    return 0;
}

void execute_bschedule()
{
    //calls the bscheduling file from here maybe
    system("./scheduling.out");
    return;
}

void  INThandler(int sig)
{
    exitRequested=1;
}