#include "GroceryItem.h"

void Customer::PrintCustomer()
{ // sampling prints the information  (name, id, … etc ) of a customer
	cout << "\n" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Name: " << this->custName << "\n" << endl;
	cout << "ID: " << this->custID << "\n" << endl;
	cout << "Password: " << this->custPass << "\n" << endl;
	cout << "Address: " << this->custAddress << "\n" << endl;
	cout << "Amount Owed: " << this->custTotalBill << "\n" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "\n" << endl;
}
//-----------------------------

void Customer::ListPurchasedItems()
{
	// lists all the groceries (with all their properties) purchased by a customer
	GroceryItem* elem;
	for (int i = 0; i < gitemsPurchased.size(); i++)
	{
		elem = gitemsPurchased[i];
		elem->PrintGrocery();
	}
}
//-----------------------------
void Customer::BuyAnItem(Inventory& inv)
{
	// allow the customer to view the entire inventory in here then
	// ask the customer to pick up an item and ask him/her how many wants to buy
	// add the selected item to the list of items purchased by the customer
	// modify the customer bill
	// modify the item in the inventory (quantity purchased, and quantity on hand) 
	// you should let the customer stay in this routine as long as he/she wishes. You can ask the customer to exit 
	// by typing zero

	int input, quantitiy;
	string name;
	int amount;
	GroceryItem* item;
	GroceryItem* elem;
	bool done = false;

	while (!done)
	{
		cout << "1) View Inventory " << endl;
		cout << "2) Make a purchase " << endl;
		cout << "3) Remove item from cart" << endl;
		cout << "4) Show content of cart" << endl;
		cout << "5) To check out" << endl;
		cout << ": ";
		cin >> input;
		if (input == 1)
			inv.ListAllItems();
		if (input == 2)
		{
			cout << "\n Please enter the name of the item you would like to purchase: " << endl;
			cin >> name;
			if (inv.isInInventory(name))
			{
				item = inv.getItem(name);
				gitemsPurchased.push_back(item);
				custTotalBill += item->getTemPrice();
				amount = item->getQtyOnHand() - 1;
				item->setQtyOnHand(amount);
				amount = item->getQtyPurchased() + 1;
				item->setQtyPurchased(amount);
			}
		}

		if (input == 3)
		{
			cout << "Please enter the name of the item you wish to delete: ";
			cin >> name;
			if (inv.isInInventory(name))
			{
				for (int i = 0; i < gitemsPurchased.size(); i++)
				{
					elem = gitemsPurchased[i];
					if (elem->getItemName() == name)
					{
						item = gitemsPurchased[i];
						custTotalBill -= item->getTemPrice();
						amount = item->getQtyOnHand() + 1;
						item->setQtyOnHand(amount);
						amount = item->getQtyPurchased() - 1;
						item->setQtyPurchased(amount);
						gitemsPurchased.erase(gitemsPurchased.begin() + i);
					}
				}
			}
			else
				cout << "Item not in inventory!" << endl;
		}

		if (input == 4)
		{
			for (GroceryItem* temp : gitemsPurchased)
				temp->PrintGrocery();
		}
		if (input == 5)
		{
			cout << "OK! Here's what you have in your cart: \n" << endl;
			for (GroceryItem* temp : gitemsPurchased)
				temp->PrintGrocery();
			cout << "\n Your total will be: " << custTotalBill;
			cout << "\n Expect your delivery to arrive within 24 hours. Thanks for shopping!" << endl;
			done = true;
		}
		

	}
}
//-----------------------------
void Customer::RemovePurchasedItem(Inventory& inv)
{
	// allow the customer to view the list of item he/she has purchased
	// ask the customer to pick up an item he/she wants to delete
	// remove the item from the his/her grocery list
	// modify the customer bill
	// modify the item in the inventory (quantity purchased, and quantity on hand) 
	// you should let the customer stay in this routine as long as he/she wishes. You can ask the customer to exit 
	// by typing zero

	char selection;
	string name;
	int amount;
	GroceryItem* item;
	bool done = false;

	while (!done)
	{
		cout << "\n To view available inventory, enter 'V' \n " << endl;
		cout << "To delete an item, enter 'D' \n" << endl;
		cout << "To exit, enter 'X' \n" << endl;
		cout << ": " << endl;
		cin >> selection;
		if (selection == 'V' || selection == 'v')
			inv.ListAllItems();
		if (selection == 'D' || selection == 'd')
		{
			for (int i = 0; i < gitemsPurchased.size(); i++)
			{
				item = gitemsPurchased[i];
				if (name == item->getItemName())
				{
					gitemsPurchased.erase(gitemsPurchased.begin() + i);
					custTotalBill = custTotalBill - item->getTemPrice();
					item->setQtyOnHand(item->getQtyOnHand() + 1);
					item->setQtyPurchased(item->getQtyPurchased() - 1);
				}
			}
		}
		
		if (selection == 'X' || selection == 'x')
			done = true;
	}

}
//-----------------------------
void Customer::SubmitRequest()
{
	// show the list of items purchased by the customer and show the amount that is due.
	// ask the customer if he/she is sure to submit the request. Show the customer his/her address and 
	// let the customer know that the items will be delivered to that address. Note that if the customer’s address 
	// is changed, the customer may not wish the items to be sent to a wrong place.
		// if the answer is yes,
		// print appropriate message for the customer letting the customer know that
		// someone will deliver the items to his/her house within 24 hours.
		// finally, reset the shopping status of the customer by making the customer bill to zero 
		// and removing the purchased items from his/her list of shopping

	for (GroceryItem* temp : gitemsPurchased)
		temp->PrintGrocery();

	cout << "\n Total due today: $" << custTotalBill << endl;
	cout << "\n Everything look good? Enter 'Y' to continue, 'N' to quit" << endl;
	cout << "\n : " << endl;
	char selection;
	cin >> selection;

	if (selection == 'Y' || selection == 'y')
	{
		cout << "\n" << custAddress << endl;
		cout << "\n Is this address correct? Enter 'Y' to continue, or 'N' to change the address" << endl;
		cout << "\n : " << endl;
		char correctAddress;
		cin >> correctAddress;
		if (correctAddress == 'Y' || correctAddress == 'y')
		{
			cout << "\n Your order has been placed! Expect your order to be delivered within 24 hours. " << endl;
			custTotalBill = 0;
			gitemsPurchased.erase(gitemsPurchased.begin(), gitemsPurchased.end());
			cout << "\n Size of cart after attempted deletion: " << gitemsPurchased.size();
		}
	}
}

//-----------------------------
//-----------------------------
//-----------------------------
//-----------------------------
//-----------------------------




void Inventory::AddNewGrocery()
{
	//interactively ask the user (administration) what type of grocery should be added: (Diary, Jam, etc..)
	//interactively ask for the information of the grocery, name, price, etc.
	//insert the new grocery to the list of groceries in the inventory if it is not there already

	// you should let the admin to stay in this routine as long as he/she wishes. This way
	// admin can add more than one item. You can ask the admin to exit by typing zero

	
	int item;
	string itemName, size, type;
	float price, temp, weight;
	int onHand, numPurchased, aisle;
	GroceryItem* toAdd;
	bool done= false;
	while (!done)
	{
		cout << " \n Please enter the type of grocery you would like to add " << endl;
		cout << "\n 1) Dairy \n 2) Cereal \n 3) Bread \n 4) Jam \n 5) Soup \n" << endl;
		cout << "\n To exit, enter 0 \n" << endl;
		cout << "\n : " << endl;
		cin >> item;
		if (item == 0)
			done = true;
		else
		{
			cout << "\n Please enter the item name: " << endl;
			cin >> itemName;
			cout << "\n Please enter the item's price: " << endl;
			cin >> price;
			cout << "\n Please enter the amount on hand: " << endl;
			cin >> onHand;
			cout << "\n Please enter the amount that has been sold (if none, enter 0): " << endl;
			cin >> numPurchased;

			if (item == 1)
			{
				cout << "\n Please enter the item's temperature: " << endl;
				cin >> temp;
				toAdd = new Dairy (itemName, price, onHand, numPurchased, temp);
				gitems.push_back(toAdd);
				cout << "Item added successfully!" << endl;
			}

			if (item == 2)
			{
				cout << "\n Please enter the aisle: " << endl;
				cin >> aisle;
				toAdd = new Cereal (itemName, price, onHand, numPurchased, aisle);
				gitems.push_back(toAdd);
				cout << "Item added successfully!" << endl;
			}

			if (item == 3)
			{
				cout << "\n Please enter the weight: " << endl;
				cin >> weight;
				toAdd = new Bread (itemName, price, onHand, numPurchased, weight);
				gitems.push_back(toAdd);
				cout << "Item added successfully!" << endl;
			}

			if (item == 4)
			{
				cout << "\n Please enter the size (small, medium, large): " << endl;
				cin >> size;
				toAdd = new Jam(itemName, price, onHand, numPurchased, size);
				gitems.push_back(toAdd);
				cout << "Item added successfully!" << endl;
			}

			if (item == 5)
			{
				cout << "\n Please enter the type (dry, liquid): " << endl;
				cin >> type;
				toAdd = new Soup(itemName, price, onHand, numPurchased, type);
				gitems.push_back(toAdd);
				cout << "Item added successfully!" << endl;
			}
		}		
	}
}
//-----------------------------
void Inventory::DeleteGrocery()
{
	//show the admin the list of groceries
	//admin will select the one that should be deleted
	//based on admin selection, remove the item from the inventory

	// you should let the admin to stay in this routine as long as he/she wishes. This way admin can delete more 
	// than one item if necessary 

	int selection;
	string name;
	GroceryItem* temp;
	bool done = false;

	for (GroceryItem* temp : gitems)
		temp->PrintGrocery();

	while (!done)
	{
		cout << "\n To exit, enter 0 \n" << endl;
		cout << "\n Please enter the name of the product you would like to delete: " << endl;
		cin >> name;
		if (name == "0")
			done = true;
		else
		{
			for (int i = 0; i < gitems.size(); i++)
			{
				temp = gitems[i];
				if (temp->getItemName() == name)
				{

					temp = gitems[i];
					cout << "Deleting " << temp->getItemName();
					gitems.erase(gitems.begin() + i);
					break;
				}
			}
		}
	}
}

	//-----------------------------
	void Inventory::ModifyGrocery()
	{
		//show the admin the list of groceries
		//ask admin which item should be modified
		//admin selects the item and then you need to ask which field should be modified
		//based on the field selection interactively, ask admin for the new information 

		// you should let the admin to stay in this routine as long as he/she wishes. This way admin can modify more 
		// than one item if necessary 

		string name;
		int fieldToModify, type;
		string itemName, size, soupType;
		float price, temperature, weight;
		int onHand, numPurchased, aisle;
		GroceryItem* temp;
		bool done = false;
		ListAllItems();

		while (!done)
		{
			cout << "\n To exit, enter 0 \n" << endl;
			cout << "\n Please enter the type of item you would like to modify" << endl;
			cout << "\n 1) Dairy \n 2) Cereal \n 3) Bread \n 4) Jam \n 5) Soup \n" << endl;
			cin >> type;
			if (type == 0)
				done = true;
			else
			{
				cout << "\n Please enter the name of the item you would like to modify: " << endl;
				cin >> name;

				for (int i = 0; i < gitems.size(); i++)
				{
					temp = gitems[i];
					if (temp->getItemName() == name)
					{
						itemName = temp->getItemName();
						price = temp->getTemPrice();
						onHand = temp->getQtyOnHand();
						numPurchased = temp->getQtyPurchased();

						cout << "\n Please select the value of the field you would like to modify: " << endl;
						cout << "\n 1) Name \n 2) Price \n 3) Quantity On Hand \n 4) Quantity Purchased \n" << endl;
						if (type == 1)
						{
							cout << "5) Temperature \n : " << endl;
							cin >> fieldToModify;
							if (fieldToModify == 5)
							{

								cout << "Please enter the temperature: " << endl;
								cin >> temperature;
								GroceryItem* modified = new Dairy(itemName, price, onHand, numPurchased, temperature);
								gitems[i] = modified;
							}
						}
						if (type == 2)
						{
							cout << "5) Aisle \n : " << endl;
							cin >> fieldToModify;
							if (fieldToModify == 5)
							{
								cout << "Please enter the aisle: " << endl;
								cin >> aisle;
								GroceryItem* modified = new Cereal(itemName, price, onHand, numPurchased, aisle);
								gitems[i] = modified;
							}
						}
						if (type == 3)
						{
							cout << "5) Weight \n : " << endl;
							cin >> fieldToModify;
							if (fieldToModify == 5)
							{
								cout << "Please enter the weight: " << endl;
								cin >> weight;
								GroceryItem* modified = new Bread(itemName, price, onHand, numPurchased, weight);
								gitems[i] = modified;
							}
						}
						if (type == 4)
						{
							cout << "5) Size (small, medium, large) \n : " << endl;
							cin >> fieldToModify;
							if (fieldToModify == 5)
							{
								cout << "Please enter the size: " << endl;
								cin >> size;
								GroceryItem* modified = new Jam(itemName, price, onHand, numPurchased, size);
								gitems[i] = modified;
							}
						}
						if (type == 5)
						{
							cout << "5) Type (liquid, dry) \n : " << endl;
							cin >> fieldToModify;
							if (fieldToModify == 5)
							{
								cout << "Please enter the type: " << endl;
								cin >> soupType;
								GroceryItem* modified = new Soup(itemName, price, onHand, numPurchased, soupType);
								gitems[i] = modified;
							}
						}
					}
				}
			}
		}
	}
		//-----------------------------
		void Inventory::ListAllItems()
		{
			// this routine should show all groceries on the screen
			for (int i = 0; i < gitems.size(); i++)
			{
				gitems[i]->PrintGrocery();
			}
		}

		//-----------------------------
		void OnlineShopping::changeAdminPassword()
		{
			// this routine changes admin password. Your constructor sets admin password to “12345” in the constructors
			// to start with

			string pass;
			cout << "\n Please enter the new password: " << endl;
			cin >> pass;
			setNewAdminPassword(pass);
			cout << "Password changed to: " << getAdminPassword() << endl;
		}
		//-----------------------------

		void OnlineShopping::ListAllCustomers()
		{
			// this routine lists all the customers on the screen
			for (Customer temp : cust)
				temp.PrintCustomer();
		}
		//-----------------------------
		void OnlineShopping::AddCustomer()
		{
			// interactively ask admin/customer to enter information of the new customer.
			// as long as it is a new user, (different name and password) it can be accepted

			long id;
			string pass, name, addr;
			float bill;
			bool exists;
			cout << "Please enter the customer ID: " << endl;
			cin >> id;
			exists = customerExists(id);
			if (exists == true)
			{
				while (exists)
				{
					cout << "Customer ID already exists. Please try a different ID: " << endl;
					cin >> id;
					exists = customerExists(id);
				}
			}
			cout << "Please enter the customer password: " << endl;
			cin >> pass;
			cout << "Please enter the customer name: " << endl;
			cin >> name;
			cout << "Please enter the customer address: " << endl;
			cin >> addr;
			Customer newCust(id, pass, name, addr, 0);
			cust.push_back(newCust);
			
		}
		//-----------------------------


		void OnlineShopping::DeleteCustomer()
		{
			// list the customers for admin to view which one should be deleted
			// admin selects the one that should be deleted

			// you should let the admin to stay in this routine as long as he/she wishes. This way admin can delete more 
			// than one item if necessary 

			int id;
			ListAllCustomers();
			bool done = false;
			while (!done)
			{
				cout << "Please enter the customer ID: " << endl;
				cin >> id;
				if (!customerExists(id))
					cout << "No customer with that ID" << endl;
				else
				{
					for (int i = 0; i < cust.size(); i++)
						if (cust[i].getCustomerID() == id)
						{
							cust.erase(cust.begin() + i);
							cout << "Customer removed successfully!" << endl;
							done = true;
						}
				}
			}
		}
		//-----------------------------
		void OnlineShopping::ModifyCustomer()
		{
			//list the customers for admin to view which one should be modified
			//admin selects the one that should be deleted
			// ask admin which field should be modified

			// you should let the admin to stay in this routine as long as he/she wishes. This way admin can delete more 
			// than one item if necessary 

			long id;
			string pass, name, addr;
			float bill;
			int selection, index;
			Customer theCustomer;
			bool done = false;
			while (!done)
			{
				ListAllCustomers();
				cout << "To exit, eneter 0" << endl;
				cout << "Please enter the ID of a customer you would like to modify: " << endl;
				cin >> id;
				if (id == 0)
					done = true;
				 if (!customerExists(id))
					cout << "No customer with that ID" << endl;
				else
				{
					for (int i = 0; i < cust.size(); i++)
							if (cust[i].getCustomerID() == id)
							{
								theCustomer = cust[i];
								index = i;
							}
						int changeSelect;
						cout << "Please select the field you would like to change: " << endl;
						cout << " 1) Customer ID \n 2) Customer Name \n 3) Customer Password"
							<< "\n 4) Customer Address \n 5) Customer Bill \n : " << endl;
						cin >> changeSelect;
						if (changeSelect == 1)
						{
							cout << "Please enter the customer ID: " << endl;
							cin >> id;
							theCustomer.setCustomerID(id);
							cust[index] = theCustomer;
							if (cust[index].getCustomerID() == id)
								cout << "ID changed successfully!" << endl;
							else
								cout << "Problem changing ID!" << endl;
						}
						if (changeSelect == 2)
						{
							cout << "Please enter the customer name: " << endl;
							cin >> name;
							theCustomer.setCustomerName(name);
							cust[index] = theCustomer;
							if (cust[index].getCustomerName() == name)
								cout << "Name changed successfully!" << endl;
							else
								cout << "Problem changing name!" << endl;
						}
						if (changeSelect == 3)
						{
							cout << "Please enter the customer password: " << endl;
							cin >> pass;
							theCustomer.setCustomerPassword(pass);
							cust[index] = theCustomer;
							if (cust[index].getCustomerPassword() == pass)
								cout << "Password changed successfully!" << endl;
							else
								cout << "Problem changing password!" << endl;
						}
						if (changeSelect == 4)
						{
							cout << "Please enter the customer address: " << endl;
							cin >> addr;
							theCustomer.setCustomerAddress(addr);
							cust[index] = theCustomer;
							if (cust[index].getCustomerAddress() == addr)
								cout << "Address changed successfully!" << endl;
							else
								cout << "Problem changing address!" << endl;
						}
						if (changeSelect == 5)
						{
							cout << "Please enter the cutomer bill amount: " << endl;
							cin >> bill;
							theCustomer.setCustomerBill(bill);
							cust[index] = theCustomer;
							if (cust[index].getCustomerBill() == bill)
								cout << "Bill changed successfully!" << endl;
							else
								cout << "Problem changing bill!" << endl;
					}
				}
			}
		}
		
		
		void OnlineShopping::ProcessTransactionFile()
		{
			ifstream fin;
			string filepath = "test.txt";
			string command, name, password, address, type, catagory, size,
				custName, custPassword, custAddress;
			float price, temperature, weight;
			int numOnHand, numPurchased, aisle;
			long custID;
			fin.open(filepath);
			while (fin.good())
			{
				fin >> command;

				if (command == "InsertGrocery")
				{
					fin >> catagory;
					fin >> name;
					fin >> price;
					fin >> numOnHand;
					fin >> numPurchased;

					if (catagory == "Dairy")
					{
						fin >> temperature;
						GroceryItem* item = new Dairy(name, price, numOnHand, numPurchased, temperature);
						inv.addToInventory(item);
					}

					if (catagory == "Cereal")
					{
						fin >> aisle;
						GroceryItem* item = new Cereal(name, price, numOnHand, numPurchased, aisle);
						inv.addToInventory(item);
					}

					if (catagory == "Bread")
					{
						fin >> weight;
						GroceryItem* item = new Bread(name, price, numOnHand, numPurchased, weight);
						inv.addToInventory(item);
					}

					if (catagory == "Jam")
					{
						fin >> size;
						GroceryItem* item = new Jam(name, price, numOnHand, numPurchased, size);
						inv.addToInventory(item);
					}

					if (catagory == "Soup")
					{
						fin >> type;
						GroceryItem* item = new Soup(name, price, numOnHand, numPurchased, type);
						inv.addToInventory(item);
					}
				}

				if (command == "InsertCustomer")
				{
					fin >> custID;
					fin >> custPassword;
					fin >> custName;
					fin >> custAddress;
					Customer newCust(custID, custPassword, custName, custAddress, 0);
					cust.push_back(newCust);
				}

				if (command == "AddToQtyOnHand")
				{
					fin >> catagory;
					fin >> name;
					int increase, current, total;
					fin >> increase;
					GroceryItem* item = inv.getItem(name);
					current = item->getQtyOnHand();
					total = current + increase;
					item->setQtyOnHand(total);
					inv.updateInventory(item);
				}
			}

		}
		
		//-----------------------------
		void OnlineShopping::StartUp()
		{
			// your main program should call this routine first
			// you ask the user the following questions
			//	1: existing customer " << endl;
			//	2 : new customer " << endl;
			//	3 : admin " << endl;
			//	4 : quit " << endl;

				// if it is a new customer, your program interactively ask the information of the customer and as long 
				// as such a customer does not exist, it should be allowed to be added to the list of customers

				// if it is an existing customer, check the name and password for security. If it is a valid
				// customer, two actions can be done:
				// a)	change profile
				// b)	do shopping
				// if an existing customers wants to change his/her profile, you need to ask for his/her new information
				// and modify the customer profile appropriately; otherwise, call the BuyAnItem() routine or this 
				// customer to start shopping

				// if it is the admin, you need to ask for his/her password to see if it matches the admin password. If it is a 
				// accepted, the admin can do the following task:
/*
				1  :  change your password
				2 : add new customer
				3 : delete a customer
				4 : modify a customer
				5 : add new grocery
				6 : remove a grocery
				7 : modify a grocery
				8 : List groceries
				9 : List customers
				10 : Process Transaction File
				11 : quit

				All of the above are all self - explanatory.The last one is Process transaction file.You can create a routine that reads a transaction file and process the commands.There are only three commands : InsertGrocery, InsertCustomer, and AddToQtyOnHand.

				InsertGrocery is followed by the type of grocery and its properties.For example an example of inserting a Cereal is :
			InsertGrocery	Cereal 	Raisin_Brand	2.40   	20	0	3
				Which means it is Raisin - brand cereal that costs $2.40 and there are 20 of them exist in the store.No purchase has been done and the cereal is in aisle 3.

				InsertCustomer is followed by the properties of the new customer.You need to ensure that such a customer already does not exist in the system.An example of InsertCustomer is :
			InsertCustomer	1111	28 && 28 * * 	Jim_Stairs 	899_Adams_street_SanMarcos
				Which means it is customer number 1111 with password of 28 && 28 * *.His name is Jim_Stairs.And his address is 899_Adams_street_SanMarcos.

				AddToQtyOnHand is followed by item type and item name and a number that indicates how many “the quantity on hand” should be increased.For example
				AddToQtyOnHand 	Cereal 		Raisin_Brand 		20
				means the quantity on hand of raisin - brand cereal should be increased by 20.
				*/

			int selection, index;
			char custSelection;
			long custID;
			float custBill;
			string custPass, custName, custAddress, admPass;
			Customer theCustomer;
			bool goodLoggin = false;
			bool done = false;

			while (true)
			{
				cout << "1: existing customer " << endl;
				cout << "2 : new customer " << endl;
				cout << "3 : admin " << endl;
				cout << "4 : quit " << endl;
				cin >> selection;
				
				
				
				// Existing customer
				if (selection == 1)
				{
					while (!goodLoggin)
					{
						cout << "Pleae enter your customer ID: " << endl;
						cin >> custID;
						cout << "Please enter your password: " << endl;
						cin >> custPass;
						if (!customerExists(custID))
							cout << "Invalid loggin! Try again \n" << endl;
						else
						{
							for (int i = 0; i < cust.size(); i++)
							{
								if (cust[i].getCustomerID() == custID && cust[i].getCustomerPassword() == custPass)
								{
									theCustomer = cust[i];
									index = i;
									goodLoggin = true;
								}

							}
						}
					}

					while (!done)
					{

						cout << "a)	change profile" << endl;
						cout << "b)	do shopping" << endl;
						cout << "c) exit" << endl;
						cout << ": " << endl;
						cin >> custSelection;


						// Change profile
						if (custSelection == 'A' || custSelection == 'a')
						{
							int changeSelect;
							cout << "1) Change Password: " << endl;
							cout << "2) Change Name: " << endl;
							cout << "3) Change Address: " << endl;
							cin >> changeSelect;
							if (changeSelect == 1)
							{
								cout << "Please enter your new password: " << endl;
								cin >> custPass;
								theCustomer.setCustomerPassword(custPass);
								cust[index] = theCustomer;
								if (cust[index].getCustomerPassword() == custPass)
									cout << "Password changed successfully!" << endl;
								else
									cout << "Error changing password!" << endl;
							}


							if (changeSelect == 2)
							{
								cout << "Please enter your name: " << endl;
								cin >> custName;
								theCustomer.setCustomerName(custName);
								cust[index] = theCustomer;
								if (cust[index].getCustomerName() == custName)
									cout << "Name changed successfully!" << endl;
								else
									cout << "Error changing name!" << endl;
							}

							if (changeSelect == 3)
							{
								cout << "Please enter your new address: " << endl;
								cin >> custAddress;
								theCustomer.setCustomerAddress(custAddress);
								cust[index] = theCustomer;
								if (cust[index].getCustomerAddress() == custAddress)
									cout << "Address changed successfully!" << endl;
								else
									cout << "Error changing address!" << endl;


							}
						}
							if (custSelection == 'B' || custSelection == 'b')
							{
								theCustomer.BuyAnItem(inv);
							}
							if (custSelection == 'C' || custSelection == 'c')
								done = true;
						}
					}

				
				
				// Add customer
				if (selection == 2)
				{
					AddCustomer();
				}
				
				//Admin
				if (selection == 3)
				{
					int admSelect;
					cout << "Please enter the password: " << endl;
					cin >> admPass;
					if (admPass == adminPassword)
					{
						while (true)
						{
							cout << " 1  :  change your password \n 2 : add new customer \n 3 : delete a customer"
								<< "\n 4 : modify a customer \n 5 : add new grocery \n 6 : remove a grocery"
								<< "\n 7 : modify a grocery \n 8 : List groceries \n 9 : List customers"
								<< " \n 10 : Process Transaction File \n 11 : quit " << endl;
							cin >> admSelect;
							
							// change password
							if (admSelect == 1)
							{
								cout << "Please enter your new password: " << endl;
								cin >> admPass;
								setNewAdminPassword(admPass);
								if (admPass == adminPassword)
									cout << "Password changed successfully!" << endl;
								else
									cout << "Problem changing password." << endl;
							}
							
							// add new customer
							if (admSelect == 2)
							{
								AddCustomer();
							}

							// delete customer
							if (admSelect == 3)
							{
								DeleteCustomer();
							}
							
							// modify customer
							if (admSelect == 4)
							{
								ModifyCustomer();
							}
							
							//add new grocery
							if (admSelect == 5)
							{
								inv.AddNewGrocery();
							}
							
							// remove grocery
							if (admSelect == 6)
							{
								inv.DeleteGrocery();
							}
							
							// modify grocery
							if (admSelect == 7)
							{
								inv.ModifyGrocery();
							}
							
							// list groceries
							if (admSelect == 8)
							{
								inv.ListAllItems();
							}
							
							// list customers
							if (admSelect == 9)
							{
								ListAllCustomers();
							}
							
							// process transaction file
							if (admSelect == 10)
							{
								ProcessTransactionFile();
							}
							
							// quit
							if (admSelect == 11)
								break;
						}
					}

					else
						cout << "Invalid password" << endl;
				}
				if (selection == 4)
				{
					break;
				}
			}

		}

		//-----------------------------
		int main()
		{
			OnlineShopping VONS;
			VONS.StartUp();
			return 0;

		}
