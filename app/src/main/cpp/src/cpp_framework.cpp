//============================================================================
// Name        : Cpp-Framework.cpp
// Author      : Auro
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "cpp_framework.h"

vector<ConfiguredBeacon> configured_beacons;
vector<ActiveBeacon> active_beacons;
shared_mutex activeBeaconMutex;

//void initializeConfiguredBeacon(int number){
//	for(int i=0; i<number; i++){
//
//		ConfiguredBeacon::Builder builder{};
//
//		if(i%2 == 0){	//id is odd
//			configured_beacons.push_back((builder.create()->setId(i+1)->
//				setPos(660, -500-250*i, 240)->registerFilter(new MeanFilter(3))->build()));
//		}
//		else{
//			configured_beacons.push_back(builder.create()->setId(i+1)->
//				setPos(0, -500-250*i, 240)->registerFilter(new MeanFilter(3))->build());
//		}
//		cout<<"Configured Beacon "<<i+1<<"initialized"<<endl;
//	}
//}

/**
 * Adding to configured_beacons is not thread-safe. Add Beacons
 * from a single thread only.
 * @param configured_beacon
 */
bool addToConfiguredBeacons(const ConfiguredBeacon& configured_beacon){
	for(const ConfiguredBeacon& beacon : configured_beacons){
		if(beacon == configured_beacon){
			LOGI("There is already beacon with the same id");
			return false;
		}
	}
	//The Beacon object is dynamically deleted from Java so make
	//sure that a copy is made here.
	configured_beacons.push_back(configured_beacon);
    LOGI("Beacon Added : %s",configured_beacon.toString().c_str());
	return true;
}

//void removeConfiguredBeacons(){
//	for(ConfiguredBeacon& configured_beacon : configured_beacons){
//		for(Filter* filter : configured_beacon.getFilters()){
//			delete filter;				//Filters were allocated using new so they need to be de-allocated using
//										//delete.
//		}
//		delete &configured_beacon;		//The objects in the configured_beacons vector were allocated using new so
//										//they need to be deleted.
//	}
//}


//vector<unique_ptr<BeaconSim>> beacon_sims;
//void initializeBeaconSims(int n){	//n=9;
//
//	vector<int> mean_rssi_values = {-98, -96, -93, -91, -89, -91, -93, -96, -98};
//	for(int i=0; i<9; i++){
//		unique_ptr<BeaconSim> ptr{new BeaconSim(i+1,mean_rssi_values[i])};
//		beacon_sims.emplace_back(move(ptr));
//	}
//}

//void startSimulating(int it){
//	startTrilateration();
//
//	for(unique_ptr<BeaconSim> const& ptr : beacon_sims){
//		ptr->begin(it);
//	}
//
//	this_thread::sleep_for(chrono::milliseconds(4000));
//	stopTrilateration();
//}

//void test1(){
//	int it = 10;
////	cout<<"Enter the number of iterations:\t";
////	cin>>it;
//	cout<<endl;
//	initializeConfiguredBeacon(10);		//id = 1-10 beacons are configured -> Fixed for now
//	cout<<"Configured Beacons initialized"<<endl;
//	initializeBeaconSims(9);
//	cout<<"Beacon Sims initialized"<<endl;
//	//startTrilateration();
//	startSimulating(it);
//	removeConfiguredBeacons();
//}
//
//int main() {
//	cout<<"Hello"<<endl;
//	test1();
//	cout<< "Bye"<<endl;
//	return 0;
//}
