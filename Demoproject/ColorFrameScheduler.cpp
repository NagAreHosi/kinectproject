#include "ColorFrameScheduler.h"
#include <iostream>

using namespace std;

ColorFrameScheduler::ColorFrameScheduler()
{
	this->failureTime = 0;
	this->successTime = 0;
	this->isInitialized = false;
	this->initSchduler();
}

ColorFrameScheduler::~ColorFrameScheduler()
{
	SafeRelease(this->colorFrameReader);
	SafeRelease(this->colorFrameSource);
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

HRESULT ColorFrameScheduler::acquireLatestFrame(IColorFrame*& colorFrame)
{
	HRESULT hr = S_OK;
	if (this->isInitialized)
	{
		hr = this->colorFrameReader->AcquireLatestFrame(&colorFrame);
		if (FAILED(hr) || colorFrame == nullptr)
		{
			this->failureTime += 1;
			return hr;
		}

		this->successTime += 1;
		return hr;
	}
	this->failureTime += 1;
	return hr;
}

bool ColorFrameScheduler::getFrameDescription(IFrameDescription*& frameDescription)
{
	if (!this->isInitialized)
	{
		cerr << "Failure to get frame description!" << endl;
		return false;
	}
	this->colorFrameSource->get_FrameDescription(&frameDescription);
	return true;
}

long long int ColorFrameScheduler::getFailureTime()
{
	return this->failureTime;
}

long long int ColorFrameScheduler::getSuccessTime()
{
	return this->successTime;
}
