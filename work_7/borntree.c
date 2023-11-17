#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX -1  //不可达

typedef struct VexNode  //邻接表的节点
{
    int index;  //目标节点的下标
    int wei;    //抵达节点的权值
    struct VexNode* next;   //下一节点
}VexNode;

typedef struct AdjaL    //邻接表的表头
{
    char vex;   //节点名称
    VexNode* list;  //节点邻接节点
    int vexNum; //表中的节点数目
}AdjaL;

AdjaL** initAdjaL(int num){ //创建邻接表头
    AdjaL** A = (AdjaL**)malloc(sizeof(AdjaL*)*num);
    for(int i = 0; i < num; i++){
        A[i] = (AdjaL*)malloc(sizeof(AdjaL));
        A[i]->vexNum = num;
        A[i]->list = NULL;
    }
    return A;
}

void creatAdjaL(AdjaL** A, char* vex, int* arcs){   //创建邻接表
    int length = A[0]->vexNum;
    for (int i = 0; i < length; i++)
    {
        A[i]->vex = vex[i]; //节点名称
        for(int j = 0; j < length; j++){
            if(*(arcs + i*length + j) > 0){ //头插法，不对节点权值排序
                VexNode* V = (VexNode*)malloc(sizeof(VexNode));
                V->next = A[i]->list;
                A[i]->list = V;
                V->wei = *(arcs + i*length + j); //权值
                V->index = j;
            }
        }
    }
}

void DFS(AdjaL** A, int index, int* visited){ //深度有序遍历
    visited[index] = 1; //先输出第一个节点
    printf("%c",A[index]->vex);

    VexNode* temp = A[index]->list;
    while (temp)
    {
        int t_index = temp->index;
        if(!visited[t_index]){  //未被访问
            DFS(A, t_index, visited);
        }
        temp = temp->next;
    }
}

void printAdjaL(AdjaL** A){ //通过深度优先遍历图
    int length = A[0]->vexNum;
    int* visited = (int*)malloc(sizeof(int)*length);
    memset(visited,0,sizeof(int)*length);
    DFS(A,0,visited);
}

// void shuchu(AdjaL** A){ //输出邻接表的内容
//     for(int i = 0 ;i<6;i++){
//         printf("%c :", A[i]->vex);
//         VexNode* t = A[i]->list;
//         while (t)
//         {
//             printf("%d",t->index+1);
//             t = t->next;
//         }
//         printf("\n");
//     }
// }

VexNode* initPrimList(){    //用于存储prim算法得出的生成树的各个节点下标
//没有保存权值
    VexNode* P = (VexNode*)malloc(sizeof(VexNode));
    P->index = -1;
    P->next = NULL;
    return P;
}

void tailInsertP(VexNode* P,int index){  //尾插法,没有保存权值
    VexNode* node = (VexNode*)malloc(sizeof(VexNode));
    node->index = index;
    node->next = NULL;
    VexNode* t = P;
    while (t->next)
    {
        t = t->next;
    }
    t->next = node;
}

void Findmin(AdjaL** A,VexNode* P,int* visited){
    VexNode* t = P->next; //已选定的各个顶点
    int minWeight = MAX;    //注意MAX = -1
    VexNode* minNode = NULL;
    while (t)   //对已选定的各个顶点进行遍历，寻找最小权值的边
    {
        int currentIndex = t->index;
        VexNode* temp = A[currentIndex]->list;  //各个顶点的邻接表
        while (temp)    //对各个顶点的邻接表进行遍历，以寻找最小边
        {
            if(minWeight == MAX && !visited[temp->index]){  //MAX为-1，故要先判断
            //同时要考虑改下标是否被访问
                minWeight = temp->wei;
                minNode = temp;
            }else if (temp->wei < minWeight && !visited[temp->index] && temp->wei >0)
                {
                    minWeight = temp->wei;
                    minNode = temp;
                }
            temp = temp->next;
        }
        t = t->next;
    }
    if(minNode){
        tailInsertP(P,minNode->index);
        visited[minNode->index] = 1;    //标记节点已被访问
    }
}

void prim(AdjaL** A){
    int length = A[0]->vexNum;

    VexNode* P = initPrimList();    //已选定的节点
    int* visited = (int*)malloc(sizeof(int)*length);    //已被访问的节点
    memset(visited,0,sizeof(int)*length);

    visited[0] = 1; //访问第一个节点
    tailInsertP(P,0);

    for(int i = 1; i <length; i++){
        Findmin(A,P,visited);
    }

    VexNode* t = P->next;
    while (t)
    {
        printf("%c",A[t->index]->vex);
        t = t->next;
    }
}
//通过克鲁斯卡尔算法算得最小生成树
void Kruskal(AdjaL** A){
    int length = A[0]->vexNum;

    int weight[length][length]; //存储各个边的权值
    memset(weight,0,sizeof(int)*length*length);
    for(int i = 0; i < length; i++){
        VexNode* temp = A[i]->list;
        while (temp)
        {
            weight[i][temp->index] = temp->wei;
            temp = temp->next;
        }
    }

    AdjaL** B = initAdjaL(length);  //存储最小生成树
    for(int i = 0; i < length; i++){
        B[i]->vex = A[i]->vex;
    }

    int index1 = -1;
    int index2 = -1;//在邻接表中节点域的位置
    int minWeight = MAX;
    int countEdge = 0;  //已选定的边的数目
    while(countEdge < length-1){

        for(int i = 0; i < length; i++){//寻找最小权值的边
            for(int j = 0; j < length; j++){
                if(weight[i][j] < minWeight && weight[i][j] > 0){
                    index1 = i;
                    index2 = j;
                    minWeight = weight[i][j];
                    weight[i][j] = 0;
                }
            }
        }

        VexNode* node = initPrimList();

        VexNode* temp = A[index1]->list;//找到index1的邻接表中的节点
        int index = index2;
        while(index > 0){
            temp = temp->next;
            index--;
        }
        node->index = temp->index;//将节点插入到邻接表中
        node->wei = temp->wei;
        node->next = B[index1]->list;
        B[index1]->list = node;
        
        countEdge++;
    }

}


int main(){
    AdjaL** A = initAdjaL(6);
    int arcs[6][6] = {
        0,6,1,5,MAX,MAX,
        6,0,5,MAX,3,MAX,
        1,5,0,5,6,4,
        5,MAX,5,0,MAX,2,
        MAX,3,6,MAX,0,6,
        MAX,MAX,4,2,6,0
    };
    creatAdjaL(A,"123456",(int*)arcs);
    printAdjaL(A);
    // printf("\n");
    // shuchu(A);
    printf("\nover\n");
    prim(A);
    printf("\nover\n");
    Kruskal(A);


    return 0;
}