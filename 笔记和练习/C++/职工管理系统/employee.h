//��ͨԱ��
#pragma once
#include<iostream>
using namespace std;
#include "worker.h"

class Employee :public Worker {
public:
	Employee(int id,string name,int deptid);
//������д���ി�麯��ʵ�ֶ�̬
	void showInfo();
	string getDeptName();
};