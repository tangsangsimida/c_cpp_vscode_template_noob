#include <stdio.h>

/**
 * 知识点：控制流语句 (Control Flow)
 * 1. 分支结构：if-else (范围判断), switch-case (精确匹配)
 * 2. 循环结构：for (已知次数), while (未知次数), do-while (至少执行一次)
 * 3. 跳转控制：break (跳出当前层), continue (跳过本次循环), goto (慎用)
 * 4. 常见陷阱：空语句分号、Switch 穿透、死循环风险
 */

int main() {
    printf("==== 1. 条件分支中的逻辑细节 ====\n");
    int score = 85;
    printf("[知识点] if-else 会按照顺序从上至下判断，一旦满足其中一个分支，后续分支将不再执行。\n");
    if (score >= 90) {
        printf("  - 评价：优\n");
    } else if (score >= 60) {
        printf("  - 评价：良 (当前分数 %d)\n", score);
    } else {
        printf("  - 评价：差\n");
    }

    printf("\n==== 2. Switch 的穿透 (Fall-through) 特性 ====\n");
    int option = 1;
    printf("[知识点] Switch 匹配成功后，如果没有遇到 break，会无视 case 标签继续执行后续所有代码。\n");
    switch (option) {
        case 1:
            printf("  - 执行了 Case 1\n");
            // 注意：这里故意漏掉了 break
        case 2:
            printf("  - 执行了 Case 2 (因为 Case 1 没停住)\n");
            break; 
        case 3:
            printf("  - 执行了 Case 3\n");
            break;
        default:
            printf("  - 未知选项\n");
            break;
    }

    printf("\n==== 3. 三大循环结构对比 ====\n");
    
    // for: 局部变量 i 只在循环内有效 (C99+)
    printf("[for] 最常用于处理已知范围的循环：\n");
    for (int i = 0; i < 3; i++) {
        printf("  - for 步进: %d/2\n", i);
    }

    // while: 可能一次都不执行
    printf("\n[while] 先进行条件检查，满足才进：\n");
    int w_idx = 0;
    while (w_idx < 0) { // 这里条件不满足
        printf("  - 我不会被打印\n");
    }
    printf("  - while 条件不满足，已跳过内容。\n");

    // do-while: 必定执行一次
    printf("\n[do-while] 先执行一次，再检查条件：\n");
    int d_idx = 0;
    do {
        printf("  - 我即便条件不满足(0<0)，也强行执行了一次！\n");
    } while (d_idx < 0);

    printf("\n==== 4. 高级跳转与坑点提示 ====\n");

    // 坑点 1：if 后的冒失分号
    int check = 0;
    printf("[坑点] if(条件); <-- 那个多出来的分号会终结 if，使下面的代码块变成无条件执行。\n");
    if (check == 99); 
    {
        // 实际上这已经不是 if 的作用域了
        printf("  - 危险警告：if 分号陷阱命中！代码块脱离控制执行了。\n");
    }

    // 跳转控制：break vs continue
    printf("\n[知识点] 循环控制对比：\n");
    for (int j = 1; j <= 5; j++) {
        if (j == 2) {
            printf("  - [continue] 跳过 2 的打印\n");
            continue; 
        }
        if (j == 4) {
            printf("  - [break] 发现 4，彻底终止循环\n");
            break;
        }
        printf("  - 打印数值: %d\n", j);
    }

    return 0;
}

/*
 * 应用场景：
 * 1. 状态机逻辑：使用 switch 处理不同的运行状态。
 * 2. 数组遍历：使用 for 循环扫描缓冲区。
 * 3. 输入校验：使用 do-while 提示用户输入直到格式正确。
 * 4. 嵌入式主循环：while(1) 构成的死循环是单片机程序的标配。
 */
