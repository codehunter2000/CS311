#include "SingleElementIndexing.h"


/*
	Notes:
		1 -- Rewrtie delete method. You don't need a for loop stupid, 
				they already gave you the id number!!!!!
*/


int main()
{
	SingleElementIndexing main;
	main.addEmp(123450,	"ahadaegh",	"CS211ah");
	main.printAll();
	cout << "Press any key to exit..." << endl;
	char input;
	cin >> input;
	
	
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
		Block firstBlock;
		ePtr firstElement = new Employee(id, uName, pass);
		firstBlock.top = firstElement;
		A[index] = &firstBlock;
		firstBlock.count = firstBlock.count + 1;
		return true;
	}

	else // if: A[index] != NULL
	{		
		ePtr toAdd = new Employee(id, uName, pass);
		blockPtr p = A[id%10];
		ePtr q;
		if (A[index]->nextBlock == NULL)
		{
			while (p->nextBlock != NULL)
			{
				p = p->nextBlock;
			}

			if (p->count != 4)
			{
				q = p->top;
				while (q->nextEmp != NULL)
				{
					q = q->nextEmp;
				}

				q->nextEmp = toAdd;
				p->count = p->count + 1;
				return true;
			}

			else
			{
				Block newBlock;
				newBlock.top = toAdd;
				newBlock.count = newBlock.count + 1;
				return true;
			}
		}
	}
}

bool SingleElementIndexing::printAll()
{
	
	blockPtr p;
	ePtr q;
	for (int i = 0; i < 4; i++)
	{
		p = A[i];
		while (p != NULL)
		{
			if (p->top == NULL)
				break;
			q = p->top;
			while (q != NULL)
			{
				cout << q;
				q = q->nextEmp;
			}

			p = p->nextBlock;
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

	blockPtr p;
	ePtr q, prev;
	

	for (int i = 0; i < 4; i++)
	{
		p = A[i];
		while (p != NULL)
		{
			if (p->top->empID == id)
			{
				q = p->top;
				q = q->nextEmp;
				p->top = q;
				p->count--;
				return true;
			}

			else
			{
				q = p->top;
				q = q->nextEmp;
				prev = p->top;
				while (q != NULL)
				{
					if (id == q->empID)
					{
						q = q->nextEmp;
						prev->nextEmp = q;
						p->count--;
						return true;
					}

					q = q->nextEmp;
					prev = prev->nextEmp;
				}

				p = p->nextBlock;
			}
		}
	}

	return false;
}

bool SingleElementIndexing::changeUserName(int id, string newName)
{
	if (!validID(id))
		return false;
	if (!alreadyInList(id))
		return false;

	int index = id % 10;
	blockPtr p = A[index];
	ePtr q = p->top;

	do
	{
		do
		{
			if (q->empID == id)
			{
				q->userName = newName;
				return true;
			}

			q = q->nextEmp;

		} while (q != NULL);

		p = p->nextBlock;

	} while (p != NULL);


	return false;
}

bool SingleElementIndexing::changePassword(int id, string newPass)
{
	if (!validID(id))
		return false;
	if (!alreadyInList(id))
		return false;

	int index = id % 10;
	blockPtr p = A[index];
	ePtr q = p->top;

	do
	{
		do
		{
			if (q->empID == id)
			{
				q->password = newPass;
				return true;
			}

			q = q->nextEmp;

		} while (q != NULL);

		p = p->nextBlock;

	} while (p != NULL);

	return false;
}

bool SingleElementIndexing::loadConfig()
{
	return false;
}

bool SingleElementIndexing::saveConfig()
{
	return false;
}

bool SingleElementIndexing::processTrasaction()
{
	return false;
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
	blockPtr p = A[id % 10];
	ePtr q;
	if (p == NULL)
		return false;
	else
	{
		q = p->top;
		while (q != NULL)
		{
			if (q->empID == id)
				return true;
			else
				q = q->nextEmp;
		}
	}
	return false;
}

bool SingleElementIndexing::inSecondBlock(int id)
{
	blockPtr p = A[id % 10];
	ePtr q;
	if (p == NULL)
		return false;
	if (p->nextBlock == NULL)
		return false;
	else
	{
		p = p->nextBlock;
		q = p->top;
		while (q != NULL)
		{
			if (q->empID == id)
				return true;
			else
				q = q->nextEmp;
		}
	}
	return false;
}
