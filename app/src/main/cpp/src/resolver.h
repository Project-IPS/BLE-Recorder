#ifndef RESOLVER_H
#define RESOLVER_H

#include"configured_beacon.h"
#include<iostream>
#include"active_beacon.h"


//void inline resolve(BeaconCallback callback){
//
//	string msg = "Consumed: "+callback.toString()+"\n";
//	cout<<msg<<endl;
//
//	shared_lock<shared_mutex> lock(trilaterationMutex);
//	if(!isTrilaterationActive){		//lock on isTrilaterationActive doesn't seem critical here.
//		lock.unlock();
//		return;
//	}
//	lock.unlock();
//
//	if(callback.getRssi()<MIN_ACCEPTABLE_RSSI){	//Ignore very weak signals
//		return;
//	}
//
//	int id = callback.getId();
////	int index = hash(id);
////	configured_beacons[index] == id;
////	configured_beacons[index].getNext() == id;
//
//	unique_lock<shared_mutex> lock2(activeBeaconMutex);
//	for(ActiveBeacon& active_beacon : active_beacons){
//		if(active_beacon.getId()==id){
//			cout<<"Found in Active Beacons"<<endl;
//			active_beacon.setRssi(callback.getRssi());
//			lock2.unlock();
//			return;
//		}
//	}
//	lock2.unlock();
//
//	for(const ConfiguredBeacon& cnf_beacon : configured_beacons){
//		if(cnf_beacon.getId() == id){
//			cout<<"Initialized from configured beacons"<<endl;
//			ActiveBeacon new_active_beacon{&cnf_beacon, callback.getRssi()};
//			unique_lock<shared_mutex> lock(activeBeaconMutex);
//			active_beacons.push_back(new_active_beacon);
//			lock.unlock();
//			break;
//		}
//	}
//}

void inline resolve(string uuid, int major, int minor, int rssi){
	LOGI("Resolving %s %d %d %d",uuid.c_str(),major,minor,rssi);

	shared_lock<shared_mutex> lock(trilaterationMutex);
	if(!isTrilaterationActive){		//lock on isTrilaterationActive doesn't seem critical here.
		lock.unlock();
		return;
	}
	lock.unlock();

	if(rssi<MIN_ACCEPTABLE_RSSI){	//Ignore very weak signals
		return;
	}

//	int index = hash(id);
//	configured_beacons[index] == id;
//	configured_beacons[index].getNext() == id;

	unique_lock<shared_mutex> lock2(activeBeaconMutex);
	for(ActiveBeacon& active_beacon : active_beacons){
		if((active_beacon.getUuid()==uuid)&&(active_beacon.getMajor()==major)&&(active_beacon.getMinor()==minor)){
			LOGI("Found in Active Beacons");
			active_beacon.setRssi(rssi);
			lock2.unlock();
			return;
		}
	}
	lock2.unlock();

	for(const ConfiguredBeacon& cnf_beacon : configured_beacons){
		if((cnf_beacon.getUuid() == uuid)&&(cnf_beacon.getMajor()==major)&&(cnf_beacon.getMinor()==minor)){
			LOGI("Initialized from configured beacons");
			ActiveBeacon new_active_beacon{&cnf_beacon, rssi};
			unique_lock<shared_mutex> lock3(activeBeaconMutex);
			active_beacons.push_back(new_active_beacon);
			lock3.unlock();
			break;
		}
	}
	LOGI("Configured Beacon not found");
}

#endif
