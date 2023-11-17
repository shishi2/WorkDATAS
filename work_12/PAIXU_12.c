#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RANDNUM  20000  //随机数的数目

void selectSort(int num[RANDNUM]){
    clock_t start,finish;
    double Total_time;
    start = clock();

    for (int i = 0; i < RANDNUM; i++){
        int min = num[i];
        for(int j = i + 1; j < RANDNUM; j++){
            if(num[j] < min){
                int t = num[j];
                num[j] = min;
                num[i] = t;
                min = t;
            }
        }
    }

    finish = clock();
    Total_time = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("简单选择排序耗时%f秒\n",Total_time);
}

void max_heap(int num[RANDNUM],int start,int end){  //自上而下建立一个最大堆
    int largest = start;
    int left = 2 * start + 1;
    int right = 2 * start + 2;

    if(left < end && num[left] > num[largest]){
        largest = left ;
    }

    if(right < end && num[right] > num[largest]){
        largest = right;
    }

    if(largest != start){
        int t = num[start];
        num[start] = num[largest];
        num[largest] = t;

        max_heap(num,largest,end);  //保证经过交换的子节点也是最大堆
    }
}

void HeapSort(int num[RANDNUM]){    //利用最大堆进行排序
    clock_t start,finish;
    double Total_time;
    start = clock();

    for(int i = (RANDNUM/2) - 1; i >= 0; i--){  //一半即根节点
        max_heap(num,i,RANDNUM);    //自下而上构建最大堆
    }
    for(int i = RANDNUM - 1; i > 0; i--){
        int t = num[0];
        num[0] = num[i];
        num[i] = t;
        max_heap(num,0,i);
    }

    finish = clock();
    Total_time = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("堆排序耗时%f秒\n",Total_time);
}

void merge(int num[RANDNUM], int left, int mid, int right){
    int left_num = mid - left + 1;  //mid在left中
    int right_num = right - mid;

    int Left[left_num], l;  //把数据先保存在数组中
    int Right[right_num], r;
    for(l = 0; l < left_num; l++){
        Left[l] = num[left + l];
    }
    for(r = 0; r < right_num; r++){
        Right[r] = num[mid + r + 1];
    }

    l = r = 0;
    int flag = left;    //把数据放会num数组中，并排序
    while(l < left_num && r < right_num){
        if(Left[l] <= Right[r]){
            num[flag] = Left[l];
            l++;
        }else{
            num[flag] = Right[r];
            r++;
        }
        flag++;
    }

    while (l < left_num)    //对剩下的位置进行赋值
    {
        num[flag] = Left[l];
        flag++;
        l++;
    }
    while (r < right_num)
    {
        num[flag] = Right[r];
        flag++;
        r++;
    }
}

void M_Sort(int num[RANDNUM],int left,int right){
    if(left < right){
        int mid = (left + right)>>1;
        M_Sort(num,left,mid);
        M_Sort(num,mid+1,right);
        merge(num,left,mid,right);
    }
}

void mergeSort(int num[RANDNUM]){
    clock_t start,finish;
    double Total_time;
    start = clock();

    M_Sort(num,0,RANDNUM-1);

    finish = clock();
    Total_time = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("归并排序耗时%f秒\n",Total_time);
}

int main(){
    int randnum_1[RANDNUM];
    int randnum_2[RANDNUM];
    int randnum_3[RANDNUM];

    for(int i = 0; i < RANDNUM; i++){
        randnum_1[i] = rand() % RANDNUM;
        randnum_2[i] = randnum_1[i];
        randnum_3[i] = randnum_1[i];

    }

    // for(int i = 0; i < RANDNUM; i++){
    //     printf("%4d",randnum_1[i]);
    // }
    // printf("\n");
    printf("数据的数目为%d\n",RANDNUM);
    selectSort(randnum_1);
    HeapSort(randnum_2);
    mergeSort(randnum_3);
    
    // for(int i = 0; i < RANDNUM; i++){
    //     printf("%4d",randnum_3[i]);
    // }

    return 0;
}
