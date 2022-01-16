//
// Created by aurok on 15-01-2022.
//

#ifndef CPP_FRAMEWORK_H
#define CPP_FRAMEWORK_H

#include<iostream>
#include<vector>
#include<utility>
#include"configured_beacon.h"
#include"beacon_sim.h"
#include"active_beacon.h"
#include "trilateration.h"

using namespace std;

//void initializeConfiguredBeacon(int number);

//void removeConfiguredBeacons();

bool addToConfiguredBeacons(const ConfiguredBeacon& beacon);


#endif //BLE_RECORDER_CPP_FRAMEWORK_H
