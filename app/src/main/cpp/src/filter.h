#ifndef FILTER_H
#define FILTER_H

#include<queue>
#include<math.h>

using namespace std;

class Filter{

protected:
	int estimatedRssi;

public:
	virtual ~Filter(){}

    /**
     * Update the state of this filter observer
     * @param rssi new rssi
     */
    virtual void update(int rssi) = 0;

    int getEstimatedRssi() const{
    	return estimatedRssi;
    }
};

class MeanFilter : public Filter{

private:
	int windowSize;
	int sampleAccumulator;
	queue<int> dataset;

public:
	MeanFilter(int window): windowSize{window}, sampleAccumulator{0}{
		if(window<1){
			windowSize = 1;
		}
	}
	~MeanFilter(){}

	void inline update(int rssi) override{

		if((int)dataset.size()==windowSize){
			sampleAccumulator -= dataset.front();
			dataset.pop();
		}

		dataset.push(rssi);
		sampleAccumulator += rssi;
		estimatedRssi = round(sampleAccumulator*1.0/(dataset.size()));
		string str = "Estimated rssi set to"+to_string(estimatedRssi)+"\n";
		cout<<str;
	}
};

#endif
