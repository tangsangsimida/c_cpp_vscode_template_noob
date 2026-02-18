#include <stdio.h>
#include <string.h>

/**
 * 知识点：自定义复合类型 (Structures, Unions, Enums & Typedef)
 * 1. 结构体 (struct)：多个变量的“集体宿舍”，各住各的房间，总空间是大伙的和。
 * 2. 联合体 (union)：多个变量的“共享单间”，所有人挤一张床，谁来都会睡掉前一个人的位置。
 * 3. 枚举 (enum)：给一堆整数起“绰号”，提高代码阅读体验。
 * 4. 类型定义 (typedef)：给长类型起“外号”，代码更简洁。
 * 5. 内存对齐 (Padding)：编译器为了快速访问而在变量之间留出的“空隙”。
 */

// 1. 结构体定义：模拟一个学生信息
typedef struct {
    int id;             // 4字节
    char name[20];      // 20字节
    float score;        // 4字节
} Student;

// 2. 结构体内存对齐展示
// 思考：char(1) + int(4) + char(1) = 6? 
typedef struct {
    char a;
    int b;
    char c;
} AlignmentDemo;

// 3. 联合体定义：同一块地，分不同时刻用
union Value {
    int i;
    float f;
};

// 4. 枚举定义：状态管理
enum Light { RED, YELLOW, GREEN };

int main() {
    printf("==== 1. 结构体 (Struct)：组合的力量 ====\n");
    Student s1 = {1001, "Alice", 95.5f};
    printf("[知识点] 学生 %s (ID:%d) 的分数为: %.1f\n", s1.name, s1.id, s1.score);
    printf("  - 结构体各成员地址是独立的：&id=%p, &name=%p\n", (void*)&s1.id, (void*)s1.name);

    printf("\n==== 2. 内存对齐 (Padding)：消失的字节 ====\n");
    printf("[知识点] AlignmentDemo 成员和为 6，但 sizeof 结果为: %zu\n", sizeof(AlignmentDemo));
    printf("  - 原因：CPU 喜欢 4 或 8 字节对齐访问。编译器为了讨好 CPU，在 char 后面偷偷补了空位。\n");

    printf("\n==== 3. 联合体 (Union)：内存共享陷阱 ====\n");
    union Value v;
    v.i = 42;
    printf("[初始] 设置 v.i = 42, 此时 v.i = %d\n", v.i);
    
    printf("[警告] 现在改写 v.f = 3.14f...\n");
    v.f = 3.14f;
    printf("  - 结果：v.f = %.2f\n", v.f);
    printf("  - 坑点：由于内存共享，原来的 v.i 已经被破坏，现在变成了: %d (乱码)\n", v.i);
    printf("  - 结论：Union 节省空间，但在同一时刻只能有一个成员有效！\n");

    printf("\n==== 4. 枚举 (Enum)：让代码说人话 ====\n");
    enum Light my_light = GREEN;
    printf("[知识点] GREEN 的数值其实是: %d\n", my_light);
    if (my_light == GREEN) {
        printf("  - 就像在问：信号灯是不是绿的？而不是问：变量是不是等于 2？\n");
    }

    return 0;
}

/*
 * 【复合类型应用总结】
 * 1. Struct 像是一个文件夹，把不同类型的数据打包在一起管理。
 * 2. Union 像是一个变身器，这块内存有时当 int 用，有时当 float 用，但不能同时当两者用。
 * 3. Typedef 只是起外号，为了少敲几个字符（比如不用每次写 struct Student）。
 * 4. 对齐 (Padding) 是自动的，除非在嵌入式底层开发中为了节省每一字节，否则别去折腾它。
 */
