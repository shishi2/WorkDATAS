#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Bitree
{
    char month[4];
    struct Bitree* left;
    struct Bitree* right;
}Bitree;

Bitree* initTree(){
    Bitree* B = (Bitree*)malloc(sizeof(Bitree));
    B->left = NULL;
    B->right = NULL;
    return B;
}

void insert(Bitree* B,Bitree* b){//strcmp
    if((int)b->month[0] < (int)B->month[0]){
        if(B->left){
            insert(B->left,b);
        }else{
            B->left = b;
        }
    }else if((int)b->month[0] > (int)B->month[0]){
        if(B->right){
            insert(B->right,b);
        }else{
            B->right = b;
        }
    }else{//[0]相等
        if((int)b->month[1] < (int)B->month[1]){
            if(B->left){
                insert(B->left,b);
            }else{
                B->left = b;
            }
        }else if((int)b->month[1] > (int)B->month[1]){
            if(B->right){
                insert(B->right,b);
            }else{
                B->right = b;
            }
        }else{//[1]相等
            if((int)b->month[2] < (int)B->month[2]){
                if(B->left){
                    insert(B->left,b);
                }else{
                    B->left = b;
                }
            }else if((int)b->month[2] > (int)B->month[2]){
                if(B->right){
                    insert(B->right,b);
                }else{
                    B->right = b;
                }
            }
        }//最多两个相等
    }
}

void BiSortTree(Bitree* B,char month[][4]){
    int i = 1;
    strcpy(B->month,month[0]);

    while( i < 12){
        Bitree* new = (Bitree*)malloc(sizeof(Bitree));
        new->left = NULL;
        new->right = NULL;
        strcpy(new->month,month[i]);
        insert(B,new);
        i++;
    }
}

void preRecurion(Bitree* B){//中序遍历
    if(B){
    preRecurion( B->left);
    printf("%7s",B->month);
    preRecurion( B->right);
    }  
}

int main(){
    char month[12][5] = {
        "Dec\0", "Feb\0", "Nov\0", "Oct\0","June\0", "Sept\0", "Aug\0" ,"Apr\0" ,"May\0","July\0" ,"Jan\0" , "Mar\0"
    };
    Bitree* B = initTree();
    BiSortTree(B,month[0]);
    preRecurion(B);

    return 0;
}
