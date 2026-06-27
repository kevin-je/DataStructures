#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 20

// 定义函数结束状态码
#define TRUE  1
#define FALSE 0
#define OK    1
#define ERROR 0

typedef int Status;   // 定义函数返回值的类型
typedef int Elemtype; // 定义顺序表中元素的类型

// 定义结构体
typedef struct SeqList
{
    Elemtype array[MAXSIZE];
    int length;
} SeqList;

// 函数声明
void InitList(SeqList *l);
Status ListEmpty(SeqList *l);
void ClearList(SeqList *l);
Status GetElem(const SeqList *l, int i, Elemtype *e);
int LocateElem(const SeqList *l, const Elemtype *e);
Status ListInsert(SeqList *l, int i, Elemtype e);
Status ListDelete(SeqList *l, int i, Elemtype *e);
int ListLength(const SeqList *l);

int main() {

}

// 建立空的顺序表
void InitList(SeqList *l)
{
    l -> length = 0;
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
Status GetElem(const SeqList *l, int i, Elemtype *e)
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
int LocateElem(const SeqList *l, const Elemtype *e)
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
Status ListInsert(SeqList *l, int i, Elemtype e)
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
Status ListDelete(SeqList *l, int i, Elemtype *e)
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