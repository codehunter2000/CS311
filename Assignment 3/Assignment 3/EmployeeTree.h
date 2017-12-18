#include<string>
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

class EmployeeTree
{
	friend class Node;
	friend class Employee;
protected:
	Node* root;
	const string filePathPrimary = "EmployeePrimary.txt";
	const string filePathOverflow = "EmployeeOverflow.txt";
	vector<Employee*> primary;
	vector<Employee*> overflow;
public:
	bool InsertRecord(int id, char Fname[20], char Lname[20], float Salary);
	bool DeleteRecord(int id);
	void ReadTransactions();
	void InitEmpFile();
	bool UpdateRecord(int id); 
	void PrintInOrder();
	void PrintBreadth();
	void BalanceTheTree();
	EmployeeTree();
	~EmployeeTree();
private:
	bool contains(int id);
	int getRecordNumber(int id);
	bool inPrimary(int id, int recNum);
	bool inOverflow(int id, int recNum);
	bool primaryIsOccupied(int recNum);
	bool overflowIsOccupied(int recNum);
	bool probe(int recNum, Employee* emp);
	bool addToTree(int empID, int recNum);
	void loadRecord();
	void saveRecord();

	
};

class Node
{
	friend class EmployeeTree;
protected:
	int empID, recordNumber;
	Node* left;
	Node* right;
public:
	Node()
	{
		empID = recordNumber = 0;
		left = right = nullptr;
	}
	Node(int id, int recNum)
	{
		empID = id;
		recordNumber = recNum;
		left = right = nullptr;
	}
};

class Employee
{
	friend class EmployeeTree;
protected:
	int  employeeID;
	char Fname[20];
	char Lname[20];
	float salary;
public:
	Employee()
	{
		employeeID = 0;
		for (int i = 0; i < 20; i++)
			Fname[i] = Lname[i] = 0;
		salary = 0;
	}
	Employee(int id, char first[20], char last[20], float money)
	{
		employeeID = id;
		for (int i = 0; i < 20; i++)
			Fname[i] = first[i];
		for (int j = 0; j < 20; j++)
			Lname[j] = last[j];
			salary = money;
	}
	int hashID()
	{
		return employeeID % 100;
	}
	int getEmployeeID()
	{
		return employeeID;
	}
	string getFirstNameString()
	{
		string str(Fname);
		return str;
	}
	string getLastNameString()
	{
		string str(Lname);
		return str;
	}
	float getSalary()
	{
		return salary;
	}
};

