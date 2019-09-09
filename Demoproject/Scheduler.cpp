#include "Scheduler.h"
#include <iostream>

using namespace std;

bool Scheduler::kSnrIsInitialized = false;
IKinectSensor* Scheduler::kinectSensor = nullptr;

HRESULT Scheduler::initKinectSensor()
{
	HRESULT hr = S_OK;
	if (Scheduler::kinectSensor == nullptr || !Scheduler::kSnrIsInitialized)
	{
		hr = GetDefaultKinectSensor(&Scheduler::kinectSensor);
		if (FAILED(hr)) {
			cerr << "Failure to initialize Kinect sensor! " << endl;
			return !S_OK;
		}
		hr = Scheduler::kinectSensor->Open();
		if (FAILED(hr)) {
			cerr << "Failure to open Kinect sensor! " << endl;
			return !S_OK;
		}
		return hr;
	}
	return hr;
}

Scheduler::Scheduler()
{
	this->colorFrameSource = nullptr;
	this->colorFrameReader = nullptr;
	this->bodyFrameSource = nullptr;
	this->bodyFrameReader = nullptr;
}

Scheduler::~Scheduler()
{
	SafeRelease(this->bodyFrameReader);
	SafeRelease(this->bodyFrameSource);
	SafeRelease(this->kinectSensor);
}

HRESULT Scheduler::acquireLatestFrame()
{
	return S_OK;
}
