#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"


//enum for readablity


int main(int argc, char** argv)
{
    int choice = 0;
    int procRandInt = 0;
    int bumpInt = 0;
    int priorityRandInt = 0;
    int startDirection = 0;
    int iterator = 0;
    short * position = malloc(sizeof(short));
    *position = 0;
    srand(time(NULL));

    printf("Jason Martin\nmarti566@cougars.csusm.edu\n");
    if(argc != 2)
    {
        printf("usage: priorityQ <testNumber>");
    }
    else
    {
        choice = atoi(argv[1]);
        if(choice != 1 && choice != 2)
        {
            printf("Unable to parse arugments, please enter either 1 or 2.");
        }
    }
    

    
    //seeding random number generator
    

    //init the PCB table and assign the processes in the correct format
    struct PCB pcbTable[20];
    _Bool inQueue[20];
    for(short i = 0; i < 20; i++)
    {
        inQueue[i] = 0;
        pcbTable[i].id = i;
        pcbTable[i].currentStatus = READY;
        pcbTable[i].left = 0;
        pcbTable[i].right = 0;
        //first test
        pcbTable[i].priority = i;
    }

    

    //build inital queue
    struct PCB ** q1Root = malloc(sizeof(*q1Root));

    if(choice == 1)
    {
        insertProc(5,q1Root, pcbTable);
        insertProc(8,q1Root, pcbTable);
        insertProc(1,q1Root, pcbTable);
        insertProc(11,q1Root, pcbTable);

        printf("after adding 5,8,1,11:\n\n");
        displayQueue(*q1Root,position);
        printf("\n");
        *position = 0;


        removeHighestProc(q1Root);
        displayQueue(*q1Root,position);
        printf("\n");
        *position = 0;
    
        removeHighestProc(q1Root);
        displayQueue(*q1Root,position);
        printf("\n");
        *position = 0;

for(int i = 0; i < 1000000; i++)
{
    insertProc(15,q1Root, pcbTable);
    removeHighestProc(q1Root);
}

        insertProc(3,q1Root, pcbTable);
        insertProc(7,q1Root, pcbTable);
        insertProc(2,q1Root, pcbTable);
        insertProc(12,q1Root, pcbTable);
        insertProc(9,q1Root, pcbTable);

        printf("after adding 3,7,2,12,9:\n\n");
        displayQueue(*q1Root,position);
        *position = 0;
        printf("\n");

        while(*q1Root != 0)
        {
            removeHighestProc(q1Root);
            displayQueue(*q1Root,position);
            printf("\n");
            *position = 0;

        }

        printf("\n");
        free(q1Root);
        free(position);
        return 1; 
    }
    else if(choice == 2)
    {
        for(short i = 0; i < 10; i++)
        {
            procRandInt = rand();
            priorityRandInt = procRandInt % 50;
            procRandInt = procRandInt % 20;
            if(inQueue[procRandInt])
            {
                iterator = 1;
                startDirection = procRandInt % 2;
                    if(startDirection == 1)
                    {
                        while(inQueue[procRandInt])
                        {
                            if(iterator % 2 == 0)
                            {
                                procRandInt -= iterator;
                            }
                            else
                            {
                                procRandInt += iterator;
                            }
                            if(procRandInt - iterator < 0)
                            {  
                                while(inQueue[procRandInt])
                                {
                                    procRandInt += 1;
                                }
                            }
                            else if(procRandInt + iterator > 20)
                            {
                                while(inQueue[procRandInt])
                                {
                                    procRandInt -= 1;
                                }
                            }

                            
                        }
                    }
                    else
                    {
                        while(inQueue[procRandInt])
                        {
                            if(iterator % 2 == 1)
                            {
                                procRandInt -= iterator;
                            }
                            else
                            {
                                procRandInt += iterator;
                            }
                            if(procRandInt - iterator < 0)
                            {  
                                while(inQueue[procRandInt])
                                {
                                    procRandInt += 1;
                                }
                            }
                            else if(procRandInt + iterator > 20)
                            {
                                while(inQueue[procRandInt])
                                {
                                    procRandInt -= 1;
                                }
                            }

                            
                        }

                    }

            }
            pcbTable[procRandInt].priority = priorityRandInt;
            if(insertProc(procRandInt, q1Root,pcbTable))
            {
                inQueue[procRandInt] = 1;
            }
        }
        //time goes here
        for(int m = 0; m < 100000000; m++)
        {

            procRandInt = rand();
            startDirection = procRandInt % 2;
            if(startDirection)
            {
                //add a proc
                priorityRandInt = procRandInt % 50;
                procRandInt = procRandInt % 20;
                if(inQueue[procRandInt])
                {
                    iterator = 1;
                        if(startDirection)
                        {
                            while(inQueue[procRandInt])
                            {
                                if(iterator % 2 == 0)
                                {
                                    procRandInt -= iterator;
                                }
                                else
                                {
                                    procRandInt += iterator;
                                }
                                if(procRandInt - iterator < 0)
                                {  
                                    while(inQueue[procRandInt] && procRandInt < 20)
                                    {
                                        procRandInt += 1;
                                    }
                                    if(procRandInt > 19)
                                    break;
                                }
                                else if(procRandInt + iterator > 20)
                                {
                                    while(inQueue[procRandInt] && procRandInt > -1)
                                    {
                                        procRandInt -= 1;
                                    }
                                    if(procRandInt < 0)
                                    break;

                                }
    
                                
                            }
                        }
                        else
                        {
                            while(inQueue[procRandInt])
                            {
                                if(iterator % 2 == 1)
                                {
                                    procRandInt -= iterator;
                                }
                                else
                                {
                                    procRandInt += iterator;
                                }
                                if(procRandInt - iterator < 0)
                                {  
                                    while(inQueue[procRandInt] && procRandInt < 20)
                                    {
                                        procRandInt += 1;
                                    }
                                    if(procRandInt > 19)
                                    break;
                                }
                                else if(procRandInt + iterator > 20)
                                {
                                    while(inQueue[procRandInt] && procRandInt > -1)
                                    {
                                        procRandInt -= 1;
                                    }
                                    if(procRandInt < 0)
                                    break;
                                }
    
                                
                            }
    
                        }
    
                }
                else
                {
                    continue;
                }
                if(insertProc(procRandInt, q1Root,pcbTable))
                {
                    inQueue[procRandInt] = 1;
                }
            }
            else
            {
                bumpInt = removeHighestProc(q1Root);
                if(bumpInt > -1)
                {
                    inQueue[bumpInt] = 0;
                }
            
                //remove a proc
            }
        }
    }
}