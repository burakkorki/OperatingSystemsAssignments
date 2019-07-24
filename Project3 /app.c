#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "pthread.h"
#include "ralloc.c"


int handling_method;          // deadlock handling method

#define M 3                   // number of resource types
int exist[3] =  {10, 10, 10};  // resources existing in the system

#define N 5                   // number of processes - threads
pthread_t tids[N];            // ids of created threads


void *aprocess (void *p)
{
    int req[3];
    int k;
    int pid;

    pid =  *((int *)p);

    printf ("this is thread %d\n", pid);
    fflush (stdout);

    /*req[0] = 0;
    req[1] = 1;
    req[2] = 0;*/

    /*req[0] = 7;
    req[1] = 5;
    req[2] = 3;*/

    req[0] = 5;
    req[1] = 5;
    req[2] = 5;
    ralloc_maxdemand(pid, req);

    /*req[0] = 0;
    req[1] = 0;
    req[2] = 0;*/

    /*req[0] = 0;
    req[1] = 2;
    req[2] = 0;*/
    for(k = 0 ;k < 1000000;k++  ) {
        req[0] = 1;
        req[1] = 1;
        req[2] = 1;

        ralloc_request(pid, req);

        // do something with the resources

        /*req[0] = 0;
        req[1] = 1;
        req[2] = 0;*/

        req[0] = 1;
        req[1] = 1;
        req[2] = 1;
        ralloc_release(pid, req);
    }
    printf ("Finished %d\n", pid);

    // call request and release as many times as you wish with
    // different parameters

    pthread_exit(NULL);
}

void *bprocess (void *p)
{
    int req[3];
    int k;
    int pid;

    pid =  *((int *)p);

    printf ("this is thread %d\n", pid);
    fflush (stdout);

    /*req[0] = 4;
    req[1] = 0;
    req[2] = 2;*/

    /*req[0] = 3;
    req[1] = 2;
    req[2] = 2;*/

    req[0] = 3;
    req[1] = 3;
    req[2] = 3;

    ralloc_maxdemand(pid, req);

    /*req[0] = 2;
    req[1] = 0;
    req[2] = 2;*/

    /*req[0] = 1;
    req[1] = 0;
    req[2] = 2;*/

    for(k = 0 ;k < 1000000; k++  ) {
        req[0] = 1;
        req[1] = 1;
        req[2] = 1;

        ralloc_request(pid, req);

        // do something with the resources
        /*req[0] = 2;
        req[1] = 0;
        req[2] = 0;*/

        req[0] = 1;
        req[1] = 1;
        req[2] = 1;

        ralloc_release(pid, req);
    }
    printf ("Finished %d\n", pid);

    // call request and release as many times as you wish with
    // different parameters

    pthread_exit(NULL);
}

void *cprocess (void *p)
{
    int req[3];
    int k;
    int pid;

    pid =  *((int *)p);

    printf ("this is thread %d\n", pid);
    fflush (stdout);

    /*req[0] = 3;
    req[1] = 0;
    req[2] = 3;*/

    /*req[0] = 9;
    req[1] = 0;
    req[2] = 2;*/

    req[0] = 2;
    req[1] = 2;
    req[2] = 2;

    ralloc_maxdemand(pid, req);

    /*req[0] = 0;
    req[1] = 0;
    req[2] = 1;*/
    for(k = 0 ;k < 1000000;k++  ) {
        req[0] = 1;
        req[1] = 1;
        req[2] = 1;

        ralloc_request(pid, req);

        // do something with the resources
        req[0] = 1;
        req[1] = 1;
        req[2] = 1;

        ralloc_release(pid, req);
    }
    printf ("Finished %d\n", pid);

    // call request and release as many times as you wish with
    // different parameters

    pthread_exit(NULL);
}


void *dprocess (void *p)
{
    int req[3];
    int k;
    int pid;

    pid =  *((int *)p);

    printf("this is thread %d\n", pid);
    fflush (stdout);

    /*req[0] = 3;
    req[1] = 1;
    req[2] = 1;*/

    /*req[0] = 2;
    req[1] = 2;
    req[2] = 2;*/

    req[0] = 3;
    req[1] = 3;
    req[2] = 3;

    ralloc_maxdemand(pid, req);

    for(k = 0 ;k < 1000000;k++  ) {
        req[0] = 1;
        req[1] = 1;
        req[2] = 1;

        ralloc_request(pid, req);

        // do something with the resources
        req[0] = 1;
        req[1] = 1;
        req[2] = 1;


        ralloc_release(pid, req);
    }
    printf ("Finished %d\n", pid);



    pthread_exit(NULL);
}

void *eprocess (void *p)
{
    int req[3];
    int k;
    int pid;

    pid =  *((int *)p);

    printf("this is thread %d\n", pid);
    fflush (stdout);

    /*req[0] = 0;
    req[1] = 0;
    req[2] = 4;*/

    /*req[0] = 4;
    req[1] = 3;
    req[2] = 3;*/

    req[0] = 2;
    req[1] = 2;
    req[2] = 2;

    ralloc_maxdemand(pid, req);
    for(k = 0 ;k < 1000000;k++  ) {
        req[0] = 0;
        req[1] = 0;
        req[2] = 1;

        ralloc_request(pid, req);

        // do something with the resources
        req[0] = 0;
        req[1] = 0;
        req[2] = 1;

        ralloc_release(pid, req);
    }
    printf ("Finished %d\n", pid);

    pthread_exit(NULL);
}


int main(int argc, char **argv)
{
    int dn; // number of deadlocked processes
    int deadlocked[N] ; // array indicating deadlocked processes
    int k;
    int i;
    int pids[N];

    for (k = 0; k < N; ++k)
        deadlocked[k] = -1; // initialize

    handling_method = DEADLOCK_AVOIDANCE;

    clock_t time;
    time = clock();

    ralloc_init (N, M, exist, handling_method);

    printf ("library initialized\n");
    fflush(stdout);

    for (i = 0; i < N; ++i) {
        pids[i] = i;
        deadlocked[i] = -1;
    }




    pthread_create (&(tids[0]), NULL, (void *) &aprocess,
                    (void *)&(pids[0]));
    pthread_create (&(tids[1]), NULL, (void *) &bprocess,
                    (void *)&(pids[1]));
    pthread_create (&(tids[2]), NULL, (void *) &cprocess,
                    (void *)&(pids[2]));
    pthread_create (&(tids[3]), NULL, (void *) &dprocess,
                    (void *)&(pids[3]));
    pthread_create (&(tids[4]), NULL, (void *) &eprocess,
                    (void *)&(pids[4]));



    pthread_join(tids[0],NULL);
    pthread_join(tids[1],NULL);
    pthread_join(tids[2],NULL);
    pthread_join(tids[3],NULL);
    pthread_join(tids[4],NULL);

    time = clock() - time;
    float totaltime = (float)time/CLOCKS_PER_SEC;

    printf ("threads created = %d with Handling Type %d in time = %f \n", N, Handling, totaltime);
    fflush (stdout);

    while (1) {
        sleep (5); // detection period
        if (handling_method == DEADLOCK_DETECTION) {
            dn = ralloc_detection(deadlocked);
            if (dn > 0) {
                printf ("There are deadlocked processes %d\n",dn);
            }
            else{
                printf("Currently no deadlocks\n");
            }
        }
        exit(0);

    }



}
