#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 20

// 定义函数结束状态码
#define TRUE  1
#define FALSE 0
#define OK    1
#define ERROR 0

typedef int Status;   // 定义函数返回值的类型
typedef int ElemType; // 定义顺序表中元素的类型

// 定义结构体
typedef struct SeqList
{
    ElemType array[MAXSIZE];
    int length;
} SeqList;

// 函数声明
void PrintList(SeqList *l);
void InitList(SeqList *l);
Status CreateList(SeqList *l, int n);
Status ListEmpty(SeqList *l);
void ClearList(SeqList *l);
Status GetElem(const SeqList *l, int i, ElemType *e);
int LocateElem(const SeqList *l, const ElemType *e);
Status ListInsert(SeqList *l, int i, ElemType e);
Status ListDelete(SeqList *l, int i, ElemType *e);
int ListLength(const SeqList *l);
void ListUnion(SeqList *a, SeqList b);
Status MergeList(SeqList a, SeqList b, SeqList *c);

int main() {
    SeqList a, b, c;

    // 构建有序表a, b
    InitList(&a); InitList(&b);
    CreateList(&a, 3); CreateList(&b, 2);
    PrintList(&a); PrintList(&b);

    InitList(&c);
    MergeList(a, b, &c);
    PrintList(&c);
}

// 打印顺序表
void PrintList(SeqList *l) {
    int len = ListLength(l);
    printf("[");
    int i = 1;
    while (i < len) {
        printf("%d, ", l->array[i-1]);
        i++;
    }
    printf("%d]\n", l->array[len-1]);  
}

// 建立空的顺序表
void InitList(SeqList *l) {
    l -> length = 0;
}

// 构建顺序表
Status CreateList(SeqList *l, int n) {
    if (l->length || n > MAXSIZE || n < 0) {
        return ERROR;
    }
    int i = 1;
    while (i <= n) {
        ElemType e;
        scanf("%d", &e);
        l -> array[i-1] = e;
        i++;
    }
    l -> length = n; 
}

// 判断顺序表是否为空
Status ListEmpty(SeqList *l)
{
    if (l -> length) {
        return TRUE;
    } else {
        return FALSE;
    }  
}

// 清空列表
void ClearList(SeqList *l)
{
    l -> length = 0;
}

// 将顺序表的第i个元素返回给e
Status GetElem(const SeqList *l, int i, ElemType *e)
{
    if (i >= 1 && i <= l -> length)
    {
        *e = l->array[i-1];
        return OK;
    } else {
        return ERROR;
    }
}

// 查找与给定e相等的元素下标
int LocateElem(const SeqList *l, const ElemType *e)
{
    if (l -> length < 1) {
        return ERROR;
    } else {
        for (int i = 1; i <= l -> length; i++)
        {
            if (l -> array[i-1] == *e) 
            {
                return i;
            }
        }
        return ERROR;
    }
}

// 在顺序表的第i个位置插入元素e
Status ListInsert(SeqList *l, int i, ElemType e)
{
    if (i >= 1 && i <= (l -> length) + 1 && ++(l -> length) <= MAXSIZE) {
        for (int j = l->length; j > i; j--)
        {
            l -> array[j-1] = l -> array[j-2];
        }
        l -> array[i-1] = e;
        return OK;
    } else {
        return ERROR;
    }
} 

// 删除顺序表的第i个元素，并将其值返回给e
Status ListDelete(SeqList *l, int i, ElemType *e)
{
    if (i >= 1 && i <= l -> length)
    {   
        *e = l -> array[i-1];
        for (int j = i; j <= --(l -> length); j--)
        {
            l -> array[j-1] = l ->array[j];
        }
        return OK;
    } else {
        return ERROR;
    }
}

// 返回顺序表的长度
int ListLength(const SeqList *l)
{
    return l -> length;
}

// 求两个顺序表集合的并集
void ListUnion(SeqList *a, SeqList b) {
    int i = 1 ,a_len = ListLength(a), b_len = ListLength(&b);
    while (i <= b_len) {
        ElemType e_b = b.array[i-1];
        // 与a中的元素进行逐个比较
        int j = 1, exist = 0;
        while (j <= a_len) {
            ElemType e_a = a->array[j-1];
            if (e_a == e_b) {
                exist = 1;
                break;
            }
            j++;
        }
        if (!exist) {
            ListInsert(a, a->length+1, e_b);
        }
        i++;       
    }
}

// 两个有序表的合并
Status MergeList(SeqList a, SeqList b, SeqList *c) {
    int a_len = ListLength(&a), b_len = ListLength(&b);
    if ((a_len + b_len) > MAXSIZE) {
        return ERROR;
    }
    
    int i = 1, j = 1, b_finished = 0;
    while (i <= a_len) {
        ElemType e_a;
        GetElem(&a, i, &e_a);

        if (b_finished) {
            ListInsert(c, c->length+1, e_a);
            i++;
        } else {
            // 将a的元素e_a与b的元素e_b逐个比较
            while (j <= b_len) {
                ElemType e_b;
                GetElem(&b, j, &e_b);
                if (e_a < e_b) {
                    ListInsert(c, c->length+1, e_a);
                    i++;
                    break; 
                } else if (e_a == e_b) {
                    ListInsert(c, c->length+1, e_a);
                    ListInsert(c, c->length+1, e_b);
                    if (j == b_len) {
                        b_finished = 1;
                    }
                    i++; j++;
                    break;
                } else {
                    ListInsert(c, c->length+1, e_b);
                    if (j == b_len) {
                        b_finished = 1;
                    }
                    j++;
                }            
            }
        }
    }

    while (j <= b_len) {
        ElemType e_b;
        GetElem(&b, j, &e_b);
        ListInsert(c, c->length+1, e_b);
        j++;
    }
    return OK;   
}