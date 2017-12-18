#include "Queue.h"

using namespace std;

template<class T>
Queue<T>::Queue()
{
	//theQ = new vector<T>();
}

template<class T>
void Queue<T>::Push(T item)
{
	theQ.push_back(item);
}

template<class T>
T Queue<T>::Pop()
{
	T temp = theQ[0];
	theQ.erase(theQ.begin());
	return temp;
}

template<class T>
void Queue<T>::ReadAnItem()
{
	T obj;
	cout << "Enter a number: " << endl;
	cin >> obj;
	Push(obj);
}

template<class T>
void Queue<T>::PrintQ()
{
	cout << "Printing the content of the queue: " << "\n" << endl;
	for (int i = 0; i < theQ.size(); i++)
		cout << theQ[i] << endl;
}

int main()
{
	Queue<int> tester;
	tester.Push(1);
	tester.Push(2);
	tester.Push(3);
	tester.Push(4);
	tester.PrintQ();
	tester.Pop();
	tester.PrintQ();

	Queue<Student> sTester;
	Student s1(123456, 2017, "CSUSM");
	Student s2(897465132, 1346, "MiraCosta");
	Student s3(48651, 798465, "Palomar");
	sTester.Push(s1);
	sTester.Push(s2);
	sTester.Push(s3);
	sTester.PrintQ();
	sTester.Pop();
	sTester.PrintQ();

	Queue<Employee> eTester;
	Employee e1(486513, "Tom");
	Employee e2(846513, "Dick");
	Employee e3(1257865, "Harry");
	eTester.Push(e1);
	eTester.Push(e2);
	eTester.Push(e3);
	eTester.PrintQ();
	eTester.Pop();
	eTester.PrintQ();

	cout << "Enter 'X' to close: " << endl;
	char command;
	cin >> command;
	if (command == 'X')
		return 0;
}

