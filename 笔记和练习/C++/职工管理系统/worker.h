#pragma once
#include<iostream>
using namespace std;
#include<string>
//ְ��������
class Worker {
public:
	virtual void showInfo() = 0;
	virtual string getDeptName() = 0;
	int Id;//ְ�����
	string Name;//ְ������
	int DeptId;//���ű��
};