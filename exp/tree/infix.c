#include <stdio.h>
#include <stdlib.h>

typedef struct Bitree{
    char sign;
    int num;
    struct Bitree* left;/*作为栈时，作为next*/
    struct Bitree* right;
}Bitree;

/**
 *创建一个二叉.(树,树节点)
*/
Bitree* initTree(){
    Bitree* B = (Bitree*)malloc(sizeof(Bitree));
    B->sign = '\0';
    B->num = 0;
    B->left = NULL;
    B->right = NULL;
    return B;
}

/**
*入栈
 *头插法
 *@param B 栈
 *@param data 入栈的节点
*/
void InertStack(Bitree* B,Bitree* data){
    Bitree* T = B->left;
    B->left = data;
    data->left = T;
}

/**
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
 * 取数字栈顶和符号栈顶合成
 * @param S_num 数字栈顶
 * @param S_exp 符号栈顶
 * @return t 经合成后的节点, 其right为数据节点
*/
Bitree* Synthtree(Bitree* S_num,Bitree* S_exp){
    Bitree* num1 = popStack(S_num);
    Bitree* num2 = popStack(S_num);
    Bitree* signa2 = popStack(S_exp);

    if(num1->sign == '!'){
        Bitree* temp = num1;
        num1 = num1->right;
        free(temp);
    }else{
        num1->left = NULL;
        num1->right = NULL;
    }

    if(num2->sign == '!'){
        Bitree* temp = num2;
        num2 = num2->right;
        free(temp);
    }else{
        num2->left = NULL;
        num2->right = NULL;
    }
    signa2->right = num1;
    signa2->left = num2;
    Bitree* t = initTree();/*signa2的左右子树已满*/
    t->right = signa2;  /*故为其添加以！标志的父节点*/
    t->sign = '!';
    return t;
}

/**
 * 构建表达式树
*/
Bitree* experBiTree(){
    printf("\n输入一个中缀表达式(其中+-*/四个符号分别对应加法,减法,乘法,除法,最后以#结尾): \n");
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
        if((sign < '0' || sign >'9')){/*判断是否为无效字符*/
            if(sign != '+' && sign != '-' && sign != '*' && sign != '/' && sign != '(' && sign != ')'){
                printf("输入无效字符\n");
                printf("程序退出\n");
                exit(1);
            }
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
                    Bitree* t = Synthtree(S_num,S_exp);
                    InertStack(S_num,t);
                    if(S_exp->left->sign == '('){/*判断当前栈顶是否为'('*/
                        popStack(S_exp);
                        kuohao = 0;
                    }else{
                        kuohao++;
                    }
                }while(kuohao);
                
            }else{/*不是右括号则入栈*/
                while(sign != '(' && S_exp->left){
                    while (S_exp->left->sign == '*' || S_exp->left->sign == '/'){
                        /*检查当前栈顶符号是否为/*若是则需要弹出*/
                        /*且不应为(,保证/*左右括号正常发挥功能*/
                        Bitree* t = Synthtree(S_num,S_exp);
                        InertStack(S_num,t);
                    }
                    if(S_exp->left->sign != '*' || S_exp->left->sign != '/'){
                        break;
                    }
                }
                Bitree* signa = initTree();
                signa->sign = sign;
                InertStack(S_exp,signa);
            }
        }  
    }

    while (1){
        Bitree* signa2 = S_exp->left;
        if(signa2){/*符号栈不为空*/
            Bitree* t = Synthtree(S_num,S_exp);
            InertStack(S_num,t);
        }else{/*符号栈为空，则结束*/
            S_num = popStack(S_num);
            if(S_num->sign == '!'){
                S_num = S_num->right;
            }
            free(S_exp);
            return S_num;
        }  
    }
}

/**
 * 中序遍历
*/
void InorderRecurion(Bitree* B){
    if(B){
        InorderRecurion(B->left);
        if(B->num){
            printf("%3d",B->num);
        }else{
            printf("%2c",B->sign);
        }
        InorderRecurion(B->right);
    }
}

/**
 * 先序遍历
*/
void PreRecurion(Bitree* B){
    if(B){
        if(B->num){
            printf("%3d",B->num);
        }else{
            printf("%2c",B->sign);
        }
        PreRecurion(B->left);
        PreRecurion(B->right);
    }
}

/**
 * 后序遍历
 * 输出逆波兰式
*/
void PostRecurion(Bitree* B){
    if(B){
        PostRecurion(B->left);
        PostRecurion(B->right);
        if(B->num){
            printf("%3d",B->num);
        }else{
            printf("%2c",B->sign);
        }
    }
}


/**
 * 输出中缀表达式
 * @param B 表达式二叉树
*/
void InfixRecurion(Bitree* B){
    if(B){
        if(B->left && B->right){/*本质为检测运算符*/
            printf("(");
        }
        InfixRecurion(B->left);
        if(B->num){
            printf("%d",B->num);
        }else{
            printf("%c",B->sign);
        }
        
        InfixRecurion(B->right);
        if(B->left && B->right){
            printf(")");
        }
    }
}

/**
 * 计算表达式树的值 
*/
int calculate(Bitree* B){
    if(B->left == NULL && B->right == NULL){
        return B->num;
    }
    int left = calculate(B->left);
    int right = calculate(B->right);
    switch (B->sign)
    {
    case '*':
        return left * right;
    case '/':
        if(right == 0){
            printf("出现除数为0\n");
            exit(1);
        }else{
            return left / right;
        }
    case '+':
        return left + right;
    case '-':
        return left - right;
    default:
        printf("无效运算符\n");
        exit(1);
    }
    return -1;
}

int main(){
    Bitree* B = experBiTree();
    while (1){
        int flag = 0;
        printf("\n中序遍历请输入1\n");
        printf("先序遍历请输入2\n");
        printf("后序遍历请输入3\n");
        printf("输出逆波兰式请输入4\n");
        printf("输出中缀表达式请输入5\n");
        printf("计算表达式请输入6\n");
        printf("退出请输入-1\n");

        scanf("%d",&flag);
        switch(flag){
            case 1:
                InorderRecurion(B);
                break;
            case 2:
                PreRecurion(B);
                break;
            case 3:
                PostRecurion(B);
                break;
            case 4:
                PostRecurion(B);
                break;
            case 5:
                InfixRecurion(B);
                break;
            case 6:
                printf("表达式的值为: %d\n",calculate(B));
                break;
            case -1:
                exit(0);
                break;
            default:
                printf("输入错误\n");
                break;
        }
    }
    
    return 0;
}
