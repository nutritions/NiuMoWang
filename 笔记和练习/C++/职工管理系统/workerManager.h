#pragma once
#include<iostream>
#include<algorithm>
using namespace std;
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
#include<fstream>
#define  FILENAME "empFlie.txt"
class WorkerManager {
public:
	WorkerManager();
	~WorkerManager();
	void showMenu();//展示菜单
	void exitSys();//退出
	int empNum;//员工人数
	Worker** empArray;//父类数组指针
	void empAdd();//添加员工
	void save();//存入文件
	bool is_FileEmpty;//文件是否不存在
	int getEmpNum();//获取现有员工人数
	void EmpInit();//从文件中获取员工数据
	void showEmp();//显示全部职工信息
	void empDel();//删除职工
	int isExist(int id);//判断职工是否存在
	int isExist(string name);
	void empMod();//修改职工信息
	void empFind();//查找员工
	template<typename T>
	void find(T source);
	void empSort();
	void fileClear();
};