#pragma once
#include "SL_PriorityQueue.h"
#include "LinkedQueue.h"
#include <iostream>


class Transaction {

private:
	char tType;
	int tTime;
	int tLength;

public:
	char getType();
	int getTime();
	int getLength();

	Transaction(char t, int time, int length);
	friend bool operator>(const Transaction& t1, const Transaction& t2);
	friend bool operator<(const Transaction& t1, const Transaction& t2);
	friend bool operator==(const Transaction& t1, const Transaction& t2);
	friend ostream& operator<<(ostream& out, Transaction& t);
	

};

void simulate();

void processArrival(Transaction& event, SL_PriorityQueue<Transaction>& pQueue, LinkedQueue<Transaction>& bQueue,bool& tellerAvaialable, int cur);
void processDeparture(Transaction& event, SL_PriorityQueue<Transaction>& pQueue, LinkedQueue<Transaction>& bQueue,bool& tellerAvaialable, int cur,  int& w);