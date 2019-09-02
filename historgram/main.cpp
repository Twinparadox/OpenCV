#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;
int main(void)
{
	Mat src1 = imread("C:\\Users\\wonwoo\\Downloads\\room.jpg", IMREAD_GRAYSCALE);
	Mat src2 = imread("C:\\Users\\wonwoo\\Downloads\\leaves.jpg", IMREAD_GRAYSCALE);
	Mat rSrc1, rSrc2;

	resize(src1, rSrc1, Size(640, 480), 0, 0, INTER_AREA);
	resize(src2, rSrc2, Size(640, 480), 0, 0, INTER_AREA);

	Mat dst;

	dst = 0.5*rSrc1 + 0.5*rSrc2;

	imshow("dst", dst);
	waitKey(0);
	destroyAllWindows();
}