#include "EmployeeTree.h"



void EmployeeTree::loadRecord()
{
	ifstream fin, finOverflow;
	int id;
	string firstName, lastName;
	float salary;
	char fName[20];
	char lName[20];
	fin.open(filePathPrimary);
	while (fin.good())
	{
		fin >> id;
		fin >> firstName;
		fin >> lastName;
		fin >> salary;
		strcpy_s(fName, firstName.c_str());
		strcpy_s(lName, lastName.c_str());
		Employee* emp = new Employee(id, fName, lName, salary);
		primary.push_back(emp);
	}
	
	fin.close();

	finOverflow.open(filePathOverflow);
	while (finOverflow.good())
	{
		fin >> id;
		fin >> firstName;
		fin >> lastName;
		fin >> salary;
		strcpy_s(fName, firstName.c_str());
		strcpy_s(lName, lastName.c_str());
		Employee* emp = new Employee(id, fName, lName, salary);
		overflow.push_back(emp);
	}
	finOverflow.close();
}

void EmployeeTree::saveRecord()
{
	ofstream ofPrimary, ofOverflow;
	ofPrimary.open(filePathPrimary);
	for (Employee* emp : primary)
	{
		ofPrimary << emp->getEmployeeID() + "\t"
		<< emp->getFirstNameString() + "\t"
		<< emp->getLastNameString() + "\t"
		<< emp->getSalary() << endl;
	}
	ofPrimary.close();

	ofOverflow.open(filePathOverflow);
	for (Employee* emp : overflow)
	{
		ofOverflow << emp->getEmployeeID() + "\t"
			<< emp->getFirstNameString() + "\t"
			<< emp->getLastNameString() + "\t"
			<< emp->getSalary() << endl;
	}
	ofOverflow.close();
}

bool EmployeeTree::InsertRecord(int id, char Fname[20], char Lname[20], float Salary)
{
	Employee* newEmp = new Employee(id, Fname, Lname, Salary);
	int recNum = newEmp->hashID();
	if (!primaryIsOccupied(recNum))
	{
		primary[recNum] = newEmp;
		cout << "Inserted in Primary" << endl;
		addToTree(id, recNum);
	}
	else if (!overflowIsOccupied(recNum))
	{
		overflow[recNum] = newEmp;
		cout << "Inserted in Overflow" << endl;
		addToTree(id, recNum);
	}
	else
		if(probe(recNum, newEmp))
			addToTree(id, recNum);

	return false;
}

bool EmployeeTree::primaryIsOccupied(int recNum)
{
	Employee* emp;
	emp = primary[recNum];
	if (emp != nullptr)
		return true;
	else
		return false;
}

bool EmployeeTree::overflowIsOccupied(int recNum)
{
	Employee* emp;
	emp = overflow[recNum];
	if (emp != nullptr)
		return true;
	else
		return false;
}

bool EmployeeTree::probe(int recNum, Employee* emp)
{
	Employee* temp;
	//check upper half first
	for (int upper = recNum; upper < overflow.size(); upper++)
	{
		temp = overflow[upper];
		if (temp == nullptr)
		{
			overflow[upper] = emp;
			cout << "Item inserted by probing" << endl;
			return true;
		}
	}

	//check lower half
	for (int lower = recNum; lower > -1; lower--)
	{
		temp = overflow[lower];
		if (temp == nullptr)
		{
			overflow[lower] = emp;
			cout << "Item inserted by probing" << endl;
			return true;
		}
	}
	
	return false;
}

bool EmployeeTree::addToTree(int empID, int recNum)
{
	Node* emp = new Node(empID, recNum);
	Node* p = root;
	if (p == nullptr)
		root = emp;
	else
	{
		while (true)
		{
			if (empID > p->empID)
			{
				if (p->right == nullptr)
				{
					p->right == emp;
					cout << "Inserted into tree" << endl;
					return true;
				}
				else
					p = p->right;

			}
			else if (empID < p->empID)
			{
				if (p->left == nullptr)
				{
					p->left = emp;
					cout << "Inserted into tree" << endl;
					return true;
				}
				else
					p = p->left;
			}
		}
	}
	return false;
}

bool EmployeeTree::contains(int id)
{
	Node* temp = root;
	bool rightNull, leftNull;
	rightNull = leftNull = false;
	if (temp == nullptr)
		return false;
	else
	{
		while (true)
		{
			if (temp->right == nullptr)
				rightNull = true;
			if (temp->left == nullptr)
				leftNull = true;
			if (leftNull == true && rightNull == true)
			{
				cout << "Employee does not exist" << endl;
				return false;
			}
			if (id == temp->empID)
				return true;
			if (rightNull != true && id > temp->empID)
			{
				temp = temp->right;
				rightNull = leftNull = false;
			}

			if (leftNull != true && id < temp->empID)
			{
				temp = temp->left;
				rightNull = leftNull = false;
			}
		}
	}
}

int EmployeeTree::getRecordNumber(int id)
{
	if (!contains(id))
		return -1;
	else
	{
		Node* temp = root;
		bool rightNull, leftNull;
		rightNull = leftNull = false;
		if (id == temp->empID)
			return temp->recordNumber;

		else
		{
			while (true)
			{
				if (temp->right == nullptr)
					rightNull = true;
				if (temp->left == nullptr)
					leftNull = true;
				if (id == temp->empID)
					return temp->recordNumber;
				if (rightNull != true && id > temp->empID)
				{
					temp = temp->right;
					rightNull = leftNull = false;
				}

				if (leftNull != true && id < temp->empID)
				{
					temp = temp->left;
					rightNull = leftNull = false;
				}
			}
		}
	}
}

bool EmployeeTree::DeleteRecord(int id)
{
	int recNum = getRecordNumber(id);
	if (primary[recNum]->employeeID == id)
		primary.erase(primary.begin() + recNum);
	else if (overflow[recNum]->employeeID == id)
		overflow.erase(overflow.begin() + recNum);
}

int main()
{

}