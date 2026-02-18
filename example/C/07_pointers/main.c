#include <stdio.h>
#include <stdlib.h>

/**
 * 知识点：指针 (Pointers) - C 语言的灵魂
 * 1. 物理含义：内存地址 (指针变量里存的就是一串 16 进制数字，代表内存位置)
 * 2. 核心操作：取地址 (&) 与 解引用 (*)
 * 3. 内存修改：通过指针实现“跨函数”修改变量
 * 4. 指针算术：为什么指针加一不是物理意义上的加一？
 * 5. 安全准则：空指针、野指针、悬挂指针的防范
 */

// 函数演示：如何通过指针修改外部变量 (真身交换)
// swap 函数接收的是两个内存地址
void swap_real(int *a, int *b) {
    int temp = *a; // 获取地址 a 指向的内容
    *a = *b;       // 将地址 b 指向的内容写入地址 a
    *b = temp;     // 将备份的内容写入地址 b
}

// 模拟一个回调函数
void on_event_received(int data) {
    printf("    [回调触发] 函数指针正在执行逻辑，收到数据: %d\n", data);
}

int main() {
    printf("==== 1. 指针的“户口登记”：地址与取值 ====\n");
    int treasure = 999;
    int *map = &treasure; // map 是指针(藏宝图)，&treasure 是取地址(地图上的坐标)

    printf("[解释] 变量 treasure 存储在内存坐标: %p\n", (void*)&treasure);
    printf("[解释] 指针变量 map 内部存储的内容正好是: %p\n", (void*)map);
    printf("[解释] 使用 * 符号(解引用)顺着地图找宝藏: *map = %d\n", *map);

    printf("\n==== 2. 实战：如何用指针“隔空取物” ====\n");
    int val1 = 10, val2 = 20;
    printf("[交换前] val1 = %d, val2 = %d\n", val1, val2);
    swap_real(&val1, &val2); // 传地址过去
    printf("[交换后] val1 = %d, val2 = %d (外部变量被修改了)\n", val1, val2);

    printf("\n==== 3. 指针运算：不仅是数学，更是逻辑 ====\n");
    int items[3] = {100, 200, 300};
    int *p = items; // 指向第一个元素
    printf("[知识点] 当前 p 指向: %d (地址: %p)\n", *p, (void*)p);
    
    p++; // 指针自增 1
    printf("[知识点] p++ 执行后，指向: %d (地址: %p)\n", *p, (void*)p);
    printf("  - 结论：指针自增 1，物理地址其实跳过了 %zu 字节 (一个 int 的宽度)。\n", sizeof(int));

    printf("\n==== 4. 安全红线：实践指南 ====\n");
    
    // 情况 A：空指针 (The NULL Pointer)
    int *p_null = NULL;
    printf("[红线] NULL 指针就像一个空地址。代码千万不要尝试取出它的值 (*p_null)。\n");
    if (p_null == NULL) {
        printf("  - [方案] 永远在使用指针前进行 if(p != NULL) 的安全检查。\n");
    }

    // 情况 B：野指针 (Wild Pointer)
    // int *p_wild; // 声明了但没给它地图，它指向哪完全凭运气。
    printf("[红线] 严禁声明指针后不初始化直接使用。它们像“疯掉的向导”，会带你去非法的内存区导致崩溃。\n");

    // 情况 C：悬挂指针 (Dangling Pointer)
    int *p_dynamic = (int*)malloc(sizeof(int));
    *p_dynamic = 88;
    free(p_dynamic); 
    // 此时 p_dynamic 依然存着那个地址，但那块内存已经被销毁了，这就是悬挂指针。
    printf("[红线] free 释放内存后，必须养成习惯：p = NULL; 彻底切断因果链。\n");
    p_dynamic = NULL;

    printf("\n==== 5. 进阶：把函数装进指针里 ====\n");
    // 函数指针定义：返回类型 (*指针名)(参数列表)
    void (*ptr_to_msg)(int) = on_event_received;
    printf("[知识点] 现在 ptr_to_msg 就是函数 on_event_received 的别名。\n");
    ptr_to_msg(777); // 调用

    return 0;
}

/*
 * 【深入理解指针本质】
 * 指针最难的不是语法，而是脑海里的“图像”。
 * 1. 想象内存是一排带门牌号的抽屉。
 * 2. 普变量(int) 是抽屉里的东西。
 * 3. 指针变量(int*) 是另一张纸条，上面写着第一个抽屉的门牌号。
 * 4. * 号就是“去那个门牌号的抽屉里拿东西”的动作。
 * 打通了这个物理模型，C 语言就再也没有秘密了。
 */
