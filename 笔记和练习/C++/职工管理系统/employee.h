//普通员工
#pragma once
#include<iostream>
using namespace std;
#include "worker.h"

class Employee :public Worker {
public:
	Employee(int id,string name,int deptid);
//子类重写父类纯虚函数实现多态
	void showInfo();
	string getDeptName();
};