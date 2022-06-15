/*-------------------------------------------------------------------------
 *
 * function.h
 *	  程序运行主逻辑登录和实际运算内容需要的宏定义和枚举 常量定义
 *
 * 位置
 *	  src/function.h
 *
 *-------------------------------------------------------------------------
 */
#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// 运算符类型
// 加 减 乘 除 平方 立方 默认未知
typedef enum Operation
{
    T_add = 0,
    T_sub,
    T_mul,
    T_div,
    T_squre,
    T_cube,
    T_unknow = 100
}Operation;

// 定义计算中使用的数据类型
typedef double float8;

// 计算使用的函数指针和枚举类型对应
// 用来按运算符枚举作为下表调用对应的运算函数
typedef void (*FUNC)(const char*,const char*);

#if __GNUC__ >= 3
#define unlikely(x) __builtin_expect((x) != 0, 0)
#else
#define unlikely(x) ((x) != 0)
#endif

// 小数位的后面精度
#define precision 0.0000005
#define double_zero 0.00
// 每个操作符运算可以计算的最大次数
#define max_per_opertion    15

#define max_size    256         // 字符串最大长度
#define password_max_size   4   // 8888 长度4
#define password_max_count  3   // 3次密码失败退出
#define calculator_type 6       // 6种计算类型加减乘除平方立方
// 判断两个double类型数据是否相等
#define is_double_equal(x,y) (((x)-(y)>=-precision) && ((x)-(y)<precision))

// 打印日志 暂时打印标准错误输出-控制台
#define Log(fmt,...) fprintf(stderr,(fmt),__VA_ARGS__)

// 报错打印
#define float_overflow_error() Log("%s \n", "value out of range: overflow")
#define float_underflow_error() Log("%s \n", "value out of range: underflow")
#define float_zero_divide_error() Log("%s \n", "division by zero")
#define float_operation_error() Log("%s \n", "input error: operation error")

// 获取输入打印
#define float_operation_input() \
Log("%s \n", "input format:\tnumber1  operation  number2");\
Log("%s \n", "\t0-add 1-sub 2-mul 3-div 4-squre 5-cube")


// 打印计算结果
#define print_calculator_result(result) Log("result: %g \n\n", (result))
#define print_enter_password() Log("%s \n", "Enter password:")
#define print_not_welcome() Log("%s \n", "You are welcome!")
#define print_wrong_password() Log("%s \n", "Wrong password!")
#define print_enter_password_again() Log("%s \n", "Enter agin:")
#define print_enter_times() Log("%s \n", "You have entered three times! You are not welcome!")

// 简写代码 每个函数都有 看起来又臭又长的
#define get_argc_num() float8 number1 = atof(num1); float8 number2 = atof(num2);
#define check_calculator_count(count)   \
do  \
{   \
    if ((count) >= max_per_opertion)    \
    {   \
        Log("%s \n", "count flow"); \
        return; \
    }   \
} while (0);
#define  get_num_and_check_count(count)	get_argc_num(); check_calculator_count((count))

// 功能：计算主循环
//      获取用户输入 调用计算函数计算 打印解锁结果
// 函数：run
// 返回：无
// 输入：无 键盘获取
// 输出：无 打印控制台
extern void run();

// 功能：获取用户登录
//      获取用户密码 校验密码 正确登录 错误继续 3次退出
// 函数：login
// 返回：无
// 输入：无 键盘获取
// 输出：无 打印控制台
extern void login();

#endif // _FUNCTION_H_
