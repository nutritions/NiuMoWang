#include<iostream>
#include<Windows.h>
using namespace std;
#include"workerManager.h"
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
int main() {
	
	WorkerManager wm;
	
	int choice=0;
	while (true) {
		wm.showMenu();
		cout << "输入选择" << endl;
		cin >> choice;
		switch (choice) {
		case 0://退出程序
			wm.exitSys();
			break;
		case 1://增加员工
			wm.empAdd();
			system("cls");
			break;
		case 2://显示信息
			wm.showEmp();
			break;
		case 3://删除员工
			wm.empDel();
			break;
		case 4://修改员工信息
			wm.empMod();
			break;
		case 5://查找职工
			wm.empFind();
			system("pause");
			system("cls");
			break;
		case 6://排序职工
			wm.empSort();
			break;
		case 7://清空文档
			wm.fileClear();
			break;
		default:
			cout << "没有该项功能...等待刷新" << endl;
			Sleep(1000);
			system("cls");
			break;
		}

	}

	return 0;
}