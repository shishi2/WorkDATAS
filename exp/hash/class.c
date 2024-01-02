#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct class_addr{
    char name[20];/*姓名 拼音*/
    int id;/*学号*/
    int domitory;/*宿舍*/
    int phone;/*手机号*/
}class_addr;

/**
 * 哈希表
*/
typedef struct class_hash{
    class_addr *addr;
    int length;/*表中元素个数*/
    int size;/*表长*/
}class_hash;

/**
 * 初始化哈希表
 * @param size 哈希表大小
*/
class_hash *init_class_hash(int size){
    class_hash *hash = (class_hash *)malloc(sizeof(class_hash));
    hash->length = 0;
    hash->size = size;
    hash->addr = (class_addr *)malloc(sizeof(class_addr) * size);
    for(int i = 0; i < size; i++){
        hash->addr[i].id = -1;
        hash->addr[i].domitory = -1;
        hash->addr[i].phone = -1;
        hash->addr[i].name[0] = '\0';
    }
    return hash;
}

/**
 * 哈希函数
 * @param name 姓名
 * @param size 哈希表大小
 * @return 哈希值
*/
int hash_func(char name[20],int size){
    int t = 0;
    int i = 0;
    while (name[i] != '\0'){
        t += name[i];
        i++;
    }
    
    return t % size;
}

/**
 * 添加学生信息
 * @param hash 通讯录哈希表
 * @param id 学号
 * @param domitory 宿舍号
 * @param phone 手机号
 * @param name 姓名
*/
void add_class_addr(class_hash *hash, int id, int domitory, int phone, char name[20]){
    if(hash->length == hash->size){
        printf("通讯录已满\n");
        return;
    }

    int index = hash_func(name, hash->size);//计算哈希值
    while(hash->addr[index].id != -1){//线性探测
        index = (index + 1) % hash->size;
    }

    hash->addr[index].domitory = domitory;
    hash->addr[index].id = id;
    hash->addr[index].phone = phone;
    strcpy(hash->addr[index].name, name);
    hash->length++;
}

/**
 * 查询学生信息
 * @param hash 通讯录哈希表
 * @param name 姓名
*/
void search_student(class_hash *hash, char name[20]){
    int index = hash_func(name, hash->size);
    int count = 0;
    while(count < hash->size && hash->addr[index].id != -1 && strcmp(hash->addr[index].name, name) != 0){
        index = (index + 1) % hash->size;
        count++;
    }
    if(count == hash->size){
        printf("查无此人\n");
        return;
    }
    printf("姓名：%s  ", hash->addr[index].name);
    printf("学号：%d  ", hash->addr[index].id);
    printf("宿舍号：%d  ", hash->addr[index].domitory);
    printf("手机号：%d  ", hash->addr[index].phone);
    printf("\n");
    printf("查找次数：%d\n", count);
}

/**
 * 修改学生信息
 * 若是修改姓名，则需要先删除再添加
 * 若是修改其他信息，0表示不修改 -1表示删除
 * 
 * @param hash 通讯录哈希表
 * @param name 姓名
 * @param id 学号
 * @param domitory 宿舍号
 * @param phone 手机号
*/
void modify_student(class_hash *hash, char name[20], int id, int domitory, int phone){
    int index = hash_func(name, hash->size);
    int count = 0;
    while(count < hash->size && hash->addr[index].id != -1 && strcmp(hash->addr[index].name, name) != 0){
        index = (index + 1) % hash->size;
        count++;
    }
    if(count == hash->size){
        printf("查无此人\n");
        return;
    }

    if(id != 0){
        hash->addr[index].id = id;
    }
    if(domitory != 0){
        hash->addr[index].domitory = domitory;
    }
    if(phone != 0){
        hash->addr[index].phone = phone;
    }
}

/**
 * 删除学生信息
 * @param hash 通讯录哈希表
 * @param name 姓名
*/
void delete_student(class_hash *hash, char name[20]){
    int index = hash_func(name, hash->size);
    int count = 0;
    while(count < hash->size && hash->addr[index].id != -1 && strcmp(hash->addr[index].name, name) != 0){
        index = (index + 1) % hash->size;
        count++;
    }
    if(count == hash->size){
        printf("查无此人\n");
        return;
    }
    hash->addr[index].id = -1;
    hash->addr[index].domitory = -1;
    hash->addr[index].phone = -1;
    hash->addr[index].name[0] = '\0';
    hash->length--;
}

int main(){

    return 0;
}