/*
	Files: Queue.h, Queue.cpp
	Author: Gabriel Hunt
	Date Last Modified: 9/25/2017
*/


#include<string>
#include<vector>
#include<iostream>

using namespace std;

class Employee
{
protected:
	long empId;
	string empName;
	string email;
public:
	Employee() {}
	Employee(long i, string n) { empName = n, empId = i; email = "Unknow"; }
	friend ostream & operator<<(ostream & output, const Employee & em)
	{
		output << "ID: " << em.empId << "\t" << "Name: " << em.empName << "\t" << "Email: " << em.email << "\n";
		return output;
	}


};


class Student
{
private:
	long	stId;
	int	year;
	string	email;
	string	schoolName;
public:
	Student() {}
	Student(long i, int y, string sn) { stId = i; year = y; email = "Unknown"; schoolName = sn; }
	friend ostream & operator<<(ostream & output, const Student & st)
	{
		output << "ID: " << st.stId << "\t" << "Year: " << st.year <<  "\n" << "Email: " << st.email 
			<< "\t" << "School: " << st.schoolName << "\n";
		return output;
	}
};

template<class T>
class Queue
{

private:
	vector<T> theQ;
public:
	Queue();
	void Push(T item);
	T Pop();
	void ReadAnItem();
	void PrintQ();
	friend ostream& operator<<(ostream& os, const Student& st);
	friend ostream& operator<<(ostream& os, const Employee& em);

};