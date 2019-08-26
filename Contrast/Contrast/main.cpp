#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;
// basic contrast
void contrast1()
{
	Mat src = imread("D:\\Downloads\\leaves.jpg", IMREAD_GRAYSCALE);
	Mat resizeSrc;

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	
	resize(src, resizeSrc, Size(640, 480), 0, 0, INTER_AREA);

	float s = 2.f;
	Mat dst = s * resizeSrc;

	imshow("src", resizeSrc);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}
// saturate + effective contrast
void contrast2()
{
	Mat src = imread("D:\\Downloads\\leaves.jpg", IMREAD_GRAYSCALE);
	Mat resizeSrc;

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	resize(src, resizeSrc, Size(640, 480), 0, 0, INTER_AREA);

	float alpha = 2.f;
	Mat dst = resizeSrc +(resizeSrc - 128) * alpha;

	imshow("src", resizeSrc);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}
int main(void)
{
	contrast2();
	return 0;
}