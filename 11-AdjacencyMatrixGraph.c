#include <stdio.h>
#include <stdlib.h>

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