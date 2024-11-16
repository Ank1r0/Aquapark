#include <iostream>
#include "Aquapark.h"
#include <string>

using namespace std;

void Aquapark::run() 
{
	string input;
	bool endFlag = true;
	int id;
	while (endFlag)
	{		
		intMenu();
		getline(cin, input);
		
		id = stoi(input.substr(input.find(" ") + 1));
		switch (input.at(0))
		{
		case '0':
			end();
			endFlag = false;
			break;	
		case '1':
			topup(id);
			break;	
		case '2':
			getPass(id);
			break;	
		case '3':			
			into(id);
			break;	
		case '4':
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

char  Aquapark::topup(int id) 
{ 
	cout << "topup\n";
	return 't';
}
char  Aquapark::getPass(int _id) 
{ 
	string tariff;
	char h;
	cout << "select tariff\n";
	cout << "1H - 85 CZK, 2H - 145 CZK, 3H - 200 CZK\n";
	cout << "To confirm operation choose tariff and enter numbers from 1 to 3.\n";
	cout << "In case of not accepting the price list enter N to cancel the operation.\n\n";
	getline(cin, tariff);

	switch (tariff.at(0))
	{
	case '1':
		h = '1';
		break; 
	case '2':
		h = '2';
		break;
	case '3':
		h = '3';
		break;
	default:
		break;
	}

	if (tariff.at(0) == 'N' || tariff.at(0) == 'n') { cout << "operation terminated by choice.\n"; return 't'; }
	Ticket t(_id,true,h);	
	tickets.push_back(t);

	cout << "Operation done. Ticket with information below was added to the database.\n";
	cout << "id: "<< t.id_ <<"\n";
	cout << "Hours: "<< t.tariff_ <<"\n";
	cout << "Operation done.\n\n";

	return 'd';
}
char  Aquapark::into(int id) 
{
	string stime;
	int time;
	int tid = -1;
	for (size_t i = 0; i < tickets.size(); i++)
	{
		if (tickets.at(i).id_ == id) 
		{
			tid = i;
		}
	}
	if (tid == -1) { cout << "Identifier not found.\n"; return 'f'; }

	int sid = -1;
	for (size_t i = 0; i < active.size(); i++)
	{
		if (active.at(i).id_== id)
		{
			sid = i;
		}
	}
	if (sid != -1) { cout << "It's already active.\n"; return 'f'; }

	cout << "Enter time in minutes.\n";
	getline(cin, stime);
	time = stoi(stime);
	
	active.push_back(Session (id, time));

	cout << "Ticket activated.\ntime:" << time << "\n";
	return 'k';
}
char  Aquapark::out(int id) 
{ 
	//OUTOUTOUTOUTOUTOUT
	string stime;
	int time;
	int tid = -1;
	for (size_t i = 0; i < tickets.size(); i++)
	{
		if (tickets.at(i).id_ == id)
		{
			tid = i;
		}
	}
	if (tid == -1) { cout << "Identifier not found.\n"; return 'f'; }

	int sid = -1;
	for (size_t i = 0; i < active.size(); i++)
	{
		if (active.at(i).id_ == id)
		{
			sid = i;
		}
	}
	if (sid == -1) { cout << "It's not active.\n"; return 'f'; }

	cout << "Enter time in minutes.\n";
	getline(cin, stime);
	time = stoi(stime);
	int mintopay = time - active.at(sid).in_;
	cout << "\nwas in: " << mintopay << " minutes.\n";

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

	cout << "was in: " << mintopay << "\n";
	if (mintopay > 0)
	{
		cout << "ask to pay : " << mintopay*1.5 << " CZK\n";
	}

	cout << "Ticket deactivated.\ntime:" << time << "\n";
	return 'k';
}
char  Aquapark::listAll()
{ 
	for (size_t i = 0; i < tickets.size(); i++)
	{
		cout << "id: " << tickets.at(i).id_ << "\n";
		cout << "balance: " << tickets.at(i).balance_ << "\n";
		cout << "tariff: " << tickets.at(i).tariff_ << "\n";
		cout << "type: " << (tickets.at(i).temp_ == 1 ? "One time ticket " : "subscribtion") << "\n";
	}
	return 'd';
}
int  Aquapark::avg() 
{ 
	cout << "avg\n";
	return 1;
}

void  Aquapark::end() {}