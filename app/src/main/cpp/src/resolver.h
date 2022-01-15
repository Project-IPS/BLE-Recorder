#ifndef RESOLVER_H
#define RESOLVER_H

#include"configured_beacon.h"
#include<iostream>
#include"active_beacon.h"

void inline resolve(BeaconCallback callback){

	string msg = "Consumed: "+callback.toString()+"\n";
	cout<<msg<<endl;

	shared_lock<shared_mutex> lock(trilaterationMutex);
	if(!isTrilaterationActive){		//lock on isTrilaterationActive doesn't seem critical here.
		lock.unlock();
		return;
	}
	lock.unlock();

	if(callback.getRssi()<MIN_ACCEPTABLE_RSSI){	//Ignore very weak signals
		return;
	}

	int id = callback.getId();
//	int index = hash(id);
//	configured_beacons[index] == id;
//	configured_beacons[index].getNext() == id;

	unique_lock<shared_mutex> lock2(activeBeaconMutex);
	for(ActiveBeacon& active_beacon : active_beacons){
		if(active_beacon.getId()==id){
			cout<<"Found in Active Beacons"<<endl;
			active_beacon.setRssi(callback.getRssi());
			lock2.unlock();
			return;
		}
	}
	lock2.unlock();

	for(const ConfiguredBeacon& cnf_beacon : configured_beacons){
		if(cnf_beacon.getId() == id){
			cout<<"Initialized from configured beacons"<<endl;
			ActiveBeacon new_active_beacon{&cnf_beacon, callback.getRssi()};
			unique_lock<shared_mutex> lock(activeBeaconMutex);
			active_beacons.push_back(new_active_beacon);
			lock.unlock();
			break;
		}
	}
}

#endif
