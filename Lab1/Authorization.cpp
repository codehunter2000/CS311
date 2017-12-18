#include "Authorization.h"

Authorization::Authorization()
{
	top = NULL;
}

bool Authorization::addMember(int studentID, string user, string pass)
{
	bool wasAdded = false;
	Node* p = top;
	Node* q = new Node(studentID, user, pass);
	if (top == NULL)
	{
		top = q;
		wasAdded = true;
	}

	else
	{
		while (p->next != NULL)
		{
			p = p->next;
		}

		p->next = q;
		wasAdded = true;
	}

	return wasAdded;
}

bool Authorization::removeMember(int studentID)
{
	bool wasRemoved = false;
	Node* p = top;
	Node* prev = top;

	if (top == NULL)
		return wasRemoved;

	else
	{
		while (p->next != NULL)
		{
			if (p->sID == studentID)
			{
				p = p->next;
				prev->next = p;
				wasRemoved = true;
				return wasRemoved;
			}

			p = p->next;
		}
	}
	return wasRemoved;
}

bool Authorization::searchID(int studentID)
{
	bool wasFound = false;
	Node* p = top;

	if (top == NULL)
		return wasFound;

	else
	{
		while (p->next != NULL)
		{
			if (p->sID == studentID)
			{
				wasFound = true;
				break;
			}

			p = p->next;
		}
	}
	return wasFound;
}

bool Authorization::changePassword(int id, string pass)
{
	bool wasChanged = false;
	Node* p = top;

	if (top == NULL)
		return wasChanged;

	else
	{
		while (p->next != NULL)
		{
			if (p->sID == id)
			{
				p->pass = pass;
				wasChanged = true;
				break;
			}

			p = p->next;
		}
	}

	return wasChanged;
}

bool Authorization::printAll()
{
	bool wasPrinted = false;
	Node* p = top;

	if (top == NULL)
		return wasPrinted;

	else
	{
		wasPrinted = true;
		while (p->next != NULL)
		{
			cout << "Student ID: " << p->sID << "\t User ID: " << p->uID << "\t Password: " << p->pass << endl;
			p = p->next;
		}
	}
	return wasPrinted;
}

bool Authorization::printRecord(int userID)
{
	bool wasPrinted = false;
	Node* p = top;

	if (top == NULL)
		return wasPrinted;

	else
	{
		while (p->next != NULL)
		{
			if (p->sID == userID)
			{
				cout << "Student ID: " << p->sID << "\t User ID: " << p->uID << "\t Password: " << p->pass << endl;
				wasPrinted = true;
				break;
			}
			p = p->next;
		}
	}

	return wasPrinted;
}


bool Authorization::processTransaction()
{
	bool wasProcessed = false;
	string filePath, command, uName, uPass;
	int studentID;
	cout << "Please enter the path of the file you with to process: " << endl;
	cin >> filePath;
	ifstream fin;
	fin.open(filePath);
	wasProcessed = true;
	while (fin.good())
	{
		fin >> command;

		if (command == "Insert")
		{
			fin >> studentID >> uName >> uPass;
			addMember(studentID, uName, uPass);
		}

		if (command == "Delete")
		{
			fin >> studentID;
			removeMember(studentID);
		}

		if (command == "Find")
		{
			fin >> studentID;
			searchID(studentID);
		}

		if (command == "Print")
		{
			printAll();
		}

		if (command == "PrintRecord")
		{
			fin >> studentID;
			printRecord(studentID);
		}

		if (command == "ChangePassword")
		{
			fin >> studentID >> uPass;
			changePassword(studentID, uPass);
		}
	}

	fin.close();
	return wasProcessed;
}

bool Authorization::saveConfiguration()
{
	bool wasSaved = false;
	Node* p = top;
	string filePath = "SaveConfig.txt";
	ofstream fileOut;
	fileOut.open(filePath);
	
	if (top == NULL)
		return wasSaved;

	else
	{
		while (p->next != NULL)
		{
			fileOut << p->sID << " " << p->uID << " " << p->pass;
			p = p->next;
		}
		
		wasSaved = true;
		fileOut.close();
	}

	return wasSaved;
}

bool Authorization::loadConfiguration()
{
	bool wasLoaded = false;
	string filePath = "SaveConfig.txt";
	Node* p = top;
	ifstream fin;
	string uID, pass;
	int sID;
	fin.open(filePath);

	while (fin.good())
	{
		fin >> sID >> uID >> pass;
		addMember(sID, uID, pass);
		wasLoaded = true;
	}

	fin.close();

	return wasLoaded;
}


int main()
{
	Authorization test;
	test.loadConfiguration();
	bool done = false;
	string command, filePath;
	while (!done)
	{
		cout << "Please select one of the following: " << endl;
		cout << "1) Processing a transaction file" << endl;
		cout << "2)	Saving the information in the configuration file" << endl;
		cout << "3)	Quit/Exit" << endl;
		cout << ": ";
		cin >> command;

		if (command == "1")
		{
			test.processTransaction();
		}

		if (command == "2")
		{
			test.saveConfiguration();
		}

		if (command == "3")
		{
			test.saveConfiguration();
			done = true;
		}
	}
}