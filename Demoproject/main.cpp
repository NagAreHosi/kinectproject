#include <iostream>
#include <opencv2\imgproc.hpp>	//opencvÍ·ÎÄ¼þ
#include <opencv2\calib3d.hpp>
#include <opencv2\highgui.hpp>
#include "ColorImage.h"

using namespace std;

int main() {
	ColorImage test;
	cv::Mat copy;
	while (1) {
		test.getColorImage(copy);
		imshow("TEST", copy);
		if (cv::waitKey(30) == VK_ESCAPE)
			break;
	}
	system("pause");
	return 0;
}