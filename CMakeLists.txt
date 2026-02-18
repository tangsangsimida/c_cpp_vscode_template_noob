# CMake 最低版本要求，确保支持现代特性（如 Presets）
cmake_minimum_required(VERSION 3.22)

# --- 项目名称自动设置 ---
# 获取当前工作目录的名称作为项目名，实现克隆项目后自动重命名
get_filename_component(PROJECT_NAME_AUTO ${CMAKE_CURRENT_SOURCE_DIR} NAME)
# 定义项目名称并开启 C 和 C++ 语言支持
project(${PROJECT_NAME_AUTO} LANGUAGES C CXX)

# --- 编程语言标准配置 ---
# 定义可选的 C/C++ 标准变量，允许通过修改该变量快速切换版本（如从 23 改为 17）
set(CPP_LEARNING_C_STD "11" CACHE STRING "要使用的 C 语言标准")
set(CPP_LEARNING_CXX_STD "23" CACHE STRING "要使用的 C++ 语言标准")

set(CMAKE_C_STANDARD ${CPP_LEARNING_C_STD})     # 设置 C 语言标准
set(CMAKE_C_STANDARD_REQUIRED ON)               # 强制要求该标准
set(CMAKE_C_EXTENSIONS OFF)                    # 禁用编译器特定扩展以保证跨平台兼容

set(CMAKE_CXX_STANDARD ${CPP_LEARNING_CXX_STD}) # 设置 C++ 语言标准
set(CMAKE_CXX_STANDARD_REQUIRED ON)              # 强制要求该标准
set(CMAKE_CXX_EXTENSIONS OFF)                   # 禁用编译器特定扩展

# --- 编译选项（代码质量） ---
# 开启所有常见的编译警告，帮助新手在编写代码时发现潜在问题
if(MSVC)
  add_compile_options(/W4 /WX)                   # Windows MSVC 的警告设置
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Wshadow) # GCC/Clang 的警告设置
endif()


# --- 源码与头文件全自动检索 ---
# 递归搜索 src 目录下所有的 .cpp 和 .c 源代码文件
file(GLOB_RECURSE SOURCES 
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.c"
)

# 递归搜索 src 和 include 目录下所有的头文件，用于计算自动包含路径
file(GLOB_RECURSE HEADERS 
    "${PROJECT_SOURCE_DIR}/src/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.hpp"
    "${PROJECT_SOURCE_DIR}/include/*.h"
    "${PROJECT_SOURCE_DIR}/include/*.hpp"
)

# 自动提取所有发现的头文件所在的文件夹路径
set(INCLUDE_DIRS "")
foreach(header ${HEADERS})
    get_filename_component(header_dir ${header} DIRECTORY)
    list(APPEND INCLUDE_DIRS ${header_dir})
endforeach()
# 强制加入根目录下的 include 文件夹，并去重
list(APPEND INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/include")
list(REMOVE_DUPLICATES INCLUDE_DIRS)

# --- 目标构建配置 ---
# 根据搜索到的源代码生成可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})

# 针对 Windows/MinGW 环境启用静态链接
# 这将把标准库打包进 .exe 中，确保程序可以在任何没有安装 GCC 的电脑上运行
if(NOT MSVC AND WIN32)
    target_link_options(${PROJECT_NAME} PRIVATE -static -static-libgcc -static-libstdc++)
endif()

# 将自动检索到的所有头文件目录告诉编译器，这样你就可以直接 #include 它们了
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})

# 提示：以后如果你想添加新的库（如通过 vcpkg），可以在这里继续添加配置
