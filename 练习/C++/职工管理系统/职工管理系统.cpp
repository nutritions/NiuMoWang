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
		cout << "����ѡ��" << endl;
		cin >> choice;
		switch (choice) {
		case 0://�˳�����
			wm.exitSys();
			break;
		case 1://����Ա��
			wm.empAdd();
			system("cls");
			break;
		case 2://��ʾ��Ϣ
			wm.showEmp();
			break;
		case 3://ɾ��Ա��
			wm.empDel();
			break;
		case 4://�޸�Ա����Ϣ
			wm.empMod();
			break;
		case 5://����ְ��
			wm.empFind();
			system("pause");
			system("cls");
			break;
		case 6://����ְ��
			wm.empSort();
			break;
		case 7://����ĵ�
			wm.fileClear();
			break;
		default:
			cout << "û�и����...�ȴ�ˢ��" << endl;
			Sleep(1000);
			system("cls");
			break;
		}

	}

	return 0;
}