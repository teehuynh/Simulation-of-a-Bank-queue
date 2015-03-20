#include "Transaction.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

Transaction::Transaction(char t, int time, int length) {
	tType = t;
	tTime = time;
	tLength = length;
}

char Transaction::getType() {
	return tType;
}
int Transaction::getTime() {
	return tTime;
}

int Transaction::getLength() {
	return tLength;
}

void simulate() {

	LinkedQueue<Transaction> bankQueue;
	SL_PriorityQueue<Transaction> eventListPQueue;
	
	int arriveTime;
	int transTime;
	int wait = 0;
	int count = 0;

	bool tellerAvailable = true;

	ifstream infile("events.txt");
	

	while (!infile.eof()) {

		infile >> arriveTime >> transTime;
		Transaction newArrivalEvent('A', arriveTime, transTime);
		cout << "Read in " << newArrivalEvent << endl;
		eventListPQueue.add(newArrivalEvent);
		count++;
	}

	while (!eventListPQueue.isEmpty()) {
		Transaction newEvent = eventListPQueue.peek();
	    int currentTime = newEvent.getTime();
		cout << "new event " << newEvent << endl;

		if (newEvent.getType() == 'A') 
			processArrival(newEvent, eventListPQueue, bankQueue,tellerAvailable, currentTime);
		else
			processDeparture(newEvent, eventListPQueue, bankQueue,tellerAvailable, currentTime, wait);
		
	}
	cout << "Wait time for " << count << " customers is total of " << wait << " which averages " << 1.0*wait/count << endl;
}

void processArrival(Transaction& event, SL_PriorityQueue<Transaction>& pQueue, LinkedQueue<Transaction>& bQueue, bool& tellerAvailable, int currentTime) {

	pQueue.remove();

	Transaction customer = event;

	if(bQueue.isEmpty() && tellerAvailable)
	{
		int departureTime = currentTime + event.getLength();
		Transaction newDepartureEvent('D', departureTime, 0);
		pQueue.add(newDepartureEvent);
		tellerAvailable = false;
	}
	else
	{
		bQueue.enqueue(customer);
	}
}
void processDeparture(Transaction& event, SL_PriorityQueue<Transaction>& pQueue, LinkedQueue<Transaction>& bQueue, 
					  bool& tellerAvailable, int currentTime, int& wait) {
	pQueue.remove();
	if(!bQueue.isEmpty()) {
		Transaction customer = bQueue.peekFront();
		bQueue.dequeue();
		cout << "ct " << currentTime << endl;
		int departureTime = currentTime + customer.getLength();
		Transaction newDepartureEvent('D', departureTime, 0);
		pQueue.add(newDepartureEvent);

		wait += (currentTime - customer.getTime());
	}
	else
		tellerAvailable = true;
}

bool operator>(const Transaction& t1, const Transaction& t2)
{
	return t1.tTime > t2.tTime;
}
bool operator<(const Transaction& t1, const Transaction& t2) {
	return t1.tTime < t2.tTime;
}
bool operator==(const Transaction& t1, const Transaction& t2) {
	return t1.tTime == t2.tTime;
}
ostream& operator<<(ostream& out, Transaction& t)
{
	out << t.tType << " " << t.tTime << " " << t.tLength;
	return out;
}
	