# 项目使用指南

本手册旨在指导开发者快速上手，并充分利用本项目提供的自动化构建与进阶调试功能。

## 环境准备 (Environment)

在开始之前，请确保您的系统中已正确安装以下工业级工具链：

1. **编译器 (Compiler)**: 
    - 统一使用 [GCC](https://gcc.gnu.org/) 系列。在 Windows 环境下，建议通过 [MinGW-w64](https://www.mingw-w64.org/) 安装（建议版本 12.0+）。
2. **构建管理 (Build Tools)**: 
    - [CMake (3.22+)](https://cmake.org/): 核心构建系统。
    - [Ninja](https://ninja-build.org/): 极速构建后端。
3. **编辑器 (IDE)**: 
    - [Visual Studio Code](https://code.visualstudio.com/): 建议安装 `C/C++ Extension Pack` 插件包（重点包含 `C/C++` 语言支持、`CMake Tools` 构建支持以及 `Doxygen` 注释支持）。
4. **辅助工具 (代码质量)**: 
    - `clang-format`: 用于代码自动美化。
    - `clang-tidy`: 用于静态分析（可选但推荐）。

**注意**：所有工具的可执行文件路径（如 `gcc.exe`, `cmake.exe`, `ninja.exe`）均需手动添加到系统的环境变量 `PATH` 中。


## 基础操作流

### 1. 初始化配置
- 打开项目文件夹。
- 按下 `Ctrl+Shift+P` 调出命令面板。
- 输入并执行 `CMake: Delete Cache and Reconfigure`。
- 在状态栏弹出的列表中选择 `default` 预设。

### 2. 构建项目
- 点击 VS Code 底部状态栏的“生成”按钮，或按 `Ctrl+Shift+B`。
- 构建产物将存放在 `build/` 文件夹下。

### 3. 运行与调试
- 设置断点后，按 `F5` 启动 GDB 调试。
- 调试器已配置为自动追踪最新的构建路径。

## 进阶功能使用

### 动态版本切换
- 打开 `CMakePresets.json`。
- 修改 `cacheVariables` 中的 `CPP_LEARNING_C_STD` 或 `CPP_LEARNING_CXX_STD`。
- 保存后，CMake 会提示重新配置，完成后即按新标准编译。

### 内存分析 (ASan)
- 在 VS Code 底部 CMake 状态栏点击预设名称（默认为 `default`）。
- 在弹出的预设列表中选择 `debug-asan`。
- 重新构建并运行。如果程序存在内存越界或泄露，控制台将输出详细的错误报告。

### 代码美化
- 模板内置了基于 Google 风格的缩进和对齐规则。
- 在任何源文件（.c, .cpp, .h）中按 `Shift + Alt + F` 即可自动执行格式化。

### 静态代码检查
- 编译时，系统会自动调用 `clang-tidy`（如果已安装）。
- 检查结果将直接显示在 VS Code 的“问题”面板中，请根据建议修改不规范的内容。

## 多文件开发说明

本模板采用递归检索机制：
- **添加源文件**: 只需在 `src/` 目录下创建文件或子文件夹，无需修改 CMake。
- **添加头文件**: 在 `include/` 或 `src/` 下创建头文件，系统会自动将所在目录加入搜索路径。
- **混合编程**: 支持在同一个项目中同时使用 `.c` 和 `.cpp` 文件。

祝您的学习过程顺利。
