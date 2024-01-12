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
	void showMenu();//չʾ�˵�
	void exitSys();//�˳�
	int empNum;//Ա������
	Worker** empArray;//��������ָ��
	void empAdd();//���Ա��
	void save();//�����ļ�
	bool is_FileEmpty;//�ļ��Ƿ񲻴���
	int getEmpNum();//��ȡ����Ա������
	void EmpInit();//���ļ��л�ȡԱ������
	void showEmp();//��ʾȫ��ְ����Ϣ
	void empDel();//ɾ��ְ��
	int isExist(int id);//�ж�ְ���Ƿ����
	int isExist(string name);
	void empMod();//�޸�ְ����Ϣ
	void empFind();//����Ա��
	template<typename T>
	void find(T source);
	void empSort();
	void fileClear();
};