#include <stdio.h>
#include <stdlib.h>

#define StackSize 16
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
typedef struct SeqStack {
    ElemType data[StackSize];
    int top;
} SeqStack;

// 函数声明
Status InitStack(SeqStack *s);
Status DestroyStack(SeqStack **s);
Status ClearStack(SeqStack *s);
Status StackEmpty(SeqStack *s);
int    StackLength(SeqStack *s);
Status Push(SeqStack *s, ElemType *e);
Status Pop(SeqStack *s, ElemType *e);
Status GetTop(SeqStack *s, ElemType *e);

// 主程序
int main() {

    return 0;
}

// 函数定义
Status InitStack(SeqStack *s) {
    if (!s) return ERROR;
    int top = 0;
    return OK;
}

Status DestroyStack(SeqStack **s) {
    if (!(*s)) return ERROR;
    free(*s);
    *s = NULL;
    return OK;
}

Status ClearStack(SeqStack *s) {
    if (!s) return ERROR;
    s->top = 0;
    return OK;
}

Status StackEmpty(SeqStack *s) {
    if (!s) return ERROR;
    if (s->top) return FALSE;
    else return TRUE;
}

int StackLength(SeqStack *s) {
    return s->top;
}

Status Push(SeqStack *s, ElemType *e) {
    if (s) return ERROR;
    if (s->top == StackSize) {
        return OVERFLOW;
    }

    s->data[s->top] = *e;
    s->top++;
    return OK;
}

Status Pop(SeqStack *s, ElemType *e) {
    if (!s) return ERROR;
    if (!s->top) return UNDERFLOW;

    *e = s->data[--(s->top)];
    return OK;
}

Status GetTop(SeqStack *s, ElemType *e) {
    if (!s) return ERROR;
    *e = s->data[s->top];
    return OK;
}