#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ElemType //存储的数据
{
    char name[20];
    char num[20];
    int grade;
}ElemType;

typedef struct Node//链表
{
    ElemType *elem;
    struct Node *next;
    int num;
}Node;

Node* initLinkL(){//初始化
    Node* N = (Node*)malloc(sizeof(Node));
    if(!N) exit(0);
    N->elem = NULL;
    N->next = NULL;
    N->num = 0;
    return N;
}

ElemType* ElemSet(char* name,char* num, int grade){//初始化存储的数据
    ElemType* E = (ElemType*)malloc(sizeof(ElemType));
    E->grade = grade;
    strcpy(E->name,name);
    strcpy(E->num,num);
    return E;
}

ElemType* CopyElem(ElemType* E){//深度拷贝数据
    ElemType* result = (ElemType*)malloc(sizeof(ElemType));
    result->grade = E->grade;
    strcpy(result->name,E->name);
    strcpy(result->num,E->num);
    return result;
}

void TailInertL(Node *L, ElemType *elem){//尾插法添加新节点
    Node* Find = (Node*)malloc(sizeof(Node));
    if(!Find) exit(0);
    Node* Temp = L;
    while(Temp->next)
    {
        Temp = Temp->next;
    }
    Find->elem = CopyElem(elem);//不使用的话，原有数据被删有影响。
    Find->next = NULL;
    Temp->next = Find;
    Temp->num++;
}

void HeadInsertL(Node* L,ElemType* E){//头插法添加新节点
    Node* node = (Node*)malloc(sizeof(Node));
    node->elem = CopyElem(E);
    node->next = L->next;
    L->next = node;
}


int DeletL(Node* L,char name[20]){//删除节点，依照姓名匹配，全部匹配
    Node* Find = L->next;
    Node* pre = L;
    while(Find){
        if(strcmp(Find->elem->name,name) == 0){
            pre->next = Find->next;
            free(Find);
            L->num--;
            Find = pre->next;
            continue;
        }
        pre = pre->next;
        Find = Find->next;
    }
}

void printList(Node* L){//输出：姓名，学号，成绩
    Node* Temp = L->next;
    while (Temp != NULL)
    {
        printf("%s %s %d\n",Temp->elem->name,Temp->elem->num,Temp->elem->grade);
        Temp = Temp->next;
    }
}

int main(){
    Node* N = initLinkL();
    ElemType *E1 = ElemSet("name","12345",22);
    ElemType *E2 = ElemSet("dsae","7845",85);
    ElemType *E3 = ElemSet("dsae","519",95);
    ElemType *E4 = ElemSet("adsgyhj","172",42);
    TailInertL(N,E1);
    TailInertL(N,E2);
    free(E2);
    TailInertL(N,E3);
    TailInertL(N,E4);
    printList(N);
    printf("\n");
    DeletL(N,"dsae");
    printList(N);
    return 0;
}