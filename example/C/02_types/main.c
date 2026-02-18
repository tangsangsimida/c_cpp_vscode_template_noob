#include <stdio.h>
#include <stdbool.h>
#include <limits.h> // 包含各类型的最大/最小值定义
#include <float.h>  // 包含浮点数的精度限制

/**
 * 知识点：数据类型、变量与常量 (Data Types, Variables & Constants)
 * 1. 整数类型：char, short, int, long, long long
 * 2. 浮点类型：float, double
 * 3. 类型修饰符：unsigned (无符号), signed (有符号)
 * 4. 常量定义：#define vs const vs enum
 * 5. 常见坑点：未初始化、隐式转换、类型溢出
 */

#define PI_MACRO 3.14  // 宏定义常量 (简单的文本替换，无类型检查)
const double PI_CONST = 3.14159; // const 常量 (有类型，受作用域限制)

enum Status { SUCCESS = 0, ERROR = -1 }; // 枚举常量 (提高代码可读性)

int main() {
    printf("==== 1. 核心数据类型大小 (不同平台可能有差异) ====\n");
    printf("[知识点] char      占 %zu 字节 (范围: %d 到 %d)\n", sizeof(char), CHAR_MIN, CHAR_MAX);
    printf("[知识点] int       占 %zu 字节 (范围: %d 到 %d)\n", sizeof(int), INT_MIN, INT_MAX);
    printf("[知识点] float     占 %zu 字节 (精度保障: %d 位有效数字)\n", sizeof(float), FLT_DIG);
    printf("[知识点] double    占 %zu 字节 (精度保障: %d 位有效数字)\n", sizeof(double), DBL_DIG);

    printf("\n==== 2. 变量与常量陷阱集锦 ====\n");

    // 坑点 1：未初始化
    int uninitialized_var;
    (void)uninitialized_var; // 消除编译警告
    printf("[坑点] 局部变量(栈)未初始化直接读取是“未定义行为(UB)”。它的值可能是内存中残留的垃圾数据。\n");

    // 坑点 2：无符号与有符号混合运算
    signed int s_val = -1;
    unsigned int u_val = 1;
    printf("[坑点] 重要陷阱！计算 -1 > 1U：\n");
    if (s_val > u_val) {
        printf("  - 结果为真：因为 -1 在内存中是 0xFFFFFFFF，转为无符号后变成了 %u\n", (unsigned int)s_val);
    }

    // 坑点 3：类型溢出
    char over_flow = 127;
    over_flow = over_flow + 1;
    printf("[坑点] 溢出：char(127) + 1 = %d (在大多数系统上会绕回为负数)\n", over_flow);

    printf("\n==== 3. const 常量与指针辨析 ====\n");
    int val = 100;
    const int *ptr_to_val = &val;  // 指针指向的内容被 const 锁死，不能通过该指针修改内容
    int * const const_ptr = &val;  // 指针本身是 const，不能让它指向其它地址
    
    printf("[知识点] 阅读诀窍：以 * 为界。const 在左，指向的内容不可变；const 在右，指针本身不可变。\n");
    
    // 消除所有未使用变量/常量的警告
    (void)PI_MACRO; (void)PI_CONST; (void)ptr_to_val; (void)const_ptr; (void)over_flow;

    return 0;
}

/*
 * 应用场景：
 * 1. 节省内存：在单片机中，能用 char 的地方绝不用 int。
 * 2. 跨平台：使用头文件 <stdint.h> 中的 int32_t 等类型保证在 16/32/64 位系统下宽度一致。
 * 3. 程序配置：使用 const 或 enum 管理全局状态或配置。
 */
