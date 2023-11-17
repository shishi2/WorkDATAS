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
 * 查找学生信息
 * 在表中的下标
 * @param hash 通讯录哈希表
 * @param name 姓名
*/
int findIndex(class_hash *hash, char name[20]){
    int index = hash_func(name, hash->size);
    int count = 0;
    while(count < hash->size){
        if(hash->addr[index].id != -1){/*内容不为空*/
            if(strcmp(hash->addr[index].name, name) != 0){/*匹配姓名*/
                index = (index + 1) % hash->size;
                count++;
            }else{
                break;
            }
        }{
            index = (index + 1) % hash->size;
            count++;
        }
    }
    if(count == hash->size){
        return -1;
    }
    return index;
}

/**
 * 查询学生信息
 * @param hash 通讯录哈希表
 * @param name 姓名
*/
void search_student(class_hash *hash, char name[20]){
    int index = hash_func(name, hash->size);
    int count = 0;
    while(count < hash->size){
        if(hash->addr[index].id != -1){/*内容不为空*/
            if(strcmp(hash->addr[index].name, name) != 0){/*匹配姓名*/
                index = (index + 1) % hash->size;
                count++;
            }else{
                break;
            }
        }else{
            index = (index + 1) % hash->size;
            count++;
        }
    }
    if(count == hash->size){
        printf("查无此人\n\n");
        return;
    }
    printf("姓名：%s  ", hash->addr[index].name);
    printf("学号：%d  ", hash->addr[index].id);
    printf("宿舍号：%d  ", hash->addr[index].domitory);
    printf("手机号：%d  ", hash->addr[index].phone);
    printf("\n");
    printf("查找次数：%d\n", count + 1);
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
    int index = findIndex(hash, name);
    if(index == -1){
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
    int index = findIndex(hash, name);
    if(index == -1){
        printf("查无此人\n");
        return;
    }
    hash->addr[index].id = -1;
    hash->addr[index].domitory = -1;
    hash->addr[index].phone = -1;
    hash->addr[index].name[0] = '\0';
    hash->length--;
}

/**
 * 打印哈希表
*/
void print_hash(class_hash *hash){
    for(int i = 0; i < hash->size; i++){
        if(hash->addr[i].id != -1){
            printf("姓名：%s  ", hash->addr[i].name);
            printf("学号：%d  ", hash->addr[i].id);
            printf("宿舍号：%d  ", hash->addr[i].domitory);
            printf("手机号：%d", hash->addr[i].phone);
            printf("\n");
        }
    }
}

/**
 * 读取文件
*/
void read_file(class_hash *hash){
    FILE *fp = fopen("hash.txt", "r");//打开文件 只读
    if(fp == NULL){
        printf("文件打开失败\n");
        return;
    }
    if(feof(fp)){
        printf("文件为空\n");
        return;
    }

    int num = -1;
    char name[20];
    int id;
    int domitory;
    int phone;
    fscanf(fp, "%*[^\n]");//跳过第一行
    int count = 0;
    while (fscanf(fp, "%d %s %d %d %d", &num, name, &id, &domitory, &phone) == 5){
        add_class_addr(hash, id, domitory, phone, name);
        count++;
        if(count == hash->size){
            printf("文件过大\n");
            printf("仅读取%d条数据\n", count);
            return;
        }
    }
    fclose(fp);//关闭文件
}

/**
 * 文件写入
*/
void write_file(class_hash *hash){
    FILE *fp = fopen("hash.txt", "w");//打开文件 只写
    if(fp == NULL){
        printf("文件打开失败\n");
        return;
    }else{
        fprintf(fp, "序号 姓名 学号 宿舍号 手机号\n");
        for(int i = 0; i < hash->size; i++){
            if(hash->addr[i].id != -1){
                fprintf(fp, "%d %s %d %d %d\n", i, hash->addr[i].name, hash->addr[i].id, hash->addr[i].domitory, hash->addr[i].phone);
            }
        }
    }
    fclose(fp);//关闭文件
}

int main(){

    class_hash *hash = init_class_hash(10);
    // add_class_addr(hash, 217, 429, 12345, "qwe");
    // add_class_addr(hash, 218, 430, 1234, "asd");
    // add_class_addr(hash, 219, 431, 123, "zxc");
    // add_class_addr(hash, 220, 432, 12, "qaz");
    // add_class_addr(hash, 221, 433, 1, "wsx");

    read_file(hash);//读取文件
    // printf("%d\n", hash->length);
    int change = 0;
    int flag = 0;
    printf("管理员请输入1, 用户请输入0\n");
    scanf("%d", &flag);
    switch (flag){
        case 0://普通用户
            while(1){
                printf("普通用户界面\n");
                printf("信息查询请输入1\n其他操作请输入0\n退出请输入-1\n");
                int flag1 = -1;
                scanf("%d", &flag1);
                if(flag1 == 1){
                    printf("请输入姓名\n");
                    char name[20];
                    scanf("%s", name);
                    search_student(hash, name);
                }else if(flag1 == -1){
                    break;
                }else{
                    printf("暂无权限\n\n");
                }
            }
            break;
        case 1://管理员
            while(1){
                printf("管理员界面\n");
                printf("添加学生信息请输入1\n修改学生信息请输入2\n删除学生信息请输入3\n查看整个通讯录请输入4\n退出请输入-1\n");
                int flag2 = -1;
                scanf("%d", &flag2);
                if(flag2 == 1){
                    printf("请输入学生的姓名 学号 宿舍号 电话号码\n");
                    int id;
                    int domitory;
                    int phone;
                    char name[20];
                    scanf("%s %d %d %d", name, &id, &domitory, &phone);
                    add_class_addr(hash, id, domitory, phone, name);
                    change = 1;
                }else if(flag2 == 2){
                    printf("请输入欲修改学生的姓名 学号 宿舍号 电话号码\n");
                    printf("不修改的信息请输入0\n删除该项信息请输入-1\n");
                    char name[20];
                    int id;
                    int domitory;
                    int phone;
                    scanf("%s %d %d %d", name, &id, &domitory, &phone);
                    modify_student(hash, name, id, domitory, phone);
                    change = 1;
                }else if(flag2 == 3){
                    printf("请输入欲删除学生的姓名\n");
                    char name[20];
                    scanf("%s", name);
                    delete_student(hash, name);
                    change = 1;
                }else if(flag2 == 4){
                    printf("以下是通讯录中的所有信息\n");
                    print_hash(hash);
                }else if(flag2 == -1){
                    break;
                }
            }   
        default:
            break;
    }
    if(change == 1){
        write_file(hash);//写入文件
    }
    
    return 0;
}