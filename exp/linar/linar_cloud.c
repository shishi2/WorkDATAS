#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*服务器
*@param vm1 cpu: 2 memory: 4
*@param vm2 cpu: 8 memory: 32
*@param vm3 cpu: 24 memory: 64
*/
typedef struct Server{
    int CPU;/*已使用cpu*/
    int MEMORY;/*已使用内存*/
    int vm1;/*已使用的VM1的数目*/
    int vm2;/*已使用的VM2的数目*/
    int vm3;/*已使用的VM3的数目*/
}Server;

/*虚拟机数目*/
typedef struct VMNum{
    int vm1;/*vm1数目*/
    int vm2;/*vm2数目*/
    int vm3;/*vm3数目*/
}VMNum;

/*
*创建虚拟机数目
*@param vm1 当输入为-1时，随机生成vm1数目
*@param vm2 当输入为-1时，随机生成vm2数目
*@param vm3 当输入为-1时，随机生成vm3数目
*/
VMNum* initVM(int vm1,int vm2,int vm3){
    VMNum* V = (VMNum*)malloc(sizeof(VMNum));
    if(vm1 >= 0){
        V->vm1 = vm1;
    }else{
        V->vm1 = rand()%71 + 30;
    }
    printf("vm1:%d\n",V->vm1);
    if(vm2 >= 0){
        V->vm2 = vm2;
    }else{
        V->vm2 = rand()%71 + 30;
    }
    printf("vm2:%d\n",V->vm2);
    if(vm3 >= 0){
        V->vm3 = vm3;
    }else{
        V->vm3 = rand()%71 + 30;
    }
    printf("vm3:%d\n",V->vm3);
    return V;
}

/*
*计算剩余cpu核心数目
*/
int useCpu(int vm1,int vm2,int vm3){
    return (vm1*2 + vm2*8 + vm3*24);
}
/*
*计算剩余内存数目
*/
int useMemoray(int vm1,int vm2,int vm3){
    return (vm1*4 + vm2*32 + vm3*64);
}

/**
 * 创建服务器
*/
Server* initServer(VMNum* V){
    Server* S = (Server*)malloc(sizeof(Server)*(30));
    memset(S,0,sizeof(Server)*30);
    for(int i = 0; i < 30; i++){
        S[i].CPU = 0;
        S[i].MEMORY = 0;
        S[i].vm1 = 0;
        S[i].vm2 = 0;
        S[i].vm3 = 0;
    }
    return S;
}

/*
*添加虚拟机
*/
void addVm(Server* S,VMNum* V,int* num){
    *num = 0;
    int S_count = 0;
    int vm_count[3] = {V->vm1,V->vm2,V->vm3};//各种虚拟机的数目
    int requre_cpu[3] = {2,8,24};
    int requre_memory[3] = {4,32,64};
    int vm1_count[30] = {0},vm2_count[30] = {0},vm3_count[30] = {0};
    //对应服务器分配的虚拟机数目

    for(int i = 0; i < 3; i++){//三种虚拟机
        for(int j = 0; j < vm_count[i];j++){//对i类虚拟机进行分配
            int allocat = 0;//为0时表示未能找到对应的服务器进行分配
            S_count++;
            for(int k = 0; k <= S_count; k++){//查找适合的服务器0~S_count[)
                //内存比较富余, 主要以cpu核心数为限制
                //只有当服务器全部使用VM2的时候才会使得内存占满, 但同时cpu也满了。
                //故可以考虑不对内存剩余量进行比较, 可以加快速度
                if((128 - useCpu(vm1_count[k],vm2_count[k],vm3_count[k])) >= requre_cpu[i]
                && (512 - useMemoray(vm1_count[k],vm2_count[k],vm3_count[k])) >= requre_memory[i]){
                    //若服务器有剩余的核心和内存
                    if(requre_cpu[i] == 2){//当前为vm1
                        vm1_count[k]++;
                        allocat = 1;
                        break;
                    }
                    if(requre_cpu[i] == 8){//当前为vm2
                        vm2_count[k]++;
                        allocat = 1;
                        break;
                    }
                    if(requre_cpu[i] == 24){//当前为vm3
                        vm3_count[k]++;
                        allocat = 1;
                        break;
                    }
                }
            }
            
            if (allocat == 0){//在当前已启动的服务器中未有盈余，故新启动一台
                S_count++;//新启动一台服务器
                if(requre_cpu[i] == 2){
                    vm1_count[S_count]++;
                    continue;
                }
                if(requre_cpu[i] == 8){
                    vm2_count[S_count]++;
                    continue;
                }
                if(requre_cpu[i] == 64){
                    vm3_count[S_count]++;
                    continue;
                }
            }
        }
    }
    //将服务器信息存入S中
    for (int i = 0; i <= S_count + 1; i++){
        S[i].vm1 = vm1_count[i];
        S[i].vm2 = vm2_count[i];
        S[i].vm3 = vm3_count[i];
        S[i].CPU = useCpu(S[i].vm1,S[i].vm2,S[i].vm3);
        S[i].MEMORY = useMemoray(S[i].vm1,S[i].vm2,S[i].vm3);
        if(S[i].vm3 == 0 && S[i].vm1 == 0 && S[i].vm2 == 0){
            *num = i;
            break;
        }
    }
}

/*
*输出服务器及分配的虚拟机目录
*/
void printServer(Server* S,int num){
    
    printf("目前已启动%d台服务器\n",num);
    for(int i = 0; i < num ;i++){
        printf("服务器%3d:\n",i);
        printf("分配VM1共%3d台,分配VM2共%3d台,分配VM3共%3d台\n",S[i].vm1,S[i].vm2,S[i].vm3);
    }
}

int main(){
    int* num = (int*)malloc(sizeof(int));

    while (1){
        int flag = 0;
        printf("创建虚拟机请求请输入1\n");
        printf("在服务器上添加虚拟机请输入2\n");
        printf("输出虚拟机目录请输入3\n");
        printf("退出请输入-1\n");
        scanf("%d",&flag);
        int vm1,vm2,vm3;
        switch (flag){
            case 1:
                printf("创建虚拟机请求\n");
                printf("请输入VM1的数目(随机请输入-1)\n");
                scanf("%d",&vm1);
                printf("请输入VM2的数目(随机请输入-1)\n");
                scanf("%d",&vm2);
                printf("请输入VM3的数目(随机请输入-1)\n");
                scanf("%d",&vm3);
                VMNum* V1 = initVM(vm1,vm2,vm3);
                Server* S = initServer(V1);
                addVm(S,V1,num);
                break;
            case 2:
                printf("在服务器上添加虚拟机\n");
                S = initServer(V1);
                addVm(S,V1,num);
                break;
            case 3:
                printf("输出服务器目录\n");
                printServer(S,*num);
                break;
            case -1:
                return 0;
            default:
                printf("输入错误，请重新输入\n");
                break;
        }
    }
    

    return 0;
}