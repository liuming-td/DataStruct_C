#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

//链队列的实现
typedef struct QNode{
    ElemType data;
    struct QNode * next;
}QNode;

typedef struct LinkQueue{
    QNode *front;
    QNode *rear;
}LinkQueue;

//链队列的基本操作
Status InitQueue(LinkQueue *Q){
    //头结点指向队头，尾结点指向队尾，front始终指向头结点，rear始终指向尾结点
    //头结点的数据域保存队列长度
    // 不用为LinkQueue *Q的Q申请空间，前提是在外部使用 LinkQueue Q定义了一个非指针类型的变量？
    Q->front = (QNode *)malloc(sizeof(QNode));
    if(!Q->front) exit(OVERFLOW);
    Q->front->data = 0;
    Q->front->next = NULL;
    Q->rear = Q->front;
    return OK;
}

Status DestroyQueue(LinkQueue *Q){
    //销毁包括头结点在内的所有结点，回收空间
    while (Q->front){
        Q->rear =Q->front->next;
        free(Q->front);
        Q->front = Q->rear;
    }
    return OK;
}

Status ClearQueue(LinkQueue *Q){
    //销毁除头结点尾结点外的其它结点，回收空间
    QNode *p = Q->front->next;
    while(p){
        Q->rear = p->next;
        free(p);
        p = Q->rear;
    }
    Q->front->next = p;     //p == NULL
    Q->front->data = 0;
    return OK;
}

Status QueueEmpty(LinkQueue Q){
    return Q.front->data == 0 ? TRUE : FALSE;
}

int QueueLength(LinkQueue Q){
    return Q.front->data;
}

Status getHead(LinkQueue Q,ElemType *e){
    //若队列不空，则用e返回Q的队头元素，并返回OK，否则返回error
    if(!Q.front->next) return ERROR;
    (*e) = Q.front->next->data;
    return OK;
}

Status EnQueue(LinkQueue *Q,ElemType e){
    //插入元素e为Q的新的队尾元素
    QNode *newnode = (QNode *)malloc(sizeof(QNode));
    if(!newnode) exit(OVERFLOW);
    newnode->data = e;
    newnode->next = NULL;
    Q->rear->next = newnode;
    Q->rear = newnode;
    Q->front->data++;
    return OK;
}

Status visit_Q(ElemType e){
    printf("%c\n",e);
    return OK;
}

Status DeQueue(LinkQueue *Q,ElemType *e){
    if(!Q->front->next) return ERROR;
    QNode *p = Q->front->next;      //将p指向待删除的队头元素
    Q->front->next = p->next;
    (*e) = p->data;
    free(p);
    Q->front->data--;
    if(Q->front->data == 0) Q->rear = Q->front; //当队列中没有节点了，尾结点要重新指向头结点
    return OK;
}

Status QueueTraverse(LinkQueue Q,Status (*visit_Q)(ElemType e)){
    //遍历链表
    if(!Q.front->next) return ERROR;
    QNode *p = Q.front->next;   //将p指向队头结点
    for (int i = 0; i < QueueLength(Q); i++){
        visit_Q(p->data);
        p = p->next;
    }
    return OK;
}

#endif