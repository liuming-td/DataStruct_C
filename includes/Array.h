#ifndef ARRAY_H
#define ARRAY_H

#include<stdarg.h>          //用于存取变长参数表
#include"utils.h"
#include<stdlib.h>

#define MAX_ARRAY_DIM 18    //数组最大维度为18
typedef struct Array
{
    ElemType *base;         //数组元素基地址
    int dim;                //数组维数
    int *bounds;            //数组维界基址，什么是维界？下标的取值范围，数组每一维的界
    int *constants;         //数组映像函数常量基址，由InitArray分配
}Array;

Status InitArray(Array *A,int dim,...){
    //若维数dim和各维长度合法，则构造相应的数组A，并返回OK
    if(dim<1 || dim > MAX_ARRAY_DIM) return ERROR;
    A->dim = dim;
    A->bounds = (int *)malloc(dim * sizeof(int));
    if(!A->bounds) exit(OVERFLOW);
    //若各维长度合法，则存入A.bounds，并求出A的元素总数elemtotal
    int elemtotal = 1;
    va_list ap;     //用于存放变长参数表信息的数组
    va_start(ap,dim);
    for(int i = 0;i<dim;i++){
        A->bounds[i] = va_arg(ap,int);
        if(A->bounds[i]<0) return ERROR;    //下溢
        elemtotal *= A->bounds[i];
    }
    va_end(ap);
    A->base = (ElemType *)malloc(elemtotal * sizeof(ElemType));
    if(!A->base) exit(OVERFLOW);
    //求映像函数的常数c，并存入A->constants[i-1],i = 1,....,dim
    A->constants = (int *)malloc(dim*sizeof(int));
    A->constants[dim-1] = 1;
    for(int i=dim-2;i>-1;--i){
        A->constants[i] = A->bounds[i+1] * A->constants[i+1];
    }
    return OK;
}

Status DestroyArray(Array *A){
    //销毁数组A
    if(!A->base) return ERROR;
    free(A->base);  A->base = NULL;         //free后的指针成为野指针，因为它还是指向原来的地址
    if(!A->bounds) return ERROR;            //但是这个地址并不存在了，所以置为NULL，防止误用。
    free(A->bounds);  A->bounds = NULL;
    if(!A->constants) return ERROR;
    free(A->constants);  A->constants = NULL;
    return OK;
}

Status Locate(Array A,va_list ap,int *off){     //传入的参数值是大于等于0小于维界，取值从0开始
    // 若ap指示的各下标值合法，则求出该元素在A中相对地址off
    // Assign和Value都要使用这个函数
    // 要在va_start()后使用
    *off = 0;
    int temp = 0;
    for(int i = 0;i<A.dim;++i){
        temp = va_arg(ap,int);
        if((temp>0 || temp == 0) && temp<A.bounds[i]) 
            *off += A.constants[i] * temp;
        else return ERROR; 
    }
    return OK;
}

Status Value(Array A,ElemType *e,...){
    //A是n维数组，e是元素变量，后面是n个下标值
    //若下标不越界，则e赋值为对应位置的元素值
    va_list ap;
    int off = 0;
    va_start(ap,&e);
    if(!Locate(A,ap,&off)) return ERROR;
    *e = *(A.base + off);
    //e = (A.base + off);  //经典，只修改了地址，但是地址里面的内容没有变化，函数结束了就被销毁了，没有达到目的。
    return OK;
}

Status Assign(Array *A,ElemType e,...){
    //A是n维数组，e为元素变量，随后是n个下标值
    //若下标不超界，则将e的值赋给所指定的A的元素
    va_list ap;
    int off = 0;
    va_start(ap,e);
    if(!Locate(*A,ap,&off)) return ERROR;
    *(A->base + off) = e;
    return OK;
}

#endif