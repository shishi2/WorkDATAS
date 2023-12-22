#include <stdio.h>
#include <stdlib.h>
#define RANDNUM 20   //随机数的数目

void InsertSort(int num[RANDNUM]){  //插入排序
    for(int i = 1; i < RANDNUM; i++){
        int t = num[i];
        int j = i - 1;
        while (j >= 0 && num[j] > t)
        {   
            num[j+1] = num[j];
            j--;
        }
        num[j+1] = t;
    }
}

void BiInsertSort(int num[RANDNUM]){    //折半排序
    //找到后将其往后移动其运算次数 == 直接查找？
    //减少比较次数，但是移动次数不变
    for (int i = 1; i < RANDNUM; i++)
    {
        int t = num[i];
        int mid;
        int left = 0;
        int right = i - 1;

        while (left <= right)   //必须<=
        {
            mid = (left + right)/2;
            if(num[mid] < t){
                left = mid + 1;
            }else{
                right = mid - 1;
            }  
        }
        int j = i - 1;
        while (j >= left )
        {
            num[j+1] = num[j];
            j--;
        }
        num[j+1] = t;
    }
}

int main(){
    int randnum[RANDNUM];
    for(int i = 0; i < RANDNUM; i++){
        randnum[i] = rand() % RANDNUM;
    }
    for(int i = 0; i < RANDNUM; i++){
        printf("%4d",randnum[i]);
    }
    printf("\n");
    //InsertSort(randnum);
    BiInsertSort(randnum);
    for(int i = 0; i < RANDNUM; i++){
        printf("%4d",randnum[i]);
    }


    return 0;
}
