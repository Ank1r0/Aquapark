#pragma once
#include "vector";
#include "unordered_map"
#include "sstream";
using namespace std;

class Aquapark
{
public:

	class Subscription {
	public:
		int id_;
		int balance_;
		bool isActive = false;
		Subscription(int _id, int _balance)
		{
			id_ = _id;
			balance_ = _balance;
		}
		~Subscription() {}
	};

	class Ticket {
	public:
		int id_;
		char tariff_;
		bool used = false;
		bool isActive = false;

		Ticket(int _id,char _tariff){
			id_ = _id;			
			tariff_ = _tariff;
		}
		~Ticket(){}

		friend std::ostream& operator<<(std::ostream& os, const Ticket& obj) {
			return os << obj.toString();
		}

		string toString() const {
			std::ostringstream s;
			s << "Ticket [ID: " << id_ << ", Tariff: " << tariff_ << "]";
			return s.str();
		}
	};

	unordered_map<int,Subscription> subscriptions;
	unordered_map<int, Ticket> tickets;

	int totalM = 0;

	void run();

	char topup(int id);
	char getPass(int id);
	char into(int id);
	char out(int id);
	void listAll();
	int avg();
	void intMenu();
	void test();

	void end();
	
};

