/*--------------------------------------------------------------------
 * staff.h
 *
 * 说明：
 * 		职工数据结构文件。存放职工各类属性数据，全局属性定义错误码等信息。
 *
 * 位置：
 * 		src/include/staff.h
 *--------------------------------------------------------------------
 */

#ifndef _STAFF_H_
#define _STAFF_H_

// 接头体按1字节对齐
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

// 定义职工姓名字符串最大长度
#define NAME_SIZE       50

#define MAXSIZE         256

// 性别
typedef enum _Sex
{
    S_man = 0,          // 男
    S_woman             // 女
}Sex;

// 学历信息
typedef enum _Edu
{
    E_zhuanke = 0,      // 专科
    E_benke,            // 本科
    E_yanjiusheng,      // 研究生
    E_boshi             // 博士
}Edu;

// 主菜单选项
typedef enum _Option
{
    T_invalid = 0,      // 无效选项
    
    T_input,            // 1-职工信息录入
    T_scan,             // 2-浏览功能
    T_count,            // 3-统计功能
    T_query,            // 4-查询功能
    T_sort,             // 5-排序功能
    T_update,           // 6-修改功能
    T_delete,           // 7-删除功能
    T_exit              // 8-退出系统
}Option;

// 职工数据类型
typedef struct _Staff
{
    /* data */
    size_t      id;                 // 职工号-不允许重复
    char        name[NAME_SIZE+1];  // 姓名
    Sex         sex;                // 性别
    size_t      age;                // 年龄
    Edu         edu;                // 学历
    double      salary;             // 工资
    char        isdelete;           // 是否已经删除 0-已删除 1-正在使用
}__PACKED__ Staff;

// 职工数组每次扩充的数量
#define STAFF_EXTEND_SIZE    50

// 错误码
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