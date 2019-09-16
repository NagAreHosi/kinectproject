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
	inline void safeRelease(Interface*& pInterfaceToRelease);
protected:
	static IKinectSensor* kinectSensor;
	static HRESULT initKinectSensor();
private:
	static bool kSnrIsInitialized;
};

template<class Interface>
inline void Scheduler::safeRelease(Interface*& pInterfaceToRelease)
{
	if (pInterfaceToRelease != NULL)
	{
		pInterfaceToRelease->Release();
		pInterfaceToRelease = NULL;
	}
}