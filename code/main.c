#include<stdio.h>
#include<stdlib.h>
#include <time.h>

int main(){
    float frequency;
    int i;
    long double time_in_seconds;

    printf("Enter frequency in Hz = ");
    scanf("%f", &frequency);

    time_in_seconds= (long double)1/(long double)frequency;

    printf("\nTime in seconds = %.20Lf\n",time_in_seconds); 

    for (i=0;i<2;i++)
    {
        system("./out");
        // _execl();
        printf("Finished\n ");
    }
    
    return 0;
}