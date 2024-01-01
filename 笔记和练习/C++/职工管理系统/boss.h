#pragma once
#include "worker.h"
class Boss :public Worker
{
public:
	Boss(int id, string name, int deptid);
	void showInfo();
	string getDeptName();
};

