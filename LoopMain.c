#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "adts.c"


//enum for readablity
_Bool insertProc(short proc, short * count, struct PCB * root, struct PCB PCB_Table[20]);
_Bool removeHighestProc(struct PCB * root);
int sizeOfQueue(struct PCB * root);
void displayQueue(struct PCB * root, short * position);

int main()
{
    //seeding random number generator
    srand(time(NULL));
    short currentQueLen = 0;
    
    //init the PCB table and assign the processes in the correct format
    struct PCB pcbTable[20];
    _Bool inQueue[20];
    for(short i = 0; i < 20; i++)
    {
        inQueue[i] = 0;
        pcbTable[i].id = i;
        pcbTable[i].currentStatus = READY;
        //first test
    }

    

    //build inital queue
    struct PCB * q1Root;

}