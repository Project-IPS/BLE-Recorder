#ifndef CONFIGURED_BEACON_H
#define CONFIGURED_BEACON_H

#include<vector>
#include<utility>
#include<algorithm>		//for std::find
#include"global.h"
#include"filter.h"

using namespace std;

class ConfiguredBeacon{

protected:
	int rssi_d0;
	int d0;
	string uuid;
	int major;
	int minor;
	Position pos;
	[[maybe_unused]] float beacon_coeff;
	float x_sigma;
	vector<Filter *> filters; 	// filter observers
	ConfiguredBeacon* next = nullptr;		//for chaining - maybe.
								//Not required if HashTable is a separate class.

	ConfiguredBeacon():rssi_d0{DEFAULT_RSSI_D0}, d0{DEFAULT_D0}, uuid{""}, major{-1}, minor{-1}, pos{DEFAULT_POS}, beacon_coeff{DEFAULT_BEACON_COEFF},
			x_sigma{DEFAULT_X_SIGMA}, next{nullptr}{}

	//Moving a ConfiguredBeacon would delete the vector of filters in the original object.
	ConfiguredBeacon(ConfiguredBeacon&&) = delete;
	ConfiguredBeacon& operator=(ConfiguredBeacon&&) = delete;

public:
	virtual ~ConfiguredBeacon(){}

	ConfiguredBeacon(const ConfiguredBeacon&) = default;
	ConfiguredBeacon& operator=(ConfiguredBeacon&) = default;

	bool operator==(const ConfiguredBeacon& beacon) const{
		if((this->getUuid() == beacon.getUuid())&&(this->getMajor() == beacon.getMajor())&&(this->getMinor() == beacon.getMinor())){
			return true;
		}
		else{
			return false;
		}
	}
	bool operator!=(const ConfiguredBeacon& beacon) const{
		return !(this->operator==(beacon));
	}

	class Builder{
	private:
		ConfiguredBeacon* cnfg_beacon_ptr;

	public:
		Builder* create();
		Builder* setId(string uuid, int major, int minor);
		Builder* setPos(int x, int y, int z);
		Builder* setRssiD0(int rssi);
		Builder* setD0(int d);
		Builder* setBeaconCoeff(float coeff);
		Builder* setXSigma(float x_sig);
		Builder* registerFilter(const Filter* filter);

		[[maybe_unused]] Builder* removeFilter(Filter* filter);
		ConfiguredBeacon& build();
		/**
		 * This a bad function. Try to avoid using it as
		 * it would return a back pointer and may lead to
		 * memory leaks.
		 */
        [[maybe_unused]] ConfiguredBeacon* getConfiguredBeaconPointer() const;
	};

	string getUuid() const{
		return uuid;
	}

	int getMajor() const{
		return major;
	}

	int getMinor() const{
		return minor;
	}

	[[ maybe_unused ]] ConfiguredBeacon* getNext() const{
		return next;		//Inside the hash function this pointer can be checked as not null
	}

	vector<Filter*> getFilters() const{
		return filters;
	}

	Position getPosition() const{
		return pos;
	}

	string toString() const;
};

extern vector<ConfiguredBeacon> configured_beacons;

#endif
