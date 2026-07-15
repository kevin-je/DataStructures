#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE  256
#define MAXLEAF  16
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
// 1、双亲表示法
typedef struct {
    ElemType e;
    int parent;
} PTNode;

typedef struct {
    PTNode array[MAXSIZE];
    int r, n;
} PTree;

// 2、孩子双亲表示法
typedef struct CTNode{
    int child;
    struct CTNode *next;
} CTNode;

typedef struct {
    ElemType data;
    int parent;
    CTNode *firstchild;
} CPNode;

typedef struct {
    CPNode array[MAXSIZE];
    int r, n;
} CPTree;

//  3、孩子兄弟表示法（二叉链表表示法）
typedef struct CSNode{
    ElemType data;
    struct CSNode *firstchild, *sibling;
} CSNode, *CSTree;

// 定义哈夫曼节点及哈夫曼树
typedef struct {int weight, parent, lch, rch} HTNode, *HTree;

// 定义哈夫曼编码表
typedef char *HuffmanCode[MAXLEAF+1];

// 函数声明
void InitHuffmanTree(HTree tree, int num_leaf);
Status Select(HTree tree, int k, int *p1, int *p2);
void CreateHuffmanTree(HTree tree, int num_leaf);
Status CreateHuffmanCode(HTree tree, int num_leaf, HuffmanCode *codelist);

// 主程序
int main() {

    return 0;
}

// 函数定义
void InitHuffmanTree(HTree tree, int num_leaf) {
    int i = 1, num_node = 2*num_leaf-1;
    while(i <= num_node) {
        tree[i].parent = tree[i].lch = tree[i].rch = 0;
        i++;
    }
}

Status Select(HTree tree, int k, int *p1, int *p2) {
    // // 寻找第一个和第二个双亲为0的节点
    // int i = 1, min1, min2, count = 0;
    // while (i <= k && count < 2) {
    //     if (tree[i].parent == 0) {
    //         if (count == 0) {
    //             min1 =  tree[i].weight;
    //             *p1 = i;
    //         }
    //         if (count == 1) {
    //             int temp = tree[i].weight;
    //             if (temp < min1) {
    //                 min2 = min1; min1 = temp; 
    //                 *p2 = *p1; *p1 = i;
    //             } else {min2 = tree[i].weight; *p2 = i;}
    //         }
    //         count++;
    //     }
    //     i++;
    // }
    // if (count < 2) return ERROR;

    // while(i <= k) {
    //     if (tree[i].parent == 0) {
    //         if (tree[i].weight <= min1) {
    //             min2 = min1;
    //             min1 = tree[i].weight;
    //             *p2 = *p1; *p1 = i;
    //         } else if (tree[i].weight < min2) {
    //             min2 = tree[i].weight;
    //             *p2 = i;
    //         }
    //     }
    //     i++;    
    // }
    // return OK;

    int i = 1; 
    *p1 = *p2 = 0;
    while (i <= k) {
        if (tree[i].parent != 0) continue;

        if (*p1 == 0 || tree[i].weight <= tree[*p1].weight) {
            *p2 = *p1;
            *p1 = i;
        } else if (*p2 == 0 || tree[i].weight < tree[*p2].weight) {
            *p2 = i;
        }
        i++;
    }
    return (*p2 && *p1) ? OK : ERROR;
}

void CreateHuffmanTree(HTree tree, int num_leaf) {
    // 输入二叉树的叶子节点
    int i = 1, weight;
    while(i <= num_leaf) {
        scanf("%d", &weight);
        tree[i++].weight = weight;
    }

    int p1, p2, k = num_leaf, num_node = 2*num_leaf-1;
    while(k <= num_node-1) {
        Select(tree, k, &p1, &p2);
        tree[p1].parent = tree[p2].parent = k+1;
        tree[k+1].weight = tree[p1].weight + tree[p2].weight;
        tree[k+1].lch = p1; tree[k+1].rch = p2;
        k++;
    }
}

Status CreateHuffmanCode(HTree tree, int num_leaf, HuffmanCode *codelist) {
    int i;
    char templist[num_leaf+1]; templist[num_leaf] = '\0';

    for (i = 1; i <= num_leaf; i++) {
        int j = tree[i].parent, child = i, k = num_leaf-1;
        while(j) {
            if (tree[j].lch == child) templist[k] = '0';
            else templist[k] = '1';
            k--; child = j; j = tree[j].parent;
        }
        (*codelist)[i] = (char*) malloc(num_leaf-k);
        if (!(*codelist)[i]) return ERROR;
        strcpy((*codelist)[i], templist+k+1);
    }
    return OK;
}