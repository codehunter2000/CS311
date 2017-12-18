
/*
	Author: Gabriel Hunt
	Files: GroceryItem.h, GroceryItem.cpp
	Date Last Modified: October 25, 2017

*/

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;


class GroceryItem
{
protected:
	string	itemName;
	float	temPrice;
	int	qtyOnHand;
	int	qtyPurchased;
public:
	virtual void PrintGrocery() = 0;
	string getItemName()
	{
		return itemName;
	}
	void setItemName(string name)
	{
		itemName = name;
	}
	float getTemPrice()
	{
		return temPrice;
	}
	void setTemPrice(float price)
	{
		temPrice = price;
	}
	int getQtyOnHand()
	{
		return qtyOnHand;
	}
	void setQtyOnHand(int qt)
	{
		qtyOnHand = qt;
	}
	int getQtyPurchased()
	{
		return qtyPurchased;
	}
	void setQtyPurchased(int qt)
	{
		qtyPurchased = qt;
	}
};
//-----------------------------
class Dairy : public GroceryItem
{
protected:
	float temperature;
public:
	Dairy(string name, float price, int onHand, int numSold, float temp)
	{
		itemName = name;
		temPrice = price;
		qtyOnHand = onHand;
		qtyPurchased = numSold;
		temperature = temp;
	}
	float getTemperature()
	{
		return temperature;
	}
	void setTemperature(float temp)
	{
		temperature = temp;
	}
	virtual void PrintGrocery()
	{
		cout << "\n" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "Name: " << itemName << "\n" << endl;
		cout << "Temperature: " << temperature << "\n" << endl;
		cout << "Price: " << temPrice << "\n" << endl;
		cout << "Amount In Stock: " << qtyOnHand << "\n" << endl;
		cout << "Amount Purchased: " << qtyPurchased << "\n" << endl;
	}
};
//-----------------------------
class Cereal : public GroceryItem
{
protected:
	int aisle;
public:
	Cereal(string name, float price, int onHand, int numSold, int location)
	{
		itemName = name;
		temPrice = price;
		qtyOnHand = onHand;
		qtyPurchased = numSold;
		aisle = location;
	}
	int getAisle()
	{
		return aisle;
	}
	void setAisle(int aisle)
	{
		this->aisle = aisle;
	}
	virtual void PrintGrocery()
	{
		cout << "\n" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "Name: " << itemName << "\n" << endl;
		cout << "Aisle: " << aisle << "\n" << endl;
		cout << "Price: " << temPrice << "\n" << endl;
		cout << "Amount In Stock: " << qtyOnHand << "\n" << endl;
		cout << "Amount Purchased: " << qtyPurchased << "\n" << endl;
	}
};
//-----------------------------
class Bread : public GroceryItem
{
protected:
	float weight;
public:
	Bread(string name, float price, int onHand, int numSold, float weight)
	{
		itemName = name;
		temPrice = price;
		qtyOnHand = onHand;
		qtyPurchased = numSold;
		this->weight = weight;
	}
	float getWeight()
	{
		return weight;
	}
	void setWeight(float weight) {
		this->weight = weight;
	}
	virtual void PrintGrocery()
	{
		cout << "\n" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "Name: " << itemName << "\n" << endl;
		cout << "Weight: " << weight << "\n" << endl;
		cout << "Price: " << temPrice << "\n" << endl;
		cout << "Amount In Stock: " << qtyOnHand << "\n" << endl;
		cout << "Amount Purchased: " << qtyPurchased << "\n" << endl;
	}
};
//-----------------------------
class Jam : public GroceryItem
{
protected:
	string size; // must be one of  “small”, “medium”, or “large”
public:
	Jam(string name, float price, int onHand, int numSold, string size)
	{
		itemName = name;
		temPrice = price;
		qtyOnHand = onHand;
		qtyPurchased = numSold;
		this->size = size;
	}
	string getSize()
	{
		return size;
	}
	void setSize(string size)
	{
		this->size = size;
	}
	virtual void PrintGrocery()
	{
		cout << "\n" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "Name: " << itemName << "\n" << endl;
		cout << "Size: " << size << "\n" << endl;
		cout << "Price: " << temPrice << "\n" << endl;
		cout << "Amount In Stock: " << qtyOnHand << "\n" << endl;
		cout << "Amount Purchased: " << qtyPurchased << "\n" << endl;
	}
};
//-----------------------------
class Soup : public GroceryItem
{
protected:
	string type; // must be “dry” or “liquid”
public:
	Soup(string name, float price, int onHand, int numSold, string type)
	{
		itemName = name;
		temPrice = price;
		qtyOnHand = onHand;
		qtyPurchased = numSold;
		this->type = type;
	}
	string getType()
	{
		return type;
	}
	void setType(string type)
	{
		this->type = type;
	}
	
	virtual void PrintGrocery()
	{
		cout << "\n" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "Name: " << itemName << "\n" << endl;
		cout << "Type: " << type << "\n" << endl;
		cout << "Price: " << temPrice << "\n" << endl;
		cout << "Amount In Stock: " << qtyOnHand << "\n" << endl;
		cout << "Amount Purchased: " << qtyPurchased << "\n" << endl;
	}
};

//-----------------------------



class Inventory
{
protected:
	vector<GroceryItem*> gitems;
public:
	void AddNewGrocery();
	void DeleteGrocery();
	void ModifyGrocery();
	void ListAllItems();
	bool isInInventory(string name)
	{
		for (GroceryItem* temp : gitems)
			if (temp->getItemName() == name)
				return true;
		return false;
	}
	void addToInventory(GroceryItem* item)
	{
		gitems.push_back(item);
	}
	GroceryItem* getItem(string name)
	{
		for (GroceryItem* temp : gitems)
			if (temp->getItemName() == name)
				return temp;
	}
	bool updateInventory(GroceryItem* item)
	{
		GroceryItem* temp;
		for (int i = 0; i < gitems.size(); i++)
		{
			temp = gitems[i];
			if (temp->getItemName() == item->getItemName())
			{
				gitems[i] = item;
				return true;
			}
		}
		return false;
	}
	
};
//-----------------------------
class Customer
{
protected:
	long custID;
	string custPass;
	string custName;
	string custAddress;
	float custTotalBill;
	vector<GroceryItem*> gitemsPurchased;

public:
	Customer()
	{
		custID = 0;
		custPass = custName = custAddress = " ";
		custTotalBill = 0;
	}
	Customer(long id, string pass, string name, string addr, float bill)
	{
		custID = id;
		custPass = pass;
		custName = name;
		custAddress = addr;
		custTotalBill = bill;
	}
	
	void PrintCustomer();
	void ListPurchasedItems();
	void BuyAnItem(Inventory&);
	void RemovePurchasedItem(Inventory&);
	void SubmitRequest();
	long getCustomerID()
	{
		return custID;
	}
	void setCustomerID(long id)
	{
		custID = id;
	}
	string getCustomerPassword()
	{
		return custPass;
	}
	void setCustomerPassword(string pass)
	{
		custPass = pass;
	}
	string getCustomerName()
	{
		return custName;
	}
	void setCustomerName(string name)
	{
		custName = name;
	}
	string getCustomerAddress()
	{
		return custAddress;
	}
	void setCustomerAddress(string addr)
	{
		custAddress = addr;
	}
	float getCustomerBill()
	{
		return custTotalBill;
	}
	void setCustomerBill(float total)
	{
		custTotalBill = total;
	}
};
//-----------------------------
class OnlineShopping
{
protected:
	vector<Customer> cust;
	string adminPassword;
	Inventory inv;
public:
	OnlineShopping() { adminPassword = "12345"; };
	~OnlineShopping() {};

	bool customerExists(long id)
	{
		for (Customer temp : cust)
			if (temp.getCustomerID() == id)
				return true;
		return false;
	}
	
	void AddCustomer();
	void DeleteCustomer();
	void ModifyCustomer();
	void ListAllCustomers();
	void changeAdminPassword();
	void ProcessTransactionFile();
	string getAdminPassword()
	{
		return adminPassword;
	}
	void setNewAdminPassword(string pass)
	{
		adminPassword = pass;
	}

	void StartUp();
};
