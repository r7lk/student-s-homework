/*-------------------------------------------------------------------------
 *
 * function.c
 *	  程序运行主逻辑 包含登录和实际运算内容
 *
 * 位置
 *	  src/function.c
 *
 *-------------------------------------------------------------------------
 */

#include "function.h"

static int add_count = 0;
static int sub_count = 0;
static int mul_count = 0;
static int div_count = 0;
static int squre_count = 0;
static int cube_count = 0;

// 功能：计算加法
//		计算两个数相加的结果 浮点数计算不会造成溢出异常 系统会返回inf
// 函数：float8_pl
// 参数：val1 加法数据1
// 参数：val2 加法数据2
// 返回：计算加法的结果
static inline float8
float8_pl(const float8 val1, const float8 val2)
{
	float8		result;

	result = val1 + val2;
	// 判断数据计算后是否合法
	if (unlikely(isinf(result)) && !isinf(val1) && !isinf(val2))
		float_overflow_error();

	return result;
}

// 功能：计算减法
//		计算两个数相减的结果 浮点数计算不会造成溢出异常 系统会返回inf
// 函数：float8_mi
// 参数：val1 被减数
// 参数：val2 减数
// 返回：计算减法的结果
static inline float8
float8_mi(const float8 val1, const float8 val2)
{
	float8		result;

	result = val1 - val2;
	if (unlikely(isinf(result)) && !isinf(val1) && !isinf(val2))
		float_overflow_error();

	return result;
}

// 功能：计算乘法
//		计算两个数相乘的结果 浮点数计算不会造成溢出异常 系统会返回inf
// 函数：float8_mul
// 参数：val1 乘数1
// 参数：val2 乘数2
// 返回：计算相乘的结果
static inline float8
float8_mul(const float8 val1, const float8 val2)
{
	float8		result;

	result = val1 * val2;
	if (unlikely(isinf(result)) && !isinf(val1) && !isinf(val2))
		float_overflow_error();
	if (unlikely(result == 0.0) && val1 != 0.0 && val2 != 0.0)
		float_underflow_error();

	return result;
}

// 功能：计算除法
//		计算两个数相除的结果 浮点数计算不会造成溢出异常 系统会返回inf
// 函数：float8_div
// 参数：val1 被除数
// 参数：val2 除数
// 返回：计算相除的结果
static inline float8
float8_div(const float8 val1, const float8 val2)
{
	float8		result;

	if (unlikely(val2 == 0.0))
		float_zero_divide_error();
	result = val1 / val2;
	if (unlikely(isinf(result)) && !isinf(val1) && !isinf(val2))
		float_overflow_error();
	if (unlikely(result == 0.0) && val1 != 0.0)
		float_underflow_error();

	return result;
}

// 功能：计算加法
//		计算两个数相加的结果 当一个为0返回另一个 调用float8_pl计算
// 函数：func_add
// 参数：num1 加数1
// 参数：num2 加数2
// 返回：计算相加的结果
static void
func_add(const char* num1, const char* num2)
{
	get_num_and_check_count(add_count);

    if (is_double_equal(number1, 0.0))
        print_calculator_result(number2), add_count++;
    else if (is_double_equal(number2, 0.0))
        print_calculator_result(number1), add_count++;
    else
        print_calculator_result(float8_pl(number1, number2)), add_count++;
}

// 功能：计算加法
//		计算两个数相加的结果 当一个为0特殊处理一下 调用float8_mi
// 函数：func_sub
// 参数：num1 被减数
// 参数：num2 减数
// 返回：计算相减的结果
static void
func_sub(const char* num1, const char* num2)
{
	get_num_and_check_count(sub_count);

    if (is_double_equal(number1, 0.0))
        print_calculator_result(-number2), sub_count++;
    else if (is_double_equal(number2, 0.0))
        print_calculator_result(number1), sub_count++;
    else
        print_calculator_result(float8_mi(number1, number2)), sub_count++;
}

// 功能：计算乘法
//		计算两个数相乘的结果 当一个为0特殊处理一下 调用float8_mul
// 函数：func_sub
// 参数：num1 乘数1
// 参数：num2 乘数2
// 返回：计算相乘的结果
static void
func_mul(const char* num1, const char* num2)
{
	get_num_and_check_count(mul_count);
    
	if (is_double_equal(number1, 0.0) || is_double_equal(number2, 0.0))
        print_calculator_result(0), mul_count++;
    else
        print_calculator_result(float8_mul(number1, number2)), mul_count++;
}

// 功能：计算除法
//		计算两个数相除的结果 当一个为0特殊处理一下 调用float8_div
// 函数：func_div
// 参数：num1 被除数
// 参数：num2 除数
// 返回：计算相除的结果
static void
func_div(const char* num1, const char* num2)
{
	get_num_and_check_count(div_count);
    
	if (is_double_equal(number1, 0.0))
        print_calculator_result(0), div_count++;
    else if (is_double_equal(number2, 0.0))
        float_overflow_error(), div_count++;
    else
        print_calculator_result(float8_div(number1, number2)), div_count++;
}

// 功能：计算平方
//		计算数平方的结果 当为0特殊处理一下 调用float8_mul两个相同的数相乘
// 函数：func_square
// 参数：num1 求平方的数
// 参数：num2 无实际意义 和函数指针类型相同 占位
// 返回：计算平方的结果
static void
func_squre(const char* num1, const char* num2)
{
	get_num_and_check_count(squre_count);
    
	if (is_double_equal(number1, 0.0))
        print_calculator_result(0), squre_count++;
    else
        print_calculator_result(float8_mul(number1, number1)), squre_count++;
}

// 功能：计算立方
//		计算数立方的结果 当为0特殊处理一下 调用float8_mul连续乘3次
// 函数：func_cube
// 参数：num1 求立方的数
// 参数：num2 无实际意义 和函数指针类型相同 占位
// 返回：计算立方的结果
static void
func_cube(const char* num1, const char* num2)
{
	get_num_and_check_count(cube_count);
    
	if (is_double_equal(number1, 0.0))
        print_calculator_result(0), cube_count++;
    else
        print_calculator_result(float8_mul(
						float8_mul(number1, number1), number1)),
		cube_count++;
}

// 函数指针数组
// 顺序和运算符类型的枚举顺序一致
static FUNC func[] =
	{
		func_add, func_sub, func_mul, func_div, func_squre, func_cube
	};

// 功能：计算运算结果
// 函数：calculator
// 参数：num1 运算数1
// 参数：num2 运算数2 当平方和立方时无实际意义
// 返回：无
static void
calculator(const char* num1, const char* num2, Operation operation)
{
	func[operation](num1, num2);
}

// 功能：主循环
//		获取键盘输入 计算 输出 当统计次数溢出时退出
// 函数：run
void run()
{
	char num1[max_size] = {0};
	char num2[max_size] = {0};
	Operation operation = T_unknow;

	// 统计已经进行运算计算过的次数
	while (add_count+sub_count+mul_count+div_count+squre_count+cube_count
			 < max_per_opertion*calculator_type+1) //6种计算类型
	{
		// 打印提示信息
		float_operation_input();
		
		// 获取键盘输入
		int result = scanf("%s %d %s", num1, &operation, num2);
		if(operation < T_add && operation >T_cube)
			float_operation_error();
		
		// 计算 打印结果
		calculator(num1, num2, operation);
	}
}

#ifndef WIN32
    #include<unistd.h>
    #include<termios.h>
#else
    #include <conio.h>
#endif
// 功能：获取用户键盘输入密码
//		获取一定长度的输入 输入不回显
// 函数：get_passwd
// 参数：passed 存放输入的指针
// 参数：max 获取输入的最大长度
// 返回：无
static void
get_password(char* passwd, int max)
#ifndef WIN32
{
	struct termios save, current;
	tcgetattr(0, &save);// 得到原来的终端属性
	current = save;
	current.c_lflag &= ~ECHO;// 关闭回显
	tcsetattr(0, TCSANOW, &current);// 设置新的终端属性
 
	// 获取键盘输入
	char temp[max_size] = {0};
	int ret = scanf("%s", temp);
	// 截断密码长度 防止过长越界
	strncpy(passwd, temp, max);
 
 	// 恢复原来的终端属性，以免干扰shall和之后的程序运行
	tcsetattr(0, TCSANOW, &save);
}
#else
{
	int i = 0;
	char ch;

	while (1)
	{
		ch = _getch(); //获取输入不回显
		if (ch == '\r')
			{
				printf("\n");
				break;
			}
		else if (ch == '\b')
		{
			if (i > 0) {
				printf("\b \b");
				i--;
			}
			continue;
		}
		printf("*");
		if (i > max)
			{
				printf("\n");
				break;
			}
		passwd[i++] = ch;
	}
	passwd[i] = 0;
}
#endif

// 密码输入次数
static int passwd_count = 0;

// 静态密码 8888
static char password[] = "8888";

// 功能：获取密码 验证登录
void
login()
{
	char passwd[max_size] = {0};

	// 键盘输入密码提示
	print_enter_password();

	while(passwd_count < password_max_count)
	{
		// 获取密码
		get_password(passwd, password_max_size);
		
		// 校验
		if (0 == strcmp(passwd, password))
		{
			print_not_welcome();
			return;
		}
		else
		{
			// 密码错误提示
			print_wrong_password();
			passwd_count++;
			if (passwd_count < password_max_count) 
				// 再次输入提示
				print_enter_password_again();
			continue;
		}
	}
	
	// 3次退出提示信息
	print_enter_times();
	exit(1);
}
