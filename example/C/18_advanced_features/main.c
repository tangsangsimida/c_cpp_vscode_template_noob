/**
 * @file main.c
 * @brief C语言进阶用法全面展示
 *
 * 本示例包含以下内容：
 * 1. 内存管理进阶（内存池、对齐分配、Debug内存追踪）
 * 2. 指针高级用法（跳转表、函数指针）
 * 3. 预处理高级技巧（宏元编程、泛型宏）
 * 4. 位操作进阶（位域、位技巧）
 * 5. 可变参数与多线程（C11 threads）
 * 6. 现代C标准特性（C11/_Generic/静态断言等）
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <math.h>
#include <assert.h>

/* 检测是否支持 C11 线程库 */
#if defined(__STDC_NO_THREADS__) || defined(__MINGW32__)
  #define HAS_THREADS 0
#else
  #include <threads.h>
  #include <stdatomic.h>
  #define HAS_THREADS 1
#endif

/* ========================================================================== */
/*                           一、内存管理进阶                                */
/* ========================================================================== */

/* 1.1 自定义内存池 */
typedef struct {
    void* memory;
    size_t block_size;
    size_t block_count;
    bool* free_map;
} MemPool;

MemPool* pool_create(size_t block_size, size_t count) {
    MemPool* p = (MemPool*)malloc(sizeof(MemPool));
    if (!p) return NULL;
    
    p->memory = malloc(block_size * count);
    p->block_size = block_size;
    p->block_count = count;
    p->free_map = (bool*)calloc(count, sizeof(bool)); /* false = 空闲 */
    
    // 简单的错误处理
    if (!p->memory || !p->free_map) {
        free(p->memory);
        free(p->free_map);
        free(p);
        return NULL;
    }
    return p;
}

void* pool_alloc(MemPool* p) {
    for (size_t i = 0; i < p->block_count; i++) {
        if (!p->free_map[i]) {
            p->free_map[i] = true;
            return (char*)p->memory + i * p->block_size;
        }
    }
    return NULL; /* 池满 */
}

void pool_free(MemPool* p, void* ptr) {
    // 检查指针是否在池内
    char* start = (char*)p->memory;
    char* end = start + (p->block_size * p->block_count);
    if ((char*)ptr < start || (char*)ptr >= end) {
        printf("错误: 释放了不属于该内存池的指针\n");
        return;
    }
    
    size_t idx = ((char*)ptr - (char*)p->memory) / p->block_size;
    p->free_map[idx] = false;
}

void pool_destroy(MemPool* p) {
    if (!p) return;
    free(p->memory);
    free(p->free_map);
    free(p);
}

/* 1.2 内存泄漏检测宏演示 */
/* 注意：实际工程中通常会放在独立的头文件中，并通过宏开关控制 */
#ifdef DEBUG_MEM
    #define MY_MALLOC(size) _debug_malloc(size, __FILE__, __LINE__)
    #define MY_FREE(ptr)    free(ptr)
#else
    #define MY_MALLOC(size) malloc(size)
    #define MY_FREE(ptr)    free(ptr)
#endif

void* _debug_malloc(size_t size, const char* file, int line) {
    void* ptr = malloc(size);
    printf("[内存分配] 地址:%p 大小:%zu 位置:%s:%d\n", ptr, size, file, line);
    return ptr;
}

void test_memory_advanced() {
    printf("\n--- 1. 内存管理进阶示例 ---\n");
    
    // 测试内存池
    printf("创建内存池 (块大小: 32, 数量: 4)...\n");
    MemPool* pool = pool_create(32, 4);
    
    void* p1 = pool_alloc(pool);
    void* p2 = pool_alloc(pool);
    void* p3 = pool_alloc(pool);
    
    printf("分配了三个块: %p, %p, %p\n", p1, p2, p3);
    
    pool_free(pool, p2);
    printf("释放了第二个块 p2\n");
    
    void* p4 = pool_alloc(pool);
    printf("再次分配，应该复用 p2 的位置: %p\n", p4);
    
    pool_destroy(pool);
    
    // 测试 Debug Malloc (手动开启演示)
    printf("测试调试版 Malloc:\n");
    void* ptr = _debug_malloc(128, __FILE__, __LINE__);
    free(ptr);
}

/* ========================================================================== */
/*                             二、指针高级用法                              */
/* ========================================================================== */

/* 2.1 函数指针数组（跳转表） */
typedef void (*CmdHandler)(const char* args);

/* 枚举命令 */
typedef enum {
    CMD_HELP,
    CMD_LOAD,
    CMD_SAVE,
    CMD_MAX
} CommandType;

void cmd_help(const char* args) { printf("执行帮助命令, 参数: %s\n", args); }
void cmd_load(const char* args) { printf("执行加载命令, 参数: %s\n", args); }
void cmd_save(const char* args) { printf("执行保存命令, 参数: %s\n", args); }

/* 跳转表 */
static const CmdHandler cmd_table[CMD_MAX] = {
    [CMD_HELP] = cmd_help,
    [CMD_LOAD] = cmd_load,
    [CMD_SAVE] = cmd_save,
};

void dispatch(CommandType cmd, const char* args) {
    if (cmd >= CMD_MAX) {
        printf("未知命令!\n");
        return;
    }
    // O(1) 跳转
    cmd_table[cmd](args);
}

void test_pointer_advanced() {
    printf("\n--- 2. 指针高级用法示例 ---\n");
    dispatch(CMD_LOAD, "config.json");
    dispatch(CMD_HELP, "--verbose");
    dispatch(CMD_SAVE, "data.bin");
}

/* ========================================================================== */
/*                           三、预处理高级技巧                              */
/* ========================================================================== */

#define STR(x) #x
#define XSTR(x) STR(x)
#define CONCAT(a, b) a##b
#define XCONCAT(a, b) CONCAT(a, b)

/* 泛型宏 (C11) */
#if __STDC_VERSION__ >= 201112L
#define generic_abs(x) _Generic((x), \
    int: abs, \
    long: labs, \
    float: fabsf, \
    double: fabs \
)(x)
#else
#define generic_abs(x) (x < 0 ? -(x) : (x))
#endif

void test_preprocessor() {
    printf("\n--- 3. 预处理高级技巧示例 ---\n");
    
    // 字符串化
    printf("当前行号字符串化: " XSTR(__LINE__) "\n");
    
    // 拼接变量名
    int var_100 = 42;
    // 假设我们要访问 var_100，利用宏拼接
    // 这里为了演示，我们假设我们知道后缀是 100
    int val = XCONCAT(var_, 100); 
    printf("通过宏拼接访问变量 var_100: %d\n", val);
    
    // 泛型宏
    #if __STDC_VERSION__ >= 201112L
    printf("泛型绝对值 (int -5): %d\n", generic_abs(-5));
    printf("泛型绝对值 (float -3.14): %f\n", generic_abs(-3.14f));
    #else
    printf("当前编译器不支持 C11 _Generic，使用回退宏\n");
    #endif
}

/* ========================================================================== */
/*                             四、位操作进阶                                */
/* ========================================================================== */

#define IS_POWER_OF_2(x) (((x) > 0) && (((x) & ((x) - 1)) == 0))
#define ALIGN_UP(x, align) (((x) + (align) - 1) & ~((align) - 1))

/* 交换两数（无临时变量） - 仅作演示，实际推荐用临时变量更清晰 */
void swap_xor(int* a, int* b) {
    if (a != b) {
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }
}

/* 位域结构体 */
typedef struct {
    uint32_t enable : 1;
    uint32_t mode   : 3;
    uint32_t speed  : 4;
    uint32_t reserved : 24;
} DeviceReg;

void test_bitwise() {
    printf("\n--- 4. 位操作进阶示例 ---\n");
    
    printf("8 是 2 的幂吗? %s\n", IS_POWER_OF_2(8) ? "是" : "否");
    printf("7 是 2 的幂吗? %s\n", IS_POWER_OF_2(7) ? "是" : "否");
    
    printf("15 对齐到 8: %d\n", ALIGN_UP(15, 8));
    printf("17 对齐到 8: %d\n", ALIGN_UP(17, 8));
    
    int a = 10, b = 20;
    printf("交换前: a=%d, b=%d\n", a, b);
    swap_xor(&a, &b);
    printf("XOR交换后: a=%d, b=%d\n", a, b);
    
    DeviceReg reg = {0};
    reg.enable = 1;
    reg.mode = 5; // 二进制 101
    reg.speed = 15; // 二进制 1111
    
    printf("位域测试: Enable=%d, Mode=%d, Speed=%d\n", reg.enable, reg.mode, reg.speed);
    printf("位域结构体大小: %zu 字节\n", sizeof(DeviceReg)); // 应该是 4
}

/* ========================================================================== */
/*                         五、可变参数与多线程                              */
/* ========================================================================== */

void log_printf(const char* level, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    
    fprintf(stdout, "[%s] ", level);
    vfprintf(stdout, fmt, args);
    fprintf(stdout, "\n");
    
    va_end(args);
}

#if HAS_THREADS

int worker_thread(void* arg) {
    int id = *(int*)arg;
    printf("线程 %d 正在运行...\n", id);
    return 0;
}

typedef struct {
    atomic_int counter;
    atomic_flag lock;
} ThreadSafeCounter;

void safe_increment(ThreadSafeCounter* c) {
    // 自旋锁保护 (仅作演示，原子操作本身不需要锁，这里演示复合操作或锁机制)
    while (atomic_flag_test_and_set(&c->lock)) {
        // 自旋等待
    }
    
    // 临界区
    atomic_fetch_add(&c->counter, 1);
    
    atomic_flag_clear(&c->lock);
}

#endif

void test_threads_variadic() {
    printf("\n--- 5. 可变参数与多线程示例 ---\n");
    
    log_printf("INFO", "这是一条日志信息，数值=%d", 100);
    log_printf("ERROR", "发生错误，代码=%d", 404);

#if HAS_THREADS
    printf("启动 C11 线程测试...\n");
    thrd_t threads[2];
    int ids[2] = {1, 2};
    
    if (thrd_create(&threads[0], worker_thread, &ids[0]) == thrd_success) {
        thrd_join(threads[0], NULL);
    } else {
        printf("线程创建失败\n");
    }
    
    ThreadSafeCounter counter;
    atomic_init(&counter.counter, 0);
    atomic_flag_clear(&counter.lock);
    
    safe_increment(&counter);
    printf("线程安全计数器值: %d\n", atomic_load(&counter.counter));
#else
    printf("当前环境不支持 C11 <threads.h>，跳过线程测试。\n");
#endif
}

/* ========================================================================== */
/*                             六、主函数                                    */
/* ========================================================================== */

int main() {
    printf("==========================================\n");
    printf("      C 语言进阶特性综合演示 (Advanced C)  \n");
    printf("==========================================\n");
    
    test_memory_advanced();
    test_pointer_advanced();
    test_preprocessor();
    test_bitwise();
    test_threads_variadic();
    
    printf("\n演示结束。\n");
    return 0;
}
