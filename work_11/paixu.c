#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RANDNUM 200000   //随机数的数目

void InsertSort(int num[RANDNUM]){  //插入排序
    clock_t start,finish;
    double Total_time;
    start = clock();

    for(int i = 1; i < RANDNUM; i++){
        int t = num[i];
        int j = i - 1;  //从0到当前数据t之前
        while (j >= 0 && num[j] > t){   
            num[j+1] = num[j];  //数据t之前的数据已排好，故直接交换
            j--;
        }
        num[j+1] = t;
    }

    finish = clock();
    Total_time = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("插入排序耗时%f秒\n",Total_time);
}

void BiInsertSort(int num[RANDNUM]){    //折半排序
    //找到后将其往后移动其运算次数 == 直接查找？
    //减少比较次数，但是移动次数不变
    clock_t start,finish;
    double Total_time;
    start = clock();

    for (int i = 1; i < RANDNUM; i++){
        int t = num[i];
        int mid;
        int left = 0;
        int right = i - 1;

        while (left <= right){  //必须 <=
            mid = (left + right)>>1;    //位运算 == /2
            if(num[mid] < t){
                left = mid + 1; //比[mid]大，left右移
            }else{
                right = mid - 1;    //比[mid]小，right左移
            }  
        }
        int j = i - 1;
        while (j >= left ){
            num[j+1] = num[j];
            j--;
        }
        num[j+1] = t;   //left的位置
    }
    
    finish = clock();
    Total_time = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("折半排序耗时%f秒\n",Total_time);
}

void Bi2_InsertSort(int num[RANDNUM],int result[RANDNUM]){  //2-路插入排序
    clock_t start,finish;
    double Total_time;
    start = clock();

    result[0] = num[0];
    for(int i = 1; i < RANDNUM; i++){
        int left = 0;
        int right = i - 1;
        int mid;
        int t = num[i];
        while (left <= right){
            mid = (left + right)>>1;
            if(result[mid] < t){
                left = mid + 1;
            }else{
                right = mid - 1;
            }
        }
        int j = i - 1;
        while (j >= left){
            result[j+1] = result[j];
            j--;
        }
        result[j + 1] = t;
    }
    finish = clock();
    Total_time = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("2-路插入排序耗时%f秒\n",Total_time);
}

void maopao(int num[RANDNUM]){
    clock_t start,finish;
    double Total_time;
    start = clock();

    for(int i = 0; i < RANDNUM; i++){
        for(int j = 0; j < RANDNUM - i - 1; j++){
            if(num[j] > num[j+1]){
                int t = num[j];
                num[j] = num[j+1];
                num[j+1] = t;
            }
        }
    }

    finish = clock();
    Total_time = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("冒泡排序耗时%f秒\n",Total_time);
}

void fast(int num[RANDNUM],int left,int right){
    clock_t start,finish;
    double Total_time;
    start = clock();

    int i = left;
    int j = right;
    int t = num[left];
    if(left > right){
        return;
    }
    while (i != j){
        while (num[j] >= t && i < j){
            j--;
        }
        while (num[i] <= t && i < j){
            i++;
        }
        if(i < j){
            int temp = num[i];
            num[i] = num[j];
            num[j] = temp;
        }
    }
    num[left] = num[i];
    num[i] = t;
    fast(num,left,i-1);
    fast(num,i+1,right);
}

void fastSort(int num[RANDNUM]){
    clock_t start,finish;
    double Total_time;
    start = clock();

    fast(num,0,RANDNUM-1);

    finish = clock();
    Total_time = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("快速排序耗时%f秒\n",Total_time);
}

    int randnum_1[RANDNUM]; //插入排序
    int randnum_2[RANDNUM]; //折半排序
    int randnum_3[RANDNUM]; //2-路插入排序
    int randnum_4[RANDNUM]; //2-路插入排序辅助
    int randnum_5[RANDNUM]; //冒泡排序
    int randnum_6[RANDNUM]; //快速排序

int main(){
    
    for(int i = 0; i < RANDNUM; i++){
        randnum_1[i] = rand() % RANDNUM;
        randnum_2[i] = randnum_1[i];
        randnum_3[i] = randnum_1[i];
        randnum_5[i] = randnum_1[i];
        randnum_6[i] = randnum_1[i];
    }
    // for(int i = 0; i < RANDNUM; i++){
    //     printf("%4d",randnum_1[i]);
    // }
    printf("\n");
    printf("随机数的数目%d\n",RANDNUM);
    InsertSort(randnum_1);
    BiInsertSort(randnum_2);
    Bi2_InsertSort(randnum_3,randnum_4);
    maopao(randnum_5);
    fastSort(randnum_6);
    // for(int i = 0; i < RANDNUM; i++){
    //     printf("%4d",randnum_4[i]);
    // }


    return 0;
}
