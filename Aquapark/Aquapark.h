#pragma once
#include "vector";

using namespace std;

class Aquapark
{
public:

	class Ticket {
	public:
		int id_;
		bool temp_;
		int balance_;
		char tariff_;

		Ticket(int _id, bool _temp,char _tariff){
			id_ = _id;
			temp_ = _temp;
			tariff_ = _tariff;
			balance_ = -1;
		}
		~Ticket(){}
	};
	
	class Session {
	public:
		int in_;
		int id_;

		Session(int id, int time)
		{
			in_ = time;
			id_ = id;
		}
		~Session(){}
	};

	

	vector<Ticket> tickets;
	vector<Session> active;

	void run();

	char topup(int id);
	char getPass(int id);
	char into(int id);
	char out(int id);
	char listAll();
	int avg();
	void intMenu();

	void end();
	
};

