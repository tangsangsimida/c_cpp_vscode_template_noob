#include <stdio.h>
#include <assert.h> // 包含断言工具 assert
#include <errno.h>  // 包含错误码全局变量 errno
#include <string.h> // 包含 strerror 处理错误信息

/**
 * 知识点：C 语言开发最佳实践与经验总结 (Best Practices)
 * 1. 错误捕获：如何优雅地知道程序为什么会报错？ (errno)
 * 2. 逻辑卫士：用断言 (assert) 抓住那些“绝不该发生”的逻辑 Bug。
 * 3. 编程哲学：防御性编程，不要信任任何输入。
 * 4. 终极自查：开发者 Top 10 避坑雷区。
 */

// 示例：防御性编程
// 与其让代码崩溃，不如先判断是否合法
void safe_division(int numerator, int denominator) {
    if (denominator == 0) {
        printf("[防御性检查] 警告：发现除数为 0。拦截本次运算以防止程序崩溃。\n");
        return;
    }
    printf("  - 运算结果: %d / %d = %d\n", numerator, denominator, numerator / denominator);
}

int main() {
    printf("==== 1. 捕捉系统的“悲鸣” (errno) ====\n");
    
    // 故意尝试打开一个不存在的文件
    FILE *fp = fopen("secret_treasure.txt", "r");
    
    if (fp == NULL) {
        // [知识点] errno 是一个全局变量，当系统函数出错时，它会被赋予一个错误代码。
        printf("[知识点] 系统报错了！错误代码 (errno): %d\n", errno);
        // 使用 strerror 把冷冰冰的数字转成人类能看懂的文字
        printf("[知识点] 翻译成人类语言: %s\n", strerror(errno));
    }

    printf("\n==== 2. 断言 (assert)：开发者的强力助手 ====\n");
    printf("[建议] 只在“这行代码逻辑如果错了，后面就没法运行”的地方使用 assert。\n");
    
    int age = 20;
    // 断言 age 必须大于 0。如果 age <= 0，程序会在这里立刻打印位置并自杀。
    assert(age > 0); 
    printf("  - [执行] 断言通过，age 为正数。\n");

    printf("\n==== 3. 开发者 Top 10 终极避坑清单 ====\n");
    printf("  [1] 【未初始化】局部变量不给 0，它的值就是内存里的垃圾。\n");
    printf("  [2] 【越界访问】数组 int a[5] 的下标不到 5。a[5] 是别人的领地。\n");
    printf("  [3] 【解引用 NULL】指针是 NULL 时，绝对不能加 * 去取值。\n");
    printf("  [4] 【内存泄漏】malloc 了不 free，就像借了钱不还，钱会越来越少。\n");
    printf("  [5] 【scanf 漏写 &】scanf(\"%%d\", val) 是常见的 Crash 原因。\n");
    printf("  [6] 【赋值 vs 等于】if (a = 5) 将永远为真。请用 ==。\n");
    printf("  [7] 【浮点比相等】float 不能直接 == 比较。应判断差值是否小于 0.00001。\n");
    printf("  [8] 【宏定义括号】宏只是替换，不给参数加括号会引发优先级灾难。\n");
    printf("  [9] 【分号陷阱】if (cond); 后面的代码块将永远执行。\n");
    printf(" [10] 【忽略 Warning】编译器报警说明你代码有病。请务必像消除 Error 一样消除 Warning。\n");

    printf("\n==== 4. 【结语】C 语言的权责对等 ====\n");
    printf("  - C 语言赋予开发者极高的自由度，但也要求开发者承担相应的责任。\n");
    printf("  - 尊重每一块内存，检查每一个返回值，你就能写出极其稳健的底层系统。\n");

    safe_division(10, 0);

    return 0;
}

/*
 * 【致开发者的最后一段话】
 * 每一个高手都是从几千个 Bug 堆里爬出来的。
 * 不要害怕报错，要学会利用 errno 和调试器去解剖报错。
 * 祝你在 C 语言的世界里探索愉快，Happy Coding!
 */
