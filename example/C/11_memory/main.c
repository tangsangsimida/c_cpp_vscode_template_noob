#include <stdio.h>
#include <stdlib.h> // 处理动态内存必须包含的头文件

/**
 * 知识点：动态内存管理 (Dynamic Memory Management)
 * 1. 概念：栈 (Stack) 空间很小且自动回收，堆 (Heap) 空间很大但需要手动管理。
 * 2. malloc 与 free：申请与归还“借来的”内存。
 * 3. 内存泄漏 (Memory Leak)：借了不还，导致程序最后无地可用。
 * 4. 防御性编程：申请后的空指针检查，释放后的指针置空。
 */

int main() {
    printf("==== 1. 内存的“借”与“还”模式 ====\n");
    
    // 我们想存 3 个整数，但由于某种原因，我们不能在代码里写死 int arr[3]
    // 指针 p 本身在“栈”上，它指向的内容在“堆”上。
    int size = 3;
    int *p = (int*)malloc(size * sizeof(int));

    // [知识点] 永远要考虑申请失败的情况（虽然在现代电脑上很少见）
    if (p == NULL) {
        printf("[错误] 操作系统拒绝了你的申请，内存不足！\n");
        return 1;
    }

    printf("[成功] 成功在堆区借到了 %zu 字节空间，地址为: %p\n", size * sizeof(int), (void*)p);

    // 像普通数组一样使用它
    p[0] = 10; p[1] = 20; p[2] = 30;
    printf("  - 写入数据成功: p[1] = %d\n", p[1]);

    // [知识点] 这块地是你借的，如果你不主动还，它会一直被你霸占
    printf("\n==== 2. 避免内存泄漏 (Memory Leak) ====\n");
    printf("[建议] 养成习惯：用了 malloc，就必须在不使用时配合一个 free。\n");
    free(p); 
    
    // [坑点] 释放后的“悬挂指针”问题
    printf("[坑点] free(p) 仅仅是告诉系统：这块地你可以拿走了。但 p 变量里依然存着旧地址！\n");
    printf("  - 此时如果再去执行 *p = 10，会导致程序立即崩溃或产生不可预知的错误。\n");
    
    p = NULL; // 最佳实践：释放后立即将指针“物理断开” (抹掉地址)
    printf("[安全] 已将指针置为 NULL，后续如果误用 *p，现代编译器和系统会帮你快速定位错误。\n");

    printf("\n==== 3. 扩容术 (realloc) 的安全姿势 ====\n");
    int *original = (int*)malloc(sizeof(int) * 2);
    printf("[初始] 申请了 2 个 int 的空间。\n");

    // 我们想把它改大一点
    // [坑点] 这里的 realloc 可能在原地扩容，也可能把数据挪到新家后删除旧家
    // 所以千万不能写成 original = realloc(original, ...) 
    // 万一失败了，original 变 NULL，原来的内存地址就再也找不到了（导致泄漏）
    int *safer_temp = (int*)realloc(original, sizeof(int) * 100);
    
    if (safer_temp != NULL) {
        original = safer_temp; 
        printf("[成功] 顺利用 realloc 将空间扩大到 100 个 int，原数据已自动搬迁。\n");
        free(original);
    } else {
        printf("[失败] 扩容失败，但 original 依然指向原来的 2 个空间，我们需要手动处理它。\n");
        free(original);
    }

    return 0;
}

/*
 * 【动态内存最佳实践】
 * 1. 【严禁二次释放】如果你对同一个地址 free 两次，程序会立刻原地爆炸 (Crash)。
 * 2. 【严禁释放非堆内存】你不能去 free 一个普通的数组名 (如 int a[10]; free(a);)。
 * 3. 【申请必检查】每次 malloc 之后，第一时间写 if(p == NULL)。
 * 4. 【释放必置空】每次 free(p) 之后，第一时间写 p = NULL;。
 */
