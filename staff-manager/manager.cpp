/*--------------------------------------------------------------------
 * manager.cpp
 *
 * ˵����
 * 		ְ�����ݹ�����ʵ���ļ���
 *
 * λ�ã�
 * 		src/include/manager.cpp
 *--------------------------------------------------------------------
 */

#include "manager.h"

// ��ӡ���
FILE* fp_out = stdout;

Manager::Manager()
{
    m_staff = (Staff*)malloc(sizeof(Staff)*STAFF_EXTEND_SIZE);
    if(NULL == m_staff)
        abort();
    memset(m_staff, 0x00, sizeof(Staff)*STAFF_EXTEND_SIZE);
    m_staff_total_count = STAFF_EXTEND_SIZE;
    m_staff_count = 0;
}

int Manager::run()
{
    int input;          // �ж�scanf�����������
    while (true)
    {
        int index = 0;  // ����ѡ��
        int ret = 0;    // ѡ��ִ�н��������

#include "option.h"

        char input_index[MAXSIZE] = { 0 };
        input = scanf("%s", input_index);
        if (1 != input)
            continue;

        input_index[sizeof(input_index) - 1] = '\0';
        index = atoi(input_index);

        switch (index)
        {
            case T_input:
            case T_query:
            case T_update:
            case T_delete:
                deal_acid_option((Option)index);
                break;
            case T_scan:
                print_all_staffs(m_staff, m_staff_count, fp_out);
                break;
            case T_sort:
                {
                    Staff* temp = sort_staffs_by_age();
                    print_all_staffs(temp, m_staff_count, fp_out);
                    free(temp);
                }
                break;
            case T_count:
                {
                    double man_avg = count_avg_salary(S_man);
                    double woman_avg = count_avg_salary(S_woman);
                    fprintf(fp_out, "��ְ��ƽ������: %lf Ůְ��ƽ������: %lf \n",
                    man_avg, woman_avg);
                }
                break;
            case T_exit:
                fini();
                return 0;
            default:
                fprintf(fp_out, "%s", "��Чѡ��\n");
                break;
        }
    }
}

int Manager::deal_acid_option(Option option)
{
    switch (option)
    {
    // 1-ְ����Ϣ¼��
    case T_input:
        {
            Staff staff;
            memset(&staff, 0x00, sizeof(Staff));

            // ��ȡ����
            fprintf(fp_out, "%s \n", 
                " ������Ϣ: ְ���� ���� �Ա�(0-�� 1-Ů) ���� "
                "ѧ��(0-ר�� 1-���� 2-�о��� 3-��ʿ) ���� \n");
            int input = scanf("%d %s %d %d %d %lf", 
                &staff.id,      // ְ����id
                staff.name,     // ����
                &staff.sex,     // �Ա�
                &staff.age,     // ����
                &staff.edu,     // ѧ��
                &staff.salary); // ����
            staff.isdelete = 1; // ����ӵ�Ϊ����ʹ�õ�
            if(6 != input) // �����������ȷ
            {
                fprintf(fp_out, "%s \n", "������Ϣ����ȷ! \n");
                return RET_WRONG_INPUT;
            }
            
            // ������Ϣ
            int ret = add_staff(&staff);
            if(0 == ret)
                fprintf(fp_out, "%s \n", "���ӳɹ�! \n");
            else if(RET_EXIST == ret)
                fprintf(fp_out, "%s \n", "ְ�����Ѵ���! \n");
            else if(RET_MEM_FAIL == ret)
            {
                fprintf(fp_out, "%s \n", "�����ڴ�ʧ��! �˳� \n");
                abort();
            }
            else fprintf(fp_out, "%s \n", "����ʧ��! \n");
            return ret;
        }
        break;
    // 7-ɾ�����ܣ�������ɾ��ĳ��ְ����Ϣ
    case T_delete:
        {
            char name[NAME_SIZE+1] = {0};
            fprintf(fp_out, "%s \n", "����ְ������ \n");
            scanf("%s", name);
            int ret = delete_staff_by_name(name);
            
            if(0 == ret)
                fprintf(fp_out, "%s \n", "ɾ���ɹ�! \n");
            else if(RET_NOT_EXIST == ret)
                fprintf(fp_out, "%s \n", "ְ�����Ʋ�����! \n");
            else fprintf(fp_out, "%s \n", "ɾ��ʧ��! \n");
            return ret;
        }
        break;
    // 6-�޸Ĺ���: ���о���ѧ����ְ����������1000Ԫ
    case T_update:
        {
            int money = 1000;
            int ret = update_staff(money);

            if(0 == ret)
                fprintf(fp_out, "%s \n", "�޸ĳɹ�! \n");
            else fprintf(fp_out, "%s \n", "�޸�ʧ��! \n");
            return ret;
        }
        break;
    // 4-��ѯ���ܣ���������һ��ְ���ţ���ѯ��ְ������Ϣ
    case T_query:
        {
            Staff staff;
            size_t id = 0;
            fprintf(fp_out, "%s \n", "����ְ���� \n");
            scanf("%d", &id);
            int ret = query_staff_info_by_id(id, &staff);
            if(0 == ret)
                print_single_staff(&staff, fp_out);
            else if(RET_NOT_EXIST == ret)
                fprintf(fp_out, "%s \n", "ְ���Ų�����! \n");
            else fprintf(fp_out, "%s \n", "��ѯʧ��! \n");
            return ret;
        }
        break;  
    default:
        break;
    }
    printf("\n");
}

int Manager::add_staff(Staff* staff)
{
    /*
    // ����Ҫ��������
    if (0 == m_staff_total_count || m_staff_count == m_staff_total_count)
    {
        Staff* m_staff = (Staff*)realloc(m_staff,
                        (m_staff_total_count+STAFF_EXTEND_SIZE)*sizeof(Staff));
        if(NULL == m_staff) 
            return RET_MEM_FAIL;
        m_staff_total_count +=  STAFF_EXTEND_SIZE;
    }
    */
    // ����Ѿ�����
    Staff* temp = m_staff;
    int count = m_staff_count; 
    while (count--)
    {
        if(temp->id == staff->id)
            return RET_EXIST;
        temp++;
    }

    // ����
    m_staff[m_staff_count].age    = staff->age;
    m_staff[m_staff_count].edu    = staff->edu;
    m_staff[m_staff_count].id     = staff->id;
    m_staff[m_staff_count].salary = staff->salary;
    m_staff[m_staff_count].sex    = staff->sex;
    m_staff[m_staff_count].isdelete = 1;
    strcpy(m_staff[m_staff_count].name, staff->name);
    
    m_staff_count++;
    return 0;
}

// �Ա��ַ���
const char* str_sex[] = {"��", "Ů"};

// ѧ����Ϣ�ַ���
const char* str_edu[] = {"ר��", "����", "�о���", "��ʿ"};

// �Ƿ�ɾ���ַ���
const char* str_isdelete[] = { "��", "��", "�о���", "��ʿ" };

int Manager::print_single_staff(Staff* staff, FILE* fp)
{
    if(0 == staff->isdelete) return 0;

    fprintf(fp, "%s", "==================================== \n");
    fprintf(fp, " ְ���� %d \n ���� %s \n �Ա� %s \n ���� %d \n"
                    " ѧ�� %s \n ���� %lf \n",
            staff->id, staff->name, str_sex[staff->sex], staff->age,
            str_edu[staff->edu], staff->salary
    );
    fprintf(fp, "%s", "==================================== \n");
    return 0;
}

int Manager::print_all_staffs(Staff* staff, size_t count, FILE* fp)
{
    Staff* temp = staff;
    while (count--)
        print_single_staff(temp++, fp);
    return 0;
}

int Manager::count_avg_salary(Sex sex)
{
    Staff* temp = m_staff;
    int count = m_staff_count;
    int salary = 0;
    int people = 0;
    while (count)
    {
        if(sex == temp->sex)
            salary += temp->salary, people++;
        temp++, count--;
    }

    if (0 == people)
        return 0.0;

    return salary/people;
}

int Manager::query_staff_info_by_id(size_t id, Staff* staff)
{
    Staff* temp = m_staff;
    int count = m_staff_count;

    while (count--)
    if(id == temp->id)
    {
		staff->age      = temp->age;
		staff->edu      = temp->edu;
		staff->id       = temp->id;
		staff->salary   = temp->salary;
		staff->sex      = temp->sex;
		staff->isdelete = temp->isdelete;
		strcpy(staff->name, temp->name);

        return 0;
    }
    else temp++;

    return RET_NOT_EXIST;
}


int compare_staff_by_age(const void* s1, const void* s2)
{
    if(((Staff*)s1)->age > ((Staff*)s2)->age)  return -1;
}

Staff* Manager::sort_staffs_by_age()
{
    if(0 == m_staff_count) return NULL;

    Staff* sort_staff = (Staff*)malloc(m_staff_count*sizeof(Staff));
    if(NULL == sort_staff) return NULL;

    memset(sort_staff, 0x00, m_staff_count*sizeof(Staff));
    memcpy(sort_staff, m_staff, m_staff_count*sizeof(Staff));
    qsort(sort_staff, m_staff_count, sizeof(Staff), compare_staff_by_age);

    return sort_staff;
}

int Manager::update_staff_inline()
{
    return 0;
}

int Manager::update_staff(int money)
{
    Staff* temp = m_staff;
    int count = m_staff_count;

    while (count--)
    {
        if(E_yanjiusheng == temp->edu)
            temp->salary += money;
        temp++;
    }

    return 0;
}

int Manager::delete_staff_by_name(char* name)
{
    Staff* temp = m_staff;
    int count = m_staff_count;

    while (count--)
    {
		if (0 == strcmp(name, temp->name))
		{
			temp->isdelete = 0;
			return 0;
		}
        temp++;
    }


    return RET_NOT_EXIST;
}

int Manager::fini()
{
    if(NULL != m_staff)
    {
        FILE* fp = fopen("result.txt", "w");
        if (NULL == fp)
            fprintf(fp_out, "%s", "result.txt can not open \n");
        else print_all_staffs(m_staff, m_staff_count, fp);
        
        fflush(fp);
        fclose(fp);
        free(m_staff);
    }
    
    return 0;
}