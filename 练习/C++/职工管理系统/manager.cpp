#include "manager.h"

Manager::Manager(int id, string name, int deptid) {
	this->Id = id;
	this->Name = name;
	this->DeptId = deptid;
}
void Manager::showInfo() {
	cout << "ְ����ţ� " << this->Id;
	cout << "\tְ�������� " << this->Name;
	cout << "\tְ����λ�� " << this->getDeptName() << endl;
}
string Manager::getDeptName() {
	return string("����");
}
