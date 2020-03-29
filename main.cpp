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



void solve() {
    int i = 5;
    timeThread((void *)(&i));
}


int main() {

    srand(time(0));
    int t = 1;
    //cin>>t;
    while (t--)
        solve();
    return 0;
}