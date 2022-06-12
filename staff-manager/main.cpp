/*--------------------------------------------------------------------
 * main.cpp
 *
 * 说明：
 * 		main文件
 *
 * 位置：
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