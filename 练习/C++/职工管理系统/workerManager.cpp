#include "workerManager.h"

WorkerManager::WorkerManager() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	//文件不存在
	if (!ifs.is_open()) {
		cout << "文件不存在" << endl;
		this->empNum = 0;
		this->empArray = NULL;
		this->is_FileEmpty = true;
		ifs.close();
		return;
	}
	//文件为空
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "文件为空" << endl;
		this->empNum = 0;
		this->empArray = NULL;
		this->is_FileEmpty = true;
		ifs.close();
		return;
	}
	//文件存在且有数据，记录
	int num = this->getEmpNum();
	cout << "职工人数为：" << num<<endl;
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
	cout << "0.退出管理程序" << endl;
	cout << "1.增加职工信息"<< endl;
	cout << "2.显示职工信息" << endl;
	cout << "3.删除离职员工" << endl;
	cout << "4.修改职工信息" << endl;
	cout << "5.查找职工信息" << endl;
	cout << "6.按照编号排序" << endl;
	cout << "7.清空所有文档" << endl;
	
}
void WorkerManager::exitSys() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::empAdd() {
	cout << "请输入要添加的职工人数：" << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0) {
		//设置添加新职工后新数组大小
		int newsize = this->empNum + addNum;
		//设置新数组
		Worker** newSpace = new Worker * [newsize];
		if (this->empArray != NULL) {
			for (int i = 0; i < this->empNum; i++) {
				newSpace[i] = this->empArray[i];
			}
		}
		//根据部门不同实例化不同员工
		for (int i = 0; i < addNum; i++) {
			int id;
			string name;
			int deptid;
			cout << "请输入第" << i + 1 << "个新职工id：" << endl;
			cin >>id;
			cout << "请输入第" << i + 1 << "个新职工姓名：" << endl;
			cin >> name;
			cout << "请选择该职工岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
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
			//加入新职工
			newSpace[this->empNum + i] = worker;
		}
		//更新
		delete[] this->empArray;
		this->empArray = newSpace;
		this->empNum = newsize;
		cout << "成功添加" << addNum << "名新职工" << endl;
		this->save();//保存到文件
	}
	else {
		cout << "输入数据有误" << endl;

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
		if (dept == "普通职工") {
			worker = new Employee(id, name, 1);
		}
		else if(dept=="经理") {
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
		cout << "文件不存在或为空" << endl;
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
		cout << "文件不存在或为空" << endl;
	}
	else {
		cout << "请输入想要删除的职工编号：" << endl;
		int id;
		cin >> id;
		int idx = this->isExist(id);
		if(idx != -1) {
			for (int i = idx; i < this->empNum; i++) {
				this->empArray[i] = this->empArray[i + 1];
			}
			this->empNum--;
			//同步到文件
			this->save();
			cout << "删除成功" << endl;
		}else{
			cout << "不存在该编号员工" << endl;
		}

	}
	system("pause");
	system("cls");
}
void WorkerManager::empMod() {
	if (this->is_FileEmpty) {
		cout << "文件不存在或为空" << endl;
	}
	else {
		cout << "请输入要修改的员工编号：" << endl;
		int id;
		cin >> id;
		int idx = this->isExist(id);
		if (idx!=-1) {
			delete this->empArray[idx];
			int newid;
			string newname;
			int newdept;
			cout << "请输入修改后的编号：" << endl;
			cin >> newid;
			cout << "请输入修改后的姓名：" << endl;
			cin >> newname;
			cout << "请选择修改后职工岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
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
			cout << "修改成功" << endl;
			this->save();

		}
		else {
			cout << "该编号员工不存在" << endl;
		}
	}
}

void WorkerManager::empFind() {
	cout << "请输入查找方式：" << endl;
	cout << "1、按编号查找" << endl;
	cout<< "2、按姓名查找" << endl;
	int choice;
	cin >> choice;
	if (choice == 1) {
		int id;
		cout << "请输入编号/姓名：" << endl;
		cin >> id;
		find(id);
	}
	else {
		string name;
		cout << "请输入编号/姓名：" << endl;
		cin >> name;
		find(name);
	}
}
template<typename T>
void WorkerManager::find(T source) {
	int idx = this->isExist(source);
	if (idx != -1) {
		cout << "查询成功，信息如下：" << endl;
		this->empArray[idx]->showInfo();

	}
	else {
		cout << "查无此人" << endl;
	}
}

void WorkerManager::empSort() {
	if (this->is_FileEmpty) {
		cout << "文件不存在或为空" << endl;
		return;
	}
	cout << "请输入排序方式：" << endl;
	cout << "1、按升序" << endl;
	cout << "2、按降序" << endl;
	int choice;
	cin >> choice;
	for (int i = 0; i < this->empNum; i++)
	{
		int minOrMax = i;
		for (int j = i + 1; j < this->empNum; j++)
		{
			if (choice == 1) //升序
			{
				if (this->empArray[minOrMax]->Id > this->empArray[j]->Id)
				{
					minOrMax = j;
				}
			}
			else  //降序
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

	cout << "排序成功,排序后结果为：" << endl;
	this->save();
	this->showEmp();

}
void WorkerManager::fileClear() {
	cout << "确定清空？" << endl;
	cout << "1、确定" << endl;
	cout << "2、取消" << endl;
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
		cout << "清空成功" << endl;
		system("pause");
		system("cls");
	}

}
