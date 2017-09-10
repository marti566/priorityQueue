#ifndef FUNCTIONS_H
#define FUNCTIONS_H

enum status
{
    NEW = 0,
    READY = 1,
    RUNNING = 2,
};
//holds the values of the PCB
struct PCB
{
    short id;
    short priority;
    enum status currentStatus;
    struct PCB * left;
    struct PCB * right;
};

_Bool insertProc(short proc, struct PCB ** root, struct PCB PCB_Table[20]);
int removeHighestProc(struct PCB ** root, struct PCB PCB_Table[20]);
int sizeOfQueue(struct PCB * root);
void displayQueue(struct PCB * root);
void displayRecoursion(struct PCB* root, short * position);
void treeState(struct PCB * root, int depth, int parent,char side);
#endif