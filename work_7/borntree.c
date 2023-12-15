#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    int len = A[0]->vexNum;
    int* visited = (int*)malloc(sizeof(int)*A[0]->vexNum);
    memset(visited,0,sizeof(int)*A[0]->vexNum);
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


int main(){
    AdjaL** A = initAdjaL(6);
    int arcs[6][6] = {
        0,6,1,5,0,0,
        6,0,5,0,3,0,
        1,5,0,5,6,4,
        5,0,5,0,0,2,
        0,3,6,0,0,6,
        0,0,4,2,6,0
    };
    creatAdjaL(A,"123456",(int*)arcs);
    printAdjaL(A);
    printf("\n");
    shuchu(A);

    return 0;
}