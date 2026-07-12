#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN   255
#define Status   int

// 异常处理
#define OK     1
#define ERROR -1
#define TRUE   1
#define FALSE  0
#define FAIL 0

// 定义字符串类型
typedef char SeqString[MAXLEN+1];

// 函数声明
int StringLength(SeqString s);
void InitString(SeqString s);
Status CreateString(SeqString s);
int Index_BF(SeqString s, SeqString t);
Status get_next(SeqString t, int *next);
Status get_nextval(SeqString t, int *next);
int Index_KMP(SeqString s, SeqString t);

// 主程序
int main() {
    SeqString s, t;
    InitString(s); InitString(t);
    CreateString(s); CreateString(t);
    printf("BF:  %d\n", Index_BF (s, t));
    printf("KMP: %d\n", Index_KMP(s, t));
    return 0;
}

// 函数定义
int StringLength(SeqString s) {
    return (unsigned char) s[0];
}

void InitString(SeqString s) {
    s[0] = (unsigned char) 0;
}

Status CreateString(SeqString s) {
    if (!fgets(s+1, MAXLEN, stdin)) return ERROR;
    int s_len = strlen(s+1);
    if (s[s_len] == '\n') s_len--;
    s[0] = (unsigned char) s_len;
    return OK;
}

int Index_BF(SeqString s, SeqString t) {
    int s_len = StringLength(s), t_len = StringLength(t);
    if (s_len < t_len || t_len < 1) return ERROR;

    int i=1, j=1;
    while (i <=s_len && j <= t_len) {
        if (s[i] == t[j]) {
            if (j == t_len) return i-j+1;
            else {i++; j++;}
        } else {
            i = i-j+2;
            j = 1;
        }
    }
    return FAIL;
}

Status get_next(SeqString t, int *next) {
    int t_len = StringLength(t);
    if (!next || !t_len) return ERROR;  
    next[0] = 0;
    if (t_len > 1) next[1] = 1;

    int k = 1, j = 3;
    while (j <= t_len) {
        if (k == 0 || t[k] == t[j-1]) {
            k++; next[j-1] = k; j++;
        } else {
            k = next[k-1];
        }
    }
    return OK;
}

Status get_nextval(SeqString t, int *next) {
    int t_len = StringLength(t);
    if (!next || !t_len) return ERROR;  
    next[0] = 0;
    if (t_len > 1) next[1] = 1;

    int k = 1, j = 3;
    while (j <= t_len) {
        if (k==0 || t[k] == t[j-1]) {
            k++;
            if (t[j] == t[k]) next[j-1] = next[k-1];
            else next[j-1] = k;
            j++;
        } else {
            k = next[k-1];
        }
    }
    return OK;
}

int Index_KMP(SeqString s, SeqString t) {
    int s_len = StringLength(s), t_len = StringLength(t);
    if (t_len < 1 || s_len < t_len) return ERROR;
    int next[t_len], i=1, j=1;
    get_nextval(t, next);

    while (i <= s_len && j <= t_len) {
        if (s[i] == t[j]) {
            if (j == t_len) return i-j+1;
            i++; j++;
        }
        else {
            j = next[j-1];
            if (j == 0) {j = 1; i++;}
        }
    }
    return FAIL;
}