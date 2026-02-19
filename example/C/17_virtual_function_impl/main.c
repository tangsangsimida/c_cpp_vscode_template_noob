#include <stdio.h>
#include <stdlib.h>

/**
 * @file main.c
 * @brief C语言模拟虚函数和虚函数表的详细实现
 *
 * 本示例展示了如何在C语言中使用结构体和函数指针来模拟C++中的面向对象特性：
 * 1. 继承 (Inheritance)
 * 2. 多态 (Polymorphism)
 * 3. 虚函数表 (Virtual Function Table / vtable)
 *
 * 在C++中，虚函数是通过虚函数表（vtable）来实现的。每个包含虚函数的类都有一个
 * 对应的vtable，表中存储了该类各个虚函数的地址。每个对象包含一个指向该vtable的
 * 指针（vptr），通常位于对象的内存布局的最前面。
 *
 * 下面我们将手动构建这一机制。
 */

/* ========================================================================== */
/*                                基础定义                                   */
/* ========================================================================== */

// 前向声明 Shape 结构体，以便在 vtable 中使用
struct Shape;

/**
 * @brief 虚函数表结构体定义
 *
 * 定义了 Shape 类支持的所有操作（虚函数）。
 * 这里我们定义了两个虚函数：
 * - area: 计算面积
 * - draw: 绘制图形
 */
typedef struct {
    double (*area)(struct Shape* self); // 虚函数指针：计算面积
    void (*draw)(struct Shape* self);   // 虚函数指针：绘制自己
} ShapeVTable;

/**
 * @brief 基类 Shape
 *
 * 这是我们的“基类”。它包含一个指向虚函数表的指针 (vptr)。
 * 在C++中，这个 vptr 是编译器自动插入的，但在C中我们需要显式定义。
 */
typedef struct Shape {
    const ShapeVTable* vptr; // 虚表指针 (vptr)
    const char* name;        // 成员变量：图形名称
} Shape;

/* ========================================================================== */
/*                                基类方法                                   */
/* ========================================================================== */

/**
 * @brief Shape 的构造函数
 *
 * 初始化 Shape 对象。
 */
void Shape_ctor(Shape* self, const char* name, const ShapeVTable* vtable) {
    self->vptr = vtable;
    self->name = name;
}

/**
 * @brief 基类的多态调用接口
 *
 * 这些是我们在代码中调用的普通函数，它们内部会查找 vtable 并跳转到正确的函数。
 * 这对应于 C++ 中的 `obj->method()` 或者 `ptr->method()` 调用。
 */
double Shape_area(Shape* self) {
    // 间接调用：通过 self->vptr 找到 area 函数指针，并传入 self
    return self->vptr->area(self);
}

void Shape_draw(Shape* self) {
    // 间接调用：通过 self->vptr 找到 draw 函数指针，并传入 self
    self->vptr->draw(self);
}

/* ========================================================================== */
/*                            派生类 1: Circle                               */
/* ========================================================================== */

/**
 * @brief 派生类 Circle
 *
 * 通过将基类 Shape 作为第一个成员来实现“继承”。
 * 这样 Circle 指针可以安全地强制转换为 Shape 指针。
 */
typedef struct {
    Shape base;     // 继承自 Shape (必须是第一个成员)
    double radius;  // Circle 特有的成员
} Circle;

// Circle 的具体实现函数
double Circle_area(Shape* self) {
    // 将基类指针转换为派生类指针以访问特有成员
    Circle* this = (Circle*)self;
    return 3.14159 * this->radius * this->radius;
}

void Circle_draw(Shape* self) {
    Circle* this = (Circle*)self;
    printf("绘制圆形: %s, 半径: %.2f\n", this->base.name, this->radius);
}

// Circle 的虚函数表
// 注意：这是一个静态常量，所有 Circle 对象共享同一个 vtable
const ShapeVTable circle_vtable = {
    .area = Circle_area,
    .draw = Circle_draw
};

// Circle 的构造函数
void Circle_ctor(Circle* self, const char* name, double radius) {
    // 首先调用基类构造函数，并传入 Circle 类的 vtable
    Shape_ctor(&self->base, name, &circle_vtable);
    self->radius = radius;
}

/* ========================================================================== */
/*                          派生类 2: Rectangle                              */
/* ========================================================================== */

/**
 * @brief 派生类 Rectangle
 */
typedef struct {
    Shape base;      // 继承自 Shape
    double width;
    double height;
} Rectangle;

// Rectangle 的具体实现函数
double Rectangle_area(Shape* self) {
    Rectangle* this = (Rectangle*)self;
    return this->width * this->height;
}

void Rectangle_draw(Shape* self) {
    Rectangle* this = (Rectangle*)self;
    printf("绘制矩形: %s, 宽: %.2f, 高: %.2f\n", 
           this->base.name, this->width, this->height);
}

// Rectangle 的虚函数表
const ShapeVTable rectangle_vtable = {
    .area = Rectangle_area,
    .draw = Rectangle_draw
};

// Rectangle 的构造函数
void Rectangle_ctor(Rectangle* self, const char* name, double width, double height) {
    Shape_ctor(&self->base, name, &rectangle_vtable);
    self->width = width;
    self->height = height;
}

/* ========================================================================== */
/*                                主函数                                     */
/* ========================================================================== */

int main() {
    printf("=== C语言 虚函数与虚函数表 模拟 ===\n\n");

    // 1. 创建对象
    Circle c1;
    Circle_ctor(&c1, "Circle A", 5.0);

    Rectangle r1;
    Rectangle_ctor(&r1, "Rectangle B", 4.0, 6.0);

    // 2. 多态的使用
    // 我们使用基类指针 (Shape*) 来指向派生类对象
    // 这在C++中非常常见：Shape* s = new Circle(...);
    
    Shape* shapes[2];
    shapes[0] = (Shape*)&c1;
    shapes[1] = (Shape*)&r1;

    printf("多态遍历图形对象：\n");
    printf("-----------------------------------------\n");

    for (int i = 0; i < 2; ++i) {
        // 在这里，我们不知道 shapes[i] 到底是指向 Circle 还是 Rectangle
        // 但是通过 vptr，代码会自动调用正确的函数实现
        
        // 调用 draw 虚函数
        Shape_draw(shapes[i]); 
        
        // 调用 area 虚函数
        double area = Shape_area(shapes[i]);
        printf("面积: %.2f\n\n", area);
    }

    /* 内部机制剖析 */
    printf("=== 深入剖析虚函数表 (VTable) ===\n");
    // 让我们手动检查一下内存，看看 vptr 是如何工作的
    
    // 获取 c1 对象的地址
    void* obj_ptr = &c1;
    // 对象的前8个字节（在64位系统上）就是 vptr
    // 我们将其强制转换为 ShapeVTable** 来读取它
    ShapeVTable* vptr_value = *(ShapeVTable**)obj_ptr;

    printf("对象 c1 的地址:       %p\n", obj_ptr);
    printf("c1.vptr 的地址:       %p\n", (void*)vptr_value);
    printf("circle_vtable 的地址: %p\n", (void*)&circle_vtable);
    
    if (vptr_value == &circle_vtable) {
        printf("验证成功: c1.vptr 指向 circle_vtable\n");
    } else {
        printf("验证失败！\n");
    }

    printf("\n手动通过虚表指针调用函数：\n");
    // 手动通过 vptr 调用
    vptr_value->draw((Shape*)&c1);

    return 0;
}
