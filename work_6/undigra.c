//无向图
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Graph//邻接矩阵
{
    char* vexs;
    int** arcs;
    int VexNum;
    int ArcNum;
} Graph;

Graph* initGraph(int VexNum){//创建图
    Graph* G = (Graph*)malloc(sizeof(Graph));
    G->vexs = (char*)malloc(sizeof(char)*VexNum);
    G->arcs = (int**)malloc(sizeof(int*)*VexNum);
    for(int i = 0; i < VexNum; i++){
        G->arcs[i] = (int*)malloc(sizeof(int)*VexNum);
    }
    G->VexNum = VexNum;
    G->ArcNum = 0;
}

void creatGraph(Graph* G, char* vexs, int* arcs){
    //创建邻接矩阵
    for(int i = 0; i < G->VexNum; i++){
        G->vexs[i] = vexs[i];//添加图上的点
        for(int j = 0; j < G->VexNum; j++){
            G->arcs[i][j] = *(arcs + i * G->VexNum + j);//点对应的边
            //arcs传进来之前是一个二维数组
            //传进来的是arcs[0]的地址
            if(G->arcs[i][j] != 0){
                G->ArcNum++;
            }
        }
    }
    G->ArcNum /= 2;//无向图
}

void DFS(Graph* G, int* visited, int index){//深度优先
    printf("%5c",G->vexs[index]);
    visited[index] = 1;//已被访问
    for(int i = 0; i < G->VexNum; i++){
        if(G->arcs[index][i] && !visited[i]){//有边且未被访问
            DFS(G, visited, i);
        }
    }
}

typedef struct Queue//创建队列
{
    int data;
    struct Queue* next;
} Queue;

Queue* initQueue(){//创建对列
    Queue* Q = (Queue*)malloc(sizeof(Queue));
    Q->data = 0;
    Q->next = NULL;
    return Q;
}

int isEmpty(Queue* Q){//判断队列是否为空
    if(Q->next){
        return 1;
    }else{
        return 0;
    }
}

int enQueue(Queue* Q, int data){//入队
        Queue* node = (Queue*)malloc(sizeof(Queue));
        node->data = data;
        node->next = NULL;
        Queue* temp = Q;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = node;
        return 1;
}

int deQueue(Queue* Q){//出队
    if(isEmpty(Q)){
        int data = Q->next->data;
        Queue* T = Q->next;
        Q->next = T->next;
        free(T);
        return data;
    }else{
        return 0;
    }
}

void BFS(Graph* G, int* visited){//广度优先
    int index = 0;
    Queue* Q = initQueue();
    printf("%5c",G->vexs[index]);
    visited[index] = 1;//已被访问
    enQueue(Q,index);//下标作为数据
    while (isEmpty(Q))
    {
        int i = deQueue(Q);//出队的点
        for(int j = 0; j < G->VexNum; j++){
            if(G->arcs[i][j] && !visited[j]){
                printf("%5c",G->vexs[j]);
                visited[j] = 1;
                enQueue(Q,j);
            }
        }
    } 
}

typedef struct VexNode//邻接表节点
{
    int data;//节点下标
    struct VexNode* next;//下一个邻接节点
}VexNode;

typedef struct AdjaL//邻接表头
{
    char data;//节点数据
    int VexNum;
    VexNode* next;//邻接节点
}AdjaL;

AdjaL** initAdjaL(int num){//创建邻接表头
    AdjaL** A = (AdjaL**)malloc(sizeof(AdjaL*)*num);
    for(int i = 0; i < num; i++){
        A[i] = (AdjaL*)malloc(sizeof(AdjaL));
        A[i]->VexNum = num;
    }
    return A;
}

void creatAdjaL(AdjaL** A,char* vexs,int* arcs){//建立邻接表
    int LengthA = A[0]->VexNum;
    for(int i = 0; i < LengthA; i++){
        A[i]->data = vexs[i];
        for(int j = LengthA - 1; j >= 0; j--){
            //从后往前，用头插法，才能保证小的节点在前面
            if(*(arcs + i*LengthA + j) == 1){
                VexNode* V = (VexNode*)malloc(sizeof(VexNode));
                V->data = 1;
                V->next = A[i]->next;
                A[i]->next = V;
            }
        }
    }
}

AdjaL* FirstAdjVex(AdjaL** A, char vex){
    //返回vex的第一个邻接节点
    int LengthA = A[0]->VexNum;
    for(int i = 0; i < LengthA; i++){
        if(A[i]->data == vex){//匹配到vex
            if(A[i]->next){
                return A[A[i]->next->data];//vex有邻接节点
            }else{
                return NULL;//vex无邻接节点
            }
        }
    }
    return NULL;//表中无vex
}

AdjaL* NextAdjVex(AdjaL** A,char vex, char w){
    int LengthA = A[0]->VexNum;
    for(int i = 0; i < LengthA; i++){
        if(A[i]->data == vex){//匹配到vex
        VexNode* T = A[i]->next;
            while (A[T->data]->data == w)//在vex的邻接节点中找w
            {
                if(T->next){//找到w
                    return A[T->next->data];//w不是最后的邻接节点
                }else{
                    return NULL;//w是最后的邻接节点
                }
                T = T->next;//进入下一邻接节点
            }
            return NULL;//vex中未找到w
        }
    }
    return NULL;//未找到vex
}

void InsertVex(AdjaL** A, char vex){//插入新节点，新节点的联通情况未知
    int LengthA = A[0]->VexNum;
    AdjaL** newA = (AdjaL**)realloc(*A,sizeof(AdjaL*)*(LengthA + 1));
    *A = *newA;
    A[LengthA] = (AdjaL*)malloc(sizeof(AdjaL));
    memset(A[LengthA],0,sizeof(AdjaL));
    for(int i = 0; i <= LengthA; i++){
        A[i]->VexNum = LengthA + 1;
    }
}

void Insert(AdjaL** A, char vex, char w){//插入vex和w的联通关系
    int numV = -1;//邻接表中vex的位置
    int numW = -1;//邻接表中w的位置
    AdjaL* V = NULL;//邻接表中的Vex
    AdjaL* W = NULL;//邻接表中的w
    for(int i = 0; i < A[0]->VexNum; i++){//找到vex和w
        if(A[i]->data == vex){
            numV = i;//得到vex对应的下标
            V = A[i];//邻接表头中v的位置
        }
        if(A[i]->data == w){
            numW = i;//得到w对应的下标
            W = A[i];//邻接表头中w的位置
        }
    }

    if(V->next){//在v的邻接表中添加w的信息
           VexNode* V1 = V->next;
        while (V1)    
        {
            if((V1->data < numW && V1->next->data > numW) || V1->next == NULL ){
                VexNode* new = (VexNode*)malloc(sizeof(VexNode));
                new->data = w;
                new->next = V1->next;
                V1->next = new;
            }
            V1 = V1->next;
        }  
    }else{
        VexNode* new = (VexNode*)malloc(sizeof(VexNode));
        new->data = w;
        new->next = NULL;
    }    

    if(V->next){//在w的邻接表中添加vex的信息
           VexNode* W1 = W->next;
        while (W1)    
        {
            if((W1->data < numV && W1->next->data > numW) || W1->next == NULL ){
                VexNode* new = (VexNode*)malloc(sizeof(VexNode));
                new->data = vex;
                new->next = W1->next;
                W1->next = new;
            }
            W1 = W1->next;
        }  
    }else{
        VexNode* new = (VexNode*)malloc(sizeof(VexNode));
        new->data = vex;
        new->next = NULL;
    } 
}

void DeleteArc(AdjaL** A, char vex, char w){//删除vex和w的关系
    int numV = -1;//邻接表中vex的位置
    int numW = -1;//邻接表中w的位置
    AdjaL* V = NULL;//邻接表中的Vex
    AdjaL* W = NULL;//邻接表中的w
    for(int i = 0; i < A[0]->VexNum; i++){//找到vex和w
        if(A[i]->data == vex){
            numV = i;//得到vex对应的下标
            V = A[i];//邻接表头中v的位置
        }
        if(A[i]->data == w){
            numW = i;//得到w对应的下标
            W = A[i];//邻接表头中w的位置
        }
    }

    if(V->next){//在v的邻接表中删除w的信息
        VexNode* V1 = V->next;
        if(V1->data == numW){//第一个节点就是w，直接删
            V->next = NULL;
        }else{
            while (V1)    
            {
                if(V1->next->data == numW)
                {
                    if(V1->next->next==NULL){
                        V1->next = NULL;//w无后继
                    }else{
                        V1->next = V1->next->next;//w有后继
                    }
                }
                V1 = V1->next;
            } 
        } 
    }   

    if(V->next){//在w的邻接表中删除vex的信息
        VexNode* W1 = W->next;
        if(W1->data == numV){//第一个节点就是vex，直接删
            W->next = NULL;
        }else{
            while (W1)    
            {
                if(W1->next->data == numV)
                {
                    if(W1->next->next==NULL){
                        W1->next = NULL;//vex无后继
                    }else{
                        W1->next = W1->next->next;//vex有后继
                    }
                }
                W1 = W1->next;
            } 
        } 
    }
}

int main(){
    Graph* G = initGraph(5);
    int* visited = (int*)malloc(sizeof(int)*G->VexNum);
    memset(visited, 0, sizeof(int)*G->VexNum);
    int arcs[5][5] = {
        0,1,0,1,0,
        1,0,1,0,1,
        0,1,0,1,1,
        1,0,1,0,0,
        0,1,1,0,0
    };
    printf("输出DFS\n");
    creatGraph(G,"12345",(int*)arcs);
    DFS(G, visited, 0);
    printf("\n输出BFS\n");
    memset(visited, 0, sizeof(int)*G->VexNum);
    BFS(G,visited);
    AdjaL** A = initAdjaL(5);

    creatAdjaL(A,"54321",(int*)arcs);

    return 0;
}
