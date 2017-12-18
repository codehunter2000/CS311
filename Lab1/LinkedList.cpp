#include "LinkedList.h"
#include<iostream>
#include<string>

using namespace std;


int main()
{
	Authorization main;
	main.LoadConfiguration();
	while (true)
	{
		cout << "1)	Processing a transaction file \n"
			<< "2)	Saving the information in the configuration file \n"
			<< "3)	Quit/Exit \n : " << endl;
		int selection;
		cin >> selection;
		if (selection == 1)
			main.ProcessTransaction();
		if (selection == 2)
			main.SaveConfiguration();
		if (selection == 3)
		{
			main.SaveConfiguration();
			return 0;
		}
	}
}

bool LinkedList::add(int studentId, string user, string pass)
{
	if (contains(studentId))
		return true;
	
	Student *temp = new Student(studentId, user, pass);
	if (size == 0)
	{
		head = temp;
		tail = temp;
		temp = NULL;
		size++;
		return true;
	}

	else
	{
		tail->next = temp;
		tail = temp;
		size++;
		return true;
	}
}


bool LinkedList::remove(int sId)
{
	if (!contains(sId))
		return false;

	Student *current = new Student();
	Student *previous = new Student();
	
	if (sId == head->stId)
	{
		current = head;
		head = head->next;
		delete current;
		size--;
		return true;
	}

	current = head->next;
	previous = head;

	for (int i = 0; i < size; i++)
	{
		if (sId == current->stId)
		{
			previous->next = current->next;
			size--;
			return true;
		}

		previous = current;
		current = current->next;
	}
	return false;
}

bool LinkedList::printAll()
{
	if (size == 0)
		return false;

	Student *temp = new Student;
	temp = head;
	for (int i = 0; i < size; i++)
	{
		cout << "Student ID: " << temp->stId << endl;
		cout << "User ID: " << temp->userid << endl;
		cout << "Password: " << temp->password << endl;
		cout << "\n" << endl;
		temp = temp->next;
	}

	return true;
}

bool LinkedList::print(int sId)
{
	if (!contains(sId))
		return false;

	Student *temp = new Student;
	temp = head;
	for (int i = 0; i < size; i++)
	{
		if (temp->stId == sId)
		{
			cout << "Student ID: " << temp->stId << endl;
			cout << "User ID: " << temp->userid << endl;
			cout << "Password: " << temp->password << endl;
			cout << "\n" << endl;
			return true;
		}
		temp = temp->next;
	}
	return false;
}

bool LinkedList::contains(int sId)
{
	if (size == 0)
		return false;
	
	Student *temp = new Student;
	temp = head;
	for (int i = 0; i < size; i++)
	{
		if (temp->stId == sId)
			return true;
		temp = temp->next;
	}
	return false;
}

bool LinkedList::modifyPass(int sId, string newPass)
{
	if (!contains(sId))
		return false;

	Student *temp = new Student;
	temp = head;
	for (int i = 0; i < size; i++)
	{
		if (temp->stId == sId)
		{
			temp->password = newPass;
			return true;
		}
		temp = temp->next;
	}
	return false;
}

bool Authorization::AddMember(int studentId, string user, string pass)
{
	list->add(studentId, user, pass);
	return true;
}

bool Authorization::RemoveMember(int studentId)
{
	return list->remove(studentId);
}

bool Authorization::SearchId(int StudentId)
{
	return list->contains(StudentId);
}

bool Authorization::ChangePassword(int userId, string newPass)
{
	return list->modifyPass(userId, newPass);
}

bool Authorization::PrintAll()
{
	return list->printAll();
}

bool Authorization::PrintRecord(int StudentId)
{
	return list->print(StudentId);
}

bool Authorization::ProcessTransaction()
{
	string filepath, command, uid, pass;
	int sid;
	cout << "Please enter the file path: " << endl;
	cin >> filepath;
	ifstream fin;
	fin.open(filepath);
	if (!fin.good())
	{
		cout << "Bad file path!" << endl;
		return false;
	}

	while (fin.good())
	{
		fin >> command;

		if (command == "Insert")
		{
			fin >> sid;
			fin >> uid;
			fin >> pass;
			AddMember(sid, uid, pass);
		}

		if (command == "Delete")
		{
			fin >> sid;
			RemoveMember(sid);
		}

		if (command == "Find")
		{
			fin >> sid;
			SearchId(sid);
		}

		if (command == "Print")
		{
			PrintAll();
		}

		if (command == "PrintRecord ")
		{
			fin >> sid;
			PrintRecord(sid);
		}

		if (command == "ChangePassword")
		{
			fin >> sid;
			fin >> pass;
			ChangePassword(sid, pass);
		}

	}
	fin.close();
	return true;
}

bool Authorization::SaveConfiguration()
{
	string filepath = "SaveConfig.txt";
	ofstream fout;
	fout.open(filepath);
	if (list->getSize() == 0)
		return false;
	Student *temp = new Student();
	temp = list->getHead();
	for (int i = 0; i < list->getSize(); i++)
	{
		fout << temp->stId << endl;
		fout << temp->userid << endl;
		fout << temp->password << endl;
		temp = temp->next;
	}
	fout.close();
	return true;
}

bool Authorization::LoadConfiguration()
{
	string filepath = "SaveConfig.txt";
	int sid;
	string uid, pass;
	ifstream fin;
	fin.open(filepath);
	if (!fin.good())
		return false;

	while (fin.good())
	{
		fin >> sid;
		fin >> uid;
		fin >> pass;
		AddMember(sid, uid, pass);
	}
	fin.close();

	return true;
}

