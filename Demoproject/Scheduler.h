#pragma once
#include <iostream>
#include <Kinect.h>

using namespace std;

class Scheduler
{
public:
	Scheduler();
	//Scheduler(const Scheduler& copy);
	virtual ~Scheduler();

	virtual HRESULT acquireLatestFrame();
	template<class Interface>
	inline void SafeRelease(Interface*& pInterfaceToRelease)
	{
		if (pInterfaceToRelease != NULL)
		{
			pInterfaceToRelease->Release();
			pInterfaceToRelease = NULL;
		}
	}

protected:
	static IKinectSensor* kinectSensor;
	static HRESULT initKinectSensor();

	IColorFrameSource* colorFrameSource;
	IColorFrameReader* colorFrameReader;

	IBodyFrameSource* bodyFrameSource;
	IBodyFrameReader* bodyFrameReader;

private:
	static bool kSnrIsInitialized;
};
