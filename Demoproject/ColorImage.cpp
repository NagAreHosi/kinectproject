#include "ColorImage.h"



ColorImage::ColorImage()
{
	this->initImage();
}


ColorImage::~ColorImage()
{
	delete myScheduler;
}

void ColorImage::initImage()
{
	this->myScheduler = new ColorFrameScheduler();
	this->myScheduler->description->get_Height(&this->height);
	this->myScheduler->description->get_Width(&this->width);
	this->capacity = this->height * this->width * 4;
	this->image = cv::Mat::zeros(this->height, this->width, CV_8UC4);
}

int ColorImage::getHeight()
{
	return this->height;
}

int ColorImage::getWidth()
{
	return this->width;
}

void ColorImage::getColorImage(cv::Mat& copy)
{
	myScheduler->acquireLatestFrame();
	myScheduler->colorFrame->CopyConvertedFrameDataToArray(this->capacity, this->image.data, ColorImageFormat_Bgra);
	copy = this->image.clone();
	//this->image.release();
}