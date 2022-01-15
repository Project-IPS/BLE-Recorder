#ifndef UPDATE_CYCLE_H
#define UPDATE_CYCLE_H

#include<forward_list>
#include"scoped_thread.h"
#include"active_beacon.h"

using namespace std;

void infiniteUpdateLoop();

/**
 * It should contain values that are strictly necessary for trilateration.
 */
class Entry{

private:
	int estimatedRssi;
	Position pos;

public:
	Entry(int estimatedRssi, Position pos): estimatedRssi{estimatedRssi}, pos{pos}{}
	~Entry(){}

	Entry(const Entry&) = default;
	Entry& operator=(const Entry&) = default;

	//Move semantics is basically the same as copy semantics so no need to add it.

	int getRssi() const{
		return estimatedRssi;
	}

	string toString() const{
		string str = "{"+pos.toString()+" : "+to_string(estimatedRssi)+"}";
		return str;
	}
};

class UpdateCycle{

private:
	/**
	 * Contains entries in descending order of rssi
	 */
	forward_list<Entry> update_cycle;
	unsigned short no_of_entries;

	/**
	 * Contains logic for insertion into the update_cycle
	 */
	void insert(Entry entry);

	/**
	 * For insertion sort into the list.
	 */
	void addEntry(Entry entry);

	UpdateCycle():no_of_entries{0}{}

public:
	~UpdateCycle(){}

	UpdateCycle(const UpdateCycle&) = default;
	UpdateCycle& operator=(const UpdateCycle&) = default;

	UpdateCycle(UpdateCycle&&) = default;
	UpdateCycle& operator=(UpdateCycle&&) = default;

	static void generateUpdateCycle(vector<ActiveBeacon>& beacons);

	string toString();
};

extern ScopedThread updateCycleThread;
extern queue<UpdateCycle> update_queue;
extern mutex updateQueueMutex;
extern condition_variable newUpdateCycleReady;
#endif
