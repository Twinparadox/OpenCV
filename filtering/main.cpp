#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

Mat calculateGrayHist(const Mat& img)
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
void blurring_mean(const Mat& src)
{
	imshow("src", src);

	Mat dst;
	for (int ksize = 3; ksize <= 15; ksize += 4) {
		blur(src, dst, Size(ksize, ksize));

		String desc = format("Mean: %dx%d", ksize, ksize);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);

		imshow("dst", dst);
		waitKey(0);
	}

	destroyAllWindows();
}
void blurring_gaussian(const Mat& src)
{
	imshow("src", src);

	Mat dst;
	for (int sigma = 1; sigma <= 5; sigma++) {
		GaussianBlur(src, dst, Size(), (double)sigma);

		String desc = format("sigma: %d", sigma);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);

		imshow("dst", dst);
		waitKey(0);
	}

	destroyAllWindows();
}
void unsharp_mask(const Mat& src)
{
	for (int sigma = 1; sigma <= 5; sigma++) {
		Mat blurred;
		GaussianBlur(src, blurred, Size(), sigma);

		float alpha = 1.f;
		Mat dst = (1 + alpha)*src - alpha * blurred;

		String desc = format("sigma: %d", sigma);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);

		imshow("dst", dst);
		waitKey(0);
	}

	destroyAllWindows();
}
void noise_gaussian(const Mat& src)
{
	for (int stddev = 10; stddev <= 30; stddev += 10) {
		Mat noise(src.size(), CV_32SC1);
		randn(noise, 0, stddev);

		Mat dst;
		add(src, noise, dst, Mat(), CV_8U);

		String desc = format("stddev: %d", stddev);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);
		
		imshow("dst", dst);
		waitKey(0);
	}

	destroyAllWindows();
}
void filter_bilateral(const Mat& src)
{
	Mat noise(src.size(), CV_32SC1);
	randn(noise, 0, 5);
	add(src, noise, src, Mat(), CV_8U);

	Mat dst1;
	GaussianBlur(src, dst1, Size(), 5);

	Mat dst2;
	bilateralFilter(src, dst2, -1, 10, 5);
	
	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	waitKey();

	destroyAllWindows();
}
void filter_median(Mat& src)
{
	int num = (int)(src.total()*0.1);
	for (int i = 0; i < num; i++) {
		int x = rand() % src.cols;
		int y = rand() % src.rows;
		src.at<uchar>(y, x) = (i % 2) * 255;
	}

	Mat dst1;
	GaussianBlur(src, dst1, Size(), 1);

	Mat dst2;
	medianBlur(src, dst2, 3);

	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	waitKey();

	destroyAllWindows();
}
int main(void)
{
	Mat src = imread("C:\\Users\\wonwoo\\Downloads\\room.jpg", IMREAD_GRAYSCALE);
	Mat resizeSrc, hist;

	if (src.empty() == true) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	resize(src, resizeSrc, Size(640, 480), 0, 0, INTER_AREA);

	//blurring_mean(resizeSrc);
	//blurring_gaussian(resizeSrc);
	//unsharp_mask(resizeSrc);
	//noise_gaussian(resizeSrc);
	//filter_bilateral(resizeSrc);
	filter_median(resizeSrc);
	return 0;
}

