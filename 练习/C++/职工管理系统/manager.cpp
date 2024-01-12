#include "manager.h"

Manager::Manager(int id, string name, int deptid) {
	this->Id = id;
	this->Name = name;
	this->DeptId = deptid;
}
void Manager::showInfo() {
	cout << "职工编号： " << this->Id;
	cout << "\t职工姓名： " << this->Name;
	cout << "\t职工岗位： " << this->getDeptName() << endl;
}
string Manager::getDeptName() {
	return string("经理");
}
