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

// 定义边表结点类型
typedef struct ArcNode{
    int adjvex;
    ArcType weight;
    struct ArcNode *next;
} ArcNode;

// 定义顶点表的结点类型
typedef struct VexNode{
    VertexType vertex;
    ArcNode *firstarc;
} VexNode, AdjList[MAXVEXNUM];

typedef struct {
    AdjList vexlist;
    int vexnum, arcnum;
} ALGraph;

// 函数声明
Status InitUDN(ALGraph *g, int vexnum);
int LocateVex(ALGraph *g, VertexType vertex);

// 主程序
int main() {

    return 0;
}

// 函数定义(以无向网为例)
Status InitUDN(ALGraph *g, int vexnum) {
    if (!g) return ERROR;
    g->vexnum = vexnum;
    int i;
    for (i = 0; i < vexnum; i++) {
        g->vexlist[i].firstarc = NULL;
    }
    return OK;
}

int LocateVex(ALGraph *g, VertexType vertex) {
    if (!g) return ERROR;
    int i;
    for (i = 0; i < g->vexnum; i++) {
        if (g->vexlist[i].vertex == vertex) return i;
    }
    return ERROR;
}

Status CreateUDN(ALGraph *g) {
    if (!g) return ERROR;
    int i, j, arcnum = 0;
    // 读取所有顶点
    for (i = 0; i < g->vexnum; i++) {
        scanf(" %c", &g->vexlist[i].vertex);
    }

    // 读取每一个顶点所邻接的边
    int vexnum, adjvex;
    VertexType vertex;
    ArcType    weight;
    for (i = 0; i < g->vexnum; i++) {
        // 输入当前顶点有几个边
        scanf("%d", &vexnum);
        if (vexnum < 0) return ERROR;
        arcnum += vexnum;

        ArcNode *p, *node;
        for (j = 0; j < vexnum; j++) {
            scanf(" %c %d", &vertex, &weight);
            node = malloc(sizeof(ArcNode));
            if (!node) return ERROR;
            adjvex = LocateVex(g, vertex);
            if (adjvex == ERROR) return ERROR;
            node->adjvex = adjvex;
            node->next = NULL;
            node->weight = weight;

            if (j == 0) {
                g->vexlist[i].firstarc = node;
                p = node;
            }
            else {
                p->next = node;
                p = p->next;
            }
        }
    }
    g->arcnum = arcnum / 2;
    return OK;
}