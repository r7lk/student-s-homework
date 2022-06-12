/*--------------------------------------------------------------------
 * manager.h
 *
 * ˵����
 * 		ְ�����ݹ����������ļ���
 * 
 *      ʵ�����¹���
 *      1-ְ����Ϣ¼�� ���ļ�����
 *      2-������ܣ���ʾ����ְ����Ϣ
 *      3-ͳ�ƹ��ܣ��ֱ������ְ����Ůְ����ƽ������
 *      4-��ѯ���ܣ���������һ��ְ���ţ���ѯ��ְ������Ϣ
 *      5-�����ܣ��������ɴ�С����
 *      6-�޸Ĺ���: ���о���ѧ����ְ����������1000Ԫ
 *      7-ɾ�����ܣ�������ɾ��ĳ��ְ����Ϣ
 *      8-�˳�ϵͳ
 *
 * λ�ã�
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
    // ������run
    // ���ܣ�������ѭ������ ������������û�����
    // 0-�ɹ� ����-ʧ��
    int run();

private:
    
    // ������deal_acid_option
    // ���ܣ�������ɾ�Ĳ����5������
    // ������option ����ѡ��
    // ���أ�0-�ɹ� ����-ʧ��
    int deal_acid_option(Option option);

    // ������add_staff
    // ���ܣ����ӵ���ְ����Ϣ �����������ȡ����������Ϣ
    //      1-ְ����Ϣ¼�� ���ļ����� 
    // ������staff Ҫ���ӵ�ְ����Ϣ
    // ���أ�0-�ɹ� RET_EXIST-�Ѵ��� RET_MEM_FAIL-�����ڴ�ʧ�� ����-ʧ��
    int add_staff(Staff* staff);

    // print_single_staff
    // ���ܣ���ӡ����ְ����Ϣ
    // ������staff Ҫ��ӡְ����Ϣ������
    // ������staff Ҫ��ӡ�ĵ���ְ����Ϣ
    // ������fp ��ӡ������ļ�������
    // ���أ�0-�ɹ� RET_FILE_NULL �ļ�������
    int print_single_staff(Staff* staff, FILE* fp);

    // ������print_all_staff
    // ���ܣ���ӡ����ְ����Ϣ
    //      2-������ܣ���ʾ����ְ����Ϣ
    // ������staff Ҫ��ӡְ����Ϣ������
    // ������count Ҫ��ӡ��ְ����Ϣ����
    // ������fp ��ӡ������ļ�������
    // ���أ�0-�ɹ� RET_FILE_NULL �ļ�������
    int print_all_staffs(Staff* staff, size_t count, FILE* fp);

    // ������count_avg_salary
    // ���ܣ�ͳ��ƽ������ 
    //      3-ͳ�ƹ��ܣ��ֱ������ְ����Ůְ����ƽ������
    // ������sex �Ա� S_man��ְ�� S_woman-Ůְ��
    // ���أ���Ӧ�Ա��ƽ��н��
    int count_avg_salary(Sex sex);

    // ������query_staff_info_by_id
    // ���ܣ���ѯ����ְ����Ϣ
    //      4-��ѯ���ܣ���������һ��ְ���ţ���ѯ��ְ������Ϣ
    // ������id ��ѯ�����ְ����
    // ������staff ���ز�ѯ��ְ����Ϣ
    // ���أ�0-�ɹ� RET_NOT_EXIST-���Ų�����
    int query_staff_info_by_id(size_t id, Staff* staff);

    // ������sort_staffs_by_age
    // ���ܣ�������Ӵ�С����ְ����Ϣ
    //      5-�����ܣ��������ɴ�С����
    // ���أ�������ְ����Ϣ-�ɹ� NULL-ʧ��
    Staff* sort_staffs_by_age();

    // ������update_staff
    // ���ܣ��޸ĵ���ְ������Ϣ
    int update_staff_inline();

    // ������update_staff
    // ���ܣ��о���ѧ����ְ����������
    //      6-�޸Ĺ���: ���о���ѧ����ְ����������1000Ԫ
    // ������money ���ӵ�����
    // ���أ�0-�ɹ� ����-ʧ��
    int update_staff(int money);

    // ������delete_staff_by_name
    // ���ܣ�������ɾ��ְ����Ϣ
    //      7-ɾ�����ܣ�������ɾ��ĳ��ְ����Ϣ
    // ������name Ҫɾ����ְ������
    // ���أ�0-�ɹ� ����-ʧ�� RET_NOT_EXIST-���Ų�����
    int delete_staff_by_name(char* name);

    // ������fini
    // ���ܣ��˳�ϵͳ �����ڴ��˳�����
    //      8-�˳�ϵͳ
    // ���أ�һ���ɹ�
    int fini();

private:

    Staff*      m_staff;                // ְ����Ϣ����
    size_t      m_staff_total_count;    // ְ����Ϣ�����ܳ���
    size_t      m_staff_count;          // ְ������-�������ó���
};





#endif // _MANAHER_H