//
// Created by aurok on 21-01-2022.
//
#include "dead_reckoning.h"

Position dr_position{0,0,0};
shared_mutex drPositionMutex;

int step_length = 74;

void initializeDeadReckoning(int x,int y, int z){
    dr_position = Position(x,y,z);
}

void onPositionUpdated(int x, int y){
    LOGI("New Position: {%d,%d}",x,y);
}