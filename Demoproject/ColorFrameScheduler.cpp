#include "ColorFrameScheduler.h"
#include <iostream>

using namespace std;

ColorFrameScheduler::ColorFrameScheduler()
{
	this->failureTime = 0;
	this->successTime = 0;
	this->isInitialized = false;
	this->colorFrameSource = nullptr;
	this->colorFrameReader = nullptr;
	this->colorFrame = nullptr;
	this->description = nullptr;
	this->initSchduler();
	if(this->isInitialized)
		this->colorFrameSource->get_FrameDescription(&this->description);
}

ColorFrameScheduler::~ColorFrameScheduler()
{
	safeRelease(this->colorFrameReader);
	safeRelease(this->colorFrameSource);
	safeRelease(this->colorFrame);
	safeRelease(this->description);
}

void ColorFrameScheduler::initSchduler()
{
	HRESULT hr;
	hr = initKinectSensor();
	if (SUCCEEDED(hr))
	{
		hr = kinectSensor->get_ColorFrameSource(&this->colorFrameSource);
		if (FAILED(hr) || this->colorFrameSource == nullptr)
		{
			cerr << "Failure to get color frame source!" << endl;
			return;
		}

		hr = this->colorFrameSource->OpenReader(&this->colorFrameReader);
		if (FAILED(hr) || this->colorFrameReader == nullptr)
		{
			cerr << "Failure to get color frame source!" << endl;
			return;
		}

		cout << "Succeessfully initialize color frame scheduler!" << endl;
		this->isInitialized = true;
		return;
	}
	cerr << "Failure to initialize color frame scheduler!" << endl;
	return;
}

HRESULT ColorFrameScheduler::acquireLatestFrame()
{
	HRESULT hr = S_OK;
	if (this->isInitialized)
	{
		safeRelease(this->colorFrame);
		while (FAILED(this->colorFrameReader->AcquireLatestFrame(&this->colorFrame)) || colorFrame == nullptr)
		{
			this->failureTime += 1;
		}
		this->successTime += 1;
		return hr;
	}
	return hr;
}

long long int ColorFrameScheduler::getFailureTime()
{
	return this->failureTime;
}

long long int ColorFrameScheduler::getSuccessTime()
{
	return this->successTime;
}
