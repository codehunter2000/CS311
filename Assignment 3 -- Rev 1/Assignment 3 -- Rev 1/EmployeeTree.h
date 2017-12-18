
/*
	Author: Gabriel Hunt
	Files: EmployeeTree.h, EmployeTree.cpp
	Date Last Modified: November 20, 2017

*/


#include<iostream>
#include<fstream>
#include<iomanip>
#include<queue>
#include<string>
using namespace std;

class EmployeeTree
{
public:
	EmployeeTree();
	~EmployeeTree();
};

struct EmpData
{
	int  employeeId;
	char fname[20];
	char lname[20];
	float salary;
};

//--------------------------------------------
class node
{
	friend class BST;
protected:
	int empIndexId;
	int recNum;
	node* left;
	node* right;
public:
	node() { empIndexId = 0; recNum = 0; left = NULL; right = NULL; }
	void print()
	{
		cout << "------------------------------------------" << "\n" << endl;
		cout << "Employee ID: " << empIndexId << "\n" << endl;
		cout << "Record Number: " << recNum << "\n" << endl;
		cout << "------------------------------------------" << "\n" << endl;
	}
};

//--------------------------------------------
class BST
{
	friend class node;
private:
	node* root;
	bool removeLeafNode(int empId, node* toRemove);
	bool removeNodeSingleChild(int empId, node* toRemove);
	bool removeNodeTwoChild(int empId, node* toRemove);
	void storeNodes(node* temp, vector<node*> &nodes);
	node* constructBalancedTree(vector<node*> &nodes, int start,
		int end);
	void printInOrder(node* temp);
public:
	BST() { root = NULL; }
	bool  insert(int empId, int recNumber);
	bool  remove(int empId);
	int   search(int empId);  // if empId exists it returns the record Number 
							  // where empId is stored in the file
	void printInOrder();
	void printBreath();
	bool BalanceTree();
};
//-----------------------------------------------
class RandAccessFile
{
	friend class BST;
private:
	BST  empIndexTree;
	ofstream fout;
	ifstream fin;
	
public:
	RandAccessFile(); // initializes the records in a file
	int insertRecord(int empID, const char* Fname[20], const char* Lname[20], float Salary);
	bool deleteRecord(int empID);
	int insertByProbing(EmpData emp1, int recNum);
	bool updateEmpID(int empID, int newID);
	bool updateEmpFirstName(int empID, const char* Fname[20]);
	bool updateEmpLastName(int empID, const char* Lname[20]);
	bool updateEmpSalary(int empID, float monies);
	void processTransFile(string filePath);
	void printRAF();
};

//-----------------------------------------------
RandAccessFile::RandAccessFile() // initializes the records in a file
{
	cout.setf(ios::fixed, ios::floatfield);
	cout.setf(ios::showpoint);
	cout << setprecision(2);

	// opening up the file for input and outut
	fout.open("data.txt", ios::ate);
	fin.open("data.txt", ios::in);

	// initializing the bufer
	EmpData blankEmp1, blankEmp2;
	blankEmp2.employeeId = -1;
	strcpy_s(blankEmp2.fname, "---");
	strcpy_s(blankEmp2.lname, "---");
	blankEmp2.salary = 0.0;


	// it is important to initialize the Random Access file first
	// record 0 through 199
	for (int i = 0; i<200; i++)
		fout.write(reinterpret_cast<const char*>(&blankEmp2), sizeof(blankEmp2));

	
	/*
	// printing the records
	for (int i = 0; i<200; i++)
	{
		fin.seekg(sizeof(blankEmp2)*i);
		fin.read(reinterpret_cast<char*>(&blankEmp2), sizeof(blankEmp2));
		cout << blankEmp2.employeeId << "\t" << blankEmp2.fname << "\t"
			<< blankEmp2.lname << "\t" << blankEmp2.salary << "\t" << endl;
	}
	*/
}

void RandAccessFile::printRAF()
{
	EmpData blankEmp2;
	for (int i = 0; i<200; i++)
	{
		fin.seekg(sizeof(blankEmp2)*i);
		fin.read(reinterpret_cast<char*>(&blankEmp2), sizeof(blankEmp2));
		cout << blankEmp2.employeeId << "\t" << blankEmp2.fname << "\t"
			<< blankEmp2.lname << "\t" << blankEmp2.salary << "\t" << endl;
	}
}