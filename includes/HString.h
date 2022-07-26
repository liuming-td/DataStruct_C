#ifndef HSTRING_H
#define HSTRING_H

#include <stdlib.h>
#include "utils.h"

//=====================串的实现====================
typedef struct HString{
    char *ch;           //若是非空串，则按串长分配存储区，否则ch为NULL,从ch[0]开始存储
    int length;         //串长度
}HString;

//====================串的基本操作==================
Status StrAssign(HString *T,const char *string){
    //生成一个其值等于串常量string的串T
    if(T->ch) free(T->ch);
    int len = 0;                
    while(string[len]){
        len++;              //求串长
    }
    T->ch = (char *)malloc(len * sizeof(char));     //重新分配空间
    if(!T->ch) exit(OVERFLOW);
    //T->ch = string; //感觉这句话有点问题，string指向的地址会在函数结束被释放，那么是不是应该对T->ch一一赋值？
    //这里的话，调试发现在函数结束后，string指向的地址没有被释放，但是保险起见还是一一赋值吧
    for (int i = 0; i < len; i++){
        T->ch[i] = string[i];
    }
    T->length = len;
    return OK;
}

Status StrLength(HString T){
    return T.length;
}

int StrCompare(HString T1,HString T2){
    //比较字符串是按照字符串中的字符一个个比较，只要一个字符不相同，那么就停止比较得出结果。
    //如果比较了的部分都相同，那么就按长度大小返回
    for (int i = 0; i < T1.length && i < T2.length; i++){
        if(T1.ch[i] != T2.ch[i]) return T1.ch[i]-T2.ch[i];
    }
    return T1.length - T2.length;
}

Status ClearString(HString *T){
    if(!T->ch) return ERROR;
    free(T->ch);
    T->ch = NULL;
    T->length = 0;
    return OK;
}

Status Concat(HString *T,HString S1,HString S2){
    //用T返回由S1和S2连接而成的新串
    if(T->ch) free(T->ch);
    T->ch = (char *)malloc((S1.length + S2.length) * sizeof(char));
    if(!T->ch) exit(OVERFLOW);
    for (int i = 0; i < S1.length; i++){
        T->ch[i] = S1.ch[i];
    }
    for (int i = 0; i < S2.length; i++)
    {
        T->ch[S1.length+i] = S2.ch[i];
    }
    T->length = S1.length + S2.length;
    return OK;
}

HString SubString(HString S,int pos,int len){
    //返回一个子串
    HString temp = {NULL,0};
    temp.ch = (char *)malloc(len * sizeof(char));
    if(!temp.ch) exit(OVERFLOW);
    for (int i = 0; i < len; i++){
        temp.ch[i] = S.ch[pos+i];
    }
    temp.length = len;
    return temp;
}

Status GetNext(HString T,int * next){
    //求解模式串T的next数组，赋值给next，返回OK
    if(T.length <= 0) return ERROR;

    int i = 0, j = -1;
    next[0] = -1; next[1] = 0;  //next[0]一定是-1，next[1]一定是0，不过next[1]=0可以不写，下面可以直接算出来
    
    while(i<T.length){
        if(j == -1|| T.ch[i] == T.ch[j]){
            ++i; ++j;
            next[i] = j;   
        } else {
            j = next[j];
        }
    }

    return OK;
}

int Index(HString S,HString T,int pos){
    //返回子串T在主串S中第pos个字符之后的位置。若不存在，则函数值为0
    //其中，T非空，0<=pos<=length-1
    //使用KMP算法
    //主串aabbcc，子串ab，pos=0，返回值1
    int * next = NULL;
    next = (int *)malloc(T.length * sizeof(int));
    if(!next) exit(OVERFLOW);
    if(!GetNext(T,next)) return ERROR;  //子串为空
    int i = 0,j = 0;
    
    while(i<T.length || j<T.length){
        if(S.ch[i] == T.ch[j] || j == -1){
                i++; j++;
            } else {
                j = next[j]; 
            }
    }
    if(j == T.length) return i - T.length;
    else return -1;   //没有找到子串
} 

Status StrInsert(HString *T,int pos, HString S){
    //0<=pos<=length(T),在串T的第pos个字符之前插入串S
    if(pos < 0 || pos>T->length) return ERROR;
    if (S.length){
        T->ch = (char *)realloc(T->ch,(T->length + S.length) * sizeof(char));
        if(!T->ch) exit(OVERFLOW);
        int len = T->length;
        for (int i = 0; i < len - pos; i++){
            T->ch[pos + S.length + i] = T->ch[pos + i];
        }
        for (int i = 0; i < S.length; i++){
            T->ch[pos+i] = S.ch[i];
        }
        T->length += S.length;
    }
    return OK;
}


#endif