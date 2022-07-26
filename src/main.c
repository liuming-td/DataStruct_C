// 测试用C文件
#include <stdio.h>
#include "HString.h"
#include "string.h"


int main(){
    HString T = {NULL,0};
    HString S1 = {NULL,0};
    HString S2 = {NULL,0};
    if(StrAssign(&T,"aabbcc") && strcmp(T.ch,"aabbcc")) printf("pass 1.\n");
    if(StrAssign(&S1,"ddeeff") && strcmp(T.ch,"ddeeff")) printf("pass 2.\n");
    if(StrAssign(&S2,"gghhii") && strcmp(T.ch,"gghhii")) printf("pass 3.\n");
    if(Concat(&T,S1,S2) && strcmp(T.ch,"ddeeffgghhii")) printf("pass 4.\n");
    if(6 == Index(T,S2,0)) printf("pass 5.\n");
    if(strcmp(SubString(T,1,5).ch,"deeff") ) printf("pass 6.\n");
    if(StrInsert(&S1,2,S2) && strcmp(S1.ch,"ddgghhiieeff")) printf("pass 7.\n");
    HString S3 = {NULL,0};
    StrAssign(&S3,"ddeeff");
    if(StrCompare(S1,S3) > 0) printf("pass 8.\n");
    if(ClearString(&S3) && S3.ch == NULL && S3.length == 0) printf("pass 9.\n");
    return 0;
}
