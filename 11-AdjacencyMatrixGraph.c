#include <stdio.h>
#include <stdlib.h>
#include "SeqStack.h"
#include "SeqQueue.h"

#define MAXVEXNUM 256
#define MAXINT    2147483647
#define Status     int
#define VertexType char
#define ArcType    int

// 异常处理
#define OK     1
#define ERROR -1
#define TRUE   1
#define FALSE  0
#define OVERFLOW   2
#define UNDERFLOW -1

// 定义图的邻接矩阵存储类型
typedef struct {
    VertexType vertex[MAXVEXNUM];
    ArcType arc[MAXVEXNUM][MAXVEXNUM];
    int vexnum, arcnum;
} AMGraph;

// 函数声明


// 主程序
int main() {

    return 0;
}

// 函数定义
Status InitUDN(AMGraph *g, int vexnum) {
    if (!g) return ERROR;
    g->vexnum = vexnum;
    g->arcnum = 0;

    int i, j;
    for (i = 0; i < g->vexnum; i++) {
        for (j = 0; j < g->vexnum; j++) {
            g->arc[i][j] = MAXINT;
        }
    }
    return OK;
}

Status CreateUDN(AMGraph *g) {
    if (!g) return ERROR;

    int i, j;
    // 读取顶点
    for (i = 0; i < g->vexnum; i++) {
        scanf(" %c", &g->vertex[i]);
    }

    // 读取权重
    for (i = 0; i < g->vexnum; i++) {
        for (j = i+1; j < g->vexnum; j++) {
            scanf("%d", &g->arc[i][j]);
            g->arc[j][i] = g->arc[i][j];
            if (g->arc[i][j] < MAXINT) g->arcnum++;
        }
    }
    return OK;
}

Status DFSTraverse_MyWork(AMGraph *g, int start) {
    if (!g || start < 0) return ERROR;
    if (start > g->vexnum-1) return ERROR;

    // 建立一个数组，记录该下标的顶点是否被访问过
    int visited[g->vexnum], i;
    for (i = 0; i < g->vexnum; i++) visited[i] = 0;

    // 建立一个数组，存储访问路径
    int trajectory[2*g->vexnum];
    // for (i = 0; i < 2*g->vexnum; i++) trajectory[i] = -1;

    i = start; int j, vexfound = 1, w = 0, r;
    while (vexfound) {
        printf("%c ", g->vertex[i]);
        visited[i] = 1;
        trajectory[w++] = i;

        vexfound = 0;
        for (r = w-1; r >= 0; r--) {
            i = trajectory[r];
            for (j = 0; j < g->vexnum; j++) {
                if (g->arc[i][j] && !visited[j]) {
                    i = j;
                    vexfound = 1;
                    break;
                }
            }
            if (vexfound) break;
        }       
    }
    printf("\n");
    return OK;
}

Status DFSTraverse_Stack(AMGraph *g, int start) {
    if (!g || start < 0) return ERROR;
    if (start > g->vexnum-1) return ERROR;

    // 建立一个数组，记录该下标的顶点是否被访问过
    int visited[g->vexnum], i;
    for (i = 0; i < g->vexnum; i++) visited[i] = 0; 

    // 建立一个栈，容纳被访问的顶点
    SeqStack s; InitStack(&s);
    i = start; int j, found, count = 0;
    while (count < g->vexnum) {
        if (!visited[i]) {
            printf("%c ", g->vertex[i]);
            visited[i] = 1;
            count++;
        }
        
        found = 0;
        for (j = 0; j < g->vexnum; j++) {
            if (g->arc[i][j] && !visited[j]) {
                Push(&s, &i);
                i = j;
                found = 1;                              
                break;
            }           
        }
        if (!found) {
            if (!StackEmpty(&s)) Pop(&s, &i);
            else break;
        }
    }
    return OK;      
}

void DFSTraverse(AMGraph *g, int start, int *visited) {
    // if (!g || start < 0) return ERROR;
    // if (start > g->vexnum-1) return ERROR;

    printf("%c ", g->vertex[start]);
    visited[start] = 1;

    int j;
    for (j = 0; j < g->vexnum; j++) {
        if (g->arc[start][j] && !visited[j])
        DFSTraverse(g, j, visited);
    }
}

Status BFSTraverse(AMGraph *g, int start, int *visited) {
    if (!g || start < 0) return ERROR;
    if (start > g->vexnum-1) return ERROR;
    
    SeqQueue q; InitQueue(&q);
    int i = start, j;
    visited[start] = 1;
    while (i == start || !QueueEmpty(&q)) {
        printf("%c ", g->vertex[i]);

        for (j = 0; j < g->vexnum; j++) {
            if (g->arc[i][j] && !visited[j]) {
                EnQueue(&q, &j);
                visited[j] = 1;
            }
        }
        DeQueue(&q, &i);
    }
    return OK;
}