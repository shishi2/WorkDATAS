#include <stdio.h>
#include <stdlib.h>

typedef struct Binary
{
    char data;
    struct Binary *left;
    struct Binary *right;
} Binary;

Binary* creatBinary(){
    char cha;
    scanf(" %c",&cha);
    if(cha == '#'){
        return NULL;
    }else{
        Binary *B = (Binary*)malloc(sizeof(Binary)); 
        B->data = cha;
        B->left = creatBinary();
        B->right = creatBinary();
        return B;
    }
}

void InOrderRecurion(Binary *B){//中序递归遍历: 左中右
    if(B == NULL){
        return;
    }else {
        InOrderRecurion(B->left);
        printf("%c",B->data);
        InOrderRecurion(B->right);
    }
}

void PreOrederRecurion(Binary *B){//先序递归遍历: 中左右
    if(B == NULL){
        return;
    }else{
        printf("%c",B->data);
        PreOrederRecurion(B->left);
        PreOrederRecurion(B->right);
    }
}

void PostOrederRecurion(Binary *B){//后序递归遍历: 左右中
    if(B == NULL){
        return;
    }else{
        PostOrederRecurion(B->left);
        PostOrederRecurion(B->right);
        printf("%c",B->data);  
    }
}


void InorderTraversal(Binary *B){//中序非递归遍历: 左中右
    if(B == NULL){
        return;
    }  

    Binary *current = B;
    Binary *statck[100];
    int top = -1;
    while(current != NULL || top != -1){
        while (current != NULL)
        {//当前节点及其左子树入栈
            statck[++top] = current;
            current = current->left;
        }
        current = statck[top--];//用后再--
        printf("%c",current->data);
        current = current->right;
    }
}
 

int main(){
    printf("请输入");
    Binary *B = creatBinary();
    
    printf("\n先序遍历\n");
    PreOrederRecurion(B);
    printf("\n中序遍历\n");
    InorderTraversal(B);
    printf("\n后序遍历\n");
    PostOrederRecurion(B);

    return 0;
}
