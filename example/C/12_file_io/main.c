#include <stdio.h>
#include <stdlib.h>

/**
 * 知识点：文件操作与数据持久化 (File Operations)
 * 1. 文件指针：FILE* 就像是操作文件的“遥控器”。
 * 2. 打开模式：'w' (写入/覆盖), 'r' (读取), 'a' (追加)。
 * 3. 错误处理：检查 fopen 的结果，防止打开不存在的文件。
 * 4. 资源释放：fclose 就像是退出登录，如果不关，可能会丢失数据或浪费系统资源。
 * 5. 缓冲区：数据并不是立刻写进磁盘的，而是先在内存排队。
 */

int main() {
    const char *path = "hello_c.txt";

    printf("==== 1. 文件的创建与写入 ====\n");
    // [知识点] fopen 打开一个文件。'w' 代表 Write (写)。
    // 警告：如果文件已存在，'w' 模式会毫不留情地删掉旧内容重新写。
    FILE *fp = fopen(path, "w");

    // [坑点] 权限不足、路劲错误、甚至磁盘满了，都会导致 fp 变成 NULL。
    if (fp == NULL) {
        printf("[错误] 无法打开文件 %s 进写入！\n", path);
        return 1;
    }

    printf("[成功] 指向文件 %s 的“遥控器”已就位。\n", path);
    
    // 使用 fprintf 像使用 printf 一样往文件里写东西
    fprintf(fp, "C 语言文件操作实战\n");
    fprintf(fp, "当前分数: %d\n", 100);
    fputs("祝你学习愉快！\n", fp);

    // [重要] 关上门！
    fclose(fp);
    printf("[成功] 数据已保存，文件已关闭。\n");

    printf("\n==== 2. 文件的读取 ====\n");
    // [知识点] 'r' 代表 Read (读)。
    fp = fopen(path, "r");
    if (fp == NULL) {
        printf("[错误] 没找到文件 %s，无法读取。\n", path);
        return 1;
    }

    char buffer[100];
    printf("[内容] 开始从磁盘读取信息：\n");
    
    // fgets 会读取一行，直到遇到换行符或读取上限
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("    读取到: %s", buffer);
    }

    fclose(fp);

    printf("\n==== 3. 常识与避坑指南 ====\n");
    printf("[坑点] “我明明写了文件，为什么打开是空的？”\n");
    printf("  - 原因：你可能忘了执行 fclose(fp)。如果不关，数据可能还在内存缓冲区没“刷新”到磁盘。\n");
    
    printf("[建议] 追加内容模式 'a' (Append)：\n");
    printf("  - 如果你不想删掉旧的，只想在文件末尾加几行，请改用 fopen(path, \"a\")。\n");

    printf("[知识点] 输入输出三剑客：\n");
    printf("  - stdin  : 标准输入 (通常是键盘)\n");
    printf("  - stdout : 标准输出 (你现在看到的屏幕)\n");
    printf("  - stderr : 标准错误输出 (用来打印报错信息)\n");

    return 0;
}

/*
 * 【文件操作实践建议】
 * 1. 永远不要假定文件一定能打开成功。
 * 2. 处理文件数据时，buffer 缓冲区的大小要预估准确，防止读取越界。
 * 3. 记住：C 语言不会帮你自动关闭文件。你 malloc 了要去 free，你 fopen 了就要去 fclose。
 */
