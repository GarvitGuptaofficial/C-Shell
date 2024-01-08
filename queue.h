#ifndef FUN_H
#define FUN_H


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct queue* Queue;

struct queue {
int element;
char * str;
Queue next;
Queue rear;
};

void Push(Queue head,int val,char*com);
int Pop(Queue head);
void find_delete(Queue head,int e);
#endif