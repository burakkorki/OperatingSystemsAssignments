#ifndef HASH_H
#define HASH_H

#include <pthread.h>

#define MIN_N 100
#define MAX_N 1000
#define MIN_M 10
#define MAX_M 1000


struct Node
{
    int key;
    void* value;
    struct Node* next;
    //pthread_mutex_t *Mutex;
};
typedef struct Node Node;

struct Bucket
{
    pthread_mutex_t Mutex;
    Node *Node;
};
typedef struct Bucket Bucket;


struct hash_table
{

    int N;
    int K;
    Bucket *Bucket;



};
typedef struct hash_table HashTable;



HashTable *hash_init (int N, int K);
int hash_insert (HashTable *hp, int k, void* v);
int hash_delete (HashTable *hp, int k);
int hash_update (HashTable *hp, int k, void *v);
int hash_get (HashTable *hp, int k, void **vp);
int hash_destroy (HashTable *hp);

void hash_print(HashTable *hp,char *filename);

#endif /* HASH_H */
