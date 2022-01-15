#include"trilateration.h"

ScopedThread readerThread;

void startTrilateration(){
	unique_lock<shared_mutex> lock(trilaterationMutex);
	isTrilaterationActive = true;
	lock.unlock();

	updateCycleThread.post(infiniteUpdateLoop);
	readerThread.post(asynchronous_reader);
}

void stopTrilateration(){
	unique_lock<shared_mutex> lock(trilaterationMutex);
	isTrilaterationActive = false;
	lock.unlock();
	updateCycleThread.join();
	newUpdateCycleReady.notify_one();
	readerThread.join();
}
