# C/C++ 通用开发与学习模板

本项目是一个功能完备的现代 C/C++ 开发与学习模板，旨在提供一站式的技术实践环境。它深度集成了自动化构建、代码规范检查、内存安全调试以及覆盖核心知识点的实战示例库，支持 Windows、Linux 和 macOS 平台。

## 核心特性

1. **自动项目命名**：系统根据当前工作目录名称自动同步项目名，无需人工干预。
2. **零维护构建**：采用递归检索模式，自动识别并管理所有子目录下的源代码与头文件。
3. **现代标准支持**：默认配置为 C++23 和 C11，支持通过 CMake 变量动态切换语言版本。
4. **高质量代码管理**：集成 Clang-Format 自动格式化和 Clang-Tidy 静态代码质量分析。
5. **内存安全保障**：内置 AddressSanitizer (ASan) 预设，精准捕获内存泄漏、越界访问等底层错误。
6. **实战示例库**：内置 16 个深度优化的 C 语言实战工程，涵盖从指针到多文件编程的所有核心底层知识。
7. **环境兼容性**：针对 Windows/MinGW 环境优化了静态链接逻辑，生成的执行程序可独立分发运行。

## 开发工具链 (Toolchain)

本项目基于工业标准的工具链构建，建议环境配置如下：

- **构建系统**：[CMake 3.22+](https://cmake.org/) (跨平台构建标准)
- **构建后端**：[Ninja](https://ninja-build.org/) (面向速度的高性能构建工具)
- **编译器**：[GCC](https://gcc.gnu.org/) (Windows 环境建议使用 [MinGW-w64](https://www.mingw-w64.org/)，建议版本 12.0+)
- **编辑器**：[Visual Studio Code](https://code.visualstudio.com/)
    - **核心插件**：`C/C++ Extension Pack` (包含 IntelliSense、CMake Tools 等)
- **调试器**：GDB (由 VS Code 插件自动识别)
- **静态分析**：[Clang-Tidy](https://clang.llvm.org/extra/clang-tidy/) (自动集成于构建流程中)
- **代码美化**：[Clang-Format](https://clang.llvm.org/docs/ClangFormat.html) (支持一键格式化)
- **内存检测**：[AddressSanitizer](https://github.com/google/sanitizers/wiki/AddressSanitizer) (ASan)

## 快速开始

1. **环境准备**：确保上述工具已安装并加入系统环境变量 `PATH`。
2. **项目配置**：在 VS Code 中运行 "CMake: Delete Cache and Reconfigure" 初始化工程。
3. **选择预设**：在 CMake 工具栏选择 `default`（标准编译）或 `debug-asan`（内存检测）。
4. **构建运行**：`Ctrl+Shift+B` 执行编译，`F5` 启动调试。

关于动态标准切换、静态检查、内存分析以及多文件开发的详细操作说明，请参阅：[docs/使用指南](docs/usage.md)。

## 文件结构

- **include/** ：存放公共头文件（支持无限级子文件夹）。
- **src/** ：存放源代码业务逻辑，已内置 `main.cpp` 入口。
- **example/** ：**核心示例库**，包含按语言分类的独立实战工程（如 C 语言指针、内存管理等）。
- **docs/** ：存放项目相关的技术文档与开发笔记。
- **.clang-format** ：工业级代码美化规则。
- **.clang-tidy** ：严苛的代码质量检测规则。
- **CMakePresets.json** ：标准化的构建预设配置文件。

## 工具化部署建议

本项目可作为脚手架工具使用：
1. **快速克隆**：直接复制整个目录并重命名文件夹即可开启新项目。
2. **自动同步**：模板会自动提取新文件夹名作为项目名，无需修改 `CMakeLists.txt`。
3. **跨平台适配**：调试器会自动追踪编译路径，确保在不同操作系统下的调试体验一致。

---
*祝您在 C/C++ 的探索旅程中不断精进。*
