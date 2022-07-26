#ifndef SQLIST_H
#define SQLIST_H

#include <stdlib.h>
#include "utils.h"
#define LIST_INIT_SIZE 100      //线性表存储空间的初始分配量
#define LISTINCREMENT 10        //线性表存储空间的分配增量

typedef struct Sqlist
{
    ElemType *elem;             //存储空间基地址
    int length;                 //当前长度
    int listsize;               //当前分配的存储容量
}Sqlist;


/********************************************/
/* 顺序表的实现
/********************************************/

// 构造一个空的线性表
Status InitList_Sq(Sqlist *L){
    L->elem = (ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if(!L->elem)exit(OVERFLOW);
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;
    return OK;
}


// 销毁线性表
Status DestroyList_Sq(Sqlist *L){
    if(!L->elem) return INFEASIBLE;            //线性表不存在，TODO:这个不存在的条件要再想一下
    free(L->elem);
    L->length = 0;
    L->listsize = 0;
    return OK;
}

// 将线性表置为空表
Status ClearList_Sq(Sqlist *L){
    if(!L->elem) return INFEASIBLE;
    L->length = 0;  
    return OK;
}

// 线性表是否为空
Status ListEmpty_Sq(Sqlist L){
    if(!L.elem) return INFEASIBLE;
    if(L.length) return TRUE;
    return FALSE;
}

int ListLength_Sq(Sqlist L){
    if(!L.elem) return INFEASIBLE;
    return L.length;
}

Status GetElem_Sq(Sqlist L, int i, ElemType *e){
    if(!L.elem || i<1 || i>L.length) return INFEASIBLE;
    *e = L.elem[i-1];
    return OK;
}

Status Compare_Sq(ElemType e1,ElemType e2){
    return (e1 == e2)?TRUE:FALSE;
}

//TODO:函数指针，函数指针调用 文档记录一下
int LocateElem_Sq(Sqlist L, ElemType e,Status(*Compare)(ElemType e1,ElemType e2)){
    if(!L.elem) return INFEASIBLE;
    for(int i = 0;i<L.length;i++){
        if(Compare(L.elem[i],e)){
            return i+1;
        }else{
            continue;
        }
    }
    return ERROR;
}

Status PriorElem_Sq(Sqlist L,ElemType cur_e, ElemType * pre_e){
    if(!L.elem) return INFEASIBLE;
    int pos = LocateElem_Sq(L,cur_e,Compare_Sq);
    if(pos == ERROR || pos == 1) return ERROR;
    else {
        *pre_e = L.elem[pos-1-1];
        return OK;
    }
}

Status NextElem_Sq(Sqlist L, ElemType cur_e, ElemType *next_e){
    if(!L.elem) return INFEASIBLE;
    int pos = LocateElem_Sq(L,cur_e,Compare_Sq);
    if(pos == ERROR || pos == L.length) return ERROR;
    else{
        *next_e = L.elem[pos];
        return OK;
    }
}

// 这里必须传进来的是线性表的地址，否则所有更新都不会生效，随函数结束全部销毁。
Status ListInsert_Sq(Sqlist *L,int i, ElemType e){
    if(!L->elem || i < 1 || i > L->length+1) return INFEASIBLE;
    if(L->length+1>L->listsize) {
        ElemType *newbase = (ElemType *)realloc(L->elem,(L->listsize+LISTINCREMENT)*sizeof(ElemType));  //重新分配空间（加10）
        if(!newbase) exit(OVERFLOW);
        L->elem = newbase;
        L->listsize += LISTINCREMENT;
    }
    for(int j = L->length;j>i-1;j--){
        L->elem[j] = L->elem[j-1];
    }
    L->elem[i-1] = e;
    L->length += 1;
    return OK;
}

Status ListDelete_Sq(Sqlist *L,int i, ElemType *e){
    // 删除第i个元素，并将其存到e中
    if(!L->elem || i < 1 || i > L->length) return INFEASIBLE;
    *e = L->elem[i-1];
    for(int j = i;j<L->length;j++){
        L->elem[j-1] = L->elem[j];
    }
    L->length--;
    return OK;
}

Status visit_Sq(ElemType *e){
    printf("%c\n",*e);
    return OK;
}


// 遍历
Status ListTraverse_Sq(Sqlist L,Status (*visit_Sq)(ElemType *e)){
    if(!L.elem) return INFEASIBLE;
    for (int i = 0; i < L.length; i++)
    {
        visit_Sq(L.elem+i);
    }
    return OK;
}

#endif
/********************************************/
/* main函数代码测试
/********************************************/

// #include <stdio.h>
// #include "binaryTree.h"
// #include "BiThrTree.h"
// #include "SqList.h"

// int main(){
//     Sqlist L;
//     ElemType e;
//     printf("%d\n",InitList_Sq(&L));
    
//     printf("%d\n",ListInsert_Sq(&L,1,'a'));
//     ListInsert_Sq(&L,1,'b');

//     printf("\n");
//     ListTraverse_Sq(L,visit_Sq);
//     printf("\n");

//     ListDelete_Sq(&L,1,&e);
//     printf("%c\n",e);
//     printf("%d\n",ListLength_Sq(L));
//     printf("%d\n",LocateElem_Sq(L,'a',Compare_Sq));
//     printf("%d\n",DestroyList_Sq(&L));

//     return 0;
// }

/********************************************/
