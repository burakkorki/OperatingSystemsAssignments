#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pthread.h"
#include "hash.h"

HashTable *ht1; // space allocated inside library

pthread_mutex_t Mutex;
pthread_t *threads;

clock_t timer;

int T;
int W;
int K;
int N;


void *test_runner(void *thread_number) {

    for (int i = 0; i < W; i++) {
        pthread_mutex_lock(&Mutex);
        hash_insert (ht1, i, (void *) 35000);
        pthread_mutex_unlock(&Mutex);
    }

    return 0;
}

int main(int argc, char **argv)
{
    int count = 0;

    /*  // OPERATIONS
    	// hash_get

        void * ptr;
        hash_get(ht1, 1, &ptr);

        // hash_ update
        hash_update(ht1, 2, (void *) 55);


        //delete
        hash_delete (ht1,2);

        //destroy
        hash_destroy (ht1);

    */

    count++;

    T = 1;       //--- number of threads (T) =
    W = 10;      //---number of keys/operations (W) =
    K = 10;     //---number of locks (K) =
    N = 100;    //---table size (N) =

    timer = clock();

    ht1  = hash_init (N, K);

    pthread_mutex_init(&Mutex,NULL);

    ;
    threads = malloc(T *sizeof(pthread_t));

    for(int i=0; i < T ; i++){
        pthread_t thr;
        pthread_create(&thr,NULL, test_runner, (void *)&T);
        threads[i] = thr;
    }

    for(int i=0; i < T ; i++){
        pthread_join(threads[i],NULL);
    }


    hash_destroy(ht1);

    timer = clock() - timer;

    double totaltime = ((double)timer)/CLOCKS_PER_SEC;

    printf("%i- Total time of T=%i, W=%i, K=%i, N=%i  %f seconds\n",count,T,W,K,N, totaltime);


    count++;

    T = 1;       //--- number of threads (T) =
    W = 100;      //---number of keys/operations (W) =
    K = 10;     //---number of locks (K) =
    N = 100;    //---table size (N) =


    timer = clock();


    ht1  = hash_init (N, K);

    pthread_mutex_init(&Mutex,NULL);


    threads = malloc(T *sizeof(pthread_t));

    for(int i=0; i < T ; i++){
        pthread_t thr;
        pthread_create(&thr,NULL, test_runner, (void *)&T);
        threads[i] = thr;
    }

    for(int i=0; i < T ; i++){
        pthread_join(threads[i],NULL);
    }


    hash_destroy(ht1);

    timer = clock() - timer;

    totaltime = ((double)timer)/CLOCKS_PER_SEC;

    printf("%i- Total time of T=%i, W=%i, K=%i, N=%i  %f seconds\n",count,T,W,K,N, totaltime);

    count++;

    T = 1;       //--- number of threads (T) =
    W = 1000;      //---number of keys/operations (W) =
    K = 10;     //---number of locks (K) =
    N = 100;    //---table size (N) =


    timer = clock();


    ht1  = hash_init (N, K);

    pthread_mutex_init(&Mutex,NULL);


    threads = malloc(T *sizeof(pthread_t));

    for(int i=0; i < T ; i++){
        pthread_t thr;
        pthread_create(&thr,NULL, test_runner, (void *)&T);
        threads[i] = thr;
    }

    for(int i=0; i < T ; i++){
        pthread_join(threads[i],NULL);
    }


    hash_destroy(ht1);

    timer = clock() - timer;

    totaltime = ((double)timer)/CLOCKS_PER_SEC;

    printf("%i- Total time of T=%i, W=%i, K=%i, N=%i  %f seconds\n",count,T,W,K,N, totaltime);

    count++;

    T = 1;       //--- number of threads (T) =
    W = 10000;      //---number of keys/operations (W) =
    K = 10;     //---number of locks (K) =
    N = 100;    //---table size (N) =


    timer = clock();


    ht1  = hash_init (N, K);

    pthread_mutex_init(&Mutex,NULL);


    threads = malloc(T *sizeof(pthread_t));

    for(int i=0; i < T ; i++){
        pthread_t thr;
        pthread_create(&thr,NULL, test_runner, (void *)&T);
        threads[i] = thr;
    }

    for(int i=0; i < T ; i++){
        pthread_join(threads[i],NULL);
    }


    hash_destroy(ht1);

    timer = clock() - timer;

    totaltime = ((double)timer)/CLOCKS_PER_SEC;

    printf("%i- Total time of T=%i, W=%i, K=%i, N=%i  %f seconds\n",count,T,W,K,N, totaltime);



    count++;

    T = 10;       //--- number of threads (T) =
    W = 10;      //---number of keys/operations (W) =
    K = 10;     //---number of locks (K) =
    N = 100;    //---table size (N) =


    timer = clock();


    ht1  = hash_init (N, K);

    pthread_mutex_init(&Mutex,NULL);


    threads = malloc(T *sizeof(pthread_t));

    for(int i=0; i < T ; i++){
        pthread_t thr;
        pthread_create(&thr,NULL, test_runner, (void *)&T);
        threads[i] = thr;
    }

    for(int i=0; i < T ; i++){
        pthread_join(threads[i],NULL);
    }


    hash_destroy(ht1);

    timer = clock() - timer;

    totaltime = ((double)timer)/CLOCKS_PER_SEC;

    printf("%i- Total time of T=%i, W=%i, K=%i, N=%i  %f seconds\n",count,T,W,K,N, totaltime);


    count++;

    T = 10;       //--- number of threads (T) =
    W = 100;      //---number of keys/operations (W) =
    K = 10;     //---number of locks (K) =
    N = 100;    //---table size (N) =


    timer = clock();


    ht1  = hash_init (N, K);

    pthread_mutex_init(&Mutex,NULL);


    threads = malloc(T *sizeof(pthread_t));

    for(int i=0; i < T ; i++){
        pthread_t thr;
        pthread_create(&thr,NULL, test_runner, (void *)&T);
        threads[i] = thr;
    }

    for(int i=0; i < T ; i++){
        pthread_join(threads[i],NULL);
    }


    hash_destroy(ht1);

    timer = clock() - timer;

    totaltime = ((double)timer)/CLOCKS_PER_SEC;

    printf("%i- Total time of T=%i, W=%i, K=%i, N=%i  %f seconds\n",count,T,W,K,N, totaltime);

    count++;

    T = 10;       //--- number of threads (T) =
    W = 1000;      //---number of keys/operations (W) =
    K = 10;     //---number of locks (K) =
    N = 100;    //---table size (N) =


    timer = clock();


    ht1  = hash_init (N, K);

    pthread_mutex_init(&Mutex,NULL);


    threads = malloc(T *sizeof(pthread_t));

    for(int i=0; i < T ; i++){
        pthread_t thr;
        pthread_create(&thr,NULL, test_runner, (void *)&T);
        threads[i] = thr;
    }

    for(int i=0; i < T ; i++){
        pthread_join(threads[i],NULL);
    }


    hash_destroy(ht1);

    timer = clock() - timer;

    totaltime = ((double)timer)/CLOCKS_PER_SEC;

    printf("%i- Total time of T=%i, W=%i, K=%i, N=%i  %f seconds\n",count,T,W,K,N, totaltime);


    count++;

    T = 10;       //--- number of threads (T) =
    W = 10000;      //---number of keys/operations (W) =
    K = 10;     //---number of locks (K) =
    N = 100;    //---table size (N) =


    timer = clock();


    ht1  = hash_init (N, K);

    pthread_mutex_init(&Mutex,NULL);


    threads = malloc(T *sizeof(pthread_t));

    for(int i=0; i < T ; i++){
        pthread_t thr;
        pthread_create(&thr,NULL, test_runner, (void *)&T);
        threads[i] = thr;
    }

    for(int i=0; i < T ; i++){
        pthread_join(threads[i],NULL);
    }


    hash_destroy(ht1);

    timer = clock() - timer;

    totaltime = ((double)timer)/CLOCKS_PER_SEC;

    printf("%i- Total time of T=%i, W=%i, K=%i, N=%i  %f seconds\n",count,T,W,K,N, totaltime);


    count++;

    T = 100;       //--- number of threads (T) =
    W = 10;      //---number of keys/operations (W) =
    K = 10;     //---number of locks (K) =
    N = 100;    //---table size (N) =


    timer = clock();


    ht1  = hash_init (N, K);

    pthread_mutex_init(&Mutex,NULL);


    threads = malloc(T *sizeof(pthread_t));

    for(int i=0; i < T ; i++){
        pthread_t thr;
        pthread_create(&thr,NULL, test_runner, (void *)&T);
        threads[i] = thr;
    }

    for(int i=0; i < T ; i++){
        pthread_join(threads[i],NULL);
    }


    hash_destroy(ht1);

    timer = clock() - timer;

    totaltime = ((double)timer)/CLOCKS_PER_SEC;

    printf("%i- Total time of T=%i, W=%i, K=%i, N=%i  %f seconds\n",count,T,W,K,N, totaltime);

    count++;

    T = 100;       //--- number of threads (T) =
    W = 100;      //---number of keys/operations (W) =
    K = 10;     //---number of locks (K) =
    N = 100;    //---table size (N) =


    timer = clock();


    ht1  = hash_init (N, K);

    pthread_mutex_init(&Mutex,NULL);


    threads = malloc(T *sizeof(pthread_t));

    for(int i=0; i < T ; i++){
        pthread_t thr;
        pthread_create(&thr,NULL, test_runner, (void *)&T);
        threads[i] = thr;
    }

    for(int i=0; i < T ; i++){
        pthread_join(threads[i],NULL);
    }


    hash_destroy(ht1);

    timer = clock() - timer;

    totaltime = ((double)timer)/CLOCKS_PER_SEC;

    printf("%i- Total time of T=%i, W=%i, K=%i, N=%i  %f seconds\n",count,T,W,K,N, totaltime);

    count++;

    T = 100;       //--- number of threads (T) =
    W = 1000;      //---number of keys/operations (W) =
    K = 10;     //---number of locks (K) =
    N = 100;    //---table size (N) =


    timer = clock();


    ht1  = hash_init (N, K);

    pthread_mutex_init(&Mutex,NULL);


    threads = malloc(T *sizeof(pthread_t));

    for(int i=0; i < T ; i++){
        pthread_t thr;
        pthread_create(&thr,NULL, test_runner, (void *)&T);
        threads[i] = thr;
    }

    for(int i=0; i < T ; i++){
        pthread_join(threads[i],NULL);
    }


    hash_destroy(ht1);

    timer = clock() - timer;

    totaltime = ((double)timer)/CLOCKS_PER_SEC;

    printf("%i- Total time of T=%i, W=%i, K=%i, N=%i  %f seconds\n",count,T,W,K,N, totaltime);

    count++;

    T = 100;       //--- number of threads (T) =
    W = 10000;      //---number of keys/operations (W) =
    K = 10;     //---number of locks (K) =
    N = 100;    //---table size (N) =

    timer = clock();


    ht1  = hash_init (N, K);

    pthread_mutex_init(&Mutex,NULL);


    threads = malloc(T *sizeof(pthread_t));

    for(int i=0; i < T ; i++){
        pthread_t thr;
        pthread_create(&thr,NULL, test_runner, (void *)&T);
        threads[i] = thr;
    }

    for(int i=0; i < T ; i++){
        pthread_join(threads[i],NULL);
    }


    hash_destroy(ht1);

    timer = clock() - timer;

    totaltime = ((double)timer)/CLOCKS_PER_SEC;

    printf("%i- Total time of T=%i, W=%i, K=%i, N=%i  %f seconds\n",count,T,W,K,N, totaltime);


    count++;

    T = 1000;       //--- number of threads (T) =
    W = 10;      //---number of keys/operations (W) =
    K = 10;     //---number of locks (K) =
    N = 100;    //---table size (N) =


    timer = clock();


    ht1  = hash_init (N, K);

    pthread_mutex_init(&Mutex,NULL);


    threads = malloc(T *sizeof(pthread_t));

    for(int i=0; i < T ; i++){
        pthread_t thr;
        pthread_create(&thr,NULL, test_runner, (void *)&T);
        threads[i] = thr;
    }

    for(int i=0; i < T ; i++){
        pthread_join(threads[i],NULL);
    }


    hash_destroy(ht1);

    timer = clock() - timer;

    totaltime = ((double)timer)/CLOCKS_PER_SEC;

    printf("%i- Total time of T=%i, W=%i, K=%i, N=%i  %f seconds\n",count,T,W,K,N, totaltime);

    count++;

    T = 1000;       //--- number of threads (T) =
    W = 100;      //---number of keys/operations (W) =
    K = 10;     //---number of locks (K) =
    N = 100;    //---table size (N) =


    timer = clock();


    ht1  = hash_init (N, K);

    pthread_mutex_init(&Mutex,NULL);


    threads = malloc(T *sizeof(pthread_t));

    for(int i=0; i < T ; i++){
        pthread_t thr;
        pthread_create(&thr,NULL, test_runner, (void *)&T);
        threads[i] = thr;
    }

    for(int i=0; i < T ; i++){
        pthread_join(threads[i],NULL);
    }


    hash_destroy(ht1);

    timer = clock() - timer;

    totaltime = ((double)timer)/CLOCKS_PER_SEC;

    printf("%i- Total time of T=%i, W=%i, K=%i, N=%i  %f seconds\n",count,T,W,K,N, totaltime);

    count++;

    T = 1000;       //--- number of threads (T) =
    W = 1000;      //---number of keys/operations (W) =
    K = 10;     //---number of locks (K) =
    N = 100;    //---table size (N) =


    timer = clock();


    ht1  = hash_init (N, K);

    pthread_mutex_init(&Mutex,NULL);


    threads = malloc(T *sizeof(pthread_t));

    for(int i=0; i < T ; i++){
        pthread_t thr;
        pthread_create(&thr,NULL, test_runner, (void *)&T);
        threads[i] = thr;
    }

    for(int i=0; i < T ; i++){
        pthread_join(threads[i],NULL);
    }


    hash_destroy(ht1);

    timer = clock() - timer;

    totaltime = ((double)timer)/CLOCKS_PER_SEC;

    printf("%i- Total time of T=%i, W=%i, K=%i, N=%i  %f seconds\n",count,T,W,K,N, totaltime);

    count++;

    T = 1000;       //--- number of threads (T) =
    W = 10000;      //---number of keys/operations (W) =
    K = 10;     //---number of locks (K) =
    N = 100;    //---table size (N) =


    timer = clock();


    ht1  = hash_init (N, K);

    pthread_mutex_init(&Mutex,NULL);


    threads = malloc(T *sizeof(pthread_t));

    for(int i=0; i < T ; i++){
        pthread_t thr;
        pthread_create(&thr,NULL, test_runner, (void *)&T);
        threads[i] = thr;
    }

    for(int i=0; i < T ; i++){
        pthread_join(threads[i],NULL);
    }


    hash_destroy(ht1);

    timer = clock() - timer;

    totaltime = ((double)timer)/CLOCKS_PER_SEC;

    printf("%i- Total time of T=%i, W=%i, K=%i, N=%i  %f seconds\n",count,T,W,K,N, totaltime);


    count++;

    T = 1;       //--- number of threads (T) =
    W = 10;      //---number of keys/operations (W) =
    K = 100;     //---number of locks (K) =
    N = 1000;    //---table size (N) =

    timer = clock();

    ht1  = hash_init (N, K);

    pthread_mutex_init(&Mutex,NULL);


    threads = malloc(T *sizeof(pthread_t));

    for(int i=0; i < T ; i++){
        pthread_t thr;
        pthread_create(&thr,NULL, test_runner, (void *)&T);
        threads[i] = thr;
    }

    for(int i=0; i < T ; i++){
        pthread_join(threads[i],NULL);
    }


    hash_destroy(ht1);

    timer = clock() - timer;

    totaltime = ((double)timer)/CLOCKS_PER_SEC;

    printf("%i- Total time of T=%i, W=%i, K=%i, N=%i  %f seconds\n",count,T,W,K,N, totaltime);


    count++;

    T = 1;       //--- number of threads (T) =
    W = 100;      //---number of keys/operations (W) =
    K = 100;     //---number of locks (K) =
    N = 1000;    //---table size (N) =


    timer = clock();


    ht1  = hash_init (N, K);

    pthread_mutex_init(&Mutex,NULL);


    threads = malloc(T *sizeof(pthread_t));

    for(int i=0; i < T ; i++){
        pthread_t thr;
        pthread_create(&thr,NULL, test_runner, (void *)&T);
        threads[i] = thr;
    }

    for(int i=0; i < T ; i++){
        pthread_join(threads[i],NULL);
    }


    hash_destroy(ht1);

    timer = clock() - timer;

    totaltime = ((double)timer)/CLOCKS_PER_SEC;

    printf("%i- Total time of T=%i, W=%i, K=%i, N=%i  %f seconds\n",count,T,W,K,N, totaltime);

    count++;

    T = 1;       //--- number of threads (T) =
    W = 1000;      //---number of keys/operations (W) =
    K = 100;     //---number of locks (K) =
    N = 1000;    //---table size (N) =


    timer = clock();


    ht1  = hash_init (N, K);

    pthread_mutex_init(&Mutex,NULL);


    threads = malloc(T *sizeof(pthread_t));

    for(int i=0; i < T ; i++){
        pthread_t thr;
        pthread_create(&thr,NULL, test_runner, (void *)&T);
        threads[i] = thr;
    }

    for(int i=0; i < T ; i++){
        pthread_join(threads[i],NULL);
    }


    hash_destroy(ht1);

    timer = clock() - timer;

    totaltime = ((double)timer)/CLOCKS_PER_SEC;

    printf("%i- Total time of T=%i, W=%i, K=%i, N=%i  %f seconds\n",count,T,W,K,N, totaltime);

    count++;

    T = 1;       //--- number of threads (T) =
    W = 10000;      //---number of keys/operations (W) =
    K = 100;     //---number of locks (K) =
    N = 1000;    //---table size (N) =


    timer = clock();


    ht1  = hash_init (N, K);

    pthread_mutex_init(&Mutex,NULL);


    threads = malloc(T *sizeof(pthread_t));

    for(int i=0; i < T ; i++){
        pthread_t thr;
        pthread_create(&thr,NULL, test_runner, (void *)&T);
        threads[i] = thr;
    }

    for(int i=0; i < T ; i++){
        pthread_join(threads[i],NULL);
    }


    hash_destroy(ht1);

    timer = clock() - timer;

    totaltime = ((double)timer)/CLOCKS_PER_SEC;

    printf("%i- Total time of T=%i, W=%i, K=%i, N=%i  %f seconds\n",count,T,W,K,N, totaltime);



    count++;

    T = 10;       //--- number of threads (T) =
    W = 10;      //---number of keys/operations (W) =
    K = 100;     //---number of locks (K) =
    N = 1000;    //---table size (N) =


    timer = clock();


    ht1  = hash_init (N, K);

    pthread_mutex_init(&Mutex,NULL);


    threads = malloc(T *sizeof(pthread_t));

    for(int i=0; i < T ; i++){
        pthread_t thr;
        pthread_create(&thr,NULL, test_runner, (void *)&T);
        threads[i] = thr;
    }

    for(int i=0; i < T ; i++){
        pthread_join(threads[i],NULL);
    }


    hash_destroy(ht1);

    timer = clock() - timer;

    totaltime = ((double)timer)/CLOCKS_PER_SEC;

    printf("%i- Total time of T=%i, W=%i, K=%i, N=%i  %f seconds\n",count,T,W,K,N, totaltime);


    count++;

    T = 10;       //--- number of threads (T) =
    W = 100;      //---number of keys/operations (W) =
    K = 100;     //---number of locks (K) =
    N = 1000;    //---table size (N) =


    timer = clock();


    ht1  = hash_init (N, K);

    pthread_mutex_init(&Mutex,NULL);


    threads = malloc(T *sizeof(pthread_t));

    for(int i=0; i < T ; i++){
        pthread_t thr;
        pthread_create(&thr,NULL, test_runner, (void *)&T);
        threads[i] = thr;
    }

    for(int i=0; i < T ; i++){
        pthread_join(threads[i],NULL);
    }


    hash_destroy(ht1);

    timer = clock() - timer;

    totaltime = ((double)timer)/CLOCKS_PER_SEC;

    printf("%i- Total time of T=%i, W=%i, K=%i, N=%i  %f seconds\n",count,T,W,K,N, totaltime);

    count++;

    T = 10;       //--- number of threads (T) =
    W = 1000;      //---number of keys/operations (W) =
    K = 100;     //---number of locks (K) =
    N = 1000;    //---table size (N) =


    timer = clock();


    ht1  = hash_init (N, K);

    pthread_mutex_init(&Mutex,NULL);


    threads = malloc(T *sizeof(pthread_t));

    for(int i=0; i < T ; i++){
        pthread_t thr;
        pthread_create(&thr,NULL, test_runner, (void *)&T);
        threads[i] = thr;
    }

    for(int i=0; i < T ; i++){
        pthread_join(threads[i],NULL);
    }


    hash_destroy(ht1);

    timer = clock() - timer;

    totaltime = ((double)timer)/CLOCKS_PER_SEC;

    printf("%i- Total time of T=%i, W=%i, K=%i, N=%i  %f seconds\n",count,T,W,K,N, totaltime);


    count++;

    T = 10;       //--- number of threads (T) =
    W = 10000;      //---number of keys/operations (W) =
    K = 100;     //---number of locks (K) =
    N = 1000;    //---table size (N) =


    timer = clock();


    ht1  = hash_init (N, K);

    pthread_mutex_init(&Mutex,NULL);


    threads = malloc(T *sizeof(pthread_t));

    for(int i=0; i < T ; i++){
        pthread_t thr;
        pthread_create(&thr,NULL, test_runner, (void *)&T);
        threads[i] = thr;
    }

    for(int i=0; i < T ; i++){
        pthread_join(threads[i],NULL);
    }


    hash_destroy(ht1);

    timer = clock() - timer;

    totaltime = ((double)timer)/CLOCKS_PER_SEC;

    printf("%i- Total time of T=%i, W=%i, K=%i, N=%i  %f seconds\n",count,T,W,K,N, totaltime);


    count++;

    T = 100;       //--- number of threads (T) =
    W = 10;      //---number of keys/operations (W) =
    K = 100;     //---number of locks (K) =
    N = 1000;    //---table size (N) =


    timer = clock();


    ht1  = hash_init (N, K);

    pthread_mutex_init(&Mutex,NULL);


    threads = malloc(T *sizeof(pthread_t));

    for(int i=0; i < T ; i++){
        pthread_t thr;
        pthread_create(&thr,NULL, test_runner, (void *)&T);
        threads[i] = thr;
    }

    for(int i=0; i < T ; i++){
        pthread_join(threads[i],NULL);
    }


    hash_destroy(ht1);

    timer = clock() - timer;

    totaltime = ((double)timer)/CLOCKS_PER_SEC;

    printf("%i- Total time of T=%i, W=%i, K=%i, N=%i  %f seconds\n",count,T,W,K,N, totaltime);

    count++;

    T = 100;       //--- number of threads (T) =
    W = 100;      //---number of keys/operations (W) =
    K = 100;     //---number of locks (K) =
    N = 1000;    //---table size (N) =


    timer = clock();


    ht1  = hash_init (N, K);

    pthread_mutex_init(&Mutex,NULL);


    threads = malloc(T *sizeof(pthread_t));

    for(int i=0; i < T ; i++){
        pthread_t thr;
        pthread_create(&thr,NULL, test_runner, (void *)&T);
        threads[i] = thr;
    }

    for(int i=0; i < T ; i++){
        pthread_join(threads[i],NULL);
    }


    hash_destroy(ht1);

    timer = clock() - timer;

    totaltime = ((double)timer)/CLOCKS_PER_SEC;

    printf("%i- Total time of T=%i, W=%i, K=%i, N=%i  %f seconds\n",count,T,W,K,N, totaltime);

    count++;

    T = 100;       //--- number of threads (T) =
    W = 1000;      //---number of keys/operations (W) =
    K = 100;     //---number of locks (K) =
    N = 1000;    //---table size (N) =


    timer = clock();


    ht1  = hash_init (N, K);

    pthread_mutex_init(&Mutex,NULL);


    threads = malloc(T *sizeof(pthread_t));

    for(int i=0; i < T ; i++){
        pthread_t thr;
        pthread_create(&thr,NULL, test_runner, (void *)&T);
        threads[i] = thr;
    }

    for(int i=0; i < T ; i++){
        pthread_join(threads[i],NULL);
    }


    hash_destroy(ht1);

    timer = clock() - timer;

    totaltime = ((double)timer)/CLOCKS_PER_SEC;

    printf("%i- Total time of T=%i, W=%i, K=%i, N=%i  %f seconds\n",count,T,W,K,N, totaltime);

    count++;

    T = 100;       //--- number of threads (T) =
    W = 10000;      //---number of keys/operations (W) =
    K = 100;     //---number of locks (K) =
    N = 1000;    //---table size (N) =


    timer = clock();


    ht1  = hash_init (N, K);

    pthread_mutex_init(&Mutex,NULL);


    threads = malloc(T *sizeof(pthread_t));

    for(int i=0; i < T ; i++){
        pthread_t thr;
        pthread_create(&thr,NULL, test_runner, (void *)&T);
        threads[i] = thr;
    }

    for(int i=0; i < T ; i++){
        pthread_join(threads[i],NULL);
    }


    hash_destroy(ht1);

    timer = clock() - timer;

    totaltime = ((double)timer)/CLOCKS_PER_SEC;

    printf("%i- Total time of T=%i, W=%i, K=%i, N=%i  %f seconds\n",count,T,W,K,N, totaltime);


    count++;

    T = 1000;       //--- number of threads (T) =
    W = 10;      //---number of keys/operations (W) =
    K = 100;     //---number of locks (K) =
    N = 1000;    //---table size (N) =


    timer = clock();


    ht1  = hash_init (N, K);

    pthread_mutex_init(&Mutex,NULL);


    threads = malloc(T *sizeof(pthread_t));

    for(int i=0; i < T ; i++){
        pthread_t thr;
        pthread_create(&thr,NULL, test_runner, (void *)&T);
        threads[i] = thr;
    }

    for(int i=0; i < T ; i++){
        pthread_join(threads[i],NULL);
    }


    hash_destroy(ht1);

    timer = clock() - timer;

    totaltime = ((double)timer)/CLOCKS_PER_SEC;

    printf("%i- Total time of T=%i, W=%i, K=%i, N=%i  %f seconds\n",count,T,W,K,N, totaltime);

    count++;

    T = 1000;       //--- number of threads (T) =
    W = 100;      //---number of keys/operations (W) =
    K = 100;     //---number of locks (K) =
    N = 1000;    //---table size (N) =


    timer = clock();


    ht1  = hash_init (N, K);

    pthread_mutex_init(&Mutex,NULL);


    threads = malloc(T *sizeof(pthread_t));

    for(int i=0; i < T ; i++){
        pthread_t thr;
        pthread_create(&thr,NULL, test_runner, (void *)&T);
        threads[i] = thr;
    }

    for(int i=0; i < T ; i++){
        pthread_join(threads[i],NULL);
    }


    hash_destroy(ht1);

    timer = clock() - timer;

    totaltime = ((double)timer)/CLOCKS_PER_SEC;

    printf("%i- Total time of T=%i, W=%i, K=%i, N=%i  %f seconds\n",count,T,W,K,N, totaltime);

    count++;

    T = 1000;       //--- number of threads (T) =
    W = 1000;      //---number of keys/operations (W) =
    K = 100;     //---number of locks (K) =
    N = 1000;    //---table size (N) =


    timer = clock();


    ht1  = hash_init (N, K);

    pthread_mutex_init(&Mutex,NULL);


    threads = malloc(T *sizeof(pthread_t));

    for(int i=0; i < T ; i++){
        pthread_t thr;
        pthread_create(&thr,NULL, test_runner, (void *)&T);
        threads[i] = thr;
    }

    for(int i=0; i < T ; i++){
        pthread_join(threads[i],NULL);
    }


    hash_destroy(ht1);

    timer = clock() - timer;

    totaltime = ((double)timer)/CLOCKS_PER_SEC;

    printf("%i- Total time of T=%i, W=%i, K=%i, N=%i  %f seconds\n",count,T,W,K,N, totaltime);

    count++;

    T = 1000;       //--- number of threads (T) =
    W = 10000;      //---number of keys/operations (W) =
    K = 100;     //---number of locks (K) =
    N = 1000;    //---table size (N) =


    timer = clock();


    ht1  = hash_init (N, K);

    pthread_mutex_init(&Mutex,NULL);


    threads = malloc(T *sizeof(pthread_t));

    for(int i=0; i < T ; i++){
        pthread_t thr;
        pthread_create(&thr,NULL, test_runner, (void *)&T);
        threads[i] = thr;
    }

    for(int i=0; i < T ; i++){
        pthread_join(threads[i],NULL);
    }


    hash_destroy(ht1);

    timer = clock() - timer;

    totaltime = ((double)timer)/CLOCKS_PER_SEC;

    printf("%i- Total time of T=%i, W=%i, K=%i, N=%i  %f seconds\n",count,T,W,K,N, totaltime);





}
