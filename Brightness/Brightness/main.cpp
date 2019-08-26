#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;
void brighten1()
{
	Mat src = imread("D:\\Downloads\\leaves.jpg", IMREAD_GRAYSCALE);
	Mat resizeSrc;

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	resize(src, resizeSrc, Size(640, 480), 0, 0, INTER_AREA);

	Mat dst = resizeSrc + 100;

	imshow("src", resizeSrc);
	imshow("dst", dst);
	waitKey();

	destroyAllWindows();
}
void brighten2()
{
	Mat src = imread("D:\\Downloads\\leaves.jpg", IMREAD_GRAYSCALE);
	Mat resizeSrc;

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	resize(src, resizeSrc, Size(640, 480), 0, 0, INTER_AREA);

	Mat dst(resizeSrc.rows, resizeSrc.cols, resizeSrc.type());

	for (int i = 0; i < resizeSrc.rows; i++)
		for (int j = 0; j < resizeSrc.cols; j++)
			dst.at<uchar>(i, j) = saturate_cast<uchar>(resizeSrc.at<uchar>(i, j) + 100);

	/*
	for (int i = 0; i < resizeSrc.rows; i++) {
		for (int j = 0; j < resizeSrc.cols; j++) {
			int v = resizeSrc.at<uchar>(i, j) + 100;
			dst.at<uchar>(i, j) = v > 255 ? 255 : v < 0 ? 0 : v;
		}
	}
	*/

	imshow("src", resizeSrc);
	imshow("dst", dst);
	waitKey();

	destroyAllWindows();
}
void on_brighten(int pos, void* userdata)
{
	Mat src = *(Mat*)userdata;
	Mat dst = src + pos;

	imshow("dst", dst);
}
void brighten3()
{
	Mat src = imread("D:\\Downloads\\leaves.jpg", IMREAD_GRAYSCALE);
	Mat resizeSrc;

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	resize(src, resizeSrc, Size(640, 480), 0, 0, INTER_AREA);

	namedWindow("dst");
	createTrackbar("Brightness", "dst", 0, 100, on_brighten, (void*)&resizeSrc);
	on_brighten(0, (void*)&resizeSrc);

	waitKey();
	destroyAllWindows();
}
int main(void)
{
	brighten3();
	return 0;
}