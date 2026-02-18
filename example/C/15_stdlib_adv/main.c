#include <stdio.h>
#include <stdlib.h> // 包含 qsort, rand, malloc 等工具
#include <math.h>   // 包含 sqrt, pow, sin 等数学函数
#include <time.h>   // 包含处理时间的函数

/**
 * 知识点：标准库工具与现代 C 语言特性 (Standard Library & Advanced)
 * 1. 快速排序 (qsort)：C 语言中最强大的通用排序工具，支持任何类型的数据。
 * 2. 数学函数：sqrt(开方), pow(幂)。注意：Windows 下直接运行，Linux 下需加 -lm 手动链接。
 * 3. 随机数：如何生成“看起来真正随机”的数字。
 * 4. 时间处理：获取当前系统的时间戳。
 * 5. C99 新特性：变长数组 (VLA)，允许数组大小是变量。
 */

// [知识点] qsort 的回调函数：告诉排序器如何比较两个数字
// a 和 b 是“地址”，我们需要把它们强行转换回 (int*) 并取值 (* )
int compare_numbers(const void *a, const void *b) {
    int val_a = *(const int*)a;
    int val_b = *(const int*)b;
    
    // 返回负数：a 应该在 b 前面
    // 返回正数：a 应该在 b 后面
    // 返回零： 随便
    return (val_a - val_b); 
}

int main() {
    printf("==== 1. 万能排序利器：qsort ====\n");
    int list[] = {100, 50, 200, 10, 30};
    int count = sizeof(list) / sizeof(list[0]);
    
    printf("[初始] 乱序序列: 100, 50, 200, 10, 30\n");
    
    // 参数含义：要排的数组，数组长度，每个元素占多大，怎么比的代码。
    qsort(list, count, sizeof(int), compare_numbers);
    
    printf("[成功] 排序结果: %d, %d, %d, %d, %d\n", list[0], list[1], list[2], list[3], list[4]);

    printf("\n==== 2. 让随机数“动起来” ====\n");
    // [坑点] 如果不加下面这一行，rand() 每次运行出来的结果序列都是死板固定的。
    // 我们用当前时间作为“种子”，让序列每次都不同。
    srand((unsigned int)time(NULL)); 
    
    printf("[知识点] 生成一个 0-99 之间的随机数: %d\n", rand() % 100);

    printf("\n==== 3. 数学计算与时间 ====\n");
    printf("[数学] pow(2, 10) = %.1f (2的10次方)\n", pow(2, 10));
    printf("[数学] sqrt(64)   = %.1f (64的平方根)\n", sqrt(64));
    
    time_t raw_time = time(NULL);
    printf("[时间] 自 1970年1月1日以来的秒数: %ld\n", (long)raw_time);

    printf("\n==== 4. C99 变长数组 (VLA) ====\n");
    int dynamic_size = 3;
    printf("[知识点] 现在我们可以写 int vla[%d] 了！\n", dynamic_size);
    int items[dynamic_size]; // 在老旧的编译器上这行会报错
    items[0] = 1; items[1] = 2; items[2] = 3;
    printf("  - 访问 VLA 成功: items[2] = %d\n", items[2]);

    printf("\n==== 5. 易错清单 ====\n");
    printf("[坑点] math.h 函数返回的通常是 double (浮点数)。打印时记得用 %%f。\n");
    printf("[警告] VLA 申请的空间是在“栈”上的。如果给出的动态长度太大，会导致栈溢出直接崩溃。\n");
    printf("[建议] qsort 的比较函数中，如果直接 (a - b) 可能会导致大数溢出。安全做法是 if(a>b)...语句。\n");

    return 0;
}

/*
 * 【库函数使用建议】
 * 1. 凡是这种通用的功能（排序、数学、时间），先在标准库里找，不要自己造轮子。
 * 2. 学习 qsort 是理解 C 语言“泛型编程”和“回调函数”的最佳起点。
 * 3. 多翻阅 C 标准库文档 (cppreference)，它是你最好的编程词典。
 */
