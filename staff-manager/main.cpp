/*--------------------------------------------------------------------
 * main.cpp
 *
 * ˵����
 * 		main�ļ�
 *
 * λ�ã�
 * 		src/main.cpp
 *--------------------------------------------------------------------
 */

#include "manager.h"

int main(int args, char* argv[])
{
    Manager* manager = new Manager();
    manager->run();
    delete manager;
    
    return 0;
}