#include"global.h"
#include "update_cycle.h"

ScopedThread updateCycleThread;
queue<UpdateCycle> update_queue;
mutex updateQueueMutex;
condition_variable newUpdateCycleReady;

void UpdateCycle::addEntry(const Entry& entry){
	if(no_of_entries == 0){
		update_cycle.push_front(entry);
		no_of_entries++;
		return;
	}

	if(entry.getRssi()<=update_cycle.front().getRssi()){
		update_cycle.push_front(entry);
		no_of_entries++;
		return;
	}

	auto it = update_cycle.begin();
	forward_list<Entry>::iterator temp;
	while(true){
		temp=it;
		it++;
		if(it==update_cycle.end()){
			update_cycle.insert_after(temp,entry);
			no_of_entries++;
			return;
		}
		else if(entry.getRssi()<(it->getRssi())){
			update_cycle.insert_after(temp, entry);
			no_of_entries++;
			return;
		}
	}
//	update_cycle.insert_after(temp,entry);
//	no_of_entries++;
}

void UpdateCycle::insert(const Entry& entry){
	if(no_of_entries<3){
		addEntry(entry);
		return;
	}
	else{
		if((update_cycle.front().getRssi())<entry.getRssi()){
			update_cycle.pop_front();
			no_of_entries--;
			addEntry(entry);
		}
	}
}

void UpdateCycle::generateUpdateCycle(vector<ActiveBeacon>& beacons){
	string str = "[";
	for(ActiveBeacon& beac: beacons){
		str+=beac.toString()+",";
	}
	str+="]";
	LOGI("%s",str.c_str());

	UpdateCycle update_cycle;
	for(auto it = beacons.begin(); it!=beacons.end();){
		if(!(it->isAlive())){
			it = beacons.erase(it);
			continue;
		}
		LOGI("Update Cycle' : ");
		LOGI("%s",update_cycle.toString().c_str());
		it->updateInactiveFlag();
		Entry new_entry{(it->getEstimatedRssi()),(it->getPosition())};
		update_cycle.insert(new_entry);
		it++;
	}
	LOGI("Update Cycle : ");
	LOGI("%s",update_cycle.toString().c_str());
	//put update cycle into queue.
	unique_lock<mutex> lock(updateQueueMutex);
	update_queue.push(update_cycle);
	lock.unlock();
	newUpdateCycleReady.notify_one();		//notifies the asynchronous reader
}

string UpdateCycle::toString(){
	string str = "[";
	if(!update_cycle.empty()){
		for(const Entry& entry : update_cycle){
			str += entry.toString()+",";
		}
	}
	str+="]";
	return str;
}

void infiniteUpdateLoop(){
	while(true){
		shared_lock<shared_mutex> lock(trilaterationMutex);
		if(!isTrilaterationActive){
			break;
		}
		lock.unlock();

		unique_lock<shared_mutex> lock2(activeBeaconMutex);
		cout<<"Generating Update Cycle"<<endl;
		UpdateCycle::generateUpdateCycle(active_beacons);	//move should not occur here.
		lock2.unlock();

		this_thread::sleep_for(chrono::milliseconds(DEFAULT_UPDATE_CYCLE_FREQUENCY));
	}
}
