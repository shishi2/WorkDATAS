#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct VexNode{
    int weight;
    int index;
    struct VexNode *next;
} VexNode;

//有向有权图邻接表
typedef struct AdjaL{
    int vexnum;
    char data;
    VexNode *tonext;/*到下一个顶点*/
    VexNode *nextto;/*上一个顶点*/
}AdjaL;

AdjaL** initAdjaL(int vexnum, char *data){
    AdjaL **adjaL = (AdjaL**)malloc(sizeof(AdjaL*) * vexnum);
    for(int i = 0; i < vexnum; i++){
        adjaL[i] = (AdjaL*)malloc(sizeof(AdjaL));
        adjaL[i]->vexnum = vexnum;
        adjaL[i]->data = data[i];
        adjaL[i]->tonext = NULL;
        adjaL[i]->nextto = NULL;
    }
    return adjaL;
}

//查找顶点下标
int findIndex(AdjaL **adjaL, char data){
    int i = 0;
    while(adjaL[i]->data != data){
        i++;
    }
    return i;
}

//添加边
void addedge(AdjaL** adjaL, char start, char end, int weight){
    int i = 0, j = 0;
    i = findIndex(adjaL, start);
    j = findIndex(adjaL, end);

    //start->end
    VexNode *node = (VexNode*)malloc(sizeof(VexNode));
    node->index = j;
    node->weight = weight;
    node->next = adjaL[i]->tonext;
    adjaL[i]->tonext = node;

    //end->start
    VexNode *node2 = (VexNode*)malloc(sizeof(VexNode));
    node2->index = i;
    node2->weight = weight;
    node2->next = adjaL[j]->nextto;
    adjaL[j]->nextto = node2;
}

//输出邻接表
//到下一个顶点
void printAdjaL(AdjaL **adjaL){
    int vexnum = adjaL[0]->vexnum;
    for(int i = 0; i < vexnum; i++){
        printf("%c: ", adjaL[i]->data);
        VexNode *node = adjaL[i]->tonext;
        while(node != NULL){
            printf("%c", adjaL[node->index]->data);
            node = node->next;
        }
        printf("\n");
    }
}

//输出邻接表
//到上一个顶点
void printAdjaL2(AdjaL **adjaL){
    int vexnum = adjaL[0]->vexnum;
    for(int i = 0; i < vexnum; i++){
        printf("%c: ", adjaL[i]->data);
        VexNode *node = adjaL[i]->nextto;
        while(node != NULL){
            printf("%c", adjaL[node->index]->data);
            node = node->next;
        }
        printf("\n");
    }
}

//拓扑排序
void topologicalSort(AdjaL **adjaL){
    int vexnum = adjaL[0]->vexnum;
    int indegree[vexnum];
    memset(indegree, 0, sizeof(indegree));
    for(int i = 0; i < vexnum; i++){//各节点入度表
        VexNode *node = adjaL[i]->tonext;
        while(node != NULL){
            indegree[node->index]++;
            node = node->next;
        }
    }

    int isVisited[vexnum];//0未访问，1已访问
    memset(isVisited, 0, sizeof(isVisited));

    int queue[vexnum];
    memset(queue, 0, sizeof(queue));
    int front = 0, rear = 0;
    for(int i = 0; i < vexnum; i++){//入度为0的节点入队
        if(indegree[i] == 0){
            queue[rear++] = i;
            isVisited[i] = 1;
        }
    }

    while(front != rear){
        int index = queue[front++];
        printf("%c ", adjaL[index]->data);
        VexNode *node = adjaL[index]->tonext;
        while(node != NULL){
            indegree[node->index]--;
            if(indegree[node->index] == 0 && isVisited[node->index] == 0){//入度为0的节点入队
                queue[rear++] = node->index;
                isVisited[node->index] = 1;
            }
            node = node->next;
        }
    }
    printf("\n");
}

int findMaxWeight(AdjaL** adjaL,int start,int end){//找到两点间的最大权值
    if(start == end){
        return 0;
    }

    int max = 0;
    VexNode* node =adjaL[end]->nextto;
    while(node != NULL){
        int t = 0;
        t = findMaxWeight(adjaL,start,node->index) + node->weight;
        if(t > max){
            max = t;
        }
        node = node->next;
    }
    
    return max;
}

void critialPath(AdjaL** adjaL){//输出关键路径
    int vexnum = adjaL[0]->vexnum;
    int ve[vexnum];//事件最早发生时间
    memset(ve, 0, sizeof(ve));
    int vl[vexnum];//事件最晚发生时间
    memset(vl, 0, sizeof(vl));
    
    for(int i = 0; i < vexnum; i++){//求ve
        ve[i] = findMaxWeight(adjaL,0,i);
    }

    vl[vexnum - 1] = ve[vexnum - 1];
    for(int i = vexnum - 2; i >= 0; i--){//求vl
        VexNode* node = adjaL[i]->tonext;
        int t = 0;
        int index = 0;
        while(node != NULL){
            if(node->weight > t){
                t = node->weight;
                index = node->index;
            }
            node = node->next;
        } 
        vl[i] = vl[index] - t;
    }

    for(int i = 0; i < vexnum; i++){
        if(ve[i] == vl[i]){
            printf("%c ",adjaL[i]->data);
        }
    }
    printf("\n");
}


int main(){

    char data[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};
    int vexnum = 9;
    AdjaL **adjaL = initAdjaL(vexnum, data);
    addedge(adjaL, 'a', 'b', 6);
    addedge(adjaL, 'a', 'c', 4);
    addedge(adjaL, 'a', 'd', 5);
    addedge(adjaL, 'b', 'e', 1);
    addedge(adjaL, 'c', 'e', 1);
    addedge(adjaL, 'd', 'f', 2);
    addedge(adjaL, 'e', 'g', 9);
    addedge(adjaL, 'e', 'h', 7);
    addedge(adjaL, 'f', 'h', 4);
    addedge(adjaL, 'g', 'i', 2);
    addedge(adjaL, 'h', 'i', 4);

    printAdjaL(adjaL);
    printf("\n");
    printf("输出拓扑排序：\n");
    topologicalSort(adjaL);
    printf("输出关键路径：\n");
    critialPath(adjaL);


    return 0;
}