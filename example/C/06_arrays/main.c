#include <stdio.h>

/**
 * 知识点：数组 (Arrays)
 * 1. 数组定义与内存结构：连续的内存空间
 * 2. 下标机制：为什么从 0 开始？(偏移量概念)
 * 3. 数组退化 (Decay)：数组名与指针的关系
 * 4. 多维数组：内存中的线性存储
 * 5. 安全陷阱：越界访问与非法操作
 */

// 模拟打印数组的通用函数
void print_array_info(int arr[], int size) {
    printf("\n==== 3. 数组在函数参数中的“真相” ====\n");
    printf("[知识点] 虽然参数写的是 int arr[]，但编译器会把它当成 int *arr。\n");
    printf("[证据] 函数内部 sizeof(arr) = %zu (这是指针的大小)\n", sizeof(arr));
    printf("  - 结论：这就是为什么传递数组一定要带上 size，否则函数不知道数组在哪结束。\n");
    
    printf("  - 打印数组内容: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    printf("==== 1. 数组初始化与下标本质 ====\n");
    
    // 初始化
    int ages[4] = {18, 20, 22, 25};
    
    printf("[知识点] 数组名 ages 代表数组的首地址: %p\n", (void*)ages);
    printf("[知识点] 数组总占空间: %zu 字节 (%d 个 int)\n", sizeof(ages), (int)(sizeof(ages)/sizeof(int)));

    printf("\n[深度] 为什么下标从 0 开始？\n");
    printf("  - 因为 ages[i] 的底层含义是: *(ages + i)\n");
    printf("  - ages[0] 等于 *(ages + 0)，即地址不偏离，正好是第一个元素。\n");
    printf("  - 验证：ages[2] = %d, *(ages + 2) = %d\n", ages[2], *(ages + 2));

    printf("\n==== 2. 多维数组：折叠的线性空间 ====\n");
    // 2行3列
    int grid[2][3] = {
        {11, 12, 13},
        {21, 22, 23}
    };
    
    printf("[知识点] 访问 grid[1][2]: %d\n", grid[1][2]);
    printf("[知识点] 虽然逻辑上是表格，但在内存中 grid 是连续的一排数字。\n");
    printf("  - grid[0][2] 后面紧跟着的就是 grid[1][0]。\n");

    // 调用函数演示
    print_array_info(ages, 4);

    printf("\n==== 4. 开发中常踩的坑 ====\n");

    // 坑点 1：部分初始化
    int zero_demo[10] = {1}; 
    printf("[坑点] 部分初始化 {1}：第一个是 1，后面 9 个会自动补 0 而不是随机值。\n");
    printf("  - zero_demo[0]=%d, zero_demo[9]=%d\n", zero_demo[0], zero_demo[9]);

    // 坑点 2：致命的越界
    printf("\n[警告] 致命越界：ages[4] 是不存在的！\n");
    printf("  - ages 只有下标 0, 1, 2, 3。访问 ages[4] 会读取到相邻的其它变量内存。\n");
    printf("  - 结果：轻则数据混乱，重则程序崩溃 (Segmentation Fault)。\n");

    // 坑点 3：数组名不可修改
    printf("\n[坑点] 数组名是“祖产”，不可变：\n");
    printf("  - int *p = ages; p++; // 可以，指针可以移动\n");
    // ages++; // 绝对不行！编译报错。数组名的地址在它生存期内是锁死的。

    (void)grid; (void)zero_demo;
    return 0;
}

/*
 * 学习建议：
 * 1. 永远记住：数组下标的最大值 = 长度 - 1。
 * 2. 传递数组给函数时，始终成对传递 (数组名, 长度)。
 * 3. 理解 ages[i] 就是指针偏移的缩写，能帮你打通数组与指针的任督二脉。
 */
