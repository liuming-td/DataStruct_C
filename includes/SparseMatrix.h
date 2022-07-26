#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

/********************************************/
/* 稀疏矩阵的实现
/* 存在三种表示方法
/* 1. 三元组顺序表 2. 行逻辑链接的顺序表 3. 十字链表
/********************************************/

#define METHOD TRIPLE  //TRIPLE 三元组；ROWLOGIC 行逻辑；CROSSLIST 十字链表

#include <stdlib.h>
#include "utils.h"
#include <stdio.h>

#if METHOD == TRIPLE

#define MAX_SIZE 12500
//二维稀疏矩阵
typedef struct Triple{
    int i,j;        //该非零元的行标和列标
    ElemType e;
}Triple;

// data域中表示非零元的三元组是以行序为主序顺序排列的
typedef struct TSMatrix{
    Triple data[MAX_SIZE+1];    //data[0]未用,可以考虑换成基地址，这样可以手动申请和释放空间
    int mu,nu,tu;               //矩阵的行数、列数和非零元个数
}TSMatrix;

Status CreateSMatrix(TSMatrix *M,int mu,int nu){
    //创建稀疏矩阵M
    M->tu = 0;  M->mu = mu; M->nu = nu;    
    return OK;
}

Status DestroySMaxtrix(TSMatrix *M){
    // 采用这种TSMatrix的定义方式时，data预先定义了MAX_SIZE+1个空间
    // 无法手动回收这部分空间，只能等到程序运行结束系统自动回收这部分空间
    for (int i = 1; i < M->tu+1; i++)
    {
        M->data[i].e = '0';
    }
    M->mu = M->nu = M->tu = 0;
    return OK;
}

Status PrintSMmatrix(TSMatrix M){
    int count = 1;
    for (int i = 1; i < M.mu+1; i++){   //按行打印
        for (int j = 1; j < M.nu+1; j++){
            if(M.data[count].i == i && M.data[count].j == j){
                printf("%c ",M.data[count].e);
                count++;
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
    return OK;
}

Status InsertElem(TSMatrix *M, ElemType e,int i, int j){
    //如果i和j取值合法，将元素e的值赋给所指定的M中的元素，返回OK
    //行序为主序，但是行和列必须都按顺序从小到大排列，这样的话打印才不会出错
    if(i>M->mu || j>M->nu || i<1 || j<1) return ERROR;
    int k;  //k必须在for循环外部进行定义，否则会在for循环结束时被销毁
    for(k = 1; k < M->tu+1 ; k++){      //k最大为 M->tu+1，也就是k = M->tu仍不满足条件，k会取到 M->tu+1
        if(i > M->data[k].i){
            continue;
        }
        else if(i == M->data[k].i){
            if(j > M->data[k].j){
                continue;
            }else{
                break;
            }
        } else {
            break;
        }
    }
    if(!(k>M->tu)){
        // 将从此处开始的记录向后搬运，把待插入元素插入到当前位置
        for(int l = M->tu+1 ; l>k ; l-- ){
            M->data[l] = M->data[l-1];
        }
        M->data[k].e = e;
        M->data[k].i = i;
        M->data[k].j = j;
        M->tu++;
    } else {
        M->data[k].e = e;
        M->data[k].i = i;
        M->data[k].j = j;
        M->tu++;
    }
    return OK;
}

Status TransposeSMatrix(TSMatrix M,TSMatrix *T){
    //转置矩阵，如果两矩阵规模一致，则将M的转置矩阵传入T,返回OK
    //行标、列标交换，且要保证交换后的三元组也是按顺序排列的（行序、列序均要）
    if(M.mu != T->mu || M.nu != T->nu) return ERROR;
    for(int i=1;i<M.tu+1;i++){
        InsertElem(T,M.data[i].e,M.data[i].j,M.data[i].i);  //这里直接传T可以吗？可以
    }
    return OK;
}

#endif //endif of METHOD == TRIPLE

#if METHOD == ROWLOGIC

#endif //endif of METHOD == ROWLOGIC

#if METHOD == CROSSLIST

#endif //endif of METHOD == CROSSLIST



#endif