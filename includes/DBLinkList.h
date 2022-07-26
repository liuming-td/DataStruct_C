/*******************************************************************************
* FileName:         DBLinkList.h
* Author:           liuming
* Date:             2022/07/08 21:02
* Version:          v1.0
* Description:      Data Structure Experiment #3 双向链表
*******************************************************************************/

#ifndef DBLINKLIST_H
#define DBLINKLIST_H

#include "utils.h"
#include <stdlib.h>

typedef struct DBNode           //结点类型
{
    ElemType data;
    struct DBNode *prior, *next;
}DBNode;

typedef struct DBLinkList       //双向链表类型
{
    DBNode *head, *tail;
    int len;
}DBLinkList;


/********************************************/
/* 双向链表的实现
/********************************************/

//双向链表的初始化(这里面的尾结点不知道干啥用的，就把尾结点的next指向头结点吧)
Status InitList_DB(DBLinkList *L){
    DBNode *emptynode = (DBNode *)malloc(sizeof(DBNode));
    if(!emptynode) exit(OVERFLOW);
    L->head = emptynode;
    L->head->next = L->head;      //头结点的后继指向自身
    L->head->prior = L->head;       //前驱也指向自己        
    L->tail = L->head;
    L->len = 0;
    return OK;
}

Status ListInsert_DB(DBLinkList *L, ElemType e,int location){
    //插入一个结点，location的合法值为[1,len+1]，插入成功返回OK
    if(location < 1 || location > L->len+1) return ERROR;
    DBNode *newnode = (DBNode *)malloc(sizeof(DBNode));
    newnode->data = e;
    DBNode *p = L->head;
    for(int i = 1; i < location; i++ ){
        p = p->next;
    }
    newnode->next = p->next;
    newnode->prior = p;
    newnode->next->prior = newnode;
    p->next = newnode;
    
    if(location == L->len + 1){ //插入的位置如果是表的最后，要修改尾结点
        L->tail = newnode;
        L->len++;       //长度的增1一定得写在这里
        return OK;
    }
    L->len++;
    return OK;
}

Status ListRemove_DB(DBLinkList *L,ElemType *e,int location){
    //删除一个结点，location的合法值为[1,len]，删除成功返回OK
    if(location < 1 || location > L->len) return ERROR;
    DBNode *p = L->head->next;
    for(int i = 1; i < location; i++ ){
        p = p->next;
    }
    *e = p->data;
    p->next->prior = p->prior;
    p->prior->next = p->next;

    //如果是删除表中最后一个结点，要修改尾结点
    if(location == L->len){
        L->tail = p->prior;
        free(p);
        L->len--;
        return OK;
    }
    free(p);
    L->len--;
    return OK;
}

int ListLength_DB(DBLinkList L){
    return L.len;
}

//基本上和ListRemove_DB 中的部分功能是一致的。
Status GetElem_DB(DBLinkList L,ElemType *e,int location){
    //获取指定位置的元素，location的合法值为[1,len]
    if(location < 1 || location > L.len) return ERROR;
    DBNode *p = L.head->next;
    for(int i = 1; i < location; i++ ){
        p = p->next;
    }
    *e = p->data;
    return OK;
}

//遍历双向链表，使用函数指针
Status TraverseList_DB(DBLinkList L){
    
}

Status BubbleSort_DB(DBLinkList *L){
    //对双向链表进行冒泡排序
}

#endif