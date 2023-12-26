#include <stdio.h>
#include <stdlib.h>

typedef struct Bitree
{
    char sign;
    int num;
    struct Bitree* left;/*作为栈时，作为next*/
    struct Bitree* right;
}Bitree;

/*
创建一个二叉.树+树节点
*/
Bitree* initTree(){
    Bitree* B = (Bitree*)malloc(sizeof(Bitree));
    B->sign = '\0';
    B->num = 0;
    B->left = NULL;
    B->right = NULL;
    return B;
}




/*
*入栈
头插法
@param B 栈
@param data 入栈的节点
*/
void InertStack(Bitree* B,Bitree* data){
    Bitree* T = B->left;
    B->left = data;
    data->left = T;
}

/*
 * 出栈
*/
Bitree* popStack(Bitree* B){
    if(B->left){
        Bitree* T = B->left;
        B->left = T->left;
        return T;
    }else{
        return NULL;
    }
}

/**
 * 构建表达式树
*/
Bitree* experBiTree(){
    printf("输入一个中缀表达式(以#结尾): \n");
    int flag = 0;/*记录数字的次数*/
    int num = 0;/*辅助记录数字*/
    Bitree* S_num = initTree();/*存储数字的栈*/
    Bitree* S_exp = initTree();/*存储符号的栈*/
    while(1){/*先将表达式进栈处理*/
        char sign = '\0';/*接收字符*/
        scanf("%c",&sign);
        if(sign == '#'){/*判断表达式是否终止*/
            break;
        }

        if(sign <= '9' && sign >= '0'){/*接收到数字*/
            flag++;
            if(flag == 1){/*第一个数字*/
                Bitree* number = initTree();
                number->num = (int)sign -'0';
                InertStack(S_num,number);
            }else{/*不是第一个数字*/
                num = (int)sign -'0';
                S_num->left->num = S_num->left->num *10 + num;
            }
        }else{/*收到符号*/
            flag = 0;
            num = 0;
            int kuohao = 0;/*判断是不是左括号*/
            if(sign == ')'){/*是右括号则合成一个子树,放到数字处*/
                do{
                    Bitree* num1 = popStack(S_num);
                    Bitree* num2 = popStack(S_num);
                    Bitree* signa2 = popStack(S_exp);
                    signa2->right = num1;
                    signa2->left = num2;
                    InertStack(S_num,signa2);
                    if(S_exp->left->sign == '('){
                        popStack(S_exp);
                        kuohao = 0;
                    }else{
                        kuohao++;
                    }
                }while(kuohao);
                
            }else{/*不是右括号则入栈*/
                Bitree* signa = initTree();
                signa->sign = sign;
                InertStack(S_exp,signa);
            }
        }  
    }

    while (1){
        Bitree* signa2 = popStack(S_exp);
        if(signa2->left){/*符号栈不为空*/
            Bitree* num1 = popStack(S_num);
            Bitree* num2 = popStack(S_num);
            signa2->left = num2;
            signa2->right =  num1;
            InertStack(S_num,signa2);/*组成子树，放回数字栈*/
        }else{/*符号栈为空，则结束*/
            return popStack(S_num);
        }  
    }
}

void InorderRecurion(Bitree* B){
    if(B){
        InorderRecurion(B->left);
        if(B->num){
            printf("%d",B->num);
        }else{
            printf("%c",B->sign);
        }
        InorderRecurion(B->right);
    }
}

int main(){
    Bitree* B = experBiTree();
    printf("\n");
    InorderRecurion(B);

    return 0;
}