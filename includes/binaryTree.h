#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <stdlib.h>
#include <stdio.h>
#include "utils.h"


#define RECURSION TRUE

typedef struct BiTNode
{
    ElemType data;
    struct BiTNode *lchild,*rchild;    
}BiTNode,*BiTree;                       // BiTree为一级指针



// 创建一棵二叉树
// 这段程序，只有在输入了足够多的空格' '的时候，才能正常退出，否则程序会不断索要输入
// 明白其机制了，每出现一个空格就代表一个“空结点”，将整棵树以“空结点”填充满才会退出递归
Status CreatBiTree(BiTree *T){          //这里BiTree本身为一级指针，因此T为二级指针，即指向指针的指针
    // 按先序次序输入二叉树中的结点（一个字符），空格表示空树
    // 构造二叉链表表示的二叉树T
    ElemType a;
    scanf("%c",&a);

    if(a==' '){
        *T = NULL;                      //*T才是我们定义的二叉树
        return OK;                      //返回值只能退出一层递归
    } else{
        *T = (BiTNode *)malloc(sizeof(BiTNode));
        // (*T)->data = a; 写在哪里就是什么次序的构建二叉树，当前为先序创建
        (*T)->data = a;
        CreatBiTree(&(*T)->lchild);     //(*T)->lchild为一级指针，因此需要再取地址才是二级指针
        CreatBiTree(&(*T)->rchild); 
    }
    return OK;
}   

// 访问二叉树
void visit(ElemType data){
    printf("%c",data);
}

#if RECURSION == TRUE
// 前序遍历
void PreOrderTraverse(BiTree T){
    if(T){
        visit(T->data);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}

// 中序遍历
void InOrderTraverse(BiTree T){
    if(T){
        InOrderTraverse(T->lchild);
        visit(T->data);
        InOrderTraverse(T->rchild);
    }
}

// 后序遍历
void PostOrderTraverse(BiTree T){
    if(T){
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        visit(T->data);
    }
}
#endif  // endif of #if RECURSION == TRUE

//TODO:待栈、队列代码实现之后来完善这部分代码
#if RECURSION == FALSE  // 非递归遍历（前序、中序、后序（需要用到栈）、层序（需要用到队列））
// 前序遍历
void PreOrderTraverse(BiTree T){
    
}

// 中序遍历
void InOrderTraverse(BiTree T){
    
}

// 后序遍历
void PostOrderTraverse(BiTree T){
    
}
#endif


#endif  // endif of #define BINARYTREE_H


/********************************************/
/* main函数代码测试
/********************************************/

// #include <stdio.h>
// #include "binaryTree.h"
// #include "BiThrTree.h"
// #include "SqList.h"

// int main(){
//      printf("hello world!\n");
//      BiThrTree Thrt,T = NULL;
//      CreateBiThrTree(&T);
//      InOrderThreading(&Thrt,T);
//      while(Thrt){
//          printf("%c\n",Thrt->data);
//      }
//     return 0;
// }

/********************************************/