/*******************************************************************************
* FileName:         LinkStack.h
* Author:           Liuming
* Date:             2022/07/09 23:49
* Version:          v1.0
* Description:      Data Structure Experiment #4.2 链栈
*******************************************************************************/
#ifndef LINKSTACK_H
#define LINKSTACK_H

#include "utils.h"

typedef struct StackNode{
    ElemType data;
    StackNode *next;
}StackNode;

typedef struct LinkStack{
    StackNode *head;        //头结点的data域保存链栈长度
}LinkStack;

Status InitStack(LinkStack *S){

}

Status DestroyStack(LinkStack *S){
    
}

Status ClearStack(LinkStack *S){
    
}

Status StackEmpty(LinkStack S){
    
}

int StackLength(LinkStack S){

}

Status GetTop(LinkStack S,ElemType *e){

}

Status Push(LinkStack *S,ElemType e){

}

Status Pop(LinkStack *S,ElemType *e){

}

Status StackTraverse(LinkStack S,Status (*visit)()){

}

#endif
