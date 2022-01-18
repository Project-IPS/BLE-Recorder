#ifndef GLOBAL_H
#define GLOBAL_H

#include<iostream>
#include "../libs/thread_pool.h"
#include "beacon_callback.h"
#include"position.h"
#include<shared_mutex>
#include <android/log.h>
#ifdef LOGI
#undef LOGI
#endif
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-lib::", __VA_ARGS__))

using namespace std;

extern ThreadPool pool;

//Some Defaults:
extern const float DEFAULT_N;
extern const int DEFAULT_D0;
extern const int DEFAULT_RSSI_D0;
extern const Position DEFAULT_POS;		//invalid position
extern const float DEFAULT_X_SIGMA;
extern const float DEFAULT_BEACON_COEFF;
extern const int MAX_INACTIVE_FLAG;
extern const int DEFAULT_UPDATE_CYCLE_FREQUENCY;
extern const int MIN_ACCEPTABLE_RSSI;

extern const unsigned int MAX_UPDATE_CYCLES_IN_QUEUE;

extern shared_mutex trilaterationMutex;
//extern condition_variable trilateration_condition;
extern bool isTrilaterationActive;

extern volatile Position user_position;
extern shared_mutex positionMutex;

#endif
