#include "boss.h"
Boss::Boss(int id, string name, int deptid) {
	this->Id = id;
	this->Name = name;
	this->DeptId = deptid;
}
void Boss::showInfo() {
	cout << "职工编号： " << this->Id;
	cout << "\t职工姓名： " << this->Name;
	cout << "\t职工岗位： " << this->getDeptName() << endl;
}
string Boss::getDeptName() {
	return string("老板");
}