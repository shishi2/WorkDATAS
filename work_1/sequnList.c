#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OVERFLOW 0
#define List_INIT_SIZE 100  //基础容量
#define LISTINCREMENT 10    //增量

typedef struct ElemType//存储的数据
{
    char name[20];
    char num[20];
    int grade;
}ElemType;

typedef struct SqList//顺序表
{
    ElemType *elem;
    int length;
    int Listsize; 
}SqList;

SqList* initSq(){//初始化顺序表
    SqList* S = (SqList*)malloc(sizeof(SqList));
    if(!S) exit(OVERFLOW); 

    S->elem = (ElemType*)malloc(sizeof(ElemType)*List_INIT_SIZE);
    if (! S->elem) exit(OVERFLOW);

    S->length = 0;
    S->Listsize = List_INIT_SIZE;
    return S;
}

ElemType* ElemSet(char* name,char* num, int grade){//初始化存储的数据
    ElemType* E = (ElemType*)malloc(sizeof(ElemType));
    E->grade = grade;
    strcpy(E->name,name);
    strcpy(E->num,num);
    return E;
}

int InsertSq(SqList* S,int i , ElemType* ele){//在i处插入数据
    if(i < 1 || i > S->Listsize + 1){
        return 0;//存储已满或 i的顺序错误
    }
    //暂不实现空间不足

    //把i及其后数据后移一位
    for (int j = S->Listsize - 2; j >= i - 1; j--) {
        strcpy(S->elem[j + 1].name, S->elem[j].name);
        strcpy(S->elem[j + 1].num, S->elem[j].num);
        S->elem[j + 1].grade = S->elem[j].grade;
    }
    //插入的数据
    strcpy(S->elem[i-1].name,ele->name);
    strcpy(S->elem[i-1].num,ele->num);
    S->elem[i-1].grade = ele->grade;

    S->length++;
    return 1;
}

void printSq(SqList* S){
    for(int i =0; i < S->Listsize; i++){
        printf("%d",S->elem[i].grade);
    }
}

int main(){
    SqList* S =initSq();
    ElemType *stu1, *stu2, *stu3;
    stu1 = ElemSet("jack","78451",99);
    stu2 = ElemSet("mark","85641",22);
    stu3 = ElemSet("name","961",22);

    InsertSq(S,0,stu1);
    InsertSq(S,1,stu2);
    InsertSq(S,2,stu3);

    printSq(S);
    return 0;
}
