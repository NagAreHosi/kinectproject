#pragma once
#include "Scheduler.h"
#include <iostream>

using namespace std;

template<class I_FrameSource, class I_FrameReader>
class FrameScheduler :
	public Scheduler
{
public:
	FrameScheduler();
	virtual ~FrameScheduler();

	template<class I_Frame>
	HRESULT acquireLatestFrame(I_Frame*& frame);
private:
	I_FrameSource* frameSource;
	I_FrameReader* frameReader;
};

template<class I_FrameSource, class I_FrameReader>
FrameScheduler<I_FrameSource, I_FrameReader>::FrameScheduler()
{
	this->frameSource = nullptr;
	this->frameReader = nullptr;
}

template<class I_FrameSource, class I_FrameReader>
FrameScheduler<I_FrameSource, I_FrameReader>::~FrameScheduler()
{
	SafeRelease(this->frameReader);
	SafeRelease(this->frameSource);
}

template<class I_FrameSource, class I_FrameReader>
template<class I_Frame>
HRESULT FrameScheduler<I_FrameSource, I_FrameReader>::acquireLatestFrame(I_Frame *& frame)
{
	HRESULT hr;
	IKinectSensor* kinectSensor;
	hr = acquireKinectSensor();
	if (SUCCEEDED(hr))
	{
		if (!getKinectSensor(kinectSensor))
		{
			cerr << "Failure to get kinect senesor!" << endl;
			return hr;
		}

		/*if (typeid(frame) == typeid(IColorFrame*))
		{
			hr = kinectSensor->get_ColorFrameSource(&this->frameSource);
			cout << "color" << endl;
		}
		else if (typeid(frame) == typeid(IBodyFrame*))
		{
			hr = kinectSensor->get_BodyFrameSource(&this->frameSource);
			cout << "body" << endl;
		}
		else
		{
			cerr << "none" << endl;
			return !S_OK;
		}*/

		if (FAILED(hr))
		{
			cerr << "Failure to get frame source!" << endl;
			return hr;
		}

		hr = this->frameSource->OpenReader(&this->frameReader);
		if (FAILED(hr))
		{
			cerr << "Failure to open frame reader!" << endl;
			return hr;
		}

		hr = this->frameReader->AcquireLatestFrame(&frame);
		if (FAILED(hr))
		{
			cerr << "Failure to acquire latest frame!" << endl;
			return hr;
		}

		cout << "Succeessfully acquire latest frame!" << endl;
	}
	cerr << "Failure to acquire latest frame!" << endl;
	return hr;
}

