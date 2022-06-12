/*--------------------------------------------------------------------
 * manager.h
 *
 * 说明：
 * 		职工数据管理类声明文件。
 * 
 *      实现以下功能
 *      1-职工信息录入 用文件保存
 *      2-浏览功能：显示所有职工信息
 *      3-统计功能：分别计算男职工和女职工的平均工资
 *      4-查询功能：任意输入一个职工号，查询该职工的信息
 *      5-排序功能：按年龄由大到小排序
 *      6-修改功能: 将研究生学历的职工工资增加1000元
 *      7-删除功能：按姓名删除某个职工信息
 *      8-退出系统
 *
 * 位置：
 * 		src/include/manager.h
 *--------------------------------------------------------------------
 */

#ifndef _MANAHER_H
#define _MANAHER_H

#include "staff.h"

class Manager
{

public:
    Manager(/* args */);
    ~Manager() {};

public:
    // 函数：run
    // 功能：进程主循环函数 处理输入输出用户交互
    // 0-成功 其他-失败
    int run();

private:
    
    // 函数：deal_acid_option
    // 功能：处理增删改查浏览5个功能
    // 参数：option 功能选项
    // 返回：0-成功 其他-失败
    int deal_acid_option(Option option);

    // 函数：add_staff
    // 功能：添加单个职工信息 函数不负责获取键盘输入信息
    //      1-职工信息录入 用文件保存 
    // 参数：staff 要增加的职工信息
    // 返回：0-成功 RET_EXIST-已存在 RET_MEM_FAIL-申请内存失败 其他-失败
    int add_staff(Staff* staff);

    // print_single_staff
    // 功能：打印单个职工信息
    // 参数：staff 要打印职工信息的数组
    // 参数：staff 要打印的单个职工信息
    // 参数：fp 打印输出的文件描述符
    // 返回：0-成功 RET_FILE_NULL 文件不存在
    int print_single_staff(Staff* staff, FILE* fp);

    // 函数：print_all_staff
    // 功能：打印所有职工信息
    //      2-浏览功能：显示所有职工信息
    // 参数：staff 要打印职工信息的数组
    // 参数：count 要打印的职工信息个数
    // 参数：fp 打印输出的文件描述符
    // 返回：0-成功 RET_FILE_NULL 文件不存在
    int print_all_staffs(Staff* staff, size_t count, FILE* fp);

    // 函数：count_avg_salary
    // 功能：统计平均工资 
    //      3-统计功能：分别计算男职工和女职工的平均工资
    // 参数：sex 性别 S_man男职工 S_woman-女职工
    // 返回：对应性别的平均薪资
    int count_avg_salary(Sex sex);

    // 函数：query_staff_info_by_id
    // 功能：查询单个职工信息
    //      4-查询功能：任意输入一个职工号，查询该职工的信息
    // 参数：id 查询输入的职工号
    // 参数：staff 返回查询的职工信息
    // 返回：0-成功 RET_NOT_EXIST-工号不存在
    int query_staff_info_by_id(size_t id, Staff* staff);

    // 函数：sort_staffs_by_age
    // 功能：按年龄从大到小排序职工信息
    //      5-排序功能：按年龄由大到小排序
    // 返回：排序后的职工信息-成功 NULL-失败
    Staff* sort_staffs_by_age();

    // 函数：update_staff
    // 功能：修改单个职工的信息
    int update_staff_inline();

    // 函数：update_staff
    // 功能：研究生学历的职工工资增加
    //      6-修改功能: 将研究生学历的职工工资增加1000元
    // 参数：money 增加的数量
    // 返回：0-成功 其他-失败
    int update_staff(int money);

    // 函数：delete_staff_by_name
    // 功能：按姓名删除职工信息
    //      7-删除功能：按姓名删除某个职工信息
    // 参数：name 要删除的职工姓名
    // 返回：0-成功 其他-失败 RET_NOT_EXIST-工号不存在
    int delete_staff_by_name(char* name);

    // 函数：fini
    // 功能：退出系统 清理内存退出进程
    //      8-退出系统
    // 返回：一定成功
    int fini();

private:

    Staff*      m_staff;                // 职工信息数组
    size_t      m_staff_total_count;    // 职工信息数组总长度
    size_t      m_staff_count;          // 职工数量-数组已用长度
};





#endif // _MANAHER_H