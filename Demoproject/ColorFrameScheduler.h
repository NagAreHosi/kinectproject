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
	virtual HRESULT acquireLatestFrame();

	long long int getFailureTime();
	long long int getSuccessTime();

private:
	friend class ColorImage;
	IColorFrameSource* colorFrameSource;
	IColorFrameReader* colorFrameReader;
	IColorFrame* colorFrame;
	IFrameDescription* description;
	bool isInitialized;
	
	void initSchduler();

	long long int failureTime;
	long long int successTime;
};

