#include<iostream>
#include<string>
#include<fstream>

using namespace std;


struct Student
{
	int stId;
	string userid;
	string password;
	Student *next;
	Student()
	{
		stId = 0;
		password = userid = " ";
		next = NULL;
	}
	Student(int sId, string uId, string pass)
	{
		stId = sId;
		userid = uId;
		password = pass;
		next = NULL;
	}
};


class LinkedList
{
protected:
	Student *head;
	Student *tail;
	int size;

public:
	LinkedList()
	{
		head = tail = NULL;
		size = 0;
	}
	bool add(int studentId, string user, string pass);
	bool remove(int sId);
	bool printAll();
	bool print(int sId);
	bool contains(int sId);
	bool modifyPass(int sId, string newPass);
	int getSize()
	{
		return size;
	}
	Student* getHead()
	{
		return head;
	}
};

class Authorization
{
protected:
	LinkedList *list;
public: 
	Authorization()
	{
		list = new LinkedList();
	}
	bool AddMember(int studentId, string user, string  pass);
	bool RemoveMember(int studentId);
	bool SearchId(int StudentId);
	bool ChangePassword(int userId, string newPass);
	bool PrintAll();
	bool PrintRecord(int StudentId);;
	bool ProcessTransaction();
	bool SaveConfiguration();
	bool LoadConfiguration();
};