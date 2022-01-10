#include <stdio.h>
#include <stdlib.h>
#include "fatal.h"

#ifndef _QUEUE_H
#define _QUEUE_H
#define MaxVertexNum 100
#define MaxEdgeNum 100

typedef char VertexType;


typedef VertexType ET;

struct QueueRecord;
typedef struct QueueRecord* Queue;

int isEmpty(Queue Q);
int isFull(Queue Q);
Queue createQueue(int maxElements);
void disposeQueue(Queue Q);
void makeEmpty(Queue Q);
void enqueue(ET elem, Queue Q);
ET front(Queue Q);
void dequeue(Queue Q);
ET frontAndDequeue(Queue Q);

Queue initializeQueue(ET array[], int lengthArray);

#endif
