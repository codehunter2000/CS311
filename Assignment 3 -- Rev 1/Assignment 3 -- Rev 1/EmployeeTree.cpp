#include "EmployeeTree.h"



EmployeeTree::EmployeeTree()
{
}


EmployeeTree::~EmployeeTree()
{
}

// Remove single node w/ no children
bool BST::removeLeafNode(int empId, node* toRemove)
{
	node* prev = new node();
	prev = root;
	while (true)
	{
		if (prev->right == toRemove)
		{
			prev->right = NULL;
			delete toRemove;
			return true;
		}

		if (prev->left == toRemove)
		{
			prev->left = NULL;
			return true;
		}

		if (empId > prev->empIndexId)
			prev = prev->right;
		else if (empId < prev->empIndexId)
			prev = prev->left;
	}
	return false;
}

// Removes a node with just one child
bool BST::removeNodeSingleChild(int empId, node* toRemove)
{
	node* child = new node();
	node* prev = new node();
	if (toRemove->right != NULL)
		child = toRemove->right;
	else if (toRemove->left != NULL)
		child = toRemove->left;

	while (true)
	{
		if (prev->right == toRemove)
		{
			prev->right = child;
			delete toRemove;
			return true;
		}

		if (prev->left == toRemove)
		{
			prev->left = child;
			delete toRemove;
			return true;
		}

		if (empId > prev->empIndexId)
			prev = prev->right;
		else if (empId < prev->empIndexId)
			prev = prev->left;
	}

	return false;
}

// Removes a node with two children
bool BST::removeNodeTwoChild(int empId, node* toRemove)
{
	node* leftChild = new node();
	node* rightChild = new node();
	node* temp = new node();
	node* prev = new node();

	leftChild = toRemove->left;
	rightChild = toRemove->right;

	while (true)
	{
		if (prev->right == toRemove)
		{
			prev->right = leftChild;
			temp = leftChild;
			while (temp->right != NULL)
				temp = temp->right;
			temp->right = rightChild;
			delete toRemove;
			return true;
		}

		if (prev->left == toRemove)
		{
			prev->right = leftChild;
			temp = leftChild;
			while (temp->right != NULL)
				temp = temp->right;
			temp->right = rightChild;
			delete toRemove;
			return true;
		}

		if (empId > prev->empIndexId)
			prev = prev->right;
		else if (empId < prev->empIndexId)
			prev = prev->left;
	}
	
	return false;
}


// Insert node into tree
bool BST::insert(int empId, int recNumber)
{
	node* p = root;
	node* prev = root;
	
	while (p != NULL)
	{
		prev = p;
		if (empId < p->empIndexId)
			p = p->left;
		else if (empId > p->empIndexId)
			p = p->right;
		else
		{
			cout << "\n!!!! " << empId << " is already in the tree " << endl;
			return false;
		}
	}
	node* toAdd = new node();
	toAdd->empIndexId = empId;
	toAdd->recNum = recNumber;
	if (root == NULL)
		root = toAdd;
	else if (prev->empIndexId < empId)
		prev->right = toAdd;
	else
		prev->left = toAdd;
	cout << empId << " added to tree" << endl;
	return true;
	
	/*
	if (search(empId) == -1)
	{
		node* toAdd = new node();
		toAdd->empIndexId = empId;
		toAdd->recNum = recNumber;
		node* temp = new node();
		temp = root;
		bool rightNull, leftNull;
		if (root == nullptr)
		{
			root = toAdd;
			return true;
		}

		while (true)
		{
			rightNull = leftNull = false;

			if (temp->right == nullptr)
				rightNull = true;
			if (temp->left == nullptr)
				leftNull = true;
			if (empId > temp->empIndexId)
			{
				if (rightNull == false)
					temp = temp->right;
				else if (rightNull == true)
				{
					temp->right = toAdd;
					return true;
				}
			}

			else if (empId < temp->empIndexId)
			{
				if (leftNull == false)
					temp = temp->left;
				else if (rightNull == true)
				{
					temp->left = toAdd;
					return true;
				}
			}
		}
	}

	else
		return false;
	*/
	
}

// Delete node from tree
bool BST::remove(int empId)
{
	// Exit if node DNE
	if (search(empId) == -1)
		return false;
	
	// Proceed if node exists
	else
	{
		node* temp = new node();
		temp = root;
		while (true)
		{
			if (empId == temp->empIndexId)
			{
				if (temp->right == NULL && temp->left == NULL)
					return removeLeafNode(empId, temp);
				else if (temp->right == NULL && temp->left != NULL)
					return removeNodeSingleChild(empId, temp);
				else if (temp->right != NULL && temp->left == NULL)
					return removeNodeSingleChild(empId, temp);
				else if (temp->right != NULL && temp->left != NULL)
					return removeNodeTwoChild(empId, temp);
			}

			else if (empId > temp->empIndexId)
				temp = temp->right;
			else if (empId < temp->empIndexId)
				temp = temp->left;
		}
	}
	return false;
}

// Checks for node in tree
// Returns record number if found
// Returns -1 if DNE
int BST::search(int empId)
{
	node* temp = root;
if (temp == nullptr)
		return -1;
	else if (empId == temp->empIndexId)
		return temp->recNum;
	else
		while (true)
		{
			if (empId == temp->empIndexId)
				return temp->recNum;
			if (temp->left == NULL && temp->right == NULL)
				return -1;
			if (empId > temp->empIndexId && temp->right != NULL)
				temp = temp->right;
			else if (empId < temp->empIndexId && temp->left != NULL)
				temp = temp->left;
			else if (empId > temp->empIndexId && temp->right == NULL)
				return -1;
			else if (empId < temp->empIndexId && temp->left == NULL)
				return -1;
		}
	return -1;
}

void BST::printInOrder()
{
	printInOrder(root);
}

void BST::printInOrder(node* temp)
{
	if (temp == NULL)
		return;
	printInOrder(temp->left);
	temp->print();
	printInOrder(temp->right);
}

void BST::printBreath()
{
	queue<node*> que;
	node* p = new node();
	p = root;
	if (p != NULL)
	{
		que.push(p);
		while (!que.empty())
		{
			p = que.front();
			que.pop();
			cout << "------------------------------------------" << "\n" << endl;
			cout << "Employee ID: " << p->empIndexId << "\n" << endl;
			cout << "Record Number: " << p->recNum << "\n" << endl;
			cout << "------------------------------------------" << "\n" << endl;
			if (p->left != NULL)
				que.push(p->left);
			if (p->right != NULL)
				que.push(p->right);
		}
	}

	return;
}

// Balances the BST
bool BST::BalanceTree()
{
	node* temp = new node();
	vector<node*> nodes;
	storeNodes(root, nodes);
	int end = nodes.size();
	end--;
	constructBalancedTree(nodes, 0, end);
	return true;
}

// Helper method, recursively stores nodes in vector
void BST::storeNodes(node* temp, vector<node*> &nodes)
{
	if (temp == NULL)
		return;
	storeNodes(temp->left, nodes);
	nodes.push_back(temp);
	storeNodes(temp->right, nodes);
}

// Helper method, recursively constructs the balanced BST
node* BST::constructBalancedTree(vector<node*>& nodes, int start, int end)
{
	if (start > end)
		return NULL;
	int middle = (start + end) / 2;
	root = nodes[middle];
	root->left = constructBalancedTree(nodes, start, middle-1);
	root->right = constructBalancedTree(nodes, middle+1, end);
	return root;
}

// Inserts records into the RAF
int RandAccessFile::insertRecord(int empID, const char* firstName[20], const char* lastName[20], float monies)
{
	// First, check if record already exists
	if (empIndexTree.search(empID) > 0)
		return -1;
	int recNum = empID % 100;
	EmpData emp1, temp;
	emp1.employeeId = empID;
	strncpy_s(emp1.fname, *firstName, _TRUNCATE);
	strncpy_s(emp1.lname,*lastName, _TRUNCATE);
	emp1.salary = monies;

	// Now, check for possible collision
	fin.seekg(sizeof(temp)*recNum);
	fin.read(reinterpret_cast<char*>(&temp), sizeof(temp));
	
	// If location is empty
	if (temp.employeeId < 0)
	{
		fout.seekp(sizeof(emp1)*recNum);
		fout.write(reinterpret_cast<const char*>(&emp1), sizeof(emp1));
		fout.flush();
		empIndexTree.insert(empID, recNum);
		return recNum;
	}

	// If location is full, check overflow area
	else
	{
		recNum = recNum + 100;
		fin.seekg(sizeof(temp)*recNum);
		fin.read(reinterpret_cast<char*>(&temp), sizeof(temp));
		if (temp.employeeId < 0)
		{
			fout.seekp(sizeof(emp1)*recNum);
			fout.write(reinterpret_cast<const char*>(&emp1), sizeof(emp1));
			fout.flush();
			empIndexTree.insert(empID, recNum);
			return recNum;
		}
	}

	// Attempt to insert by probing
	return insertByProbing(emp1, recNum);
}

// Check remaining overflow area for any open spots
int RandAccessFile::insertByProbing(EmpData emp1, int recNum)
{
	EmpData temp;
	int upper, lower;
	upper = lower = recNum;
	
	// Check upper portion of overflow area
	for (int i = upper; i < 200; i++)
	{
		fin.seekg(sizeof(temp)*i);
		fin.read(reinterpret_cast<char*>(&temp), sizeof(temp));
		if (temp.employeeId < 0)
		{
			fout.seekp(sizeof(emp1)*i);
			fout.write(reinterpret_cast<const char*>(&emp1), sizeof(emp1));
			fout.flush();
			empIndexTree.insert(emp1.employeeId, recNum);
			return recNum;
		}
	}

	// Check lower portion of overflow area
	for (int i = lower; i > 99; i--)
	{
		fin.seekg(sizeof(temp)*i);
		fin.read(reinterpret_cast<char*>(&temp), sizeof(temp));
		if (temp.employeeId < 0)
		{
			fout.seekp(sizeof(emp1)*i);
			fout.write(reinterpret_cast<const char*>(&emp1), sizeof(emp1));
			fout.flush();
			empIndexTree.insert(emp1.employeeId, recNum);
			return recNum;
		}
	}
	
	return -1;
}

/* Retrieve record number fromt he BST
	then flag entry inf RAF for overwrite */
bool RandAccessFile::deleteRecord(int empID)
{
	int recNum = empIndexTree.search(empID);
	if (recNum != -1)
	{
		EmpData temp;
		fin.seekg(sizeof(temp)*recNum);
		fin.read(reinterpret_cast<char*>(&temp), sizeof(temp));
		temp.employeeId = -1;
		fout.seekp(sizeof(temp)*recNum);
		fout.write(reinterpret_cast<const char*>(&temp), sizeof(temp));
		fout.flush();
		empIndexTree.remove(empID);
		cout << "Employee #" << empID << " removed successfully!" << endl;
		return true;
	}
	cout << empID << " not found!" << endl;
	return false;
}

bool RandAccessFile::updateEmpID(int empID, int newID)
{
	int recNum = empIndexTree.search(empID);
	EmpData temp;
	fin.seekg(sizeof(temp)*recNum);
	fin.read(reinterpret_cast<char*>(&temp), sizeof(temp));
	const char* firstName = temp.fname;
	const char* lastName = temp.lname;
	deleteRecord(empID);
	empIndexTree.remove(empID);
	recNum = insertRecord(newID, &firstName, &lastName, temp.salary);
	empIndexTree.insert(newID, recNum);
	return true;
}

bool RandAccessFile::updateEmpFirstName(int empID, const char* fName[20])
{
	int recNum = empIndexTree.search(empID);
	EmpData temp;
	fin.seekg(sizeof(temp)*recNum);
	fin.read(reinterpret_cast<char*>(&temp), sizeof(temp));
	strcpy_s(temp.fname, *fName);
	fout.seekp(sizeof(temp)*recNum); // searching for the address of the record 3
	fout.write(reinterpret_cast<const char*>(&temp), sizeof(temp));
	fout.flush();
	return true;
}

bool RandAccessFile::updateEmpLastName(int empID, const char* lName[20])
{
	int recNum = empIndexTree.search(empID);
	EmpData temp;
	fin.seekg(sizeof(temp)*recNum);
	fin.read(reinterpret_cast<char*>(&temp), sizeof(temp));
	strcpy_s(temp.lname, *lName);
	fout.seekp(sizeof(temp)*recNum);
	fout.write(reinterpret_cast<char*>(&temp), sizeof(temp));
	fout.flush();
	return true;
}

bool RandAccessFile::updateEmpSalary(int empID, float monies)
{
	int recNum = empIndexTree.search(empID);
	EmpData temp;
	fin.seekg(sizeof(temp)*recNum);
	fin.read(reinterpret_cast<char*>(&temp), sizeof(temp));
	temp.salary = monies;
	fout.seekp(sizeof(temp)*recNum);
	fout.write(reinterpret_cast<char*>(&temp), sizeof(temp));
	fout.flush();
	return true;
}

void RandAccessFile::processTransFile(string filePath)
{
	string command, firstName, lastName; 
	const char* fname;
	const char* lname;
	int empID, toUpdate, newID, theNum;
	float salary;
	ifstream fin;
	fin.open(filePath);
	while (fin.good())
	{
		command = " ";
		empID = toUpdate = newID = theNum = 0;
		fin >> command;
		
		if (command == "Insert")
		{
			fin >> empID;
			fin >> firstName;
			fin >> lastName;
			fin >> salary;
			fname = firstName.c_str();
			lname = lastName.c_str();
			insertRecord(empID, &fname, &lname, salary);
		}

		else if (command == "Delete")
		{
			fin >> empID;
			deleteRecord(empID);
		}

		else if (command == "Update")
		{
			fin >> empID;
			fin >> toUpdate;

			//  Update employee id
			if (toUpdate == 1)
			{
				fin >> newID;
				updateEmpID(empID, newID);
			}

			// Update first name
			else if (toUpdate == 2)
			{
				fin >> firstName;
				fname = firstName.c_str();
				updateEmpFirstName(empID, &fname);
			}

			// Update last name
			else if (toUpdate == 3)
			{
				fin >> lastName;
				lname = lastName.c_str();
				updateEmpLastName(empID, &lname);
			}

			// Update salary
			else if (toUpdate = 4)
			{
				fin >> salary;
				updateEmpSalary(empID, salary);
			}
		}

		else if (command == "PrintInOrder")
		{
			cout << "Records via In-Order traversal \n" << endl;
			empIndexTree.printInOrder();
		}

		else if (command == "PrintBreadth")
		{
			cout << "Records via Breadth-First traversal \n" << endl; 
			empIndexTree.printBreath();
		}

		else if (command == "Search")
		{
			fin >> empID;
			theNum = empIndexTree.search(empID);
			if (theNum == -1)
				cout << empID << " is not an employee" << endl;
			else
				cout << "The record number for employe #" << empID << " is: " << theNum << endl;
		}

		else if (command == "BalanceTree")
		{
			empIndexTree.BalanceTree();
		}

	}
	fin.close();
}

int main()
{
	char stuff;
	RandAccessFile test;
	test.processTransFile("test.txt");
	cout << "Do something: " << endl;
	cin >> stuff;
}