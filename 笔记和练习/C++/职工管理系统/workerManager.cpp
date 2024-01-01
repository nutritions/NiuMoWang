#include "workerManager.h"

WorkerManager::WorkerManager() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	//�ļ�������
	if (!ifs.is_open()) {
		cout << "�ļ�������" << endl;
		this->empNum = 0;
		this->empArray = NULL;
		this->is_FileEmpty = true;
		ifs.close();
		return;
	}
	//�ļ�Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "�ļ�Ϊ��" << endl;
		this->empNum = 0;
		this->empArray = NULL;
		this->is_FileEmpty = true;
		ifs.close();
		return;
	}
	//�ļ������������ݣ���¼
	int num = this->getEmpNum();
	cout << "ְ������Ϊ��" << num<<endl;
	this->empNum = num;
	this->empArray = new Worker * [this->empNum];
	this->EmpInit();
	
}

WorkerManager::~WorkerManager() {
	if (this->empArray != NULL) {
		for (int i = 0; i < this->empNum; i++) {
			if (this->empArray[i] != NULL) {
				delete this->empArray[i];
			}
		}
		delete[] this->empArray;
		this->empArray = NULL;
		
	}
}
void WorkerManager::showMenu() {
	cout << "******************" << endl;
	cout << "0.�˳��������" << endl;
	cout << "1.����ְ����Ϣ"<< endl;
	cout << "2.��ʾְ����Ϣ" << endl;
	cout << "3.ɾ����ְԱ��" << endl;
	cout << "4.�޸�ְ����Ϣ" << endl;
	cout << "5.����ְ����Ϣ" << endl;
	cout << "6.���ձ������" << endl;
	cout << "7.��������ĵ�" << endl;
	
}
void WorkerManager::exitSys() {
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::empAdd() {
	cout << "������Ҫ��ӵ�ְ��������" << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0) {
		//���������ְ�����������С
		int newsize = this->empNum + addNum;
		//����������
		Worker** newSpace = new Worker * [newsize];
		if (this->empArray != NULL) {
			for (int i = 0; i < this->empNum; i++) {
				newSpace[i] = this->empArray[i];
			}
		}
		//���ݲ��Ų�ͬʵ������ͬԱ��
		for (int i = 0; i < addNum; i++) {
			int id;
			string name;
			int deptid;
			cout << "�������" << i + 1 << "����ְ��id��" << endl;
			cin >>id;
			cout << "�������" << i + 1 << "����ְ��������" << endl;
			cin >> name;
			cout << "��ѡ���ְ����λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> deptid; 
			Worker* worker = NULL;
			switch (deptid)
			{
			case 1:
				worker = new Employee(id,name,deptid);
				break;
			case 2:
				worker = new Manager (id, name, deptid);
				break;
			case 3:
				worker = new Boss(id, name, deptid);
				break;
			default:
				break;
			}
			//������ְ��
			newSpace[this->empNum + i] = worker;
		}
		//����
		delete[] this->empArray;
		this->empArray = newSpace;
		this->empNum = newsize;
		cout << "�ɹ����" << addNum << "����ְ��" << endl;
		this->save();//���浽�ļ�
	}
	else {
		cout << "������������" << endl;

	}
}
void WorkerManager::save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < this->empNum; i++) {
		ofs << this->empArray[i]->Id << " "
			<< this->empArray[i]->Name << " "
			<< this->empArray[i]->getDeptName() << " ";
	}
	ofs.close();
}

int WorkerManager::getEmpNum() {
	ifstream ifs;
	ifs.open(FILENAME,ios::in);
	int num = 0;
	int id;
	string name;
	string dept;

	while (ifs >> id && ifs >> name && ifs >>dept) {
		num++;
	}
	return num;
	ifs.close();
}

void WorkerManager::EmpInit() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	string dept;
	int idx = 0;
	while (ifs >> id && ifs >> name && ifs >> dept) {
		Worker* worker = NULL;
		if (dept == "��ְͨ��") {
			worker = new Employee(id, name, 1);
		}
		else if(dept=="����") {
			worker = new Manager(id, name, 2);
		}
		else {
			worker = new Boss(id, name, 3);
		}
		this->empArray[idx++] = worker;
	}
	ifs.close();
}

void WorkerManager::showEmp() {
	if (this->is_FileEmpty) {
		cout << "�ļ������ڻ�Ϊ��" << endl;
	}
	else {
		for (int i = 0; i < this->empNum; i++) {
			this->empArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}
int WorkerManager::isExist(int id) {
	int idx = -1;
	for (int i = 0; i < this->empNum; i++) {
		if(id == this->empArray[i]->Id) {
			idx = i;
			break;
		}
	}
	return idx;
}
int WorkerManager::isExist(string name) {
	int idx = -1;
	for (int i = 0; i < this->empNum; i++) {
		if (name == this->empArray[i]->Name) {
			idx = i;
			break;
		}
	}
	return idx;
}
void WorkerManager::empDel() {
	if (this->is_FileEmpty) {
		cout << "�ļ������ڻ�Ϊ��" << endl;
	}
	else {
		cout << "��������Ҫɾ����ְ����ţ�" << endl;
		int id;
		cin >> id;
		int idx = this->isExist(id);
		if(idx != -1) {
			for (int i = idx; i < this->empNum; i++) {
				this->empArray[i] = this->empArray[i + 1];
			}
			this->empNum--;
			//ͬ�����ļ�
			this->save();
			cout << "ɾ���ɹ�" << endl;
		}else{
			cout << "�����ڸñ��Ա��" << endl;
		}

	}
	system("pause");
	system("cls");
}
void WorkerManager::empMod() {
	if (this->is_FileEmpty) {
		cout << "�ļ������ڻ�Ϊ��" << endl;
	}
	else {
		cout << "������Ҫ�޸ĵ�Ա����ţ�" << endl;
		int id;
		cin >> id;
		int idx = this->isExist(id);
		if (idx!=-1) {
			delete this->empArray[idx];
			int newid;
			string newname;
			int newdept;
			cout << "�������޸ĺ�ı�ţ�" << endl;
			cin >> newid;
			cout << "�������޸ĺ��������" << endl;
			cin >> newname;
			cout << "��ѡ���޸ĺ�ְ����λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> newdept;
			Worker* worker = NULL;
			switch (newdept)
			{
			case 1:
				worker = new Employee(newid, newname, newdept);
				break;
			case 2:
				worker = new Manager(newid, newname, newdept);
				break;
			case 3:
				worker = new Boss(newid, newname, newdept);
				break;
			default:
				break;
			}
			this->empArray[idx] = worker;
			cout << "�޸ĳɹ�" << endl;
			this->save();

		}
		else {
			cout << "�ñ��Ա��������" << endl;
		}
	}
}

void WorkerManager::empFind() {
	cout << "��������ҷ�ʽ��" << endl;
	cout << "1������Ų���" << endl;
	cout<< "2������������" << endl;
	int choice;
	cin >> choice;
	if (choice == 1) {
		int id;
		cout << "��������/������" << endl;
		cin >> id;
		find(id);
	}
	else {
		string name;
		cout << "��������/������" << endl;
		cin >> name;
		find(name);
	}
}
template<typename T>
void WorkerManager::find(T source) {
	int idx = this->isExist(source);
	if (idx != -1) {
		cout << "��ѯ�ɹ�����Ϣ���£�" << endl;
		this->empArray[idx]->showInfo();

	}
	else {
		cout << "���޴���" << endl;
	}
}

void WorkerManager::empSort() {
	if (this->is_FileEmpty) {
		cout << "�ļ������ڻ�Ϊ��" << endl;
		return;
	}
	cout << "����������ʽ��" << endl;
	cout << "1��������" << endl;
	cout << "2��������" << endl;
	int choice;
	cin >> choice;
	for (int i = 0; i < this->empNum; i++)
	{
		int minOrMax = i;
		for (int j = i + 1; j < this->empNum; j++)
		{
			if (choice == 1) //����
			{
				if (this->empArray[minOrMax]->Id > this->empArray[j]->Id)
				{
					minOrMax = j;
				}
			}
			else  //����
			{
				if (this->empArray[minOrMax]->Id < this->empArray[j]->Id)
				{
					minOrMax = j;
				}
			}
		}

		if (i != minOrMax)
		{
			Worker* temp = this->empArray[i];
			this->empArray[i] = this->empArray[minOrMax];
			this->empArray[minOrMax] = temp;
		}

	}

	cout << "����ɹ�,�������Ϊ��" << endl;
	this->save();
	this->showEmp();

}
void WorkerManager::fileClear() {
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2��ȡ��" << endl;
	int choice;
	cin >> choice;
	if (choice == 1) {
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();
		if (this->empArray != NULL) {
			for (int i = 0; i < this->empNum; i++) {
				if (this->empArray[i] != NULL) {
					delete this->empArray[i];
					this->empArray[i] = NULL;
				}
			}
			delete[] this->empArray;
			this->empArray = NULL;
			this->empNum = 0;
			this->is_FileEmpty = true;

		}
		cout << "��ճɹ�" << endl;
		system("pause");
		system("cls");
	}

}
