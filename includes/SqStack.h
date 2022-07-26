/*******************************************************************************
* FileName:         SqStack.h
* Author:           Liuming
* Date:             2022/07/09 23:49
* Version:          v1.0
* Description:      Data Structure Experiment #4.1 顺序栈
*******************************************************************************/
#ifndef LINKSTACK_H
#define LINKSTACK_H

#include "utils.h"

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef struct SqStack{
   ElemType *base;
   ElemType *top;
   int stacksize;
}SqStack;

Status InitStack(SqStack *S){

}

Status DestroyStack(SqStack *S){
    
}

Status ClearStack(SqStack *S){
    
}

Status StackEmpty(SqStack S){
    
}

int StackLength(SqStack S){

}

Status GetTop(SqStack S,ElemType *e){

}

Status Push(SqStack *S,ElemType e){

}

Status Pop(SqStack *S,ElemType *e){

}

Status StackTraverse(SqStack S,Status (*visit)()){

}


#endif
