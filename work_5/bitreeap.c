#include <stdio.h>
#include <stdlib.h>

typedef struct Haf//哈夫曼树的存储结构
{//发现其实在构建的过程中*parent指针作用不大，完全可以被替代掉
    char data;
    struct Haf *left,*right,*parent;
    int weight;
}Haf;

Haf* initLink(){//临时存储哈夫曼树数据的链表
    Haf* node = (Haf*)malloc(sizeof(Haf));
    node->data = '\0';
    node->weight = 0;
    node->left = node->parent = node->right = NULL;
    return node;
}

void InsertLink(Haf* L,char data, int weight){//哈夫曼树临时权值链表的插入
    Haf* node = (Haf*)malloc(sizeof(Haf));
    node->data = data;
    node->weight = weight;
    node->left =  node->right = NULL;

    node->parent = L->parent;//此处parent暂时充当next
    L->parent = node;
    L->weight++;//统计长度
}

Haf* deMinLink(Haf* L){//找到链表之中最小的权值，返回并删除其位置
    Haf* Temp = L->parent;
    Haf* min = L->parent;
    while (Temp)
    {//寻找最小节点
        if(Temp->weight < min->weight){
            min = Temp;
        }
        Temp = Temp->parent;
    }
    Temp = L;
    while(Temp){//删除链表中最小节点的位置
    //注意仅删除链表中的位置，实际上的存储空间仍然保留，因为在构建哈夫曼树的时候
    //就是直接指向这些未被删除的节点
        if(Temp->parent == min){
            Temp->parent = min->parent;
            L->weight--;
            return min;
        }
        Temp = Temp->parent;
    }
    return NULL;
}

void InsertNode(Haf* L,Haf* H){//构建哈夫曼树时插入节点的函数
    H->parent = L->parent;
    L->parent = H;
    L->weight++;
}

Haf* initHaff(Haf* L){//创建哈夫曼树
    while (1)
    {
        Haf* H = initLink();//创建两叶子的父节点
        Haf* min1 = deMinLink(L);//目前两个最小权值的节点
        Haf* min2 = deMinLink(L);
        min1->parent = min2->parent = H;
        H->left = min1;
        H->right = min2;
        H->weight = min1->weight + min2->weight;
        InsertNode(L,H);//两个节点作为一个叶子返回到链表中
        if(L->weight == 1){
            free(L);//释放临时存储的链表
            return H;
        }
    }
}

void deleteLastNode(Haf* L) {//删除哈夫曼编码临时链表的最后的节点
    Haf* temp = L;
    while (temp->parent->parent) {//找到最后的节点
        temp = temp->parent;
    }
    free(temp->parent);//删除该节点
    temp->parent = NULL;
}

void TailInsertL(Haf* PrintL, char data){//尾插法插哈夫曼编码临时链表
    //用队列实现
    Haf* Temp = PrintL;
    while (Temp->parent)
    {
        Temp = Temp->parent;
    }
    Haf* Node = (Haf*)malloc(sizeof(Haf));
    Temp->parent = Node;
    Node->parent = NULL;
    Node->data = data;
}

void printLink(Haf* PrintL){//打印在哈夫曼编码临时链表的编码
    //其结构实际上为队列
    Haf* Temp = PrintL->parent;
    while (Temp )
    {
        printf("%c",Temp->data);
        Temp = Temp->parent;
    }
    printf("\n");   
}

void InOrderRecurion(Haf* H,Haf* PrintL){//输出哈夫曼编码
    if(H == NULL){
        return;
    }else{
        
        if(H->data != '\0'){
            printf("字符%c的哈夫曼编码为: ", H->data);
            printLink(PrintL);
        }
        TailInsertL(PrintL,'0');//往左则为0
        InOrderRecurion(H->left,PrintL);

        deleteLastNode(PrintL);
        TailInsertL(PrintL,'1');//往右则为1
        
        InOrderRecurion(H->right,PrintL);       
        deleteLastNode(PrintL);
    }
}

void zuo(Haf* B){//先序递归遍历二叉树: 中左右
    if(B == NULL){
        return;
    }else{
        printf("%c",B->data);
        zuo(B->left);
        zuo(B->right);
    }
}

int main(){
    Haf* L = initLink();
    InsertLink(L,'A',19);
    InsertLink(L,'B',18);
    InsertLink(L,'C',16);
    InsertLink(L,'D',14);
    InsertLink(L,'E',12);
    InsertLink(L,'F',8);
    InsertLink(L,'G',6);
    InsertLink(L,'H',4);
    InsertLink(L,'I',2);
    InsertLink(L,'J',1);

    Haf* H = initHaff(L);//创建哈夫曼树
    Haf* PrintL =initLink();
    InOrderRecurion(H,PrintL);
    printf("\n查看在哈夫曼树中的位置, 前序遍历\n");
    zuo(H);

    return 0;
}