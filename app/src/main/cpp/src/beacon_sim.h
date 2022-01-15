#ifndef BEACON_SIM_H
#define BEACON_SIM_H

#include<random>
#include<chrono>
#include"../libs/scoped_thread.h"
#include"global.h"
#include"resolver.h"

using namespace std;

class BeaconSim{

private:
	const int id;
	const int callback_frequency = 350;		//in ms
	int deviance = 5;
	unsigned int seed = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
	default_random_engine engine{seed};
	normal_distribution<double> normal_dist;
	ScopedThread t;

	void inline generateCallbacks(int iterations){
		int i = iterations;
		while(i--){
			BeaconCallback newCallback{id,(int)(normal_dist(engine))};
			string msg= "Callback produced: "+newCallback.toString();
			cout<<msg<<endl;
			pool.post(resolve,newCallback);
			this_thread::sleep_for(chrono::milliseconds(callback_frequency));
		}
	}

public:
	BeaconSim(int id, int mean) : id{id}, normal_dist{(double)mean,(double)deviance}{}

	~BeaconSim(){
		t.join();
	}

	BeaconSim(const BeaconSim&) = delete;
	BeaconSim& operator=(const BeaconSim&) = delete;

	BeaconSim(BeaconSim&&) = delete;
	BeaconSim& operator=(BeaconSim&&) = delete;

	void begin(int iterations){
		t.post([this, iterations]{generateCallbacks(iterations);});
	}
};


#endif
