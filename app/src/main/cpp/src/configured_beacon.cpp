#include"configured_beacon.h"

ConfiguredBeacon::Builder* ConfiguredBeacon::Builder::create(){
	cnfg_beacon_ptr = new ConfiguredBeacon();
	return this;
}

ConfiguredBeacon::Builder* ConfiguredBeacon::Builder::setId(int id_){
	cnfg_beacon_ptr -> id = id_;
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

ConfiguredBeacon::Builder* ConfiguredBeacon::Builder::registerFilter(Filter* filter){
	(cnfg_beacon_ptr -> filters).push_back(filter);
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
