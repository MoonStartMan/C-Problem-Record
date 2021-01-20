# C(宏定义与使用)

+ 宏表达式被预处理处理器,编译器不知道宏表达式的存在
+ 宏表达式用"实参"完全替代形参,不进行任何运算
+ 宏表达式没有任何的"调用"开销
+ 宏表达式不能出现递归定义
+ 宏的使用会带来一定的副作用

## 宏是什么？

宏定义是C语言提供的三种预处理功能的其中一种，这三种预处理包括：宏定义、文件包含、条件编译。宏定义和操作符的区别是：宏定义是替换，不做计算，也不做表达式求解。

## 宏定义的种类

1. 对象宏:(不带参数)

``` Objective-C

[0]#define [1]SIZE 2[10]

```

[0]#define定义宏 undef取消宏定义
[1]宏名称, 通常用大写字母
[2]宏定义的内容,在编译期要替换宏名字的内容

2. 函数宏:(带参数)

``` Objective-C

#define ADD(x, y) x + y

```


** 宏函数并非平常的函数操作,其本质还是代码块的替换。


``` Objective-C 
#define YM_Swap(_a_, _b_) {__typeof__(_a_) _t_ = _a_; (_a_) = (_b_); (_b_) = (_t_); }
#define SIZE 10
#define ADD(x, y) x + y

int left_number = 10;
int right_number = 100;
    
YM_Swap(left_number, right_number);
//	{ int _t = left_number; (left_number) = (right_number); (right_number) = (_t_); };

int totalNumber = SIZE - ADD(2, 3);
```

** 当多个宏连接使用时,运算符的级别跟连接符的级别是一样的,并不会先计算出结果然后再连接。只会一一展开。

## 对于需要多行的宏,可以使用\来连接

``` Objective-C

#define MINA(A, B) __typeof__(A) __a = (A);\
									 __typeof__(B) __b = (B);\
									 __a < __b ? __a : __b;

```

## 宏的返回值

当需要把宏内容的最后一条语句的执行结果当作返回值,我们就可以使用clang c的扩展 ({})

``` Objective-C

#define YM_TEST(_a_, _b_) _a_ = 100; _b_ = 200;
int a = 10;
int b = 20;
int res = YM_TEST(a, b);
//	转换后的代码： int res = a = 100; b = 200;;
NSLog(@"res = %d", res);

//	输出结果 res = 100;
```

如果想要结果为最后一个表达式的值

``` Objective-C

#define YM_TEST(_a_, _b_) ({_a_ = 100; _b_ = 200;})

int a = 10;
int b = 20;
int res = YM_TEST(a, b);
NSLog(@"res = %d", res);
//	转换后的代码: res = ({a = 100; b = 200;});
//	({});取最后一个变量的数值
```

## 连接多个变量

``` Objective-C

#define __NSX_PASTE__(A,B) A##B

#define __NSMIN_IMPL__(A,B,L) ({
__typeof__(A) __NSX_PASTE__(__a,L) = (A);\
__typeof__(B) __NSX_PASTE__(__b,L) = (B);\
(__NSX_PASTE__(__a,L) < __NSX_PASTE__(__b,L)) ? __NSX_PASTE__(__a,L) : __NSX_PASTE__(__b,L);\
})

#define MIN(A,B) __NSMIN_IMPL__(A,B,__COUNTER__)

int c = MIN(10, 20);
NSLog(@"c= %d",c);

```

## ##__VA_ARGS__ 处理可变参数

``` Objective-C
#define DeLog(format, ...) do {                                                                          \
printf("<%s : %d> %s\n",                                           \
[[[NSString stringWithUTF8String:__FILE__] lastPathComponent] UTF8String],  \
__LINE__, __func__);                                                        \
NSLog(format, ##__VA_ARGS__);                                           \
} while (0)
```

在宏中使用 … 定义一个可变参数, 当需要用到这个可变参数时，就要使用 ##VA_ARGS 来解析所有的可变参数。

do {} while（0）是干什么用的， 为什么不直接写成 {}。 说实话其实没什么用，只是让转化后的代码更好看，如果没有 do…while 转换后的代码 { };。 如果有，转换后的代码 do{ } while(0); 只是花括号后面跟一个;不好看而已， 话说回来了，我们又看不到。所以就无所谓了，写成什么都行。而且编译器会把他优化掉，不会影响效率。