#include <iostream>
#include "Aquapark.h"
#include <string>

using namespace std;

void Aquapark::run() 
{
	string input;
	bool endFlag = true;
	int id = 0;
	while (endFlag)
	{		
		intMenu();
		cin >> input;
		
		//id = stoi(input.substr(input.find(" ") + 1));
		switch (input.at(0))
		{
		case '0':
			end();
			endFlag = false;
			break;	
		case '1':
			cout << "Enter ID:\n";
			cin >> id;
			topup(id);
			break;	
		case '2':
			cout << "Enter ID:\n";
			cin >> id;
			getPass(id);
			break;	
		case '3':			
			cout << "Enter ID:\n";
			cin >> id;
			into(id);
			break;	
		case '4':
			cout << "Enter ID:\n";
			cin >> id;
			out(id);
			break;			
		case '5':
			listAll();
			system("pause");
			break;	
		}

		cout << " \n\n";
	
	}
};
void  Aquapark::intMenu()
{
	cout << "0. Terminate program\n";
	cout << "1. Top up the pass\n";
	cout << "2. Get one time entrance pass\n";
	cout << "3. Entrance\n";
	cout << "4. Exit\n\n";
}

void Aquapark::test()
{
	
	listAll();
}

char  Aquapark::topup(int id) 
{ 
	string input;
	int sessionid = -1;
	int sid = -1;
	int amount;

	if (subscriptions.find(id) == subscriptions.end()) {
		cout << "ID not found, create subscription with this ID? Y/N\n";
		cin >> input;
		if (input.at(0) == 'Y' || input.at(0) == 'y')
		{
			Subscription sb(id, 0);
			subscriptions.insert({ sb.id_,sb });

		}
		else
		{
			return 'f';
		}
		
	}

	sid = id;
	cout << "Enter the amount for top up.\n";
	cin >> amount;
	if (amount < 0)
	{
		return 'f';
	}
	subscriptions.at(sid).balance_ += amount;
	totalM += amount;


	return 'k';
}
char  Aquapark::getPass(int _id) 
{ 
	string tariff;
	char h = 0;
	cout << "select tariff\n";
	cout << "1H - 85 CZK, 2H - 145 CZK, 3H - 200 CZK\n";
	cout << "To confirm operation choose tariff and enter numbers from 1 to 3.\n";
	cout << "In case of not accepting the price list enter N to cancel the operation.\n\n";
	cin >> tariff;

	switch (tariff.at(0))
	{
	case '1':
		h = '1';
		totalM += 85;
		break; 
	case '2':
		h = '2';
		totalM += 145;
		break;
	case '3':
		h = '3';
		totalM += 200;
		break;
	default:
		break;
	}

	if (h == 0)
	{
		return 'f';
	}

	if (tariff.at(0) == 'N' || tariff.at(0) == 'n') { cout << "operation terminated by choice.\n"; return 't'; }
	Ticket t(_id,h);	
	tickets.insert({ t.id_,t });

	cout << "Operation done. Ticket with information below was added to the database.\n";
	cout << "id: "<< t.id_ <<"\n";
	cout << "Hours: "<< t.tariff_ <<"\n";
	cout << "Operation done.\n\n";

	return 'd';
}
char  Aquapark::into(int id) 
{
	//INTO INTO INTO
	
	int sessionid = -1;
	int sid = -1;
	int tid = -1;
	
	if (subscriptions.find(id) != subscriptions.end()) {
		sid = id;
	} else

	if (tickets.find(id) != tickets.end()) {
		
		tid = id;
	}
	else {
		return 'n';
	}

	if (tid == -1 && sid == -1) { cout << "Identifier not found.\n"; return 'f'; }

	if (tid > 0)
	{
		if (tickets.at(tid).isActive  == false && tickets.at(tid).used == false)
		{
			tickets.at(tid).isActive = true;
		}
	}

	if (sid > 0)
	{
		if (subscriptions.at(sid).isActive == false)
		{
			if (subscriptions.at(sid).balance_ >= 80)
			{
				subscriptions.at(sid).isActive = true;
			}
			else {
				cout << "Not enought balance to enter.\n";
				return 'f';
			}
			
		}
	}

	cout << "Ticket activated.\n";
	return 'k';
}
char  Aquapark::out(int id) 
{ 
	//OUTOUTOUTOUTOUTOUT
	string stime;
	int time;
	
	int sid = -1;
	int sessionid = -1;
	int tid = -1;

	if (subscriptions.find(id) != subscriptions.end()) {

		sid = id;
	}
	else

	if (tickets.find(id) != tickets.end()) {

		tid = id;
	}
	else {
		return 'n';
	}

	if (tid == -1 && sid == -1) { cout << "Identifier not found.\n"; return 'f'; }

	

	cout << "Enter time in minutes.\n";
	cin >> time;
	int mintopay = time;
	cout << "\nwas in: " << mintopay << " minutes.\n";
	if (tid > -1)
	{
		if (tickets.at(tid).isActive = true)
		{
			switch (tickets.at(tid).tariff_)
			{
			case '1':
				mintopay -= 60;
				break;
			case '2':
				mintopay -= 120;
				break;
			case '3':
				mintopay -= 180;
				break;
			default:
				break;
			}

			if (mintopay > 0)
			{
				cout << "ask to pay : " << mintopay * 1.5 << " CZK, for:" << mintopay << "minutes.\n";
				totalM += mintopay * 1.5;

			}

			tickets.at(tid).isActive = false;
			tickets.at(tid).used = true;
		}
		else {
			cout << "It's ID not active\n";
			return 'f';
		}		
	}
	
	if (sid > -1)
	{
		if (subscriptions.at(sid).isActive == true)
		{
			subscriptions.at(sid).balance_ -= 80;
			mintopay -= 60;

			if (mintopay > 0)
			{
				subscriptions.at(sid).balance_ -= mintopay;
			}

			subscriptions.at(sid).isActive = false;

			if (subscriptions.at(sid).balance_ < -200)
			{
				cout << "Ask to pay now, for credit: " << subscriptions.at(sid).balance_ << "\n";
			}

			cout << "left of balance: " << subscriptions.at(sid).balance_ << "\n";
		}		
		else {
			cout << "It's ID not active\n";
				return 'f';
		}
	}
	


	

	cout << "Ticket deactivated.\ntime:" << time << "\n";
	return 'k';
}
void  Aquapark::listAll()
{ 
	cout << "total turnover:" << totalM << '\n';
	cout << "total amount of customers:" << tickets.size() + subscriptions.size() << '\n';

	for (const auto& pair : tickets) {
		std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
	}

	cout << "\n";
}
int  Aquapark::avg() 
{ 
	cout << "avg\n";
	return 1;
}

void  Aquapark::end() {}