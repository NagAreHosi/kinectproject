#pragma once
#include<opencv2/core/core.hpp>
#include "ColorFrameScheduler.h"
class ColorImage
{
public:
	ColorImage();
	//ColorImage(const ColorImage& copy);
	virtual ~ColorImage();
	int getHeight();
	int getWidth();
	void getColorImage(cv::Mat& copy);
private:
	ColorFrameScheduler* myScheduler;
	cv::Mat image;
	int height;
	int width;
	long long int capacity;

	void initImage();
};

