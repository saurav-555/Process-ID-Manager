#include<unistd.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>


void *timeThread(void *arg){

    int threadId = *((int *)arg);

    // allocating pid

    // current date and time calculation
    time_t current_time;

    struct tm * timeInfo;
    time (&current_time);
    timeInfo = localtime (&current_time);
    printf("Thread of Time & Date | Thread Id : %d | Pid : %d \n" , threadId , 0);
    printf("%d Hr : %d mm : %d ss | %d / %d / %d \n ", timeInfo ->tm_hour , timeInfo->tm_min , timeInfo->tm_sec , timeInfo->tm_mday , timeInfo->tm_mon , timeInfo->tm_year);
    printf("\n");
    // wait random period of time bw 3 to 10 sec

    sleep(3 + rand() % 8);

    return NULL;

}

void *factorialThread(void * arg){

    int threadId = *((int *)arg);

    // allocating pid

    int upto =  rand() % 10 + 1;
    printf("Thread of Factorial( Random upto %d ) | Thread Id : %d | Pid : %d \n" , upto,  threadId , 0);
    printf("Factorial upto %d : ", upto);

    int fac = 1;
    for(int i = 1 ; i <= upto ; i++){
        fac = fac * i;
        printf("%d " , fac);
    }
    printf("\n\n");

    // wait random period of time bw 3 to 10 sec

    sleep(3 + rand() % 8);

    return NULL;

}

void *fibonacciThread(void * arg){

    int threadId = *((int *)arg);

    // allocating pid

    int upto =  rand() % 10 + 2;
    printf("Thread of Fibonacci( Random upto %d ) | Thread Id : %d | Pid : %d \n" , upto,  threadId , 0);
    printf("Fibonacci upto %d : ", upto);

    int f0 = 0 , f1 = 1;
    printf("f0 = %d | f1 = %d | " , f0 , f1);
    int f2;
    for(int i = 2 ; i <= upto ; i++){
        f2 = f0 + f1;
        printf("f%d = %d | " , i , f2);
        f0 = f1;
        f1 = f2;
    }
    printf("\n\n");

    // wait random period of time bw 3 to 10 sec

    sleep(3 + rand() % 8);

    return NULL;

}

void solve() {
    int i = 5;
    timeThread((void *)(&i));
    factorialThread((void *)(&i));
    fibonacciThread((void *)(&i));
}


int main() {

    srand(time(0));
    int t = 1;
    //cin>>t;
    while (t--)
        solve();
    return 0;

}