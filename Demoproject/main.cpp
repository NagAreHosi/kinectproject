#include <iostream>
#include <opencv2\imgproc.hpp>	//opencvͷ�ļ�
#include <opencv2\calib3d.hpp>
#include <opencv2\highgui.hpp>
#include "Scheduler.h"
#include "ColorFrameScheduler.h"

using namespace std;

int main() {
	ColorFrameScheduler test;
	IColorFrame* myColorFrame = nullptr;
	IFrameDescription* myDescription;
	if (!test.getFrameDescription(myDescription)) {
		cerr << "Failure to get frame description!" << endl;
		return 0;
	}

	int colorHeight, colorWidth;
	myDescription->get_Height(&colorHeight);
	myDescription->get_Width(&colorWidth);
	cv::Mat original(colorHeight, colorWidth, CV_8UC4);
	
	while (1) {
		while (test.acquireLatestFrame(myColorFrame) != S_OK);
		myColorFrame->CopyConvertedFrameDataToArray(colorHeight * colorWidth * 4, original.data, ColorImageFormat_Bgra);
		cv::Mat copy = original.clone();        //��ȡ��ɫͼ�����������
		imshow("TEST", copy);
		test.SafeRelease(myColorFrame);
		if (cv::waitKey(30) == VK_ESCAPE)
			break;
	}
	long long int failures = test.getFailureTime();
	long long int successes = test.getSuccessTime();
	cout << "\nFailure time: " << failures << endl;
	cout << "Success time: " << successes << endl;
	system("pause");
	return 0;
}