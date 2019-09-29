#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;
void arithmetic(const Mat& src1, const Mat& src2)
{
	Mat dst1, dst2, dst3, dst4;

	add(src1, src2, dst1);
	subtract(src1, src2, dst2);
	addWeighted(src1, 0.5, src2, 0.5, 0, dst3);
	absdiff(src1, src2, dst4);

	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);
	imshow("dst4", dst4);
	waitKey(0);

	destroyAllWindows();
}
void logical(const Mat& src1, const Mat& src2)
{
	Mat dst1, dst2, dst3, dst4;

	bitwise_and(src1, src2, dst1);
	bitwise_or(src1, src2, dst2);
	bitwise_xor(src1, src2, dst3);
	bitwise_not(src1, dst4);

	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);
	imshow("dst4", dst4);
	waitKey(0);

	destroyAllWindows();
}
int main(void)
{
	Mat src1 = imread("D:\\Downloads\\leaves.jpg", IMREAD_GRAYSCALE);
	Mat src2 = imread("D:\\Downloads\\square.bmp", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	Mat rSrc1, rSrc2;
	resize(src1, rSrc1, Size(640, 480), 0, 0, INTER_AREA);
	resize(src2, rSrc2, Size(640, 480), 0, 0, INTER_AREA);

	imshow("src1", rSrc1);
	imshow("src2", rSrc2);
	
	// arithmetic(rSrc1, rSrc2);
	logical(rSrc1, rSrc2);
	
	return 0;
}