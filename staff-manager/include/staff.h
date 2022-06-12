/*--------------------------------------------------------------------
 * staff.h
 *
 * ˵����
 * 		ְ�����ݽṹ�ļ������ְ�������������ݣ�ȫ�����Զ�����������Ϣ��
 *
 * λ�ã�
 * 		src/include/staff.h
 *--------------------------------------------------------------------
 */

#ifndef _STAFF_H_
#define _STAFF_H_

// ��ͷ�尴1�ֽڶ���
#ifdef WINDOWS
   #define __PACKED__
   #pragma pack(push,1)
#else
   #ifdef __GNUC__
      #define __PACKED__  __attribute__ ((packed))
   #else
         #define __PACKED__
   #endif
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// ����ְ�������ַ�����󳤶�
#define NAME_SIZE       50

#define MAXSIZE         256

// �Ա�
typedef enum _Sex
{
    S_man = 0,          // ��
    S_woman             // Ů
}Sex;

// ѧ����Ϣ
typedef enum _Edu
{
    E_zhuanke = 0,      // ר��
    E_benke,            // ����
    E_yanjiusheng,      // �о���
    E_boshi             // ��ʿ
}Edu;

// ���˵�ѡ��
typedef enum _Option
{
    T_invalid = 0,      // ��Чѡ��
    
    T_input,            // 1-ְ����Ϣ¼��
    T_scan,             // 2-�������
    T_count,            // 3-ͳ�ƹ���
    T_query,            // 4-��ѯ����
    T_sort,             // 5-������
    T_update,           // 6-�޸Ĺ���
    T_delete,           // 7-ɾ������
    T_exit              // 8-�˳�ϵͳ
}Option;

// ְ����������
typedef struct _Staff
{
    /* data */
    size_t      id;                 // ְ����-�������ظ�
    char        name[NAME_SIZE+1];  // ����
    Sex         sex;                // �Ա�
    size_t      age;                // ����
    Edu         edu;                // ѧ��
    double      salary;             // ����
    char        isdelete;           // �Ƿ��Ѿ�ɾ�� 0-��ɾ�� 1-����ʹ��
}__PACKED__ Staff;

// ְ������ÿ�����������
#define STAFF_EXTEND_SIZE    50

// ������
#define RET_SUCCESS          0
#define RET_EXIST           -1
#define RET_NOT_EXIST       -2
#define RET_MEM_FAIL        -3
#define RET_FILE_NULL       -4
#define RET_WRONG_INPUT     -5

#ifdef WINDOWS
   #pragma pack(pop)
#else
   #ifdef __GNUC__
   #else
         #pragma options align=reset
   #endif
#endif
#undef __PACKED__

#endif // _STAFF_H_