#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;
void filter_embossing()
{
	Mat src = imread("D:\\Downloads\\leaves.jpg", IMREAD_GRAYSCALE);
	Mat resizeSrc;

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	resize(src, resizeSrc, Size(640, 480), 0, 0, INTER_AREA);

	float data[] = { -1,-1,0,-1,0,1,0,1,1 };
	Mat emboss(3, 3, CV_32FC1, data);

	Mat dst;
	filter2D(resizeSrc, dst, -1, emboss, Point(-1, -1), 128);

	imshow("resizeSrc", resizeSrc);
	imshow("dst", dst);

	waitKey(0);
	destroyAllWindows();
}
Mat calcGrayHist(const Mat& img)
{
	CV_Assert(img.type() == CV_8UC1);

	Mat hist;
	int channels[] = { 0 };
	int dims = 1;
	const int histSize[] = { 256 };
	float graylevel[] = { 0,256 };
	const float* ranges[] = { graylevel };

	calcHist(&img, 1, channels, noArray(), hist, dims, histSize, ranges);

	return hist;
}
Mat getGrayHistImage(const Mat& hist)
{
	CV_Assert(hist.type() == CV_32FC1);
	CV_Assert(hist.size() == Size(1, 256));

	double histMax;
	minMaxLoc(hist, 0, &histMax);

	Mat imgHist(100, 256, CV_8UC1, Scalar(255));
	for (int i = 0; i < 256; i++) {
		line(imgHist, Point(i, 100), Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)), Scalar(0));
	}

	return imgHist;
}
void historgram_stretching(const Mat& src)
{
	double gmin, gmax;
	minMaxLoc(src, &gmin, &gmax);

	Mat dst = (src - gmin) * 255 / (gmax - gmin);

	imshow("src", src);
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));
	imshow("dst", dst);
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));

	waitKey();
	destroyAllWindows();
}
void histogram_equalization(const Mat& src)
{
	Mat dst;
	equalizeHist(src, dst);

	imshow("src", src);
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));
	imshow("dst", dst);
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));

	waitKey();
	destroyAllWindows();
}
int main(void)
{
	Mat src = imread("D:\\Downloads\\room.jpg", IMREAD_GRAYSCALE);
	Mat resizeSrc;

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	resize(src, resizeSrc, Size(640, 480), 0, 0, INTER_AREA);

	/*
	Mat hist = calcGrayHist(resizeSrc);
	Mat histG = getGrayHistImage(hist);

	imshow("src", resizeSrc);
	imshow("hist", histG);
	waitKey(0);
	destroyAllWindows();
	*/

	//historgram_stretching(resizeSrc);
	histogram_equalization(resizeSrc);
	return 0;
}