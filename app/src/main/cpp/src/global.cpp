#include"global.h"

ThreadPool pool{5};

//Some Defaults:
const float DEFAULT_N = 1.63;
const int DEFAULT_D0 = 100;
const int DEFAULT_RSSI_D0 = -81;
const Position DEFAULT_POS{0,1,0};		//invalid position
const float DEFAULT_X_SIGMA = 0;
const float DEFAULT_BEACON_COEFF = 1;
const int MAX_INACTIVE_FLAG = 3;
const int DEFAULT_UPDATE_CYCLE_FREQUENCY = 350;	//in ms
const int MIN_ACCEPTABLE_RSSI = -97;

const unsigned int MAX_UPDATE_CYCLES_IN_QUEUE = 3;

shared_mutex trilaterationMutex;
//condition_variable trilateration_condition;
bool isTrilaterationActive = false;

volatile Position user_position{0,0,0};
shared_mutex positionMutex;
