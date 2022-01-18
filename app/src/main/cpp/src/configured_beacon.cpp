#include"configured_beacon.h"

#include <utility>

ConfiguredBeacon::Builder* ConfiguredBeacon::Builder::create(){
	cnfg_beacon_ptr = new ConfiguredBeacon();
	return this;
}

ConfiguredBeacon::Builder* ConfiguredBeacon::Builder::setId(string uuid_, int major_, int minor_){
	cnfg_beacon_ptr -> uuid = std::move(uuid_);
	cnfg_beacon_ptr -> major = major_;
	cnfg_beacon_ptr -> minor = minor_;
	return this;
}

ConfiguredBeacon::Builder* ConfiguredBeacon::Builder::setPos(int x, int y, int z){
	cnfg_beacon_ptr -> pos = Position(x,y,z);
	return this;
}

ConfiguredBeacon::Builder* ConfiguredBeacon::Builder::setRssiD0(int rssi){
	cnfg_beacon_ptr -> rssi_d0 = rssi;
	return this;
}

ConfiguredBeacon::Builder* ConfiguredBeacon::Builder::setD0(int d){
	cnfg_beacon_ptr -> d0 = d;
	return this;
}

ConfiguredBeacon::Builder* ConfiguredBeacon::Builder::setBeaconCoeff(float coeff){
	cnfg_beacon_ptr -> beacon_coeff = coeff;
	return this;
}

ConfiguredBeacon::Builder* ConfiguredBeacon::Builder::setXSigma(float x_sig){
	cnfg_beacon_ptr -> x_sigma = x_sig;
	return this;
}

ConfiguredBeacon::Builder* ConfiguredBeacon::Builder::registerFilter(const Filter* filter){
	//A copy of the filter should be made here because the filter object is deleted
	//dynamically from java.
	if(const auto* f = dynamic_cast<const MeanFilter*>(filter); f!=nullptr) {
		//Executes if the Filter was indeed of type MeanFilter.
		(cnfg_beacon_ptr->filters).push_back(new MeanFilter{*f});
	}
	return this;
}

ConfiguredBeacon::Builder* ConfiguredBeacon::Builder::removeFilter(Filter* filter){
	auto iterator = find_if((cnfg_beacon_ptr -> filters).begin(),(cnfg_beacon_ptr -> filters).end(),[filter](Filter * f){
	    return (*filter) == (*f);
	});
	if(iterator!= (cnfg_beacon_ptr -> filters).end()){
		(cnfg_beacon_ptr -> filters).erase(iterator);
		//The filter needs to be deleted since it was
		delete *iterator;
	}
	//what otherwise
	return this;
}

ConfiguredBeacon& ConfiguredBeacon::Builder::build(){
	return *cnfg_beacon_ptr;
}

[[maybe_unused]] ConfiguredBeacon* ConfiguredBeacon::Builder::getConfiguredBeaconPointer() const{
	return cnfg_beacon_ptr;
}

string ConfiguredBeacon::toString() const {
	return "ConfiguredBeacon{"+uuid+", "+to_string(major)+", "+to_string(minor)+"}";
}