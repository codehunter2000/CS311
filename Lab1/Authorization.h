#include<iostream>
#include<string>
#include<fstream>

using namespace std;

class Node {
public:
	int sID;
	string uID, pass;
	Node* next;
	Node(int sID, string uID, string pass)
	{
		this->sID = sID;
		this->uID = uID;
		this->pass = pass;
		next = NULL;
	}
};

class Authorization
{
private:
	Node* top;

public:
	Authorization();
	bool addMember(int id, string userID, string pass);
	bool removeMember(int id);
	bool searchID(int id);
	bool changePassword(int id, string pass);
	bool printAll();
	bool printRecord(int id);
	bool processTransaction();
	bool saveConfiguration();
	bool loadConfiguration();
};
