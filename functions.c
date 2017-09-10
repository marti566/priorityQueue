/*
Jason Martin
9/9/2017
cs433 assignment 1
This program creates a list of process control blocks and organizes them into a priorityQueue.
it also has functionality for adding, removing processes from the queue, displaying the content and size of the queue.
this program takes input from the commandline for which test to run
*/

#include "functions.h"
#include <stdio.h>
#include <stdlib.h>


/*
PURPOSE: inserts a Process into the priority Queue
PARAMETERS: first a short int for the index of the process, a pointer to the pointer of the root of the queue, and the list of processes
RETURN: returns true on a successful addition
*/
_Bool insertProc(short proc, struct PCB **root, struct PCB PCB_Table[])
{
    PCB_Table[proc].currentStatus = READY;
    if (*root == 0)                         //case 1: tree is empty, insert as root
    {
        *root = &PCB_Table[proc];
        return 1;
    }
    else                                    //case 2: tree is not empty, traverse the tree until the point is found
    {
        struct PCB *traverse = *root;       //local traversal pointer so as to not affect the root while traversing
        while (traverse != 0)
        {

            if (traverse->priority <=
                PCB_Table[proc].priority)   //case 2a: traversal to the right
            {

                if (traverse->right == 0)   //case 2aa: right leaf is open insert into empty right leaf
                {
                    traverse->right = &PCB_Table[proc];
                    return 1;
                }
                else                        //case 2ab: no empty right leaf continue on to the right
                {
                    traverse = traverse->right;
                }
            }
                                            //case 2b: traverse left
            else
            {

                if (traverse->left == 0)    //case 2ba: left leaf is open, insert into empty leaf
                {

                    traverse->left = &PCB_Table[proc];
                    return 1;
                }
                else                        //case 2bb: left leaf is not open, continue traversal
                {
                    traverse = traverse->left;
                }
            }
        }
    }
    return 0;
}
/*
PURPOSE:Removes the highest priority process from the queue
PARAMETERS: takes a pointer to a pointer to the root of the tree, and a struct that contains the array of pcbs 
RETURN: returns the id of the process removed
*/
int removeHighestProc(struct PCB **root, struct PCB PCB_Table[])
{
    int popped = 0;                         // return variable
    if (*root == 0)                         // case 1 tree is empty
    {
        return -1;
    }

    struct PCB *traverse = *root;           // traversal pointer to protect root while traversing
    if (traverse->right != 0)               // case 2 root has a right branch/leaf
    {
        while (traverse->right->right != 0) //checking two ahead for the purpose of reassigning any children of the popped.
        {
            traverse = traverse->right;
        }
        popped = traverse->right->id;
        if (traverse->right->left != 0)     //case 2a: process to be popped has a left leaf, reassign to the parent of the popped
        {
            struct PCB *newRight = traverse->right->left; 
            
            traverse->right->left = 0;
            traverse->right = newRight;
        }
        else
        {
            traverse->right = 0;
        }
        PCB_Table[popped].currentStatus = RUNNING;
        return popped;
    }
    if (traverse->left != 0)                // case 3 root is non-null and has a left but no right, pop root
    {
        popped = traverse->id;
        *root = traverse->left;
        traverse->left = 0;
        PCB_Table[popped].currentStatus = RUNNING;        
        return popped;
    }

    popped = traverse->id;
    *root = 0;                              // case 4 root is the only object in the trees, pop root
    PCB_Table[popped].currentStatus = RUNNING;
    return popped;
}
/*
PURPOSE: counts the number of elements in the queue recoursively
PARAMETERS: takes a pointer to the root of the tree
RETURN: returns the number of elements
*/
int sizeOfQueue(struct PCB *root)
{
    int count = 0;
    if (root->left == 0 && root->right == 0)            //case 1: no leaves, add itself and return count
    {
        count++;
        return count;
    }
    else                                                //case 2: at least one leaf, call recoursively
    {
        if (root->left != 0)
        {
            count += sizeOfQueue(root->left);           //case 2a: left leaf present, call with left
        }
        if (root->right != 0)
        {
            count += sizeOfQueue(root->right);          //case 2b: right leaf present, call with right
        }
        count++;                                        //count itself
        return count;                                   //return
    }
}

/*
PURPOSE:begins the display recoursion
PARAMETERS: pointer to the tree based queue to be displayed
RETURN: none
*/
void displayQueue(struct PCB *root)
{
    short *position = malloc(sizeof(short));
    displayRecoursion(root,position);
}
/*
PURPOSE: recoursively displays the content of the queue
PARAMETERS: pointer to the root, pointer to a short for keeping track of position
RETURN:none
*/
void displayRecoursion(struct PCB *root, short *position)
{
    if (root == 0)                                                                  //case 1: absolute root is empty, only displayed if first iteration root is 0
    {
        printf("none in queue\n");
        return;
    }
    if (root->right == 0)                                                           //case 2: if root has no right leaf print root
    {
        printf("Process %-2i, in Position %-2i of the queue with priority %-2i.\n",
               root->id, *position, root->priority);
        *position += 1;
        if (root->left != 0)                                                        //check for left
        {
            displayRecoursion(root->left, position);                                //display left leaf tree
            return;
        }
        else                                                                        //no left, return
        {
            return;
        }
    }
    else                                                                            //case 3: there is a right
    {
        displayRecoursion(root->right, position);                                   //call recoursively to display the right
        printf("Process %-2i, in Position %-2i of the queue with priority %-2i.\n", //display itself
               root->id, *position, root->priority);
        *position += 1;
        if (root->left != 0)                                                        //check for left leaves
        {
            displayRecoursion(root->left, position);                                //display left leaves
            return;
        }
        else
        {
            return;
        }
    }
}

