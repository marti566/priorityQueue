

#include "functions.h"
#include <stdio.h>


_Bool insertProc(short proc, struct PCB ** root, struct PCB PCB_Table[])
{
    if(*root != 0)
    {
        struct PCB * traverse = *root;
        //traverse the binary tree to place the process
        while(traverse->right != 0)
        {
            
            if(traverse->priority <= PCB_Table[proc].priority)
            {
                
                if(traverse->right == 0)
                {
                    printf("traverse->right: %a\n",*traverse->right);
                    //adding the process to the tree
                    traverse->right = &PCB_Table[proc];
                    return 1;
                }
                else
                {
                    traverse = traverse->right;
                }
            }
            //traverse left side of the tree
            else
            {
                
                if(traverse->left == 0)
                {
                    //adding the process to the tree
                    traverse->left = &PCB_Table[proc];
                    return 1;
                }
                else
                {
                    traverse = traverse->left;
                }
            }
        }

    }
    else 
    {
        *root = &PCB_Table[proc];
        return 1;
    }
}

int removeHighestProc(struct PCB ** root)
{
    int popped = 0;
    if(*root == 0)
    {
        return -1;
    }
    struct PCB * traverse = *root;
    //protection for under flow taken care of before the function call
    if(traverse->right != 0)
    {
        while(traverse->right->right != 0)
        {
            traverse = traverse->right;
        }
        if(traverse->right->left != 0)
        {
            traverse->right = traverse->right->left;
        }
        else
        {
            popped = traverse->right->id;
            traverse->right->right = 0;
            traverse->right->left = 0;
            traverse->right = 0;
            return popped;
        }
    }
    else if(*root != 0)
    {
         //*root = *root->left; gave a compile error, i don't know why.
         //if root is the only node, left should be zero so it sets it to zero
         traverse = *root;
         *root = traverse ->left;
         traverse->left = 0;
         traverse->right = 0;  
         return traverse->id; 
    }
    else
    {
        return -1;
    }
    //change status
    //root->right.whatever status
}

int sizeOfQueue(struct PCB * root)
{
    int count = 0;
    if(root->left == 0 && root->right == 0)
    {
        count++;
        return count;
    }
    else
    {
        if(root ->left != 0)
        {
            count += sizeOfQueue(root->left);
        }
        if(root ->right != 0)
        {
            count += sizeOfQueue(root->right);
        }
        count++;
        return count;
    }
}

void displayQueue(struct PCB * root, short * position)
{
    if(root == 0)
    {
        printf("none in queue");
        return;
    }
    if(root->right == 0)
    {
        printf("Process %i, in Position %i of the queue with priority %i.\n", root->id, *position, root->priority);
        *position += 1;
        if(root->left != 0)
        {
            displayQueue(root->left, position);
            return;
        }
        else
        {
            return;
        }
        
    }
    else
    {
        displayQueue(root->right, position);
        printf("Process %i, in Position %i of the queue with priority %i.\n", root->id, *position, root->priority);
        *position += 1;
        if(root->left != 0)
        {
            displayQueue(root->left, position);
            return;
        }
        else
        {
            return;
        }
    }

}

void treeState(struct PCB * root, int depth, int parent,char side)
{
    if(root == 0)
    {
        return;
    }
   printf("node %i, depth %i, parent %i, side %c\n",root->id, depth, parent, side);
   if(root->right != 0)
   {
       treeState(root->right,depth+1,root->id,'r');
   }
   if(root->left != 0)
   {
       treeState(root->left,depth+1,root->id,'l');
   }
   return;
}
