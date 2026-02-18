#include <stdio.h>
#include <string.h> // 处理字符串必须包含的头文件

/**
 * 知识点：字符串 (Strings) - C 语言中的字符序列
 * 1. 字符串的本质：以空字符 '\0' 结尾的字符数组。
 * 2. 两种定义方式：字符数组 (char[]) vs 字符串指针 (char*)。
 * 3. 内存结构：'\0' 的重要性 (字符串的终止标志)。
 * 4. 常用函数：strlen (长度), strcpy (拷贝), strcmp (比较), strcat (拼接)。
 * 5. 安全红线：缓冲区溢出 (Buffer Overflow)。
 */

int main() {
    printf("==== 1. 字符串的本质：隐藏的 '\\0' ====\n");
    // 这种定义方式，编译器会自动在末尾加上 \0
    char hello[] = "Hello"; 
    
    printf("[知识点] 字符串 \"Hello\" 看起来有 5 个字符，但实际上在内存里占了 %zu 字节。\n", sizeof(hello));
    printf("  - 最后一个隐藏字符是 '\\0' (ASCII 码为 0)。没有它，printf 就不知道在哪里停下来。\n");

    printf("\n==== 2. 数组 vs 指针：谁能修改？ ====\n");
    
    // 情况 A：字符数组（在栈区，可读可写）
    char mutable_str[] = "Can Change";
    mutable_str[0] = 'c'; // 允许修改
    printf("[验证] 数组内容已修改: %s\n", mutable_str);

    // 情况 B：字符串常量指针（在常量区，只读）
    const char *readonly_str = "Cannot Change";
    // readonly_str[0] = 'c'; // [绝对禁止] 运行到这行会直接崩溃 (段错误)，因为它是只读的。
    printf("[验证] 指针指向的内容: %s\n", readonly_str);

    printf("\n==== 3. 常用库函数实战 ====\n");
    char s1[20] = "Apple";
    char s2[] = "Banana";

    // A. 长度计算
    printf("[strlen] s1 的可见长度是: %zu (不计入 '\\0')\n", strlen(s1));

    // B. 拷贝
    strcpy(s1, s2); // 把 s2 拷贝到 s1
    printf("[strcpy] 拷贝后 s1 变成了: %s\n", s1);

    // C. 比较 (最容易错的地方！)
    char str_a[] = "C++";
    char str_b[] = "C++";
    printf("[比较陷阱] 如果用 (str_a == str_b)，比较的是内存地址，结果为: %s\n", (str_a == str_b) ? "相等" : "不相等");
    if (strcmp(str_a, str_b) == 0) {
        printf("[strcmp] 正确方法：使用 strcmp 比较内容，结果为: 相等\n");
    }

    printf("\n==== 4. 【致命警告】缓冲区溢出 ====\n");
    char small_box[5]; // 只能存 4 个字符 + 1 个 \0
    printf("[警告] 如果试图往 size 为 5 的数组里拷贝 \"LongString\"，会发生什么？\n");
    printf("  - 结果：它会越界覆盖掉内存中相邻的其他变量，轻则产生乱码，重则导致黑客入侵！\n");
    printf("  - [建议] 永远考虑目标空间是否足够大，或者使用更安全的函数如 strncpy。\n");

    // 解决未使用变量警告
    (void)readonly_str;

    return 0;
}

/*
 * 【字符串操作核心总结】
 * 1. 字符串就是数组，下标依然从 0 开始。
 * 2. 永远记得：数组长度 = 字符数 + 1 (为了那个不可或缺的 \0)。
 * 3. 字符串常量 (如 "Apple") 是只读的，不能通过指针去修改它。
 * 4. 字符串比较千万别用 ==，请认准 strcmp。
 */
