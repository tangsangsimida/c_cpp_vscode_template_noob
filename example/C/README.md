# C 语言全面总结示例项目

本项目通过 16 个章节详细展示了 C 语言的核心知识点、常见坑和应用场景。

## 目录索引

1. **[01_overview](./01_overview)**: C 语言概述与程序结构
2. **[02_types](./02_types)**: 数据类型、变量、常量 (UB 陷阱)
3. **[03_operators](./03_operators)**: 运算符与表达式 (优先级坑)
4. **[04_control_flow](./04_control_flow)**: 控制流语句 (Switch/If 陷阱)
5. **[05_functions](./05_functions)**: 函数 (递归与传参优化)
6. **[06_arrays](./06_arrays)**: 数组 (越界与退化)
7. **[07_pointers](./07_pointers)**: 指针 (C 语言灵魂与 Top 坑)
8. **[08_strings](./08_strings)**: 字符串 (\0 结尾与溢出)
9. **[09_struct_union](./09_struct_union)**: 结构体、联合体、枚举、typedef (对齐坑)
10. **[10_preprocessor](./10_preprocessor)**: 预处理指令 (宏括号)
11. **[11_memory](./11_memory)**: 动态内存管理 (泄漏与 UAF)
12. **[12_file_io](./12_file_io)**: 文件操作与标准 I/O
13. **[13_bitwise](./13_bitwise)**: 位运算与底层操作
14. **[14_multi_file](./14_multi_file)**: 多文件编程与工程管理
15. **[15_stdlib_adv](./15_stdlib_adv)**: 标准库与高级特性 (qsort/VLA)
16. **[16_best_practices](./16_best_practices)**: 通用最佳实践与 UB 汇总
17. **[17_virtual_function_impl](./17_virtual_function_impl)**: C 语言实现虚函数与多态 (OOP 模拟)


## 如何阅读与编译
1. **独立编译（推荐）**：使用 VS Code 的 **“打开文件夹”** 功能，直接打开任意一个子目录（如 `07_pointers`）。由于每个目录都内置了独立的 `.vscode` 和 `CMakeLists.txt`，您可以直接在 VS Code 中点击“构建”或按 `F5` 进行调试，无需依赖根目录。
2. **源码查阅**：每个子目录下的 `main.c` 都包含了知识点总结、避坑演示和应用场景说明。
