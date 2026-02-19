# CMake 最低版本要求
cmake_minimum_required(VERSION 3.22)

# 获取当前工作目录的名称作为项目名
get_filename_component(PROJECT_NAME_AUTO ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJECT_NAME_AUTO} LANGUAGES C)

# 设置 C 语言标准 (C11)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# 编译选项
if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wformat=2 -Wunused -Wimplicit-fallthrough)
endif()

# 源码检索
file(GLOB SOURCES "*.c")

# 目标构建
add_executable(${PROJECT_NAME_AUTO} ${SOURCES})

# 链接 pthread (如果需要)
find_package(Threads)
target_link_libraries(${PROJECT_NAME_AUTO} PRIVATE Threads::Threads)

# 静态链接（Windows/MinGW）
if(NOT MSVC AND WIN32)
    target_link_options(${PROJECT_NAME_AUTO} PRIVATE -static -static-libgcc)
endif()
