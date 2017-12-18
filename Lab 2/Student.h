/*
	Files: Student.h, Student.cpp
	Author: Gabriel Hunt
	Date Last Modified: 9/18/2017
*/

#include<string>
#include<iostream>
#include<vector>
using namespace std;

class Student
{
public:
	Student();
	Student(string name, int age, int stID);
	~Student();
	virtual void printInfo() = 0;
	void printDifferentObjects(vector <Student*> roster);

protected:
	string name;
	int age, studentID;
};

class Undergraduate : public Student
{
private:
	int year, coursesCompleted;

public:
	Undergraduate();
	Undergraduate(int year, int numCourses, string name, int age, int id);
	void printInfo();
};

class Graduate : public Student
{
private:
	string advisorName, thesisTitle;

public:
	Graduate();
	Graduate(string advisorName, string title, string name, int age, int id);
	void printInfo();
};

