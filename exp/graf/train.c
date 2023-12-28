#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX -1

/**
 * 邻接表节点
*/
typedef struct VexNode{
    int index;/*邻接表下标*/
    int time;
    struct VexNode* next;
}VexNode;

/**
 * 邻接表头
*/
typedef struct AdjaL{
    char city[5];
    int VexNum;/*总节点*/
    int linenum;/*当前线路*/
    int line;/*总线路*/
    VexNode* vex;
}AdjaL;

/**
 * 创建3dim邻接表头
*/
AdjaL*** init3Adj(int line,int vexnum,char city[][5]){
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
 * 添加3dim邻接表节点
 * @param time 权值信息
*/
void creat3AdjL(AdjaL*** A,int* time){
    int VexNum = A[0][0]->VexNum;
    int line = A[0][0]->line;
    for(int i = 0; i < line; i++){
        for (int j = 0; j < VexNum; j++){
            for(int k = VexNum - 1; k >= 0; k--){
                int time_t = *(time + i * line * VexNum +j * VexNum + k);
                if(time_t == MAX || time_t == 0){/*不记录不可达和本身*/
                    continue;
                }
                VexNode* node = (VexNode*)malloc(sizeof(VexNode));
                node->index = k;
                node->time = *(time + i * line * VexNum +j * VexNum + k);
                VexNode* t = A[i][j]->vex;
                A[i][j]->vex = node;
                node->next = t;
            }
        } 
    }
}

/**
 * 创建二维邻接表，不含线路信息
*/
AdjaL** init2AdjaL(int VexNum,char city[][5]){
    AdjaL** B = (AdjaL**)malloc(sizeof(AdjaL*));
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
 * 添加2dim邻接表节点
 * 只保留两相邻节点之间更少时间的数据
 * @param line 线路图数目
*/
void creat2AdjaL(AdjaL** B,int* time,int line){
    int VexNum = B[0]->VexNum;
    for(int i = 0;i < line;i++){/*对各个线路进行遍历*/
        for(int j = 0; j < VexNum; j++){/*单个线路添加*/
            for(int k = VexNum; k >= 0; k--){
                int time_t = *(time + i*line*VexNum + j*VexNum + k);
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
 * 输出3dim的所有站点
*/
void print3AdjaL(AdjaL*** A){
    int length = A[0][0]->VexNum;
    for(int i = 0; i < length; i++){
        printf("%s\n",A[0][i]->city);
    }    
}

/**
 * 输出2dim的所有占点
*/
void print2AdjaL(AdjaL** B){
    int length = B[0]->VexNum;
    for (int i = 0; i < length; i++)
    {
        printf("%s\n",B[i]->city);
    }
    
}

int main(){
    char city[30][5]={"fir","sec","thi"};
    int time[2][3][3] = 
    {
        {{0,1,MAX},{1,0,2},{MAX,2,0}},
        {{0,4,MAX},{4,0,MAX},{MAX,MAX,0}}
    };

    AdjaL*** A = init3Adj(3,3,city);
    creat3AdjL(A,(int*)time);
    print3AdjaL(A);

    AdjaL** B = init2AdjaL(3,city);
    creat2AdjaL(B,(int*)time,2);
    print2AdjaL(B);


    return 0;
}
