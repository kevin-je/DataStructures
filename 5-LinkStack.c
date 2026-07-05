#include <stdio.h>
#include <stdlib.h>

#define ElemType int
#define Status   int

// 异常处理
#define OK     1
#define ERROR -1
#define TRUE   1
#define FALSE  0

// 定义结构体
typedef struct StackNode {
    ElemType e;
    struct StackNode *prior;
} StackNode, *LinkStack;

// 主程序
int main() {

    return 0;
}

// 函数定义
Status StackEmpty(LinkStack s) {
    if (s) return FALSE;
    else return TRUE;
}

Status Push(LinkStack *s, ElemType *e) {
    if (!e) return ERROR;
    StackNode *node = (StackNode*)malloc(sizeof(StackNode));
    if (!node) return ERROR;
    node->e = *e;
    node->prior = *s;
    *s = node;
    return OK;
}

Status Pop(LinkStack *s, ElemType *e) {
    if (!s || !e) return ERROR;
    if (!(*s)) return ERROR; 
    *e = (*s)->e;
    StackNode *temp = *s;
    *s = (*s)->prior;
    free(temp);
    return OK;
}