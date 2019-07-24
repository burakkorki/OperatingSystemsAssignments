//
#include <stdio.h>
#include <pthread.h>
#include "hash.h"
#include <stdlib.h>
// remove printf debug statements at the end

HashTable *hash_init (int N, int K)
{
//    printf ("hash_init called\n");


    int M = N/K;

    if( N < 100 || N > 1000 || M < 10 || M >1000 || M > N || N % M != 0 || K<= 0 ) {
        printf("N= %i M= %i K= %i N or K value not in desired range\n",N,M,K);
        return NULL;
    }

    HashTable *hp =  (HashTable *) malloc(sizeof(HashTable) );

    hp->N = N;
    hp->K = K;
    hp->Bucket = malloc( N * sizeof(Bucket));

    for (int i = 0; i < K; i++) {
        pthread_mutex_t mut;
        pthread_mutex_init(&mut, NULL);
        for(int j = i*M; j < (M *(i+1)) ; j++){
            hp->Bucket[j].Node = NULL;
            hp->Bucket[j].Mutex = mut;
        }
    }

    return hp;


}

int hash_insert (HashTable *hp, int k, void *v)
{
//    printf ("hash_insert called\n");

    if(k <= 0){
        return -1;
    }

    int index = k % hp->N;

    pthread_mutex_lock(&hp->Bucket[index].Mutex);

    if(hp->Bucket[index].Node == NULL) {
        hp->Bucket[index].Node = malloc(sizeof(Node));
        hp->Bucket[index].Node->value = malloc(sizeof(void *)); //new
        *(int *)hp->Bucket[index].Node->value = *(int *)v; //new
        hp->Bucket[index].Node->key = k;
        hp->Bucket[index].Node->next = NULL;
    }
    else{
        Node * cur = hp->Bucket[index].Node;
        Node * prev;
        while (cur != NULL){
            if(cur->key == k ){
                //printf("Here*/n");
                //v = cur->value ++ ;
                //(hp, cur->key, cur->value );
                pthread_mutex_unlock(&hp->Bucket[index].Mutex);
                return -1;
            }
            prev = cur;
            cur = cur->next;
        }
        /*if(hp->Bucket[index].Node->key == k ){
            v = hp->Bucket[index].Node->value  ;
            //(hp, cur->key, cur->value );
            pthread_mutex_unlock(&hp->Bucket[index].Mutex);
            return -1;
        }*/
        cur = prev;
        cur->next =  malloc(sizeof(Node));
        cur = cur->next;
        cur->value = malloc(sizeof(void *)); //new
        *(int *)cur->value = *(int *)v; //new
        cur->key = k;
        cur->next = NULL;
    }
    // mutex
    pthread_mutex_unlock(&hp->Bucket[index].Mutex);
    return 0;
}

int hash_delete (HashTable *hp, int k) {


    //printf("delete key called = %i\n",k);

    if(k <= 0){

        return -1;
    }

    int index = k % hp->N;

    pthread_mutex_lock(&hp->Bucket[index].Mutex);

    if(hp->Bucket[index].Node == NULL){
        pthread_mutex_unlock(&hp->Bucket[index].Mutex);
        return -1;
    }

    Node *head = hp->Bucket[index].Node;
    Node *cur = hp->Bucket[index].Node;

    while(cur->next != NULL){;
        Node *prev = cur;
        cur = cur->next;

        if(cur->key == k){
//            printf("Entered cur \n" );
            prev->next = cur->next;
            cur->next = NULL;
            cur->value = NULL;
            free(cur->value); //new
            cur = NULL;
            free(cur);
            break;
        }
    }

    if(head->key == k){
//        printf("Entered head \n" );
        hp->Bucket[index].Node = head->next;
        head->next = NULL;
        head->value = NULL;
        free(head->value); //new
        head = NULL;
        free(head);
    }

    pthread_mutex_unlock(&hp->Bucket[index].Mutex);

    return (0);
}

int hash_update (HashTable *hp, int k, void *v)
{
//    printf ("hash_update called\n");

    if(k <= -1){

        return -1;
    }

    int index = k % hp->N;

    pthread_mutex_lock(&hp->Bucket[index].Mutex);
//    printf ("1---\n");
    if(hp->Bucket[index].Node == NULL){
//        printf ("2---\n");
        pthread_mutex_unlock(&hp->Bucket[index].Mutex);
        return -1;
    }

    Node *cur = hp->Bucket[index].Node;

    while(cur != NULL){
        if(cur->key == k){
            //printf("Value before- %i\n", *(int *)cur->value);
            *(int *)cur->value = *(int *)v; //new
            //printf("Value after- %i\n", *(int *)cur->value);
        }
        cur = cur->next;
    }
    pthread_mutex_unlock(&hp->Bucket[index].Mutex);
    return 0;
}

int hash_get (HashTable *hp, int k, void **vp)
{
    //printf ("hash_get called\n");

    //printf("%i ",k);

    if(k <= -1){

        return -1;
    }

    int index = k % hp->N;

    //printf("index %i \n",index);

    pthread_mutex_lock(&hp->Bucket[index].Mutex);

    if(hp->Bucket[index].Node == NULL){
        pthread_mutex_unlock(&hp->Bucket[index].Mutex);
        return -1;
    }

    Node *cur = hp->Bucket[index].Node;

    while(cur != NULL){
        if(cur->key == k){
            //printf("Value - %i\n",*(int*)cur->value);
            *vp = &*(int*)cur->value; //new
            break;
        }
        cur = cur->next;
    }

    pthread_mutex_unlock(&hp->Bucket[index].Mutex);
    return 0;
}

int hash_destroy (HashTable *hp)
{
//    printf ("hash_destroy called\n");

    for(int i = 0; i < hp->N ;i++ ) {

        pthread_mutex_lock(&hp->Bucket[i].Mutex);
        Node *cur = hp->Bucket[i].Node;

        while (cur != NULL){

            //printf("%i\n",cur->key);
            pthread_mutex_unlock(&hp->Bucket[i].Mutex);
            //
            hash_delete(hp,cur->key);
            pthread_mutex_lock(&hp->Bucket[i].Mutex);
            cur= hp->Bucket[i].Node;
        }
        hp->Bucket[i].Node = NULL;
        free(hp->Bucket[i].Node);

        pthread_mutex_unlock(&hp->Bucket[i].Mutex);
            //hp->Bucket[i].Mutex = NULL ;
            //hp->Bucket[i] = NULL;

    }


    for (int i = 0; i < hp->K; i++) {

        for(int j = i*(hp->N/hp->K); j < ((hp->N/hp->K) *(i+1)) ; j++){
            hp->Bucket[j].Node = NULL;
            pthread_mutex_destroy(&hp->Bucket[i*(hp->N / hp->K)].Mutex);
        }
    }



    hp->Bucket = NULL;
    free(hp->Bucket);

    int cc = 0;
    for(int i = 0; i < hp->N ;i++ ){
        if(hp->Bucket != NULL)
            cc++;
    }
    //printf("The occurance is %i\n",cc);


    hp = NULL;
    free(hp);

    /*if(hp == NULL){
        printf("NULL \n");
    }*/

    return (0);
}

void hash_print(HashTable *hp, char *filename) {

    int *ascending;
    int count = 0;
    ascending = malloc(count*sizeof(int));

    if(hp != NULL) {
        for (int i = 0; i < hp->N; i++) {
            pthread_mutex_lock(&hp->Bucket[i].Mutex);
            Node *cur = hp->Bucket[i].Node;
            
            while (cur != NULL) {
                int *temp;

                temp = malloc(count * sizeof(int));

                for(int j = 0 ; j< count; j++)
                    temp[j] = ascending[j];


                ascending = malloc((count + 1 )*sizeof(int));


                for(int j = 0;j< count;j++) {
                        ascending[j] = temp[j];
                }

                ascending[count] = cur->key;
                count++;
                cur = cur->next;

                //free(temp);
            }
            pthread_mutex_unlock(&hp->Bucket[i].Mutex);
        }
    }

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            if (ascending[j] > ascending[i])
            {
                int temp = ascending[i];
                ascending[i] = ascending[j];
                ascending[j] = temp;
            }
        }
    }
    FILE * file;


    file = fopen (filename,"w");

    /* write 10 lines of text into the file stream
    for(i = 0; i < 10;i++){
        fprintf (fp, "This is line %d\n",i + 1);
    }

    */

    for(int i = 0; i < count; i++){
        pthread_mutex_lock(&hp->Bucket[i].Mutex);
        void *count;
        hash_get(hp,ascending[i],&count);
        pthread_mutex_unlock(&hp->Bucket[i].Mutex);
        fprintf(file,"%i: %d\n",ascending[i], *(int *)count);
    }
    fclose (file);
}
