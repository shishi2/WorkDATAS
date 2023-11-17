#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OVERFLOW 0
#define List_INIT_SIZE 100  //基础容量
#define LISTINCREMENT 10    //增量

typedef struct ElemType
{
    char* name;
    char* num;
    int grade;
}ElemType;


typedef struct SqList
{
    ElemType *elem;
    int length;
    int Listsize; 
}SqList;

SqList* initSq(){
    SqList* S = (SqList*)malloc(sizeof(SqList));
    if(!S) exit(OVERFLOW); 

    S->elem = (ElemType*)malloc(sizeof(ElemType)*List_INIT_SIZE);
    if (! S->elem) exit(OVERFLOW);

    S->length = 0;
    S->Listsize = List_INIT_SIZE;
    return S;
}

int InsertSq(SqList* S,int i , ElemType* ele){
    if(i <0 || i >= S->Listsize){
        return 0;//存储已满或 i的顺序错误
    }
    //暂不实现空间不足
    //

    if (S->length > 0 && i < S->length) {
        for (int j = S->length - 1; j >= i; j--) {
            strcpy(S->elem[j + 1].name, S->elem[j].name);
            strcpy(S->elem[j + 1].num, S->elem[j].num);
            S->elem[j + 1].grade = S->elem[j].grade;
        }
    }
    strcpy(S->elem[i-1].name,ele->name);
    strcpy(S->elem[i-1].num,ele->num);
    S->elem[i-1].grade = ele->grade;

    S->length++;
    return 1;
}

void printSq(SqList* S){
    for(int i =0; i < S->length; i++){
        printf("%s",S->elem->name);
    }
}

int main(){
    SqList* S =initSq();
    ElemType stu[10];
    stu[0].grade = 100;
    stu[0].name = "fuck";
    stu[0].num = "12345"; 
    InsertSq(S,0,&stu[0]);
    printSq(S);
    return 0;
}
