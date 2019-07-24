#include <stdio.h>
#include <pthread.h>
#include "ralloc.h"
#include <stdlib.h>
#include <stdbool.h>


int Handling; //Handling Type
int Number_Of_Processes; // N
int Number_Of_Resources_Types; // M
int Exist[MAX_RESOURCE_TYPES]; // Number of instances for resource types

int Available[MAX_RESOURCE_TYPES];

int Request[MAX_PROCESSES][MAX_RESOURCE_TYPES];

int MaxDemand[MAX_PROCESSES][MAX_RESOURCE_TYPES];
int Need[MAX_PROCESSES][MAX_RESOURCE_TYPES];
int Allocate[MAX_PROCESSES][MAX_RESOURCE_TYPES];


pthread_cond_t cond ;
pthread_mutex_t mutex ;

/*
pthread_cond_init(&cond,NULL);
pthread_mutex_init(&mutex,NULL);
*/

/*
Available[0] = 3;
Available[1] = 3;
Available[2] = 2;


Allocate[0][0] = 0;
Need[0][0] = 7 - Allocate[0][0];
Allocate[0][1] = 1;
Need[0][1] = 5 - Allocate[0][1];
Allocate[0][1] = 0;
Need[0][2] = 3 - Allocate[0][2];


Allocate[1][0] = 2;
Need[1][0] = 3 - Allocate[1][0];
Allocate[1][1] = 0;
Need[1][1] = 2 - Allocate[1][1];
Allocate[1][1] = 0;
Need[1][2] = 2 - Allocate[1][2];


Allocate[2][0] = 3;
Need[2][0] = 7 - Allocate[2][0];
Allocate[2][1] = 0;
Need[2][1] = 5 - Allocate[2][1];
Allocate[2][1] = 2;
Need[2][2] = 3 - Allocate[2][2];


Allocate[3][0] = 2;
Need[3][0] = 7 - Allocate[3][0];
Allocate[3][1] = 1;
Need[3][1] = 5 - Allocate[3][1];
Allocate[3][1] = 1;
Need[3][2] = 3 - Allocate[3][2];


Allocate[4][0] = 0;
Need[4][0] = 7 - Allocate[4][0];
Allocate[4][1] = 0;
Need[4][1] = 5 - Allocate[4][1];
Allocate[4][1] = 2;
Need[4][2] = 3 - Allocate[4][2];*/

int Avoidance(int procarray[]){
    //int TempMaxDemand[Number_Of_Processes][Number_Of_Resources_Types]; //MaxDemand
    int TempNeed[Number_Of_Processes][Number_Of_Resources_Types]; //Need
    int TempAllocate[Number_Of_Processes][Number_Of_Resources_Types]; //Alocate

    int tempAvailable[Number_Of_Resources_Types]; //Available


    for(int i = 0 ; i < Number_Of_Resources_Types; i++){
        tempAvailable[i] = Available[i];

    }

    for(int i = 0 ; i < Number_Of_Processes; i++ )
        procarray[i] = 0;

    for(int i=0 ; i < Number_Of_Processes; i++){
        for(int j=0 ; j <Number_Of_Resources_Types ; j++){
            //TempMaxDemand[i][j] = MaxDemand[i][j];
            TempNeed[i][j] = Need[i][j];
            TempAllocate[i][j] = Allocate[i][j];
            //printf("Pid = %d -> Need[%d][%d] = %d\n",i,i,j,Need[i][j]);
            //printf("Pid = %d -> TempAvailable[%d] = %d\n",i,j,Available[j]);
        }
    }




    int resourceCheck = 0;
    //int procCount = 0;
    for(int a= 0; a < Number_Of_Processes;a++) {
        for (int i = 0; i < Number_Of_Processes; i++) {
            resourceCheck = 0;
            for (int j = 0; j < Number_Of_Resources_Types; j++) {

                if (TempNeed[i][j] > tempAvailable[j]) {
                    resourceCheck = 1;
                    break;
                }
            }
            if (resourceCheck == 0 && procarray[i]==0){

                for (int k = 0 ; k < Number_Of_Resources_Types ; k++)
                    tempAvailable[k] += TempAllocate[i][k];
                procarray[i] = 1;
            }
        }
    }


     /*for(int i = 0 ; i < Number_Of_Processes; i++){
        if(i != Number_Of_Processes -1) {
            printf("%i ->", procarray[i]);
        }
        else {
            printf("%i", procarray[i]);
        }
    }
    printf("\n");*/

    int count = 0;
    for(int i = 0; i< Number_Of_Processes ; i++){
        if(procarray[i] == 0){
            count++;
        }
    }

    return count;
}

int ralloc_init(int p_count, int r_count, int r_exist[], int d_handling)
{
    if (p_count>=0 && p_count <MAX_PROCESSES && r_count>= 0 && r_count < MAX_RESOURCE_TYPES){
        //printf("Init entered\n   p_count = %d\n   r_count = %d\n   d_handling = %d\n",p_count,r_count,d_handling);

        Handling = d_handling ;

        Number_Of_Processes = p_count;

        Number_Of_Resources_Types = r_count;


        /*Exist = malloc(sizeof(int) * Number_Of_Resources_Types);

        Available = malloc(sizeof(int) * Number_Of_Resources_Types);

        MaxDemand = malloc(sizeof(int) * Number_Of_Processes);
        Need = malloc(sizeof(int) * Number_Of_Processes);
        Allocate = malloc(sizeof(int) * Number_Of_Processes);*/

        for(int i = 0; i < MAX_PROCESSES; i++){
            for(int j = 0; j < MAX_RESOURCE_TYPES; j++){
                Exist[j] = 0;
                Available[j] = 0;

                Request[i][j] = 0;

                MaxDemand[i][j] = 0;
                Need[i][j] = 0;
                Allocate[i][j] = 0;
            }
        }

        for(int i = 0; i < Number_Of_Resources_Types ; i++){
            Exist[i] = r_exist[i];
            Available[i] = r_exist[i];
        }

        pthread_mutex_init(&mutex, NULL);
        pthread_cond_init(&cond, NULL);


         //page 336

        /*Allocate[0][0] = 0;
        Allocate[0][1] = 1;
        Allocate[0][2] = 0;

        Allocate[1][0] = 2;
        Allocate[1][1] = 0;
        Allocate[1][2] = 0;

        Allocate[2][0] = 3;
        Allocate[2][1] = 0;
        Allocate[2][2] = 3;

        Allocate[3][0] = 2;
        Allocate[3][1] = 1;
        Allocate[3][2] = 1;

        Allocate[4][0] = 0;
        Allocate[4][1] = 0;
        Allocate[4][2] = 2;
        */



        /*//page333
        Allocate[0][0] = 0;
        Allocate[0][1] = 1;
        Allocate[0][2] = 0;

        Allocate[1][0] = 2;
        Allocate[1][1] = 0;
        Allocate[1][2] = 0;

        Allocate[2][0] = 3;
        Allocate[2][1] = 0;
        Allocate[2][2] = 2;

        Allocate[3][0] = 2;
        Allocate[3][1] = 1;
        Allocate[3][2] = 1;

        Allocate[4][0] = 0;
        Allocate[4][1] = 0;
        Allocate[4][2] = 2;

        Need[0][0] = 7;
        Need[0][1] = 4;
        Need[0][2] = 3;

        Need[1][0] = 3;
        Need[1][1] = 2;
        Need[1][2] = 2;

        Need[2][0] = 6;
        Need[2][1] = 0;
        Need[2][2] = 0;

        Need[3][0] = 0;
        Need[3][1] = 1;
        Need[3][2] = 1;

        Need[4][0] = 4;
        Need[4][1] = 3;
        Need[4][2] = 1;*/

        return 0;
    }
    else{
        printf("Init Error");
        return -1;
    }

}

int ralloc_maxdemand(int pid, int r_max[]){

    pthread_mutex_lock(&mutex);
    if(pid < 0 && pid > Number_Of_Processes -1 ){
        pthread_mutex_unlock(&mutex);
        return -1;
    }
    else {


        /*for(int i = 0; i< Number_Of_Resources_Types ; i++){
            if(r_max[i] > Available[i]){
                pthread_mutex_unlock(&mutex);
                return -1;
            }
        }*/

        //printf("Max Demand for pid = %d\n", pid);

        /*MaxDemand[pid] = malloc(sizeof(Number_Of_Resources_Types));
        Need[pid] = malloc(sizeof(Number_Of_Resources_Types));
        Allocate[pid] = malloc(sizeof(Number_Of_Resources_Types));*/

        for(int i = 0; i< Number_Of_Resources_Types ; i++){
            //Request[pid][i] = 0;

            MaxDemand[pid][i] = r_max[i];

            /*printf("Max--- MaxDemanc[%d][%d] = %d\n",pid,i,MaxDemand[pid][i]);
            //printf("Max--- rmax[%d][%d] = %d\n",pid,i,r_max[i]);*/

            Allocate[pid][i] = 0;
            Need[pid][i] = MaxDemand[pid][i] - Allocate[pid][i];

            /*printf("Need[%d][%d]=",pid);
            //printf("Max Demand--- Need[%d][%d] = %d\n",pid,i,Need[pid][i]);*/
        }


        pthread_mutex_unlock(&mutex);
        return (0);
    }
}

int ralloc_request (int pid, int demand[]) {

    pthread_mutex_lock(&mutex);

    if(pid < 0 && pid > Number_Of_Processes -1 ){
        pthread_mutex_unlock(&mutex);
        return -1;
    }

    for(int i = 0; i< Number_Of_Resources_Types; i++){

        /*printf("Req--- MaxDemanc[%d][%d] = %d\n",pid,i,MaxDemand[pid][i]);
        //printf("Req--- Demand[%d][%d] = %d\n",pid,i,demand[i]);*/

        if(demand[i] > MaxDemand[pid][i]) {
            //printf("Exit 1 Pid = %d \n",pid);
            pthread_mutex_unlock(&mutex);
            return -1;
        }
    }

    for(int i = 0; i< Number_Of_Resources_Types; i++) {
        Request[pid][i] = demand[i];
        //printf("R--- Request[%d][%d] = %d\n",pid,i,Request[pid][i]);
    }

    if(Handling == DEADLOCK_NOTHING ){

        //printf("Handling Type %d\n",Handling);

        int check = 0;

        for(int i = 0; i< Number_Of_Resources_Types; i++){

            /*printf("Req--- Request[%d][%d] = %d\n",pid,i,Request[pid][i]);
            //printf("Req--- Available[%d][%d] = %d\n",pid,i,Available[i]);*/

            if(Request[pid][i] > Available[i]){
                //check ++;
                //printf("--1 Pid = %d Available = %d %d %d Request = %d %d %d\n",pid,Available[0],Available[1],Available[2],Request[pid][0],Request[pid][1],Request[pid][2]);
                //printf("Waiting for signal, pid = %d\n",pid);
                pthread_cond_wait(&cond,&mutex);
                i = -1;
                //check++;
                //printf("Signal came for  pid = %d\n",pid);
                //printf("--2 Pid = %d Available = %d Request = %d\n",pid,Available[i],Request[pid][i]);
                //break;
            }

        }



        /*for(int i = 0; i< Number_Of_Resources_Types; i++){
            if(Request[pid][i] > Need[pid][i]){
                pthread_cond_wait(&cond,&mutex);
            }
        }*/

        //printf("pid = %d Request start check = %d\n",pid,check);

        if(check == 0) {
            for (int i = 0; i < Number_Of_Resources_Types; i++) {
                //printf("Req2--- Request[%d][%d] = %d\n", pid, i, Request[pid][i]);
                //printf("Req2--- Available[%d][%d] = %d\n", pid, i, Available[i]);

                Allocate[pid][i] += demand[i];
                Need[pid][i] -= demand[i];
                Available[i] -= demand[i];

                //printf("Req3--- Request[%d][%d] = %d\n", pid, i, Request[pid][i]);
                //printf("Req3--- Available[%d][%d] = %d\n", pid, i, Available[i]);

                //Available[i] += Allocate[pid][i];

                /*
                printf("Req--- Pid = %d\n",pid);
                printf("Req--- Allocate[%d][%d] = %d\n",pid,i,Allocate[pid][i]);
                printf("Req--- Need[%d][%d] = %d\n",pid,i,Need[pid][i]);
                printf("Req--- Available[%d][%d] = %d\n",pid,i,Available[i]);
                */

            }
        }
        /*if(check != 0){
            pthread_cond_wait(&cond,&mutex);
        }*/


    }

    if( Handling == DEADLOCK_AVOIDANCE){


        for(int i = 0; i< Number_Of_Resources_Types; i++){
            if(demand[i] > Available[i]){
                //printf("Avoidance Wait\n");
                pthread_cond_wait(&cond,&mutex);
            }
        }


        for(int i = 0; i< Number_Of_Resources_Types; i++){
            if(demand[i] > Need[pid][i]){
                pthread_cond_wait(&cond,&mutex);
            }
        }



        for(int i = 0 ; i < Number_Of_Resources_Types; i++){

            Allocate[pid][i] += demand[i];
            Need[pid][i] -= demand[i];
            Available[i] -= demand[i];
        }

        int procarray[Number_Of_Resources_Types];

        for(int i = 0 ; i < Number_Of_Resources_Types; i++){
            procarray[i] = -1;
        }

        int detect = Avoidance(procarray);



        for(int i = 0 ; i < Number_Of_Resources_Types; i++){
            Allocate[pid][i] -= Request[pid][i];
            Need[pid][i] += Request[pid][i];
            Available[i] += Request[pid][i];

            /*printf("Req3--- Req[%d][%d] = %d\n", pid, i, demand[i]);
            printf("Req3--- Available[%d][%d] = %d\n", pid, i, Available[i]);*/
        }


        //printf("Detect = %d\n",detect);

        if(detect != 0){
            printf("Deadlock Avoidance Detected = %d\n",detect);
            pthread_cond_wait(&cond,&mutex);
        }
        /*if(detect != 0){
            pthread_cond_wait(&cond,&mutex);
        }*/

        for(int i = 0 ; i < Number_Of_Resources_Types; i++){
            Allocate[pid][i] += Request[pid][i];
            Need[pid][i] -= Request[pid][i];
            Available[i] -= Request[pid][i];
        }

    }

    /*if(Handling == DEADLOCK_DETECTION){

        for(int i = 0; i< Number_Of_Resources_Types; i++){

            //printf("Req--- Request[%d][%d] = %d\n",pid,i,Request[pid][i]);
            //printf("Req--- Available[%d][%d] = %d\n",pid,i,Available[i]);

            if(Request[pid][i] > Available[i]){
                //check ++;
                printf("Waiting for signal, pid = %d\n",pid);
                pthread_cond_wait(&cond,&mutex);
                printf("Signal came for  pid = %d\n",pid);
            }

        }

        int procarray[Number_Of_Resources_Types];

        for(int i = 0 ; i < Number_Of_Resources_Types; i++){
            procarray[i] = -1;
        }
        pthread_mutex_unlock(&mutex);
        int detect = ralloc_detection(procarray);
        pthread_mutex_lock(&mutex);
        printf("Detect = %d, Pid = %d\n",detect,pid);

        if(detect != 0){
            printf("Deadlock Detection Detected\n");
            pthread_cond_wait(&cond,&mutex);
        }

        if(detect == 0){
            for(int i = 0 ; i < Number_Of_Resources_Types; i++){
                Allocate[pid][i] += demand[i];
                Need[pid][i] -= demand[i];
                Available[i] -= demand[i];
            }
        }
    }*/

    pthread_mutex_unlock(&mutex);
    //printf("Request pid = %d\n",pid);
    return(0); 
}

int ralloc_release (int pid, int demand[]) {

    pthread_mutex_lock(&mutex);
    if(Handling == DEADLOCK_NOTHING || Handling == DEADLOCK_AVOIDANCE ) {
        int check = 0;
        for (int i = 0; i < Number_Of_Resources_Types; i++) {
            if(Allocate[pid][i] == demand[i])
                check ++;
        }

        for (int i = 0; i < Number_Of_Resources_Types; i++) {

            //printf("Release1--- Request[%d][%d] = %d\n", pid, i, Request[pid][i]);
            //printf("Release1--- Available[%d][%d] = %d\n", pid, i, Available[i]);

            Allocate[pid][i] -= demand[i];
            Need[pid][i] += demand[i];
            Available[i] += demand[i];

            //printf("Release2--- Request[%d][%d] = %d\n", pid, i, Request[pid][i]);
            //printf("Release2--- Available[%d][%d] = %d\n", pid, i, Available[i]);
            //Available[i] -= Allocate[pid][i];
            //printf("Release2--- Request[%d][%d] = %d\n", pid, i, Request[pid][i]);
            //printf("Release2--- Available[%d][%d] = %d\n", pid, i, Available[i]);

        }
        pthread_cond_broadcast(&cond);
    }
    pthread_mutex_unlock(&mutex);
    //printf("Release pid = %d\n",pid);
    return (0); 
}

int ralloc_detection(int procarray[]) {

    //printf("Detection\n");

    pthread_mutex_lock(&mutex);


    //int TempMaxDemand[Number_Of_Processes][Number_Of_Resources_Types]; //MaxDemand
    //int TempNeed[Number_Of_Processes][Number_Of_Resources_Types]; //Need
    int TempAllocate[Number_Of_Processes][Number_Of_Resources_Types]; //Alocate

    int tempAvailable[Number_Of_Resources_Types]; //Available


    for(int i = 0 ; i < Number_Of_Resources_Types; i++){
        tempAvailable[i] = Available[i];
    }

    for(int i = 0 ; i < Number_Of_Processes; i++ )
        procarray[i] = 1;

    for(int i=0 ; i < Number_Of_Processes; i++){
        for(int j=0 ; j <Number_Of_Resources_Types ; j++){
            //TempMaxDemand[i][j] = MaxDemand[i][j];
            //TempNeed[i][j] = Need[i][j];
            TempAllocate[i][j] = Allocate[i][j];
        }
    }



    int resourceCheck = 0;
    //int procCount = 0;
    for(int a= 0; a < Number_Of_Processes;a++) {
        for (int i = 0; i < Number_Of_Processes; i++) {
            resourceCheck = 0;
            for (int j = 0; j < Number_Of_Resources_Types; j++) {
                //printf("Pid = %d -> Request[%d][%d] = %d\n",i,i,j,Request[i][j]);
                //printf("Pid = %d -> TempAvailable[%d] = %d\n",i,j,tempAvailable[j]);
                if (Request[i][j] > tempAvailable[j]) {
                    resourceCheck = 1;
                    break;
                }
            }
            if (resourceCheck == 0 && procarray[i]==1){

                for (int k = 0 ; k < Number_Of_Resources_Types ; k++)
                    tempAvailable[k] += TempAllocate[i][k];
                procarray[i] = -1;
            }
        }
    }



    /*for(int i = 0 ; i < Number_Of_Processes; i++){
        if(i != Number_Of_Processes -1) {
            printf("%i ->", procarray[i]);
        }
        else {
            printf("%i\n", procarray[i]);
        }
    }*/


    int count = 0;
    for(int i = 0; i< Number_Of_Processes ; i++){
        if(procarray[i] == 1){
            count++;
        }
    }
    pthread_mutex_unlock(&mutex);
    return (count);
}



int ralloc_end() {
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);

    Handling = 0; //Handling Type

    Number_Of_Processes = 0; // N

    Number_Of_Resources_Types = 0; // M

    for(int i = 0; i < MAX_PROCESSES; i++){
        for(int j = 0; j < MAX_RESOURCE_TYPES; j++){
            Exist[j] = 0;
            Available[j] = 0;
            Request[i][j] = 0;
            MaxDemand[i][j] = 0;
            Need[i][j] = 0;
            Allocate[i][j] = 0;
        }
    }



    return (0); 
}
