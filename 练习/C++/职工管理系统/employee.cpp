#include<iostream>
#include"employee.h"
string Employee::getDeptName() {
	return string("Ա��");
}
void Employee::showInfo() {
	cout << "ְ����ţ� " << this->Id ;
	cout << "\tְ�������� " << this->Name ;
	cout << "\tְ����λ�� " << this->getDeptName() << endl;
}
Employee::Employee(int id,string name,int deptid) {
	this->Id = id;
	this->Name = name;
	this->DeptId = deptid;
}