#include "boss.h"
Boss::Boss(int id, string name, int deptid) {
	this->Id = id;
	this->Name = name;
	this->DeptId = deptid;
}
void Boss::showInfo() {
	cout << "ְ����ţ� " << this->Id;
	cout << "\tְ�������� " << this->Name;
	cout << "\tְ����λ�� " << this->getDeptName() << endl;
}
string Boss::getDeptName() {
	return string("�ϰ�");
}