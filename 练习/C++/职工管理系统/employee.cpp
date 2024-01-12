#include<iostream>
#include"employee.h"
string Employee::getDeptName() {
	return string("员工");
}
void Employee::showInfo() {
	cout << "职工编号： " << this->Id ;
	cout << "\t职工姓名： " << this->Name ;
	cout << "\t职工岗位： " << this->getDeptName() << endl;
}
Employee::Employee(int id,string name,int deptid) {
	this->Id = id;
	this->Name = name;
	this->DeptId = deptid;
}