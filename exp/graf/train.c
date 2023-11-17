#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 54713

/**
 * 邻接表节点
*/
typedef struct VexNode{
    int index;/*邻接表下标*/
    int time;/*两站之间的时间*/
    struct VexNode* next;
}VexNode;

/**
 * 邻接表头
*/
typedef struct AdjaL{
    char city[20];
    int VexNum;/*总节点*/
    int linenum;/*当前线路*/
    int line;/*总线路*/
    VexNode* vex;
}AdjaL;

/**
 * 创建3dim邻接表头
*/
AdjaL*** init3Adj(int line,int vexnum,char city[][20]){
    AdjaL*** A = (AdjaL***)malloc(sizeof(AdjaL**)*line);
    for(int i = 0; i < line; i++){
        A[i] = (AdjaL**)malloc(sizeof(AdjaL*)*vexnum);
        for(int j = 0; j < vexnum; j++){
            A[i][j] = (AdjaL*)malloc(sizeof(AdjaL));
            strcpy(A[i][j]->city,city[j]);
            A[i][j]->vex = NULL;
            A[i][j]->VexNum = vexnum;
            A[i][j]->line = line;
            A[i][j]->linenum = i;
        }
    }
    return A;
}

/**
 * 创建3dim大量邻接表节点
 * @param time 权值信息
*/
void creat3AdjL(AdjaL*** A,int* time){
    int VexNum = A[0][0]->VexNum;
    int line = A[0][0]->line;
    for(int i = 0; i < line; i++){
        for (int j = 0; j < VexNum; j++){
            for(int k = VexNum - 1; k >= 0; k--){
                int time_t = *(time + i * VexNum * VexNum +j * VexNum + k);
                if(time_t == MAX || time_t == 0){/*不记录不可达和本身*/
                    continue;
                }
                VexNode* node = (VexNode*)malloc(sizeof(VexNode));
                node->index = k;
                node->time = *(time + i * VexNum * VexNum +j * VexNum + k);
                VexNode* t = A[i][j]->vex;
                A[i][j]->vex = node;
                node->next = t;
            }
        } 
    }
}

/**
 * 创建二维邻接表头，不含线路信息
*/
AdjaL** init2AdjaL(int VexNum,char city[][20]){
    AdjaL** B = (AdjaL**)malloc(sizeof(AdjaL*)*VexNum);
        for (int j = 0; j < VexNum; j++){
            B[j] = (AdjaL*)malloc(sizeof(AdjaL));
            strcpy(B[j]->city,city[j]);
            B[j]->VexNum =VexNum;
            B[j]->line = 0;
            B[j]->linenum = 0;
            B[j]->vex =NULL;
        }
    return B;
}

/**
 * 创建大量2dim邻接表节点
 * 只保留两相邻节点之间更少时间的数据
 * @param line 线路图数目
*/
void creat2AdjaL(AdjaL** B,int* time,int line){
    int VexNum = B[0]->VexNum;
    for(int i = 0;i < line;i++){/*对各个线路进行遍历*/
        for(int j = 0; j < VexNum; j++){/*单个线路添加*/
            for(int k = VexNum-1; k >= 0; k--){
                int time_t = *(time + i*VexNum*VexNum + j*VexNum + k);
                if(time_t == MAX || time_t == 0){/*不记录不可达和本身*/
                    continue;
                }
                VexNode* t = B[j]->vex;
                int flag = 0;/*现有链表中未有*/
                while (t){
                    if(t->index == k){
                        flag = 1;
                        if(t->time > time_t){
                            t->time = time_t;
                        }
                        break;
                    }
                    t = t->next;
                }
                if(flag == 0){
                    VexNode* node = (VexNode*)malloc(sizeof(VexNode));
                    VexNode* temp = B[j]->vex;
                    node->time = time_t;
                    node->index = k;
                    node->next = temp;
                    B[j]->vex = node;
                }
            }
        }
    }
}

/**
 * 添加2dim站点联通关系
 * 若已联通则更新时间
*/
void addAdjaL(AdjaL** B,char start[20],char end[20],int time){
    int VexNum = B[0]->VexNum;
    int start_index = -1;
    int end_index = -1;
    /*findIndex可以做到*/
    for (int i = 0; i < VexNum; i++){/*找到start和end对于的下标*/
        if(strcmp(B[i]->city,start) == 0){
            start_index = i;
            continue;
        }
        if(strcmp(B[i]->city,end) == 0){
            end_index = i;
        }
    }
    VexNode* t = B[start_index]->vex;
    int flag = true;/*表中未有*/
    while (t){/*在起始节点找，有则该*/
        if(t->index == end_index){
            flag = false;
            t->time = time;
            break;
        }
        t = t->next;
    }
    if(flag){/*表中未有*/
        VexNode* node1 = (VexNode*)malloc(sizeof(VexNode));
        node1->index = end_index;
        node1->time = time;
        t = B[start_index]->vex;
        B[start_index]->vex = node1;
        node1->next = t;

        VexNode* node2 = (VexNode*)malloc(sizeof(VexNode));
        node2->index = start_index;
        node2->time = time;
        t = B[end_index]->vex;
        B[end_index]->vex = node2;
    }else{/*有*/
        t = B[end_index]->vex;
        while(t){
            if(flag == 0){
                t->time = time;
                break;
            }
        t = t->next;
        }
    }
}

/**
 * 对2dim邻接表进行BFS
 * @param flag 0 不计算path 只计算path长度
*/
bool BFS2(AdjaL** B, int start_index, int end_index, int* path, int* path_length) {
    int VexNum = B[0]->VexNum;
    int queue[VexNum]; // 用于存放待处理的节点
    bool visited[VexNum]; // 记录节点是否被访问过
    int prev[VexNum]; // 记录路径中各节点的前驱节点
    for(int i = 0;i < VexNum; i++){
        prev[i] = -1;
        queue[i] = -1;
        visited[i] = false;
    }

    int rear = 0;/*队尾*/
    int front = 0;

    queue[rear] = start_index; rear++;/*将起始节点入队*/
    visited[start_index] = true;
    
    while(front < rear){/*正式BFS*/
        if( queue[front] >= 0 && B[queue[front]]->vex){
            VexNode* Temp = B[queue[front]]->vex;
            while (Temp){
                if(Temp->index == NULL ){
                    break;
                }
                if(visited[Temp->index] == true){
                    Temp = Temp->next;
                }else{
                    queue[rear] = Temp->index;rear++;
                    visited[Temp->index] = true;
                    prev[Temp->index] = queue[front];
                    Temp = Temp->next;
                }
                
            }            
        }
        front++; 
    }

    // if(!visited[end_index]){
    //     return false;
    // }
    /*把遍历结果放到path中*/
    *path_length = 0;
    path[*path_length] = end_index;
    (*path_length)++;
    while (prev[path[*path_length-1]] != -1){
        path[*path_length] = prev[path[*path_length - 1]];
        (*path_length)++;
    }
    path[*path_length] = start_index;

    return true;
}

/**
 * 找到城市名称对应的下标
 * @return -1 未找到 
*/
int findIndex(AdjaL** B,char cityName[20]){
    int VexNum = B[0]->VexNum;
    int index = -1;
    for(int i = 0; i < VexNum; i++){
        if(strcmp(B[i]->city,cityName) == 0){
            index = i;
            break;
        }
    }
    return index;
}

/**
 * 对2dim邻接表找最短路径仅考虑途经站数
 * 以途经的站数作为计算依据
 * 即每个可达站点之间的权值认为是1
 * 输出途经的站点
*/
void findShortestPath(AdjaL** B, char start[20], char end[20]){
    int VexNum = B[0]->VexNum;
    int start_index = findIndex(B,start);
    int end_index = findIndex(B,end);
    
    if (start_index == -1 || end_index == -1) {
        printf("起点或终点不在图中\n");
        return;
    }
    
    int path[VexNum], path_length = 0;
    bool found = BFS2(B, start_index, end_index, path, &path_length);

    if (found && path_length > 2) {
        printf("最短路径为: ");
        for (int i = path_length - 1; i >= 0; i--) {
            printf("%s ", B[path[i]]->city);
        }
        printf("\n其长度为%d\n",path_length );
    } else {
        printf("没有找到路径\n");
    }  
}

/**
 * 计算两地之间花费的最短时间
*/
void lessTime(AdjaL** B,char start[20],char end[20]){
    int VexNum = B[0]->VexNum;
    int start_index = findIndex(B,start);
    int end_index = findIndex(B,end);
    if (start_index == -1 || end_index == -1) {
        printf("起点或终点不在图中\n");
        return;
    }

    int path[VexNum], path_length = 0;
    bool found = BFS2(B, start_index, end_index, path, &path_length);

    if(found){
        int time = 0;
        int i = path_length -1;
        while (i > 0){
            VexNode* t = B[path[i]]->vex;
            while (t){
                if(t->index == path[i-1]){
                    time += t->time;
                }
                t = t->next;
            }
            i--;
        }
        printf("\n一共耗时%dmin\n",time);
    }
}

bool BFS3(AdjaL*** A, int start, int end,int* flag) {
    int line = A[0][0]->line;
    int VexNum = A[0][0]->VexNum;
    int path[line][VexNum];
    int path_length[line];

    for(int i = 0; i < line; i++){
        BFS2(A[i],start,end,(int*)path[i],&(path_length[i]));
            for(int j = 0; j < path_length[i]; j++){
                if(path[i][j] == end){
                    (*flag) ++;
                    return true;
                }
            }
    }
    for(int i = 0; i < line; i++){
        if(path_length[i] > 0){
            for(int j = path_length[i]-1; j>=0;j--){
                bool t = BFS3(A,path[i][j],end,flag);
                if(t){
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * 以换线次数为标准
 * 查询换线次数
*/
void lessChangeline(AdjaL*** A,char start[20],char end[20]){
    int line = A[0][0]->line;
    int VexNum = A[0][0]->VexNum;

    /*找下标*/
    int start_index = -1;
    int end_index = -1;
    for(int i = 0; i < VexNum; i++){
        if(strcmp(A[0][i]->city, start)){
            start_index = i;
            continue;
        }
        if (strcmp(A[0][i]->city,end)){
            end_index = i;
            continue;
        } 
    }
    int changeline = 0;
    BFS3(A,start_index,end_index,&changeline);
    printf("最少换线为%d\n",changeline);
}

/**
 * 输出3dim的所有站点
*/
void print3AdjaL(AdjaL*** A){
    int length = A[0][0]->VexNum;
    for(int i = 0; i < length; i++){
        printf("%s  ",A[0][i]->city);
        if(i%5 == 4){
            printf("\n");
        }
    }    
}

/**
 * 输出2dim的所有站点
*/
void print2AdjaL(AdjaL** B){
    int length = B[0]->VexNum;
    for (int i = 0; i < length; i++)
    {
        printf("%s  ",B[i]->city);
        if(i%5 == 4){
            printf("\n");
        }
    }
}



int main(){
    char city[30][20]={
        "香港","福田","深圳","虎门","庆盛","赣州","信丰","龙南","定南","和平"
    ,"都匀","三都","榕江","从江","三江","苗栗","新竹","桃园","板桥","台北"
    ,"瑞丽","芒市","龙陵","保山","永平","饶平","诏安","云霄","漳浦","漳州"};
    int time[5][30][30] = {0};
    for (int i = 0; i < 5; i++){
        for(int j = 0; j < 10; j++){
            for(int k = 0; k < 30; k++){
                if(j == k){
                    time[i][j][k] = 0;
                    continue;
                }
                time[i][j][k] = MAX;
            }
        }
    }
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 3; j++){
            switch (i){
            case 0:
                time[0][i*5 + j][i*5 + j + 1] = rand()%10;
                break;
            case 1:
                time[1][i*5 + j][i*5 + j + 1] = rand()%20;
                break;
            case 2:
                time[2][i*5 + j][i*5 + j + 1] = rand()%30;
                break;
            case 3:
                time[3][i*5 + j][i*5 + j + 1] = rand()%40;
                break;
            case 4:
                time[4][i*5 + j][i*5 + j + 1] = rand()%50;
                break;
            }
        }
    }

    AdjaL*** A = init3Adj(5,30,city);
    creat3AdjL(A,(int*)time);

    AdjaL** B = init2AdjaL(30,city);
    creat2AdjaL(B,(int*)time,5);
    
    print3AdjaL(A);

    // findShortestPath(B,"香港","虎门");
    // lessTime(B,"香港","虎门");
    // lessChangeline(A,"香港","虎门");
    // addAdjaL(B,"香港","虎门",10);
    // findShortestPath(B,"香港","虎门");

    while (1){
        int flag = 0;
        printf("以途经的站数为依据查询最短路径请输入1\n");
        printf("以最短时间为依据查询最短路径的时间请输入2\n");
        printf("查询最少换线次数请输入3\n");
        printf("添加站点之间的联通关系请输入4\n");
        printf("退出请输入0\n");
        scanf("%d",&flag);
        switch (flag){
        case 1:
            printf("请输入起点和终点\n");
            char start[20],end[20];
            scanf("%s",start);
            scanf("%s",end);
            findShortestPath(B,start,end);
            break;
        case 2:
            printf("请输入起点和终点\n");
            scanf("%s",start);
            scanf("%s",end);
            lessTime(B,start,end);
            break;
        case 3:
            printf("请输入起点和终点\n");
            scanf("%s",start);
            scanf("%s",end);
            lessChangeline(A,start,end);
            break;
        case 4:
            printf("请输入起点和终点\n");
            scanf("%s",start);
            scanf("%s",end);
            printf("请输入两地之间的时间\n");
            int time;
            scanf("%d",&time);
            addAdjaL(B,start,end,time);
            break;
        case 0:
            return 0;
        default:
            printf("输入错误，请重新输入\n");
            break;
        }
    }
    
    return 0;
}
