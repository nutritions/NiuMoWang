#pragma once
#include<iostream>
using namespace std;
#include<string>
//职工抽象类
class Worker {
public:
	virtual void showInfo() = 0;
	virtual string getDeptName() = 0;
	int Id;//职工编号
	string Name;//职工姓名
	int DeptId;//部门编号
};