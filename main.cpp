#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define MIN 100     // minimum value of pId
#define MAX 1000    // maximum value of pId

struct node {       // node of queue data structure
    int data;
    node *next;
};

node *front = NULL;         // front and rear ptr of queue
node *rear = NULL;

void addPid(int x) {           // add an element to queue
    node *temp = new node;
    temp->data = x;
    temp->next = NULL;
    if (rear == NULL && front == NULL) {
        rear = temp;
        front = temp;
        return;
    }
    rear->next = temp;
    rear = temp;

}

void remove_pId() {                // removes the first element of queue
    node *temp = front;
    if (front == NULL)
        return;
    if (rear == front) {
        front = rear = NULL;
        delete temp;
        return;
    }
    front = temp->next;
    delete temp;
}

int is_pId_Available() {            // get the front value of queue
    if (front == NULL) {
        return -1;
    } else
        return front->data;
}

void allocate_queue(){

    // initializing pId's in queue range from MIN to MAX
    for(int i = MIN ; i <= MAX ; i++){
        addPid(i);
    }

}

int allocate_pId(){

    // next available pId is front of queue

    int pId = is_pId_Available();

    if(pId == -1){ // queue is empty ..... (no available pId)
        return -1;
    }
    remove_pId(); // if pId is available , pId is removed from the front of the queue
    return pId;

}

int release_pId(int pId){

    // this pId  available is now returning back to queue
    addPid(pId);

}

void *timeThread(void *arg){    // one of the thread of a process , which shows current date and time

    int threadId = *((int *)arg);

    // getting id
    int id = allocate_pId();                // getting thread Id from queue
    if(id == -1){
        printf("No Thread Id is Available \n\n");

        pthread_exit(NULL);
    }

    // current date and time calculation
    time_t current_time;

    struct tm * timeInfo;
    time (&current_time);
    timeInfo = localtime (&current_time);
    printf("Thread of Time & Date | Thread Id : %d | Pid : %d \n" , threadId , id);
    printf("%d Hr : %d mm : %d ss | %d / %d / %d \n ", timeInfo ->tm_hour , timeInfo->tm_min , timeInfo->tm_sec , timeInfo->tm_mday , timeInfo->tm_mon , timeInfo->tm_year);
    printf("\n\n");

    release_pId(id);                        // releasing threadId from queue
    pthread_exit(NULL);


}

void *factorialThread(void * arg){       // one of the thread of a process, which find's factorial of random range

    int threadId = *((int *)arg);

    // getting id
    int id = allocate_pId();                 // getting thread Id from queue
    if(id == -1){
        printf("No Thread Id is Available \n\n");

        pthread_exit(NULL);
    }

    int upto =  rand() % 10 + 1;
    printf("Thread of Factorial( Random upto %d ) | Thread Id : %d | Pid : %d \n" , upto,  threadId , id);
    printf("Factorial upto %d : ", upto);

    int fac = 1;
    for(int i = 1 ; i <= upto ; i++){
        fac = fac * i;
        printf("%d " , fac);
    }
    printf("\n\n");


    release_pId(id);                        // releasing threadId from queue
    pthread_exit(NULL);



}

void *fibonacciThread(void * arg){      // one of the thread of a process which , prints fibonacci numbers for a random range

    int threadId = *((int *)arg);

    // getting id
    int id = allocate_pId();            // getting thread Id from queue
    if(id == -1){
        printf("No Thread Id is Available \n\n");
        pthread_exit(NULL);
    }

    int upto =  rand() % 10 + 2;
    printf("Thread of Fibonacci( Random upto %d ) | Thread Id : %d | Pid : %d \n" , upto,  threadId , id);
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
    release_pId(id);                        // releasing threadId from queue
    pthread_exit(NULL);


}

void pIdManager() {

    // it initialize the data structure of pId's
    allocate_queue();

    int no_of_threads;                      // no of thread that we want
    scanf("%d" , &no_of_threads);

    pthread_t thread_id[no_of_threads];

    for(int i = 0 ; i < no_of_threads ; i++){
        int r = rand() % 3;                         // giving random thread among above three thread
        if(r == 0){
            pthread_create(&thread_id[i] , NULL, timeThread , (void*)&i);
        }else if(r == 1){
            pthread_create(&thread_id[i] , NULL, fibonacciThread , (void*)&i);
        }else {
            pthread_create(&thread_id[i] , NULL, factorialThread , (void*)&i);
        }
        // waiting a particular thread is to completed...   other wise... each thread output overlap ( we can also comment below to code for see effect of concurrent threads )
        clock_t start = clock();
        while(true){
            if((double((clock() - start))/CLOCKS_PER_SEC) > 1.5 ){
                break;
            }
        }

    }

    for(int i = 0 ; i < no_of_threads ; i++)   // joining the thread...., with main process
        pthread_join(thread_id[i] , NULL);

}


int main() {

    srand(time(0));
    int t = 1;
    //cin>>t;
    while (t--)
        pIdManager();
    return 0;

}