//
// Created by aurok on 21-01-2022.
//

#ifndef DEAD_RECKONING_H
#define DEAD_RECKONING_H

#include "position.h"
#include <shared_mutex>
#include <android/log.h>
#ifdef LOGI
#undef LOGI
#endif
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-lib::", __VA_ARGS__))

extern Position dr_position;
extern shared_mutex drPositionMutex;

extern int step_length;   //in cm.

void initializeDeadReckoning(int x, int y, int z);

void onPositionUpdated(int x, int y);

void inline onStepDetected(float rotMatrix[]){
    int inc_x = rotMatrix[1]*step_length;
    int inc_y = rotMatrix[4]*step_length;
    int new_x = dr_position.getX()+inc_x;
    int new_y = dr_position.getY()+inc_y;
    unique_lock<shared_mutex> lock(drPositionMutex);
    dr_position.setX(new_x);
    dr_position.setY(new_y);
    lock.unlock();
    onPositionUpdated(new_x, new_y);
}

#endif //DEAD_RECKONING_H
