/*-------------------------------------------------------------------------
 *
 * function.c
 *	  �����������߼� ������¼��ʵ����������
 *
 * λ��
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

// ���ܣ�����ӷ�
//		������������ӵĽ�� ���������㲻���������쳣 ϵͳ�᷵��inf
// ������float8_pl
// ������val1 �ӷ�����1
// ������val2 �ӷ�����2
// ���أ�����ӷ��Ľ��
static inline float8
float8_pl(const float8 val1, const float8 val2)
{
	float8		result;

	result = val1 + val2;
	// �ж����ݼ�����Ƿ�Ϸ�
	if (unlikely(isinf(result)) && !isinf(val1) && !isinf(val2))
		float_overflow_error();

	return result;
}

// ���ܣ��������
//		��������������Ľ�� ���������㲻���������쳣 ϵͳ�᷵��inf
// ������float8_mi
// ������val1 ������
// ������val2 ����
// ���أ���������Ľ��
static inline float8
float8_mi(const float8 val1, const float8 val2)
{
	float8		result;

	result = val1 - val2;
	if (unlikely(isinf(result)) && !isinf(val1) && !isinf(val2))
		float_overflow_error();

	return result;
}

// ���ܣ�����˷�
//		������������˵Ľ�� ���������㲻���������쳣 ϵͳ�᷵��inf
// ������float8_mul
// ������val1 ����1
// ������val2 ����2
// ���أ�������˵Ľ��
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

// ���ܣ��������
//		��������������Ľ�� ���������㲻���������쳣 ϵͳ�᷵��inf
// ������float8_div
// ������val1 ������
// ������val2 ����
// ���أ���������Ľ��
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

// ���ܣ�����ӷ�
//		������������ӵĽ�� ��һ��Ϊ0������һ�� ����float8_pl����
// ������func_add
// ������num1 ����1
// ������num2 ����2
// ���أ�������ӵĽ��
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

// ���ܣ�����ӷ�
//		������������ӵĽ�� ��һ��Ϊ0���⴦��һ�� ����float8_mi
// ������func_sub
// ������num1 ������
// ������num2 ����
// ���أ���������Ľ��
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

// ���ܣ�����˷�
//		������������˵Ľ�� ��һ��Ϊ0���⴦��һ�� ����float8_mul
// ������func_sub
// ������num1 ����1
// ������num2 ����2
// ���أ�������˵Ľ��
static void
func_mul(const char* num1, const char* num2)
{
	get_num_and_check_count(mul_count);
    
	if (is_double_equal(number1, 0.0) || is_double_equal(number2, 0.0))
        print_calculator_result(0), mul_count++;
    else
        print_calculator_result(float8_mul(number1, number2)), mul_count++;
}

// ���ܣ��������
//		��������������Ľ�� ��һ��Ϊ0���⴦��һ�� ����float8_div
// ������func_div
// ������num1 ������
// ������num2 ����
// ���أ���������Ľ��
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

// ���ܣ�����ƽ��
//		������ƽ���Ľ�� ��Ϊ0���⴦��һ�� ����float8_mul������ͬ�������
// ������func_square
// ������num1 ��ƽ������
// ������num2 ��ʵ������ �ͺ���ָ��������ͬ ռλ
// ���أ�����ƽ���Ľ��
static void
func_squre(const char* num1, const char* num2)
{
	get_num_and_check_count(squre_count);
    
	if (is_double_equal(number1, 0.0))
        print_calculator_result(0), squre_count++;
    else
        print_calculator_result(float8_mul(number1, number1)), squre_count++;
}

// ���ܣ���������
//		�����������Ľ�� ��Ϊ0���⴦��һ�� ����float8_mul������3��
// ������func_cube
// ������num1 ����������
// ������num2 ��ʵ������ �ͺ���ָ��������ͬ ռλ
// ���أ����������Ľ��
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

// ����ָ������
// ˳�����������͵�ö��˳��һ��
static FUNC func[] =
	{
		func_add, func_sub, func_mul, func_div, func_squre, func_cube
	};

// ���ܣ�����������
// ������calculator
// ������num1 ������1
// ������num2 ������2 ��ƽ��������ʱ��ʵ������
// ���أ���
static void
calculator(const char* num1, const char* num2, Operation operation)
{
	func[operation](num1, num2);
}

// ���ܣ���ѭ��
//		��ȡ�������� ���� ��� ��ͳ�ƴ������ʱ�˳�
// ������run
void run()
{
	char num1[max_size] = {0};
	char num2[max_size] = {0};
	Operation operation = T_unknow;

	// ͳ���Ѿ��������������Ĵ���
	while (add_count+sub_count+mul_count+div_count+squre_count+cube_count
			 < max_per_opertion*calculator_type+1) //6�ּ�������
	{
		// ��ӡ��ʾ��Ϣ
		float_operation_input();
		
		// ��ȡ��������
		int result = scanf("%s %d %s", num1, &operation, num2);
		if(operation < T_add && operation >T_cube)
			float_operation_error();
		
		// ���� ��ӡ���
		calculator(num1, num2, operation);
	}
}

#ifndef WIN32
    #include<unistd.h>
    #include<termios.h>
#else
    #include <conio.h>
#endif
// ���ܣ���ȡ�û�������������
//		��ȡһ�����ȵ����� ���벻����
// ������get_passwd
// ������passed ��������ָ��
// ������max ��ȡ�������󳤶�
// ���أ���
static void
get_password(char* passwd, int max)
#ifndef WIN32
{
	struct termios save, current;
	tcgetattr(0, &save);// �õ�ԭ�����ն�����
	current = save;
	current.c_lflag &= ~ECHO;// �رջ���
	tcsetattr(0, TCSANOW, &current);// �����µ��ն�����
 
	// ��ȡ��������
	char temp[max_size] = {0};
	int ret = scanf("%s", temp);
	// �ض����볤�� ��ֹ����Խ��
	strncpy(passwd, temp, max);
 
 	// �ָ�ԭ�����ն����ԣ��������shall��֮��ĳ�������
	tcsetattr(0, TCSANOW, &save);
}
#else
{
	int i = 0;
	char ch;

	while (1)
	{
		ch = _getch(); //��ȡ���벻����
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

// �����������
static int passwd_count = 0;

// ��̬���� 8888
static char password[] = "8888";

// ���ܣ���ȡ���� ��֤��¼
void
login()
{
	char passwd[max_size] = {0};

	// ��������������ʾ
	print_enter_password();

	while(passwd_count < password_max_count)
	{
		// ��ȡ����
		get_password(passwd, password_max_size);
		
		// У��
		if (0 == strcmp(passwd, password))
		{
			print_not_welcome();
			return;
		}
		else
		{
			// ���������ʾ
			print_wrong_password();
			passwd_count++;
			if (passwd_count < password_max_count) 
				// �ٴ�������ʾ
				print_enter_password_again();
			continue;
		}
	}
	
	// 3���˳���ʾ��Ϣ
	print_enter_times();
	exit(1);
}
