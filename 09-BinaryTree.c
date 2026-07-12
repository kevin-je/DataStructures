#include <stdio.h>
#include <stdlib.h>
#include "SeqStack.h"
#include "SeqQueue.h"

#define MAXSIZE  256
#define Status   int
#define ElemType int

// 异常处理
#define OK     1
#define ERROR -1
#define TRUE   1
#define FALSE  0
#define OVERFLOW   2
#define UNDERFLOW -1

// 定义结构体
typedef ElemType SeqBiTree[MAXSIZE];
typedef struct BiNode{
    ElemType data;
    struct BiNode *lchild, *rchild;
} BiNode, *BiTreeLink;

// 函数声明
void PreOrderTraverse(BiNode *node);
void InOrderTraverse(BiNode *node);
void PostOrderTraverse(BiNode *node);
void InOrderTraverse_Stack(BiTreeLink tree);
void LevelOrderTraverse(BiTreeLink tree);
void CreateBiTree(BiNode **p);
void CopyBiTree(BiTreeLink tree, BiTreeLink *new);
int BiTreeDepth(BiTreeLink tree);
int NodeCount(BiTreeLink tree);
int LeafCount(BiTreeLink tree);

// 主程序
int main() {

    return 0;
}

// 函数定义
Status InitBiTree(BiTreeLink tree) {
   if (!tree) return ERROR;
   tree->lchild = tree->rchild = NULL; 
   return OK;
}

void PreOrderTraverse(BiNode *node) {
    if (!node) return;
    printf("%d ", node->data);  
    PreOrderTraverse(node->lchild);
    PreOrderTraverse(node->rchild);
}

void InOrderTraverse(BiNode *node) {
    if (!node) return;
    InOrderTraverse(node->lchild);
    printf("%d ", node->data);
    InOrderTraverse(node->rchild);
}

void PostOrderTraverse(BiNode *node) {
    if (!node) return;
    PostOrderTraverse(node->lchild);
    PostOrderTraverse(node->rchild);
    printf("%d ", node->data);
}

void InOrderTraverse_Stack(BiTreeLink tree) {
    // if (!tree) return ERROR;
    // SeqStack s;
    // InitStack(&s);
    // BiNode *p = tree;
    // struct ElemType e;
    // int status = OK;
    // while (status == OK) {
    //     if (p->lchild) {
    //         e.a = p->data; e.ptr = p;
    //         Push(&s, &e);
    //         p = p->lchild;
    //     } else {
    //         // 如果没有左分支，就打印自身
    //         printf("%d ", p->data);
    //         // 如果存在右分支
    //         if (p->rchild) p = p->rchild;
    //         // 如果不存在右分支
    //         else {
    //             status = Pop(&s, &e);
    //             p = e.ptr;
    //             ((BiNode *)p)->lchild = NULL;
    //         }
    //     }       
    // }
    // return OK;

    BiNode *p = tree, *q;
    SeqStack s; InitStack(&s);
    while(p || !StackEmpty(&s)) {
        if (p) {
            Push(&s, &p);
            p = p->lchild;
        } else {
            Pop(&s, &q);
            printf("%d ", q->data);
            p = q->rchild;
        }           
    }
}

void LevelOrderTraverse(BiTreeLink tree) {
    SeqQueue q;
    InitQueue(&q);
    EnQueue(&q, &tree);
    BiNode *p;
    while(!QueueEmpty(&q)) {
        DeQueue(&q, &p);
        if (p) {
            printf("%d ", p->data);
            EnQueue(&q, &p->lchild);
            EnQueue(&q, &p->rchild);
        }     
    }
}

void CreateBiTree(BiNode **p) {
    ElemType e;
    scanf("%d", &e);
    if (e == (int)'#') {
        *p = NULL;
        return;
    }

    *p = (BiNode*) malloc(sizeof(BiNode));
    if (!(*p)) exit(ERROR);

    (*p)->data = e;
    (*p)->lchild = (*p)->rchild = NULL;
    
    CreateBiTree(&(*p)->lchild);
    CreateBiTree(&(*p)->rchild);
}

void CopyBiTree(BiTreeLink tree, BiTreeLink *new) {
    if (!tree) {
        *new = NULL;
        return;
    }
    *new = (BiNode*) malloc(sizeof(BiNode));
    if (!(*new)) exit(ERROR);
    (*new)->data = tree->data;
    CopyBiTree(tree->lchild, &(*new)->lchild);
    CopyBiTree(tree->rchild, &(*new)->rchild);
}

int BiTreeDepth(BiTreeLink tree) {
    if (!tree) return 0;
    int l = BiTreeDepth(tree->lchild),
        r = BiTreeDepth(tree->rchild);
    return l>r ? l+1 : r+1;
}

int NodeCount(BiTreeLink tree) {
    if (!tree) return 0;
    int l = NodeCount(tree->lchild),
        r = NodeCount(tree->rchild);
    return l+r+1;
}

int LeafCount(BiTreeLink tree) {
    if (!tree) return 0;
    if (!tree->lchild && !tree->rchild) return 1;
    int l = LeafCount(tree->lchild),
        r = LeafCount(tree->rchild);
    return l+r;
}