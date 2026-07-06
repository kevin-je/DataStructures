#include <stdio.h>
#include <stdlib.h>

#define ElemType int
#define Status   int

// 异常处理
#define OK     1
#define ERROR -1
#define TRUE   1
#define FALSE  0
#define OVERFLOW   2
#define UNDERFLOW -1

// 定义结构体
typedef struct QNode {
    ElemType e;
    struct QNode *next;
} QNode;

typedef struct LinkQueue {
    QNode *front;
    QNode *rear;
} LinkQueue;

// 函数声明


// 主程序
int main() {

    return 0;
}

// 函数定义
Status InitQueue(LinkQueue *q) {
    if (!q) return ERROR;
    q->front = q->rear= (QNode*) malloc(sizeof(QNode));
    if (!(q->front)) return ERROR;
    return OK;
}

Status DestroyQueue(LinkQueue **q) {
    if (!(*q)) return ERROR;
    while ((*q)->front) {
        QNode *temp = (*q)->front->next;
        free((*q)->front);
        (*q)->front = temp;
    }
    free(*q);
    *q = NULL;
    return OK;
}

Status ClearQueue(LinkQueue *q) {
    if (!q) return ERROR;
    if (!q->front) return ERROR;
    QNode *p = q->front->next;
    while (p) {  
        QNode *temp = p->next;    
        free(p);
        p = temp;
    }
    q->rear = q->front;
    q->front->next = NULL;
    return OK;
}

Status QueueEmpty(LinkQueue *q) {
    if (!q || !q->front) return ERROR;
    if (q->front == q->rear) return TRUE;
    else return FALSE;
}

Status EnQueue(LinkQueue *q, ElemType *e) { 
    if (!q || !e) return ERROR;
    QNode *node = (QNode*) malloc(sizeof(QNode));
    if (!node) return ERROR;
    node->e = *e;
    node->next = NULL;
    q->rear = q->rear->next = node;   
    return OK;
}

Status Dequeue(LinkQueue *q, ElemType *e) {
    if (!q || !e || q->front==q->rear) return ERROR;
    *e = q->front->next->e;
    QNode *temp;
    temp = q->front->next->next;
    free(q->front->next);
    q->front->next = temp;
    if (!temp) q->rear = q->front;  
    return OK;
}