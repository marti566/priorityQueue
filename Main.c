#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

int main(int argc, char **argv)
{
    int choice = 0;             //holds commandline argument
    int procRandInt = 0;        //holds randomly generated int from rand()
    int bumpInt = 0;            //holds pid bumped from the queue
    int priorityRandInt = 0;    //holds randomly generated int for priority
    int startDirection = 0;     //holds 1 or 0 for which direction the adjustment for proc will go in
    int iterator = 0;           //used for iteration
    srand(time(NULL));          //setting seed for rand()


    printf("==========================================\n");
    printf("Jason Martin\nmarti566@cougars.csusm.edu\nCS433 Assignment 1\n");       //program setup and introduction
    printf("==========================================\n\n");
    if (argc != 2)
    {
        printf("usage:\t priorityQ <testNumber>\n");
    }
    else                                                                            //sanatize input
    {
        choice = atoi(argv[1]);
        if (choice != 1 && choice != 2)
        {
            printf("Unable to parse arugments, please enter either 1 or 2.");
        }
    }

                                                                                    
    struct PCB pcbTable[20];                        // init the PCB table and assign the processes in the correct format
    _Bool inQueue[20];                              // holds a t/f for if a process is already in the ready queue
    for (short i = 0; i < 20; i++)
    {
        inQueue[i] = 0;
        pcbTable[i].id = i;
        pcbTable[i].currentStatus = NEW;
        pcbTable[i].left = 0;
        pcbTable[i].right = 0;
        pcbTable[i].priority = i;
    }

    // build inital queue
    struct PCB **q1Root = malloc(sizeof(*q1Root));

    if (choice == 1)
    {
        insertProc(5, q1Root, pcbTable);            //insert 5 8 1 11
        insertProc(8, q1Root, pcbTable);
        insertProc(1, q1Root, pcbTable);
        insertProc(11, q1Root, pcbTable);

        printf("\nafter adding 5,8,1,11:\n\n");     //displaying queue
        displayQueue(*q1Root);
        printf("\n");
        

        removeHighestProc(q1Root,pcbTable);         //remvoing and displaying 
        displayQueue(*q1Root);
        printf("\n");
        

        removeHighestProc(q1Root,pcbTable);         //removing and displaying
        displayQueue(*q1Root);
        printf("\n");

        insertProc(3, q1Root, pcbTable);            //insert 3 7 2 12 9
        insertProc(7, q1Root, pcbTable);
        insertProc(2, q1Root, pcbTable);
        insertProc(12, q1Root, pcbTable);
        insertProc(9, q1Root, pcbTable);

        printf("after adding 3,7,2,12,9:\n\n");     //display queue
        displayQueue(*q1Root);
        printf("\n");

        while (*q1Root != 0)                        //remove all in the queue, display after each
        {
            removeHighestProc(q1Root,pcbTable);
            displayQueue(*q1Root);
            printf("\n");
        }

        printf("\n");       
        free(q1Root);       //memeory cleanup
        return 1;
    }
    else if (choice == 2)
    {
        for (short i = 0; i < 10; i++)                          //add inital 10 pcb's to the queue
        {
            procRandInt = rand();                               //generate random number and fill in needed areas
            priorityRandInt = procRandInt % 50;
            procRandInt = procRandInt % 20;
            if (inQueue[procRandInt])                           //if process is already in the queue, adjust alternating up/down or down/up depending on random number
            {
                iterator = 1;
                startDirection = procRandInt % 2;
                if (startDirection)                                         //alternating higher/lower starting with lower
                {
                    while (inQueue[procRandInt])
                    {
                        if (procRandInt - iterator > -1)
                        {
                            procRandInt = procRandInt - iterator;
                            iterator += 1;
                        }
                        else
                        {
                            while (inQueue[procRandInt] && procRandInt < 20) //if checked everything lower, check the rest of the higher
                            {
                                procRandInt += 1;
                            }
                            break;
                        }

                        if (procRandInt + iterator < 20)                    //alternating higher/lower doing higher second
                        {
                            procRandInt = procRandInt + iterator;
                            iterator += 1;
                        }
                        else
                        {
                            while (inQueue[procRandInt] && procRandInt > -1) //if checked everything higher, check the rest of the lower
                            {
                                procRandInt -= 1;
                            }
                            break;
                        }
                    }
                }
                else                                                         //alternating higher/lower starting with higher
                {
                    while (inQueue[procRandInt])
                    {

                        if (procRandInt + iterator < 20)                     //alternating higher/lower doing higher second
                        {
                            procRandInt = procRandInt + iterator;
                            iterator += 1;
                        }
                        else
                        {
                            while (inQueue[procRandInt] && procRandInt > -1)  //if checked everything higher, check the rest of the lower
                            {
                                procRandInt -= 1;
                            }
                            break;
                        }
                        if (procRandInt - iterator > -1)
                        {
                            procRandInt = procRandInt - iterator;
                            iterator += 1;
                        }
                        else
                        {
                            while (inQueue[procRandInt] && procRandInt < 20)//if checked everything lower, check the rest of the higher
                            {
                                procRandInt += 1;
                            }
                            break;
                        }
                    }
                }
            }
            if (procRandInt > 19 || procRandInt < 0) //if unable to find an open process, do nothing
            {
                continue;
            }
            pcbTable[procRandInt].priority = priorityRandInt;   //set new priority
            if (insertProc(procRandInt, q1Root, pcbTable))      //on a successful insert set queue to reflect new addition
            {
                inQueue[procRandInt] = 1;
            }
        }
        // time goes here
        struct timeval timer;
        gettimeofday(&timer,NULL);
        for (int m = 0; m < 1000000; m++)
        {
            procRandInt = rand();               //generate random number
            startDirection = procRandInt % 2;
            if (startDirection)                 //if adding a proc populate the rest of the values
            {
                priorityRandInt = procRandInt % 50;
                procRandInt = procRandInt % 20;
                if (inQueue[procRandInt])       //same shifting technique as before
                {
                    iterator = 1;
                    startDirection = procRandInt % 2;
                    if (startDirection)
                    {
                        while (inQueue[procRandInt])
                        {
                            if (procRandInt - iterator > -1)
                            {
                                procRandInt = procRandInt - iterator;
                                iterator += 1;
                            }
                            else
                            {
                                while (inQueue[procRandInt] && procRandInt < 20)
                                {
                                    procRandInt += 1;
                                }
                                break;
                                // finish in the opposite direction and return
                            }

                            if (procRandInt + iterator < 20)
                            {
                                procRandInt = procRandInt + iterator;
                                iterator += 1;
                            }
                            else
                            {
                                while (inQueue[procRandInt] && procRandInt > -1)
                                {
                                    procRandInt -= 1;
                                }
                                break;
                                // finish in the opposite direction and return
                            }
                        }
                    }
                    else
                    {
                        while (inQueue[procRandInt])
                        {

                            if (procRandInt + iterator < 20)
                            {
                                procRandInt = procRandInt + iterator;
                                iterator += 1;
                            }
                            else
                            {
                                while (inQueue[procRandInt] && procRandInt > -1)
                                {
                                    procRandInt -= 1;
                                }
                                break;
                                // finish in the opposite direction and return
                            }
                            if (procRandInt - iterator > -1)
                            {
                                procRandInt = procRandInt - iterator;
                                iterator += 1;
                            }
                            else
                            {
                                while (inQueue[procRandInt] && procRandInt < 20)
                                {
                                    procRandInt += 1;
                                }
                                break;
                                // finish in the opposite direction and return
                            }
                        }
                    }
                }
                if (procRandInt > 19 || procRandInt < 0)
                {
                    continue;
                }
                pcbTable[procRandInt].priority = priorityRandInt; //set prioirty
                if (insertProc(procRandInt, q1Root, pcbTable))    //insert process and set it as active in inQueue
                {
                    inQueue[procRandInt] = 1;
                }
            }
            else
            {
                bumpInt = removeHighestProc(q1Root,pcbTable); //remove highest proc and set it to bumpInt
                if (bumpInt > -1)                             //if successful update the inQueue
                {
                    inQueue[bumpInt] = 0;
                }

                // remove a proc
            }
        }
        struct timeval timerDone;                                   //calcuate final time and display final queue
        gettimeofday(&timerDone, NULL);
        suseconds_t finalTime = timerDone.tv_usec - timer.tv_usec;
        printf("done in %lu mu. or %f ms.\nFinal Queue:\n", finalTime, ((double)finalTime)/1000);
        displayQueue(*q1Root);
        
    }
}
