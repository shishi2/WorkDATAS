#include <stdio.h>
#include <stdlib.h>

typedef struct ElemType
{
    char* name;
    char* num;
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

void TailInertL(Node *L, ElemType *elem){

}

int main(){

    return 0;
}