#include "SingleElementIndexing.h"

int main()
{
	SingleElementIndexing main;
	int selection;
	
	while (true)
	{
		cout << "1) Read a Transaction file" << endl;
		cout << "2) Save Current Configuration" << endl;
		cout << "3) Quit " << endl;
		cout << ": " << endl;
		cin >> selection;

		if (selection == 1)
		{
			main.processTrasaction();
		}


		if (selection == 2)
		{
			main.saveConfig();
		}

		if (selection == 3)
		{
			main.saveConfig();
			return 0;
		}
	}
}

bool SingleElementIndexing::addEmp(int id, string uName, string pass)
{
	if (!validID(id))
		return false;
	if (alreadyInList(id))
		return false;

	int index = id % 10;

	if (A[index] == NULL)
	{
		Block *newBlock = new Block;
		A[index] = newBlock;
		Employee *toAdd = new Employee(id, uName, pass);
		newBlock->top = toAdd;
		newBlock->tail = toAdd;
		newBlock->count++;
		return true;
	}

	else // if: A[index] != NULL
	{
		Block *temp = new Block;
		temp = A[index];
		Employee *e = new Employee;
		Employee *toAdd = new Employee(id, uName, pass);
		if (temp->count < 4)	// Block not full
		{
			e = temp->tail;
			e->nextEmp = toAdd;
			temp->tail = toAdd;
			temp->count++;
			return true;
		}

		else // Block full
		{
			if (temp->nextBlock == NULL)
			{
				Block *newBlock = new Block;
				temp->nextBlock = newBlock;
				newBlock->top = toAdd;
				newBlock->tail = toAdd;
				newBlock->count++;
				return true;
			}

			else
			{
				temp = temp->nextBlock;
				Employee *e = new Employee;
				e = temp->tail;
				e->nextEmp = toAdd;
				temp->tail = toAdd;
				temp->count++;
				return true;
			}
		}
	}

	return false;
}

bool SingleElementIndexing::printABlock(int blockNum)
{
	Block *bTemp = new Block;
	Employee *eTemp = new Employee;

	if (A[blockNum] == NULL)
		return false;

	bTemp = A[blockNum];
	eTemp = bTemp->top;
	for (int i = 0; i < bTemp->count; i++)
	{
		cout << "===================================================" << "\n"
			<< "ID: " << eTemp->empID << "\n" << "User Name: " << eTemp->userName
			<< "\n" << "Password: " << eTemp->password << "\n";
		eTemp = eTemp->nextEmp;
	}

	if (bTemp->nextBlock != NULL)
	{
		bTemp = bTemp->nextBlock;
		eTemp = bTemp->top;
		for (int i = 0; i < bTemp->count; i++)
		{
			cout << "===================================================" << "\n"
				<< "ID: " << eTemp->empID << "\n" << "User Name: " << eTemp->userName
				<< "\n" << "Password: " << eTemp->password << "\n";
			eTemp = eTemp->nextEmp;
		}
	}

	return true;
}

bool SingleElementIndexing::printAll()
{
	Block *bTemp = new Block;
	Employee *eTemp = new Employee;
	
	for (int i = 0; i < 4; i++)
	{
		if (A[i] != NULL)
		{
			bTemp = A[i];
			eTemp = bTemp->top;
			for (int j = 0; j < bTemp->count; j++)
			{
				cout << "===================================================" << "\n"
					<< "ID: " << eTemp->empID << "\n" << "User Name: " << eTemp->userName
					<< "\n" << "Password: " << eTemp->password << "\n";
				eTemp = eTemp->nextEmp;
			}

			if (bTemp->nextBlock != NULL)
			{
				bTemp = bTemp->nextBlock;
				eTemp = bTemp->top;
				cout << bTemp->count;
				for (int j = 0; j < bTemp->count; j++)
				{
					cout << "===================================================" << "\n"
						<< "ID: " << eTemp->empID << "\n" << "User Name: " << eTemp->userName
						<< "\n" << "Password: " << eTemp->password << "\n";
					eTemp = eTemp->nextEmp;
				}
			}
		}
	}

	return true;
	
}

bool SingleElementIndexing::searchID(int id)
{
	if (!validID(id))
		return false;
	if (inFirstBlock(id))
		return true;
	if (inSecondBlock(id))
		return true;

	return false;
}

bool SingleElementIndexing::deleteEmployee(int id)
{
	if (!validID(id))
		return false;
	if (!alreadyInList(id))
		return false;
	
	int index = id % 10;

	if (A[index] == NULL)
		return false;

	Block *bTemp = new Block;
	Employee *eTemp = new Employee;
	Employee *ePrev = new Employee;
	bTemp = A[index];
	eTemp = bTemp->top;
	ePrev = bTemp->top;

	if (id == eTemp->empID)
	{
		bTemp->top = eTemp->nextEmp;
		bTemp->count--;
		return true;
	}

	eTemp = eTemp->nextEmp;
	for (int i = 1; i < bTemp->count; i++)
	{
		if (id == eTemp->empID)
		{
			ePrev->nextEmp = eTemp->nextEmp;
			bTemp->count--;
			return true;
		}
		eTemp = eTemp->nextEmp;
		ePrev = ePrev->nextEmp;
	}

	if (bTemp->nextBlock != NULL)
	{
		bTemp = bTemp->nextBlock;
		eTemp = bTemp->top;
		ePrev = bTemp->top;

		if (id == eTemp->empID)
		{
			bTemp->top = eTemp->nextEmp;
			bTemp->count--;
			return true;
		}

		eTemp = eTemp->nextEmp;
		for (int i = 1; i < bTemp->count; i++)
		{
			if (id == eTemp->empID)
			{
				ePrev->nextEmp = eTemp->nextEmp;
				bTemp->count--;
				return true;
			}
			eTemp = eTemp->nextEmp;
			ePrev = ePrev->nextEmp;
		}
	}

	return false;
}

bool SingleElementIndexing::changeEmployeeID(int oldId, int newId)
{
	if (!validID(oldId))
		return false;
	if (!validID(newId))
		return false;
	if (!alreadyInList(oldId))
		return false;

	string uId, pass;
	bool found = false;;
	Block *bTemp = new Block;
	Employee *eTemp = new Employee;
	int index = oldId % 10;
	if (A[index] == NULL)
		return false;
	bTemp = A[index];
	eTemp = bTemp->top;
	for (int i = 0; i < bTemp->count; i++)
	{
		if (eTemp->empID == oldId)
		{
			uId = eTemp->userName;
			pass = eTemp->password;
			deleteEmployee(oldId);
			found = true;
		}
		eTemp = eTemp->nextEmp;
	}

	if (found == false && bTemp->nextBlock != NULL)
	{
		bTemp = bTemp->nextBlock;
		eTemp = bTemp->top;
		for (int i = 0; i < bTemp->count; i++)
		{
			if (eTemp->empID == oldId)
			{
				uId = eTemp->userName;
				pass = eTemp->password;
				deleteEmployee(oldId);
				found = true;
			}
			eTemp = eTemp->nextEmp;
		}
	}

	return addEmp(newId, uId, pass);
}

bool SingleElementIndexing::changeUserName(int id, string newName)
{
	if (!validID(id))
		return false;
	if (!alreadyInList(id))
		return false;

	int index = id % 10;
	if (A[index] == NULL)
		return false;

	Block *bTemp = new Block;
	Employee *eTemp = new Employee;
	bTemp = A[index];
	eTemp = bTemp->top;
	for (int i = 0; i < bTemp->count; i++)
	{
		if (eTemp->empID == id)
		{
			eTemp->userName = newName;
			return true;
		}
		eTemp = eTemp->nextEmp;
	}

	if (bTemp->nextBlock != NULL)
	{
		bTemp = bTemp->nextBlock;
		eTemp = bTemp->top;
		for (int i = 0; i < bTemp->count; i++)
		{
			if (eTemp->empID == id)
			{
				eTemp->userName = newName;
				return true;
			}
			eTemp = eTemp->nextEmp;
		}
	}

	return false;
}

bool SingleElementIndexing::changePassword(int id, string newPass)
{
	if (!validID(id))
		return false;
	if (!alreadyInList(id))
		return false;
	
	int index = id % 10;
	if (A[index] == NULL)
		return false;

	Block *bTemp = new Block;
	Employee *eTemp = new Employee;
	bTemp = A[index];
	eTemp = bTemp->top;
	for (int i = 0; i < bTemp->count; i++)
	{
		if (eTemp->empID == id)
		{
			eTemp->password = newPass;
			return true;
		}
		eTemp = eTemp->nextEmp;
	}

	if (bTemp->nextBlock != NULL)
	{
		bTemp = bTemp->nextBlock;
		eTemp = bTemp->top;
		for (int i = 0; i < bTemp->count; i++)
		{
			if (eTemp->empID == id)
			{
				eTemp->password = newPass;
				return true;
			}
			eTemp = eTemp->nextEmp;
		}
	}

	return false;
}

bool SingleElementIndexing::loadConfig()
{
	string command, uId, pass;
	int eId, blockNum, whichToChange, newID;
	ifstream fin;
	fin.open(filepath);
	while (fin.good())
	{
		fin >> command;
		if (command == "Insert")
		{
			fin >> eId;
			fin >> uId;
			fin >> pass;
			addEmp(eId, uId, pass);
		}

		if (command == "Delete")
		{
			fin >> eId;
			deleteEmployee(eId);
		}

		if (command == "Modify")
		{
			fin >> eId;
			fin >> whichToChange;

			if (whichToChange == 1)
			{
				fin >> newID;
				changeEmployeeID(eId, newID);
			}

			if (whichToChange == 2)
			{
				fin >> uId;
				changeUserName(eId, uId);
			}

			if (whichToChange == 3)
			{
				fin >> pass;
				changePassword(eId, pass);
			}
		}

		if (command == "PrintAll")
		{
			printAll();
		}

		if (command == "PrintABlock")
		{
			fin >> blockNum;
			printABlock(blockNum);
		}

		if (command == "Save")
		{
			saveConfig();
		}
	}
	return true;
}

bool SingleElementIndexing::saveConfig()
{
	Block *bTemp = new Block;
	Employee *eTemp = new Employee;
	ofstream fout;
	fout.open(filepath);
	for (int i = 0; i < 4; i++)
	{
		if (A[i] != NULL)
		{
			bTemp = A[i];
			eTemp = bTemp->top;
			for (int j = 0; j < bTemp->count; j++)
			{
				fout << eTemp->empID << endl;
				fout << eTemp->userName << endl;
				fout << eTemp->password << endl;
				eTemp = eTemp->nextEmp;
			}

			if (bTemp->nextBlock != NULL)
			{
				bTemp = bTemp->nextBlock;
				eTemp = bTemp->top;
				for (int j = 0; j < bTemp->count; j++)
				{
					fout << eTemp->empID << "\t";
					fout << eTemp->userName << "\t";
					fout << eTemp->password << "\t";
					fout << "\n" << endl;
					eTemp = eTemp->nextEmp;
				}
			}
		}
	}
	
	return true;
}

bool SingleElementIndexing::processTrasaction()
{
	string command, uId, pass;
	int eId, blockNum, whichToChange;
	string userPath;
	ifstream fin;
	cout << "Please enter the file path: " << endl;
	cin >> userPath;
	fin.open(userPath);
	while (fin.good())
	{
		fin >> command;
		if (command == "Insert")
		{
			fin >> eId;
			fin >> uId;
			fin >> pass;
			addEmp(eId, uId, pass);
		}

		if (command == "Delete")
		{
			fin >> eId;
			deleteEmployee(eId);
		}

		if (command == "Modify")
		{
			fin >> eId;
			fin >> whichToChange;
			if (whichToChange == 2)
			{
				fin >> uId;
				changeUserName(eId, uId);
			}

			if (whichToChange == 3)
			{
				fin >> pass;
				changePassword(eId, pass);
			}
		}

		if (command == "PrintAll")
		{
			printAll();
		}

		if (command == "PrintABlock")
		{
			fin >> blockNum;
			printABlock(blockNum);
		}

		if (command == "Save")
		{
			saveConfig();
		}
	}
	return true;
}

bool SingleElementIndexing::validID(int id)
{
	int index = id % 10;
	if (index < 0 || index > 3)
		return false;
	return true;
}

bool SingleElementIndexing::alreadyInList(int id)
{
	if (inFirstBlock(id))
		return true;
	if (inSecondBlock(id))
		return true;
	return false;
}

bool SingleElementIndexing::inFirstBlock(int id)
{
	Block *bTemp = new Block;
	Employee *eTemp = new Employee;
	int index = id % 10;
	if (A[index] == NULL)
		return false;
	bTemp = A[index];
	eTemp = bTemp->top;
	if (eTemp == NULL)
		return false;
	for (int i = 0; i < bTemp->count; i++)
	{
		if (eTemp->empID == id)
			return true;
		eTemp = eTemp->nextEmp;
	}
	return false;
}

bool SingleElementIndexing::inSecondBlock(int id)
{
	Block *bTemp = new Block;
	Employee *eTemp = new Employee;
	int index = id % 10;
	if (A[index] == NULL)
		return false;
	bTemp = A[index];
	if (bTemp->nextBlock == NULL)
		return false;

	bTemp = bTemp->nextBlock;
	eTemp = bTemp->top;
	if (eTemp == NULL)
		return false;
	for (int i = 0; i < bTemp->count; i++)
	{
		if (eTemp->empID == id)
			return true;
		eTemp = eTemp->nextEmp;
	}
	return false;
}