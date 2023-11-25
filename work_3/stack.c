#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node* next;
    int num;
} Node;

Node* initStack(){
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = 0;
    node->next = NULL;
    node->num = 0;
    return node;
}

void InsertNode(Node* N, int data){//头插法
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = N->next;
    N->next = node;
    N->num++;
}

int isEmpty(Node* N){//空0
    if(N->next == NULL || N->num == 0){
        return 0;
    }else{
        return 1;
    }
}

int LengthStack(Node* N){//长度, 空返回-1
    if(isEmpty(N)){
        return N->num;
    }else{
        return -1;
    }
}

int topStack(Node* N){//输出栈顶,-1失败
    if(isEmpty(N)){
        return N->next->data;
    }else{
        return -1;
    }
}

void pop(Node* N){//出栈
    if(isEmpty(N)){
        Node* temp = N->next;
        N->next = temp->next;
        free(temp);
        N->num--;        
    }else{
        return;
    }
}



int main(){

    Node* N = initStack();
    for(int i = 0; i<= 4; i++){
        InsertNode(N,i);
        printf("入栈并输出所输入的数据: %d\n",N->next->data);
    }
    printf("\n输出栈长度: %d\n",LengthStack(N));
    while (isEmpty(N))
    {
        printf("出栈并输出所出栈的数据: %d\n",topStack(N));
        pop(N);
    }
    printf("\n输出栈长度: %d\n",LengthStack(N));
//长度输出可能有bug
    
    return 0;
}