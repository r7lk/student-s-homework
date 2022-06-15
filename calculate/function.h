/*-------------------------------------------------------------------------
 *
 * function.h
 *	  �����������߼���¼��ʵ������������Ҫ�ĺ궨���ö�� ��������
 *
 * λ��
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

// ���������
// �� �� �� �� ƽ�� ���� Ĭ��δ֪
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

// ���������ʹ�õ���������
typedef double float8;

// ����ʹ�õĺ���ָ���ö�����Ͷ�Ӧ
// �����������ö����Ϊ�±���ö�Ӧ�����㺯��
typedef void (*FUNC)(const char*,const char*);

#if __GNUC__ >= 3
#define unlikely(x) __builtin_expect((x) != 0, 0)
#else
#define unlikely(x) ((x) != 0)
#endif

// С��λ�ĺ��澫��
#define precision 0.0000005
#define double_zero 0.00
// ÿ��������������Լ����������
#define max_per_opertion    15

#define max_size    256         // �ַ�����󳤶�
#define password_max_size   4   // 8888 ����4
#define password_max_count  3   // 3������ʧ���˳�
#define calculator_type 6       // 6�ּ������ͼӼ��˳�ƽ������
// �ж�����double���������Ƿ����
#define is_double_equal(x,y) (((x)-(y)>=-precision) && ((x)-(y)<precision))

// ��ӡ��־ ��ʱ��ӡ��׼�������-����̨
#define Log(fmt,...) fprintf(stderr,(fmt),__VA_ARGS__)

// �����ӡ
#define float_overflow_error() Log("%s \n", "value out of range: overflow")
#define float_underflow_error() Log("%s \n", "value out of range: underflow")
#define float_zero_divide_error() Log("%s \n", "division by zero")
#define float_operation_error() Log("%s \n", "input error: operation error")

// ��ȡ�����ӡ
#define float_operation_input() \
Log("%s \n", "input format:\tnumber1  operation  number2");\
Log("%s \n", "\t0-add 1-sub 2-mul 3-div 4-squre 5-cube")


// ��ӡ������
#define print_calculator_result(result) Log("result: %g \n\n", (result))
#define print_enter_password() Log("%s \n", "Enter password:")
#define print_not_welcome() Log("%s \n", "You are welcome!")
#define print_wrong_password() Log("%s \n", "Wrong password!")
#define print_enter_password_again() Log("%s \n", "Enter agin:")
#define print_enter_times() Log("%s \n", "You have entered three times! You are not welcome!")

// ��д���� ÿ���������� �������ֳ��ֳ���
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

// ���ܣ�������ѭ��
//      ��ȡ�û����� ���ü��㺯������ ��ӡ�������
// ������run
// ���أ���
// ���룺�� ���̻�ȡ
// ������� ��ӡ����̨
extern void run();

// ���ܣ���ȡ�û���¼
//      ��ȡ�û����� У������ ��ȷ��¼ ������� 3���˳�
// ������login
// ���أ���
// ���룺�� ���̻�ȡ
// ������� ��ӡ����̨
extern void login();

#endif // _FUNCTION_H_
