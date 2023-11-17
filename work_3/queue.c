#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node* next;
} Node;

Node* initQue(){
    Node* N = (Node*)malloc(sizeof(Node));
    N->data = 0;
    N->next = NULL;
    return N;
}

void enQue(Node* N,int data){
    Node* new = (Node*)malloc(sizeof(Node)), *Temp = N;
    new->data = data;
    new->next = NULL;
    while(Temp->next){
        Temp = Temp->next;
    }
    Temp->next = new;
    N->data++;
}

int isEmpty(Node* N){//空0
    if(N->next == NULL){
        return 0;
    }else{
        return 1;
    }
}

int LengthQue(Node* N){
    if(!isEmpty(N)){
        return 0;
    }else{
        return N->data;
    }
}

int deQue(Node* N){
    if(!isEmpty(N)){
        return -1;
    }else{
        Node* temp = N->next;
        N->next = temp->next;
        free(temp);
        N->data--;
        return 1;
    }
}

int outQue(Node* N){
    if(!isEmpty(N)){
        return -1;
    }else{
        return N->next->data;
    }
}
void printQue(Node* N){
    Node* T = N->next;
    while(T){
        printf("%d",T->data);
        T = T->next;
    }
}


int main(){

    Node* N = initQue();
    for(int i = 0; i<= 4; i++){
        enQue(N,i);
    }
    printf("输出全部队列\n");
    printQue(N);

    printf("\n输出队长度: %d\n",LengthQue(N));
    while (isEmpty(N))
    {
        printf("出队并输出所出队的数据: %d\n",outQue(N));
        deQue(N);
    }
    printf("\n输出队长度: %d\n",LengthQue(N));



    return 0;
}