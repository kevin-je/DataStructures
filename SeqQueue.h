#ifndef SEQQUEUE_H
#define SEQQUEUE_H

#include <stdio.h>
#include <stdlib.h>

#define ElemType void*
#define Status   int
#define QUEUESIZE 16

// 异常处理
#define OK     1
#define ERROR -1
#define TRUE   1
#define FALSE  0

// 定义结构体
typedef struct SeqQueue {
    ElemType data[QUEUESIZE+1];
    int front;
    int rear;
} SeqQueue;

// 函数声明
Status InitQueue(SeqQueue *q);
Status ClearQueue(SeqQueue *q);
Status QueueEmpty(SeqQueue *q);
int QueueLength(SeqQueue *q);
Status EnQueue(SeqQueue *q, ElemType *e);
Status DeQueue(SeqQueue *q, ElemType *e);

// 函数定义
Status InitQueue(SeqQueue *q) {
    if (!q) return ERROR;
    q->front = q->rear = 0;
    return OK;
}

Status ClearQueue(SeqQueue *q) {
    if (!q) return ERROR;
    q->front = q->rear = 0;
    return OK;
}

Status QueueEmpty(SeqQueue *q) {
    if (!q) return ERROR;
    if (q->front == q->rear) return TRUE;
    else return FALSE;
}

int QueueLength(SeqQueue *q) {
    if (!q) return ERROR;
    if (q->front <= q->rear) return q->rear - q->front;
    else return q->rear + QUEUESIZE - q->front + 1;
}

Status EnQueue(SeqQueue *q, ElemType *e) {
    if (!q || !e) return ERROR;
    if (q->front-q->rear==1 || q->rear-q->front==QUEUESIZE)
    return ERROR;

    q->data[q->rear] = *e;
    q->rear = (q->rear+1) % (QUEUESIZE+1);
    return OK;
}

Status DeQueue(SeqQueue *q, ElemType *e) {
    if (!q || !e) return ERROR;
    if (q->front == q->rear) return ERROR;

    *e = q->data[q->front];
    q->front = (q->front+1) % (QUEUESIZE+1);
    return OK;
}

#endif