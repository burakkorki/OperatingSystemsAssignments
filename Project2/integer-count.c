#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "pthread.h"
#include "hash.h"
#include "hash.c"

HashTable *ht1; // space allocated inside library
pthread_mutex_t Mutex;
int N = 1000;
int M = 100;
int K = 10;

void *Multithread(void *filename){

    char arr[1000];

    FILE *file;

    if ((file = fopen(filename, "r")) == NULL)
    {
        printf("File is not opened %s\n",(char *)filename);
        exit(1);
    }



    while (fgets(arr, sizeof(arr), file) != NULL) {
        //printf("%i\n",atoi(&arr[0]));

        if (arr[0] > 0) {
            int temp = 1; //new
            void *count = &temp;
            int key = atoi(&arr[0]);


            pthread_mutex_lock(&Mutex);
            if (hash_insert(ht1, key, count) == -1) {
                pthread_mutex_unlock(&Mutex);
                pthread_mutex_lock(&Mutex);
                hash_get(ht1, key, &count);
                pthread_mutex_unlock(&Mutex);
                pthread_mutex_lock(&Mutex);
                *(int *)count = *(int *)count + 1; //new
                hash_update(ht1, key, count );
                pthread_mutex_unlock(&Mutex);
            } else
                pthread_mutex_unlock(&Mutex);

        }
    }



    fclose(file);
    return 0;
}

int main(int argc, char **argv)
{


    ht1 = hash_init(N,K);



    int total_txt = atoi(argv[1]);
    pthread_mutex_init(&Mutex,NULL);

    pthread_t *thread_arr;
    thread_arr = malloc(total_txt * sizeof(pthread_t));


    for(int i = 0; i < total_txt; i++){
        pthread_t thread;
        pthread_create(&thread,NULL, Multithread, argv[i+2]);
        thread_arr[i] = thread;

    }

    for(int i = 0; i < total_txt; i++){
        pthread_join(thread_arr[i],NULL);
    }


    hash_print(ht1,argv[total_txt+2]);

    /*

    printf("Destroy started\n");

    // hash_delete(ht1,1);
    // hash_delete(ht1,2001);

    hash_destroy(ht1);

    printf("Destroy end\n");

    int cc = 0;
    for(int i = 0; i < ht1->N ;i++ ){
        if(ht1->Bucket != NULL)
            cc++;
    }

    printf("The occurance is %i\n",cc);


    //printf("xd  %lu\n", sizeof(ht1));


    //hash_print(ht1);

    //ht1 = hash_init(N,K);*/
    
}
