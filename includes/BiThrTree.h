#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

typedef enum{Link,Thread} PointerTag;   // Link==0：指针，Thread==1：线索

typedef struct BiThrNode
{
    ElemType data;
    struct BiThrNode *lchild, *rchild;  //左右孩子指针
    PointerTag LTag,RTag;               //左右标志
}BiThrNode,*BiThrTree;

BiThrTree pre = NULL;

// 创建一棵线索二叉树
Status CreateBiThrTree(BiThrTree *T){
    ElemType a;
    scanf("%c",&a);
    if(' ' == a){
        *T = NULL;
        return OK;
    }else{
        *T = (BiThrNode *)malloc(sizeof(BiThrNode));
        (*T)->data = a;
        (*T)->LTag = Link;
        (*T)->RTag = Link;
        CreateBiThrTree(&(*T)->lchild);
        CreateBiThrTree(&(*T)->rchild);
    }
    return OK;
}

// 中序遍历线索化
void InThreading(BiThrTree T){
    if(T){
        InThreading(T->lchild);
        if(T->lchild != NULL){
            T->LTag = Thread;
            T->lchild = pre;
        }
        if(pre->rchild != NULL){
            pre->RTag = Thread;
            pre->rchild = T;
        }
        pre = T;
        InThreading(T->rchild);
    }
}

void InOrderThreading(BiThrTree *Thrt,BiThrTree T){     //因为要得到头节点的地址，所以传进来指针
    *Thrt = (BiThrNode *)malloc(sizeof(BiThrNode));
    (*Thrt)->LTag = Link;   (*Thrt)->RTag = Thread;
    (*Thrt)->rchild = *Thrt;
    if(!T) (*Thrt)->lchild = *Thrt;
    else{
        (*Thrt)->lchild = T;    pre = *Thrt;
        InThreading(T);
        (*Thrt)->rchild = pre;  
        pre->rchild = (*Thrt);  pre->RTag = Thread;
    }
}
