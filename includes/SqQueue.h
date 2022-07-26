#ifndef SQQUEUE_H
#define SQQUEUE_H

//顺序队列(循环队列)的实现

#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

#define MAXQSIZE 3      //队列最大长度

typedef struct SqQueue{
    ElemType *base;     //初始化的动态分配存储空间
    int front;          //头指针，若队列不空，指向队列头元素
    int rear;           //尾指针，若队列不空，指向队列尾元素的下一个位置
    int len;
}SqQueue;

//--------循环队列操作---------
Status InitQueue(SqQueue *Q){
    Q->base = (ElemType *)malloc(MAXQSIZE * sizeof(ElemType));
    if(!Q->base) exit(OVERFLOW);
    Q->front = Q->rear = 0;
    Q->len = 0;
    return OK;
}

Status DestroyQueue(SqQueue *Q){
    free(Q->base);
    Q->front = Q->rear = 0;
    Q->len = 0;
    return OK;
}

Status ClearQueue(SqQueue *Q){
    Q->front = Q->rear = 0;
    Q->len = 0;
    return OK;
}

Status QueueFilled(SqQueue Q){
    //返回队列是否已满
    return Q.len == MAXQSIZE ? TRUE : FALSE;
}

Status QueueEmpty(SqQueue Q){
    return Q.len == 0 ? TRUE : FALSE;
}

int QueueLength(SqQueue Q){
    return Q.len;
}

Status getHead(SqQueue Q,ElemType *e){
    if(!Q.len) return ERROR;
    *e = Q.base[Q.front];
    return OK;
}

Status EnQueue(SqQueue *Q,ElemType e){
    //如果队列未满，将元素插入到队尾，返回OK
    if(QueueFilled(*Q)) return ERROR;
    Q->base[Q->rear] = e;
    Q->rear++;
    if(Q->rear == MAXQSIZE) Q->rear = 0;
    Q->len++;
    return OK;
}

Status visit_Q(ElemType e){
    printf("%c\n",e);
    return OK;
}

Status DeQueue(SqQueue *Q,ElemType *e){
    //如果队列非空，将元素从队首取出，返回OK
    if(!Q->len) return ERROR;
    (*e) = Q->base[Q->front];
    Q->front++;
    if(Q->front == MAXQSIZE) Q->front = 0;
    Q->len--;
    return OK;
}

Status QueueTraverse(SqQueue Q,Status (*visit_Q)(ElemType e)){
    int pos = Q.front;
    for (int i = 0; i < Q.len; i++){
        visit_Q(Q.base[pos]);
        pos++;
        if(pos == MAXQSIZE) pos = 0;
    }
    return OK;
}


#endif