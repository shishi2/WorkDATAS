#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ElemType
{
    char name[20];
    char num[20];
    int grade;
}ElemType;

typedef struct Node
{
    ElemType *elem;
    struct Node *next;
    int num;
}Node;

Node* initLinkL(){
    Node* N = (Node*)malloc(sizeof(Node));
    if(!N) exit(0);
    N->elem = NULL;
    N->next = NULL;
    N->num = 0;
    return N;
}

ElemType* ElemSet(char* name,char* num, int grade){
    ElemType* E = (ElemType*)malloc(sizeof(ElemType));
    E->grade = grade;
    strcpy(E->name,name);
    strcpy(E->num,num);
    return E;
}

void TailInertL(Node *L, ElemType *elem){
    Node* N = (Node*)malloc(sizeof(Node));
    if(!N) exit(0);
    Node* T = L;
    while(T->next != NULL){
        T = T->next;
    }
    N->elem = elem;
    N->next = NULL;
    T->next = N;
    T->num++;
}

int DeletL(Node* L,char name[20]){
    
}

void printList(Node* L){
    Node* T = L->next;
    while (T != NULL)
    {
        printf("%s %d\n",T->elem->name,T->elem->grade);
        T = T->next;
    }
}

int main(){
    Node* N = initLinkL();
    ElemType *E = ElemSet("name","12345",22);
    ElemType *E1 = ElemSet("dsae","12345",22);
    TailInertL(N,E);
    TailInertL(N,E1);
    printList(N);
    return 0;
}