#ifndef CALLBACK_H
#define CALLBACK_H

#include<string>

using namespace std;

class BeaconCallback{

private:
	int id;
	int rssi;

public:
	BeaconCallback(int id, int rssi): id{id}, rssi{rssi}{}

	int getId(){
		return id;
	}

	int getRssi(){
		return rssi;
	}

	string toString(){
		string str = "";
		return str + "("+to_string(id)+", "+to_string(rssi)+")";
	}
};

#endif
