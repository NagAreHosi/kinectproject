#pragma once
#include "Scheduler.h"
#include <Kinect.h>

class ColorFrameScheduler :
	public Scheduler
{
public:
	ColorFrameScheduler();
	//ColorFrameScheduler(const ColorFrameScheduler& copy);
	virtual ~ColorFrameScheduler();

	virtual HRESULT acquireLatestFrame(IColorFrame*& colorFrame);
	bool getFrameDescription(IFrameDescription*& frameDescription);
	long long int getFailureTime();
	long long int getSuccessTime();
private:
	bool isInitialized;
	void initSchduler();
	long long int failureTime;
	long long int successTime;
};

