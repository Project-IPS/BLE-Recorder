#ifndef TRILATERATION_H
#define TRILATERATION_H

#include"update_cycle.h"

using namespace std;

void startTrilateration();

void stopTrilateration();

void inline asynchronous_reader(){
	while(true){
		cout<<"Asynchronous Reader called"<<endl;

		unique_lock<mutex> lock(updateQueueMutex);
		newUpdateCycleReady.wait(lock,[](){
			shared_lock<shared_mutex> lock2(trilaterationMutex);
			if(!isTrilaterationActive){
				lock2.unlock();
				return true;
			}
			lock2.unlock();
			return !update_queue.empty();
		});

		shared_lock<shared_mutex> lock2(trilaterationMutex);
		if(!isTrilaterationActive){
			cout<<"Exiting Asynchronous reader"<<endl;
			lock2.unlock();
			break;
		}
		lock2.unlock();

		if(update_queue.size()>MAX_UPDATE_CYCLES_IN_QUEUE){
			while(update_queue.size()>1){
				cout<<"Popping update cycle"<<endl;
				update_queue.pop();
			}
		}

		UpdateCycle currentUpdateCycle = update_queue.front();
		update_queue.pop();
		lock.unlock();

		string str = "Running Reader on current update cycle: "+currentUpdateCycle.toString();
		cout<<str<<endl;

		//pass current update cycle to trilateration/multilateration function.
	}
}

extern ScopedThread readerThread;

#endif
