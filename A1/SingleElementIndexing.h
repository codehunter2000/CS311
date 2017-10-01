#include<string>
#include<iostream>


using namespace std;

class Employee;
class Block;
class SingleElementIndexing;

typedef Employee* ePtr;
typedef Block* blockPtr;

class Employee
{
protected:
	int empID;
	string userName, password;
	ePtr nextEmp;
	friend SingleElementIndexing;
	

public:
	Employee()
	{
		empID = 0;
		userName = password = " ";
		nextEmp = NULL;
	}

	Employee(int id, string uName, string pass)
	{
		empID = id;
		userName = uName;
		password = pass;
		nextEmp = NULL;
	}
	friend ostream &operator<<(ostream &output, const Employee &emp)
	{
		output << "==================================================="
			<< "ID: " << emp.empID << "\n" << "User Name: " << emp.userName
			<< "\n" << "Password: " << emp.password;
		return output;
	}
};

class Block
{
protected:
	ePtr top;
	int count;
	blockPtr nextBlock;
	friend SingleElementIndexing;

public:
	Block()
	{
		top = NULL;
		count = 0;
		nextBlock = NULL;
	}
};

class SingleElementIndexing
{

protected:
	static blockPtr A[4];

public:
	SingleElementIndexing()
	{
		A[0] = A[1] = A[2] = A[3] = NULL;
	}
	bool addEmp(int id, string uName, string pass);
	bool printAll();
	bool searchID(int id);
	bool deleteEmployee(int id);
	bool changeUserName(int id, string newName);
	bool changePassword(int id, string newPass);
	bool loadConfig();
	bool saveConfig();
	bool processTrasaction();
	bool validID(int id);
	bool alreadyInList(int id);
	bool inFirstBlock(int id);
	bool inSecondBlock(int id);
};

