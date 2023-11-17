#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct VexNode{
    int weight;//两城市间距离
    int index;//城市下标
    struct VexNode *next;
}VexNode;

typedef struct AdjaL{
    char city[20];//城市名
    VexNode *vex;//邻接表节点
}AdjaL;

typedef struct Graph{
    int vexnum;//顶点数
    AdjaL **adjL;//邻接表
}Graph;

Graph* createGraph(int vexnum){//创建图邻接表
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->vexnum = vexnum;

    graph->adjL = (AdjaL**)malloc(sizeof(AdjaL*) * vexnum);//邻接表
    for(int i = 0; i < vexnum; i++){
        graph->adjL[i] = (AdjaL*)malloc(sizeof(AdjaL));
        graph->adjL[i]->vex = NULL;
        memset(graph->adjL[i]->city, '\0', sizeof(graph->adjL[i]->city));
    }

    return graph;
}

int FindIndex(Graph *graph, char city[20]){//获取城市下标
    for(int i = 0; i < graph->vexnum; i++){
        if(strcmp(graph->adjL[i]->city, city) == 0){
            return i;
        }
    }
    return -1;
}

void addEdge(Graph *graph, char start[20], char end[20], int weight){//添加边
    int start_index = FindIndex(graph, start);
    int end_index = FindIndex(graph, end);

    VexNode *node_start = (VexNode*)malloc(sizeof(VexNode));//在起始城市的邻接表中添加
    node_start->index = end_index;
    node_start->weight = weight;
    node_start->next = graph->adjL[start_index]->vex;//头插法
    graph->adjL[start_index]->vex = node_start;

    VexNode *node_end = (VexNode*)malloc(sizeof(VexNode));//在终点城市的邻接表中添加
    node_end->index = start_index;
    node_end->weight = weight;
    node_end->next = graph->adjL[end_index]->vex;
    graph->adjL[end_index]->vex = node_end;
}

void addcity(Graph *graph){//添加城市
    strcpy(graph->adjL[0]->city, "北京");
    strcpy(graph->adjL[1]->city, "天津");
    strcpy(graph->adjL[2]->city, "呼和浩特");
    strcpy(graph->adjL[3]->city, "郑州");
    strcpy(graph->adjL[4]->city, "沈阳");
    strcpy(graph->adjL[5]->city, "哈尔滨");
    strcpy(graph->adjL[6]->city, "大连");
    strcpy(graph->adjL[7]->city, "长春");
    strcpy(graph->adjL[8]->city, "徐州");
    strcpy(graph->adjL[9]->city, "上海");
    strcpy(graph->adjL[10]->city, "南昌");
    strcpy(graph->adjL[11]->city, "福州");
    strcpy(graph->adjL[12]->city, "武汉");
    strcpy(graph->adjL[13]->city, "株州");
    strcpy(graph->adjL[14]->city, "广州");
    strcpy(graph->adjL[15]->city, "深圳");
    strcpy(graph->adjL[16]->city, "南宁");
    strcpy(graph->adjL[17]->city, "柳州");
    strcpy(graph->adjL[18]->city, "贵阳");
    strcpy(graph->adjL[19]->city, "昆明");
    strcpy(graph->adjL[20]->city, "成都");
    strcpy(graph->adjL[21]->city, "西安");
    strcpy(graph->adjL[22]->city, "兰州");
    strcpy(graph->adjL[23]->city, "西宁");
    strcpy(graph->adjL[24]->city, "乌鲁木齐");
}

void dijkstra(Graph *graph, int start, int end){//通过dijkstra算法求最短路径
    int *dist = (int*)malloc(sizeof(int) * graph->vexnum);//存储起始城市到各个城市的距离
    int *path = (int*)malloc(sizeof(int) * graph->vexnum);//存储最短路径
    int *visited = (int*)malloc(sizeof(int) * graph->vexnum);//标记城市是否被访问过

    for(int i = 0; i < graph->vexnum; i++){//初始化
        dist[i] = -1;
        path[i] = -1;
        visited[i] = 0;
    }

    VexNode *node = graph->adjL[start]->vex;
    while(node != NULL){//初始化起始城市到各个城市的距离
        dist[node->index] = node->weight;
        path[node->index] = start;
        node = node->next;
    }
    visited[start] = 1;//标记起始城市已被访问

    for(int i = 0; i < graph->vexnum; i++){//循环n-1次
        int min = -1;
        int min_index = -1;
        for(int j = 0; j < graph->vexnum; j++){//找到未被访问过的最小距离的城市
            if(visited[j] == 0 && dist[j] != -1){
                if(min == -1 || dist[j] < min){
                    min = dist[j];
                    min_index = j;
                }
            }
        }
        if(min_index == -1){//如果没有找到，说明剩下的城市都不可达
            break;
        }
        visited[min_index] = 1;//标记该城市已被访问

        node = graph->adjL[min_index]->vex;
        while(node != NULL){//更新起始城市到各个城市的距离
            if(visited[node->index] == 0){
                if(dist[node->index] == -1 || dist[node->index] > dist[min_index] + node->weight){
                    dist[node->index] = dist[min_index] + node->weight;
                    path[node->index] = min_index;
                }
            }
            node = node->next;
        }
    }

    printf("最短路径为: ");
    int index = end;
    while(index != start){//打印最短路径
        printf("%s ", graph->adjL[index]->city);
        index = path[index];
    }
    printf("%s", graph->adjL[start]->city);
    printf("(%d)\n", dist[end]);
    free(dist);
    free(path);
    free(visited);
}

void A2Orthers(Graph* graph, char start[20]){//求A到其他所有的最短路径
    int start_index = FindIndex(graph, start);
    for(int i = 0; i < graph->vexnum; i++){
        if(i != start_index){
            dijkstra(graph, start_index, i);
        }
    }
}

void addCityEdge(Graph* graph){//添加城市间距离    
    addEdge(graph, "北京", "天津", 137);
    addEdge(graph, "北京", "呼和浩特", 668);
    addEdge(graph, "北京", "郑州", 695);
    addEdge(graph, "天津", "沈阳", 704);
    addEdge(graph, "沈阳", "大连", 397);
    addEdge(graph, "沈阳", "长春", 305);
    addEdge(graph, "长春", "哈尔滨", 242);
    addEdge(graph, "天津", "徐州", 674);
    addEdge(graph, "徐州", "上海", 651);
    addEdge(graph, "上海", "南昌", 825);
    addEdge(graph, "南昌", "福州", 622);
    addEdge(graph, "徐州", "郑州", 349);
    addEdge(graph, "郑州", "武汉", 534);
    addEdge(graph, "武汉", "株州", 409);
    addEdge(graph, "株州", "广州", 675);
    addEdge(graph, "株州", "贵阳", 902);
    addEdge(graph, "株州", "南昌", 367);
    addEdge(graph, "广州", "深圳", 140);
    addEdge(graph, "株州", "柳州", 672);
    addEdge(graph, "柳州", "南宁", 255);
    addEdge(graph, "柳州", "贵阳", 607);
    addEdge(graph, "贵阳", "昆明", 639);
    addEdge(graph, "贵阳", "成都", 967);
    addEdge(graph, "昆明", "成都", 1100);
    addEdge(graph, "成都", "西安", 842);
    addEdge(graph, "西安", "兰州", 676);
    addEdge(graph, "兰州", "西宁", 216);
    addEdge(graph, "兰州", "乌鲁木齐", 1892);
    addEdge(graph, "兰州", "呼和浩特", 1145);
    addEdge(graph, "郑州", "西安", 511);
}

//打印邻接表
void printGraph(Graph *graph){
    printf("起始城市: 目标城市(距离)\n");
    for(int i = 0; i < graph->vexnum; i++){
        printf("%s: ", graph->adjL[i]->city);
        VexNode *node = graph->adjL[i]->vex;
        while(node != NULL){
            printf("%s(%d) ", graph->adjL[node->index]->city, node->weight);
            node = node->next;
        }
        printf("\n");
    }
}

int main(){
    int vexnum = 25;
    Graph *graph = createGraph(vexnum);
    addcity(graph);//添加25个城市
    addCityEdge(graph);//添加城市间距离
    //printGraph(graph);//打印邻接表
    A2Orthers(graph, "徐州");//求A到其他所有的最短路径


    return 0;
}
