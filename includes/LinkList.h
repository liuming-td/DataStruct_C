#ifndef LINKLIST_H
#define LINKLIST_H

#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

typedef struct LNode
{
    ElemType data;
    struct LNode *next;    
}LNode,*LinkList;

/********************************************/
/* 链表的实现
/********************************************/

// 构造一个带头节点的空表，这个函数我没有调用，而且这个函数有问题，应该是为LinkList *L开辟一个空间。
// 直接参考下面的CreateList_L_ReverseOrder()函数即可
Status InitList_L(LinkList *L){
    LNode *emptynode = (LNode *)malloc(sizeof(LNode));
    if(!emptynode) exit(OVERFLOW);
    emptynode->next = NULL;
    emptynode->data = 0;         //头结点的数据域用于保存链表长度
    (*L)->data = 0;             
    (*L)->next = NULL;     //这里需不需要加取址符号？
    return OK;
}

// 当不设尾指针tail时，只能逆向建立单链表，即每次将新结点插入到头结点后
Status CreateList_L_ReverseOrder(LinkList *L,int n){
    (*L) = (LinkList) malloc(sizeof(LNode));
    if(!L) exit(OVERFLOW);
    (*L)->next = NULL;
    (*L)->data = 0;                 //代表链表保存的元素个数
    ElemType a;
    for (int i = 0; i < n; i++)
    {
        LNode *p = (LNode *)malloc(sizeof(LNode));
        scanf("%c",&a);
        p->data = a;
        p->next = (*L)->next;
        (*L)->next = p;
        (*L)->data++;
    }
    return OK;
}

Status ClearList_L(LinkList *L){
    for(int i = 0 ;i<(*L)->data;i++){
        LNode *p = (*L)->next;
        (*L)->next = p->next;
        free(p);
    }
    (*L)->data = 0;
    return OK;
}

Status DestroyList_L(LinkList *L){
    if((*L)->next == NULL){
        free(L); return OK;
    }else{
        ClearList_L(L);
        free(*L);
        return OK; 
    }
}

Status ListEmpty_L(LinkList L){
    if(L->data == 0 )return TRUE;
    else return FALSE;
}

int ListLength_L(LinkList L){
    return L->data;
}

Status GetElem_L(LinkList L,int i,ElemType *e){
    if(!L->next || i<1 || i>L->data) return ERROR;
    LNode *p = L;
    for(int j = 0; j<i ; j++){
        p = p->next;
    }
    *e = p->data;
    return OK;
}

Status Compare_L(ElemType e1,ElemType e2){
    return (e1 == e2)?TRUE:FALSE;
}

int LocateElem_L(LinkList L,ElemType e,Status(*Compare)(ElemType e1,ElemType e2)){
    if(!L->next)return ERROR;
    LNode *p = L->next;
    int cnt = 1;
    while (!Compare(p->data,e))
    {
        cnt++;
        if(p->next == NULL) return ERROR;
        p = p->next;
    }
    return cnt;
}

Status ListInsert_L(LinkList *L,int i ,ElemType e){
    // 在第i个结点前插入新结点
    if(i<1 || i>(*L)->data) return ERROR;
    LNode *newnode = (LNode *)malloc(sizeof(LNode));
    LNode *p = *L;
    for(int j = 1;j<i;j++){
        p = p->next;
    }
    newnode->next = p->next;
    p->next = newnode;
    newnode->data = e;
    (*L)->data++;
    return OK;
}

Status ListDelete_L(LinkList *L,int i ,ElemType *e){
    // 删除L中的第i个元素，并用e返回其值，L的长度减1
    if(i<1 || i>(*L)->data) return ERROR;
    LNode *p = *L, *q = NULL;
    for(int j = 1; j<i;j++){
        p = p->next;
    }
    q = p->next;
    p->next = p->next->next;
    *e = q->data; 
    free(q);
    (*L)->data--;
    return OK;
}

Status PriorElem_L(LinkList L,ElemType cur_e,ElemType *e){
    int pos = LocateElem_L(L,cur_e,Compare_L);
    if(!pos) return ERROR;
    if(GetElem_L(L,pos-1,e)) return OK;
}

Status NextElem_L(LinkList L,ElemType cur_e,ElemType *e){
    int pos = LocateElem_L(L,cur_e,Compare_L);
    if(!pos) return ERROR;
    if(GetElem_L(L,pos+1,e)) return OK;
}

Status visit_L(ElemType e){
    printf("%c\n",e);
    return OK;
}

Status ListTraverse_L(LinkList L,Status(*visit_L)(ElemType e)){
    if(!L->next) return ERROR;
    LNode *p = L->next;
    while(p->next){
        visit_L(p->data);
        p = p->next;
    }
    visit_L(p->data);
    //TODO:这部分程序能不能写得更好一点，这样功能也能实现，但是无可阅读性。
    return OK;
}


#endif