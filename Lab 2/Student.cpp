#include "Student.h"
#include<string>
#include<iostream>
#include<vector>

using namespace std;


Student::Student()
{
}

Student::Student(string name, int age, int stID)
{
	this->name = name;
	this->age = age;
	this->studentID = stID;
}


Student::~Student()
{
}

void Student::printInfo()
{

}

int main()
{
	vector <Student*> roster;
	Graduate mJ("Keith Richards", "You Can't Always Get What You Want", "Mick Jagger", 26, 1234);
	roster.push_back(&mJ);
	Graduate pS("Art Garfunkel", "Kodachrome", "Paul Simon", 32, 9876);
	roster.push_back(&pS);
	Undergraduate jF(3, 62, "John Fogerty", 24, 1654);
	roster.push_back(&jF);
	Undergraduate nY(2, 27, "Neil Young", 25, 5731);
	roster.push_back(&nY);
	Graduate eJ("Bernie Taupin", "Rocket Man", "Elton John", 25, 3426);
	roster.push_back(&eJ);
	Undergraduate tester;
	tester.printDifferentObjects(roster);
	cout << "Press 'X' to exit: " << endl;
	char command;
	cin >> command;
	if (command == 'X')
	{
		return 0;
	}

}

Undergraduate::Undergraduate() :Student()
{
	
}

Undergraduate::Undergraduate(int year, int numCourses, string name, int age, int id)
	:Student(name, age, id)
{
	this->year = year;
	this->coursesCompleted = numCourses;
	this->name = name;
	this->age = age;
	this->studentID = id;
}

void Undergraduate::printInfo()
{
	cout << "Undergraduate Student: " << name << "\t" << "Age: " << age << "\t" << "ID: " << studentID << endl;
	cout << "Year: " << year << "\t" << "Number of courses: " << coursesCompleted << endl;

}

Graduate::Graduate() :Student()
{
}

Graduate::Graduate(string advisorName, string title, string name, int age, int id)
	:Student(name, age, id)
{
	this->advisorName = advisorName;
	this->thesisTitle = title;
	this->name = name;
	this->age = age;
	this->studentID = id;
}

void Graduate::printInfo()
{
	cout << "Graduate Student: " << name << "\t" << "Age: " << age << "\t" << "ID: " << studentID << endl;
	cout << "Advisor: " << advisorName << "\t" << "Thesis: " << thesisTitle << endl;
}

void Student::printDifferentObjects(vector <Student*> roster)
{
	
	for (int i = 0; i < roster.size(); i++)
	{
		roster[i]->printInfo();
	}
}
