#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student
{//单个学生
    int clas;
    int num;
    char name[10];
    int sex;   //0男, 1女
    int phone;
}Student;

typedef struct List
{//学生列表
    Student* studentList;
    int length;
    int num;
}List;

List* initList(int stunum){
    List* L = (List*)malloc(sizeof(List));
    L->length = stunum;
    L->num = 0;
    L->studentList = (Student*)malloc(sizeof(Student)*stunum);
    return L;
}

void InsertList(List* L,int clas,char *name,int num,int phone ,int sex){
    L->studentList[L->num].clas = clas;
    strcpy(L->studentList[L->num].name,name);
    L->studentList[L->num].num = num;
    L->studentList[L->num].phone = phone;
    L->studentList[L->num].sex = sex;
    L->num++;
}

void creatList(List* L,int clas){
    for(int i = 0; i < L->length; i++){
        char t = (65 + i);
        char name[10] = {t};
        int num = 1000 + i;
        InsertList(L,clas,name,num,rand() % 1000,rand() % 2);
    }
}

void destory(List* L){
    free(L->studentList);
    free(L);
}

void seqSearch(List* L1,List* L2,int num,int clas){
    int i = L1->length;
    int j = L2->length;
    switch (clas)
    {
    case 1:
            while(i>=0){
                if(L1->studentList[i].num == num){
                    printf("\n以下为所查询到的学生: \n");
                    printf("班级：%d, 名字: %s, 学号: %d, 电话号码: %d, 性别: %d\n",
                        L1->studentList[i].clas,L1->studentList[i].name,L1->studentList[i].num,L1->studentList[i].phone,L1->studentList[i].sex);
                }
                i--;
            }
            break;
    case 2:
            while(j>=0){
                if(L2->studentList[i].num == num){
                    printf("\n以下为所查询到的学生: \n");
                    printf("班级：%d, 名字: %s, 学号: %d, 电话号码: %d, 性别: %d\n",
                        L2->studentList[j].clas,L2->studentList[j].name,L2->studentList[j].num,L2->studentList[j].phone,L2->studentList[j].sex);
                }
                j--;
            }
            break;
    
    default:
            printf("未能查询到对应的学生");
            break;
    }
}

void biSearch(List* L1,List* L2,int num,int clas){  
    int flag = 0;
    if(clas == 1){
        flag = 1;
        int left = 0;
        int right = L1->length;
        int mid;
        while(left <= right){
            mid = (left + right)>>1;
            if(L1->studentList[mid].num == num){
                printf("\n以下为所查询到的学生: \n");
                printf("班级：%d, 名字: %s, 学号: %d, 电话号码: %d, 性别: %d\n",
                L1->studentList[mid].clas,L1->studentList[mid].name,L1->studentList[mid].num,L1->studentList[mid].phone,L1->studentList[mid].sex);
                break;
            }
            if(L1->studentList[mid].num > num){
                right = mid-1;
            }else{
                left = mid + 1;
            }
        }
    }

    if(clas == 2){
        flag = 1;
        int left = 0;
        int right = L2->length;
        int mid;
        while(left <= right){
            mid = (left + right)>>1;
            if(L2->studentList[mid].num == num){
                printf("\n以下为所查询到的学生: \n");
                printf("班级：%d, 名字: %s, 学号: %d, 电话号码: %d, 性别: %d\n",
                L2->studentList[mid].clas,L2->studentList[mid].name,L2->studentList[mid].num,L2->studentList[mid].phone,L2->studentList[mid].sex);
                break;
            }
            if(L2->studentList[mid].num > num){
                right = mid - 1;
            }else{
                left = mid + 1;
            }
        }
    }
    if(!flag){
        printf("未能查询到对应的学生");
    }
    
}

void PrintList(List* L){
    for(int i = 0; i< L->length; i++){
        printf("班级：%d, 名字: %s, 学号: %d, 电话号码: %d, 性别: %d\n",
        L->studentList[i].clas,L->studentList[i].name,L->studentList[i].num,L->studentList[i].phone,L->studentList[i].sex);
    }
}


int main(){

    List* L1 = initList(5);
    creatList(L1,1);
    PrintList(L1);
    printf("\n");

    List* L2 = initList(5);
    creatList(L2,2);
    PrintList(L2);
    seqSearch(L1,L2,1001,1);
    printf("\n");
    biSearch(L1,L2,1002,2);

    return 0;
}
