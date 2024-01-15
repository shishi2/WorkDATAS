#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 54713

/**
 * �ڽӱ�ڵ�
*/
typedef struct VexNode{
    int index;/*�ڽӱ��±�*/
    int time;/*��վ֮���ʱ��*/
    struct VexNode* next;
}VexNode;

/**
 * �ڽӱ�ͷ
*/
typedef struct AdjaL{
    char city[20];
    int VexNum;/*�ܽڵ�*/
    int linenum;/*��ǰ��·*/
    int line;/*����·*/
    VexNode* vex;
}AdjaL;

/**
 * ����3dim�ڽӱ�ͷ
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
 * ����3dim�����ڽӱ�ڵ�
 * @param time Ȩֵ��Ϣ
*/
void creat3AdjL(AdjaL*** A,int* time){
    int VexNum = A[0][0]->VexNum;
    int line = A[0][0]->line;
    for(int i = 0; i < line; i++){
        for (int j = 0; j < VexNum; j++){
            for(int k = VexNum - 1; k >= 0; k--){
                int time_t = *(time + i * VexNum * VexNum +j * VexNum + k);
                if(time_t == MAX || time_t == 0){/*����¼���ɴ�ͱ���*/
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
 * ������ά�ڽӱ�ͷ��������·��Ϣ
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
 * ��������2dim�ڽӱ�ڵ�
 * ֻ���������ڽڵ�֮�����ʱ�������
 * @param line ��·ͼ��Ŀ
*/
void creat2AdjaL(AdjaL** B,int* time,int line){
    int VexNum = B[0]->VexNum;
    for(int i = 0;i < line;i++){/*�Ը�����·���б���*/
        for(int j = 0; j < VexNum; j++){/*������·���*/
            for(int k = VexNum-1; k >= 0; k--){
                int time_t = *(time + i*VexNum*VexNum + j*VexNum + k);
                if(time_t == MAX || time_t == 0){/*����¼���ɴ�ͱ���*/
                    continue;
                }
                VexNode* t = B[j]->vex;
                int flag = 0;/*����������δ��*/
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
 * ���2dimվ����ͨ��ϵ
 * ������ͨ�����ʱ��
*/
void addAdjaL(AdjaL** B,char start[20],char end[20],int time){
    int VexNum = B[0]->VexNum;
    int start_index = -1;
    int end_index = -1;
    /*findIndex��������*/
    for (int i = 0; i < VexNum; i++){/*�ҵ�start��end���ڵ��±�*/
        if(strcmp(B[i]->city,start) == 0){
            start_index = i;
            continue;
        }
        if(strcmp(B[i]->city,end) == 0){
            end_index = i;
        }
    }
    VexNode* t = B[start_index]->vex;
    int flag = true;/*����δ��*/
    while (t){/*����ʼ�ڵ��ң������*/
        if(t->index == end_index){
            flag = false;
            t->time = time;
            break;
        }
        t = t->next;
    }
    if(flag){/*����δ��*/
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
    }else{/*��*/
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
 * ��2dim�ڽӱ����BFS
 * @param flag 0 ������path ֻ����path����
*/
bool BFS2(AdjaL** B, int start_index, int end_index, int* path, int* path_length) {
    int VexNum = B[0]->VexNum;
    int queue[VexNum]; // ���ڴ�Ŵ�����Ľڵ�
    bool visited[VexNum]; // ��¼�ڵ��Ƿ񱻷��ʹ�
    int prev[VexNum]; // ��¼·���и��ڵ��ǰ���ڵ�
    for(int i = 0;i < VexNum; i++){
        prev[i] = -1;
        queue[i] = -1;
        visited[i] = false;
    }

    int rear = 0;/*��β*/
    int front = 0;

    queue[rear] = start_index; rear++;/*����ʼ�ڵ����*/
    visited[start_index] = true;
    
    while(front < rear){/*��ʽBFS*/
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
    /*�ѱ�������ŵ�path��*/
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
 * �ҵ��������ƶ�Ӧ���±�
 * @return -1 δ�ҵ� 
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
 * ��2dim�ڽӱ������·��������;��վ��
 * ��;����վ����Ϊ��������
 * ��ÿ���ɴ�վ��֮���Ȩֵ��Ϊ��1
 * ���;����վ��
*/
void findShortestPath(AdjaL** B, char start[20], char end[20]){
    int VexNum = B[0]->VexNum;
    int start_index = findIndex(B,start);
    int end_index = findIndex(B,end);
    
    if (start_index == -1 || end_index == -1) {
        printf("�����յ㲻��ͼ��\n");
        return;
    }
    
    int path[VexNum], path_length = 0;
    bool found = BFS2(B, start_index, end_index, path, &path_length);

    if (found && path_length > 2) {
        printf("���·��Ϊ: ");
        for (int i = path_length - 1; i >= 0; i--) {
            printf("%s ", B[path[i]]->city);
        }
        printf("\n�䳤��Ϊ%d\n",path_length );
    } else {
        printf("û���ҵ�·��\n");
    }  
}

/**
 * ��������֮�仨�ѵ����ʱ��
*/
void lessTime(AdjaL** B,char start[20],char end[20]){
    int VexNum = B[0]->VexNum;
    int start_index = findIndex(B,start);
    int end_index = findIndex(B,end);
    if (start_index == -1 || end_index == -1) {
        printf("�����յ㲻��ͼ��\n");
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
        printf("\nһ����ʱ%dmin\n",time);
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
 * �Ի��ߴ���Ϊ��׼
 * ��ѯ���ߴ���
*/
void lessChangeline(AdjaL*** A,char start[20],char end[20]){
    int line = A[0][0]->line;
    int VexNum = A[0][0]->VexNum;

    /*���±�*/
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
    printf("���ٻ���Ϊ%d\n",changeline);
}

/**
 * ���3dim������վ��
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
 * ���2dim������վ��
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
        "���","����","����","����","��ʢ","����","�ŷ�","����","����","��ƽ"
    ,"����","����","�Ž�","�ӽ�","����","����","����","��԰","����","̨��"
    ,"����","â��","����","��ɽ","��ƽ","��ƽ","گ��","����","����","����"};
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

    // findShortestPath(B,"���","����");
    // lessTime(B,"���","����");
    // lessChangeline(A,"���","����");
    // addAdjaL(B,"���","����",10);
    // findShortestPath(B,"���","����");

    while (1){
        int flag = 0;
        printf("��;����վ��Ϊ���ݲ�ѯ���·��������1\n");
        printf("�����ʱ��Ϊ���ݲ�ѯ���·����ʱ��������2\n");
        printf("��ѯ���ٻ��ߴ���������3\n");
        printf("���վ��֮�����ͨ��ϵ������4\n");
        printf("�˳�������0\n");
        scanf("%d",&flag);
        switch (flag){
        case 1:
            printf("�����������յ�\n");
            char start[20],end[20];
            scanf("%s",start);
            scanf("%s",end);
            findShortestPath(B,start,end);
            break;
        case 2:
            printf("�����������յ�\n");
            scanf("%s",start);
            scanf("%s",end);
            lessTime(B,start,end);
            break;
        case 3:
            printf("�����������յ�\n");
            scanf("%s",start);
            scanf("%s",end);
            lessChangeline(A,start,end);
            break;
        case 4:
            printf("�����������յ�\n");
            scanf("%s",start);
            scanf("%s",end);
            printf("����������֮���ʱ��\n");
            int time;
            scanf("%d",&time);
            addAdjaL(B,start,end,time);
            break;
        case 0:
            return 0;
        default:
            printf("�����������������\n");
            break;
        }
    }
    
    return 0;
}
