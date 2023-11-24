#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OVERFLOW 0
#define List_INIT_SIZE 30  //基础容量
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
        S->elem[j + 1] = S->elem[j];
    }
    //插入的数据
    S->elem[i-1] = *ele;
    S->length++;
    return 1;
}

int DeletL(SqList* S,int i){//删除第i个数据
    if(i < 1 || i > S->Listsize) return 0;
    for (int j = i - 1; j < S->Listsize; j++) {
        S->elem[j] = S->elem[j + 1];
    }
    S->length--;
    return 1;
}

int MergeL(SqList* S1,SqList* S2,SqList* C){//合并S1和S2到C
    

}

void printSq(SqList* S){
    for(int i =0; i < S->Listsize; i++){
        printf("%s %s %d\n",S->elem[i].name,S->elem[i].num,S->elem[i].grade);
    }
}

int main(){
    SqList* S =initSq();
    ElemType *stu1, *stu2, *stu3, *stu4;
    stu1 = ElemSet("jack","78451",99);
    stu2 = ElemSet("mark","85641",22);
    stu3 = ElemSet("name","961",33);
    stu4 = ElemSet("th","961",44);

    InsertSq(S,1,stu1);
    InsertSq(S,2,stu2);
    InsertSq(S,3,stu3);
    InsertSq(S,5,stu4);
    InsertSq(S,30,stu4);
    DeletL(S,30);
    printSq(S);
    printf("%d",S->length);
    // printf("######分界线####");
    // free(stu4);//为什么没影响？
    // printSq(S);

    return 0;
}
