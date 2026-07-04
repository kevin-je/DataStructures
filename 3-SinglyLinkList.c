#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义函数返回状态
#define TRUE  1
#define FALSE 0
#define OK    1
#define ERROR 0
typedef int Status;

// 定义节点元素类型：学生成绩
typedef struct {
    char id[16];
    char name[8];
    int  score;
} ElemType;

// 定义节点类型
typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

// 函数声明
Status PrintElem(ElemType *e);
Status InitList(LinkList *l);
Status ListEmpty(LinkList l);
Status ListDestroy(LinkList l);
Status ListClear(LinkList l);
int ListLength(LinkList l);
Status GetElem(LinkList l, int i, ElemType *e);
int LocateElem(LinkList l, ElemType *e);
Status ListInsert(LinkList l, int i, ElemType *e);
Status ListDelete(LinkList l, int i);
Status CreateList_H(LinkList *l, int n);
Status CreateList_T(LinkList *l, int n);
void MergeList(LinkList a, LinkList b, LinkList c);

int main() {
    // LinkList l;
    // CreateList_R(&l, 1);
    // // 获取首元节点的数据
    // ElemType e;
    // GetElem(l, 1, &e);
    // // 打印首元节点
    // PrintElem(&e);
    // return 0;

    LinkList a, b, c;
    CreateList_T(&a, 1); CreateList_T(&b, 2); InitList(&c);
    MergeList(a, b, c);
    printf("[");

    // 打印c的每个数据域
    LNode *p = c -> next;
    for (int i = 1; i <= ListLength(c); i++)
    {
        ElemType e = p -> data;
        PrintElem(&e);
        if (i != ListLength(c)) {
            printf(",\n\n");
        } else {printf("]\n");}       
        p = p -> next;
    }
    return 0;   
}

// 函数定义
Status PrintElem(ElemType *e) {
    if (!e) {
        return ERROR;
    }
    printf("ID: %s\nName: %s\nScare: %d", e->id, e->name, e->score);
    return OK;
}

Status InitList(LinkList *l) {
    *l = (LNode*) malloc(sizeof(LNode));
    if (*l) {
        (*l) -> next = NULL;
        return OK;
    } else {
        return ERROR;
    }   
}

Status ListEmpty(LinkList l) {
    if (l -> next) {
        return FALSE;
    } else {
        return TRUE;
    }
}

Status ListDestroy(LinkList l) {
    LNode *p = l;
    while (p) {
        LNode *temp = p -> next;
        free(p);
        p = temp;
    }
    return OK;   
}

Status ListClear(LinkList l) {
    LNode *p = l -> next; // 获取首元节点的地址
    l -> next = NULL; // 使头节点的地址域为NULL
    LNode *temp;
    while (p) {
        temp = p -> next;
        free(p);
        p = temp;
    }
    return OK;
}

int ListLength(LinkList l) {
    LNode *p = l -> next; // 获取首元节点的地址
    int count = 0;
    while (p) {
        count++;
        p = p -> next;
    }
    return count;
}

Status GetElem(LinkList l, int i, ElemType *e) {
    // int length = ListLength(l);
    // if (i >= 1 && i <= length) {
    //     LNode *p = l -> next; // 获取首元节点的地址
    //     for (int j = 2; j <= i; j++) {
    //         p = p -> next;
    //     }
    //     *e = p -> data;
    //     return OK;
    // } else {
    //     return ERROR;
    // }

    LNode *p = l -> next;
    if (i < 1 || !p) {
        return ERROR;
    }

    int j = 2;
    
    while (j <= i) {
        p = p -> next;
        if (!p) {
            return ERROR;
        } else {
            j++;
        }
    }

    *e = p -> data;
    return OK;
} 

int LocateElem(LinkList l, ElemType *e) {
    LNode *p = l -> next; // 获取首元节点的地址
    if (!p || !e) {
        return ERROR;
    }

    int i = 1;
    while (p) {        
        if (!strcmp((p->data).id, e->id)
            && !strcmp((p->data).name, e->name)
            && (p->data).score == e->score) { 
            return i;
        }
        p = p -> next; // 获取下一节点的地址
        i++;
    }
    return ERROR;
}

Status ListInsert(LinkList l, int i, ElemType *e) {
    // 输入参数检查
    if (i < 1 || !l) {
        return ERROR;
    }
    LNode *p = l; // 获取头节点的地址   
    int count = 1; // count表示第j个节点

    // 获取第i-1个节点的地址p
    while (count <= i-1) {
        p = p -> next;
        if (!p) {
            return ERROR;
        }
        count++;
    }
    
    // 新建一个节点
    LNode *node;
    node = (LNode*) malloc(sizeof(LNode));
    if (!node) {
        return ERROR;
    }
    node -> data = *e;
    node -> next = p -> next;
    
    // 更新第i-1个节点的next成员
    p -> next = node;
    return OK;
}

Status ListDelete(LinkList l, int i) {
    if (!l || i < 1) {
        return ERROR;
    }

    // 寻找第i-1个节点的地址
    LNode *p = l;
    int j = 1;
    while (j <= i-1) {
        p = p -> next;
        if (!p) {
            return ERROR;
        }
        j++;
    }
    LNode *q = p -> next; // 获取第i个节点的地址
    if (!q) {
        return ERROR;
    }

    p -> next = q -> next;
    free(q);  
    return OK;
}

Status CreateList_H(LinkList *l, int n) {
    // 创建头节点
    *l = (LNode*) malloc(sizeof(LNode));
    if (!(*l)) {
        return ERROR;
    }
    (*l) -> next = NULL;

    // 将第j个节点写入链表
    int j = n;
    while (j >= 1) {
        LNode *node = (LNode*) malloc(sizeof(LNode));
        if (!node) {
            return ERROR;
        }
        // 写入数据域
        scanf("%s", node->data.id);
        scanf("%s", node->data.name);
        scanf("%d", &(node->data.score));
        // 写入指针域
        node->next = (*l)->next;
        (*l)->next = node;

        j--;
    }
    return OK;
}

Status CreateList_T(LinkList *l, int n) {
    if (n < 0 || !l) {
        return ERROR;
    }
    // 创建头节点
    *l = (LNode*) malloc(sizeof(LNode));
    if (!(*l)) {
        return ERROR;
    }
    (*l) -> next = NULL;

    int i = 1;
    LNode *front = *l; // front用于保留前一个节点的地址
    while (i <= n) {
        // 创建第i个节点
        LNode *node;
        node = (LNode*) malloc(sizeof(LNode));
        if (!node) {
            return ERROR;
        }
        scanf("%s", node->data.id);
        scanf("%s", node->data.name);
        scanf("%d", &(node->data.score));
        node->next = NULL;
        front->next = node;
        front = node;

        i++;
    }
    return OK;
}

void MergeList(LinkList a, LinkList b, LinkList c) {
    // 获取首元节点的地址
    LNode *pa = a -> next, *pb = b -> next;
    int pos = 1; // 记录插入位置
    
    while (pa && pb) {
        int sa = pa -> data.score, sb = pb -> data.score;
        ElemType ea = pa -> data, eb = pb -> data;
        if (sa > sb) {
            ListInsert(c, pos, &eb);
            pb = pb -> next;
        } else {
            ListInsert(c, pos, &ea);
            pa = pa -> next;
        }
        pos++;
    }

    LNode *p = pa? pa: pb;
    while (p) {
        ListInsert(c, pos, &(p->data));
        p = p -> next;
        pos++;
    }   
}