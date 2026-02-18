#include <stdio.h>

/**
 * 知识点：函数 (Functions)
 * 1. 结构设计：声明 (Declaration) vs 定义 (Definition)
 * 2. 参数哲学：值传递 (拷贝) vs 指针传递 (引用)
 * 3. 递归机制：函数自我调用与栈内存
 * 4. 作用域控制：static 修饰符的作用
 * 5. 性能优化：为什么大数据要传指针？
 */

// --- 1. 函数声明 (书的目录) ---
// 提前告诉编译器：有一个函数叫这个名字，接收什么参数，返回什么类型。
void swap_by_value(int a, int b);
void swap_by_pointer(int *a, int *b);

// --- 2. 递归函数可视化：阶乘计算 ---
int factorial(int n) {
    // 基准情形 (终止条件)
    if (n <= 1) {
        printf("    [递归] 触底反弹: n=1, 开始向上返回 1\n");
        return 1;
    }
    printf("    [递归] 压栈: %d * factorial(%d)\n", n, n - 1);
    
    // 函数调用自身
    int result = n * factorial(n - 1);
    
    printf("    [递归] 出栈: factorial(%d) 计算完成，结果为 %d\n", n, result);
    return result;
}

// --- 3. 静态函数 (私有逻辑) ---
// 加上 static 后，该函数只能在当前 .c 文件内使用。
static void internal_logic() {
    printf("[知识点] 我是一个 static 函数，我像是一个人的隐私，外部文件无法调用我。\n");
}

int main() {
    printf("==== 1. 参数传递：幻像 vs 真身 ====\n");
    int x = 1, y = 2;
    printf("[初始状态] x=%d, y=%d\n", x, y);

    printf("\n[尝试] 值传递交换 (Pass by Value)...\n");
    swap_by_value(x, y);
    printf("[结果] x=%d, y=%d (失败！函数内部只改了副本)\n", x, y);

    printf("\n[尝试] 指针传递交换 (Pass by Pointer)...\n");
    swap_by_pointer(&x, &y); // 注意这里传的是地址 &
    printf("[结果] x=%d, y=%d (成功！函数顺着地址改了真身)\n", x, y);

    printf("\n==== 2. 递归：洋葱式的调用结构 ====\n");
    printf("[知识点] 递归就像剥洋葱，一层层进去(压栈)，到底后再一层层出来(出栈)。\n");
    int res = factorial(4);
    printf("[结论] 4! 最终计算结果为: %d\n", res);

    printf("\n==== 3. 性能陷阱：值传递的代价 ====\n");
    struct BigData { char space[1024]; } data = {{0}};
    printf("[知识点] 如果我们直接传 BigData，编译器会老老实实拷贝 1024 字节。\n");
    printf("[建议] 传递指针 (const BigData *p) 只需要传递 8 字节地址，效率提升百倍！\n");

    internal_logic();
    (void)data; // 消除警告

    return 0;
}

// --- 函数定义 (书的具体内容) ---

void swap_by_value(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
    printf("    - 函数内部: 交换完成了！(a=%d, b=%d)\n", a, b);
}

void swap_by_pointer(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    printf("    - 函数内部: 顺着地址交换完成了！\n");
}
