#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;
Point2f srcQuad[4], dstQuad[4];
Mat src1;

void affine_transform(const Mat& src)
{
	Point2f srcPts[3], dstPts[3];
	srcPts[0] = Point2f(0, 0);
	srcPts[1] = Point2f(src.cols - 1, 0);
	srcPts[2] = Point2f(src.cols - 1, src.rows - 1);
	dstPts[0] = Point2f(50, 50);
	dstPts[1] = Point2f(src.cols - 100, 100);
	dstPts[2] = Point2f(src.cols - 50, src.rows - 50);

	Mat m = getAffineTransform(srcPts, dstPts);

	Mat dst;
	warpAffine(src, dst, m, Size());
	
	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}
void affine_translation(const Mat& src)
{
	Mat m = Mat_<double>({ 2,3 }, { 1,0,150,0,1,100 });

	Mat dst;
	warpAffine(src, dst, m, Size());

	imshow("src", src);
	imshow("dst", dst);
	
	waitKey(0);
	destroyAllWindows();
}
void affine_shear(const Mat& src)
{
	double mx = 0.3;
	Mat m = Mat_<double>({ 2,3 }, { 1,mx,0,0,1,0 });

	Mat dst;
	warpAffine(src, dst, m, Size(cvRound(src.cols + src.rows*mx), src.rows));

	imshow("src", src);
	imshow("dst", dst);

	waitKey(0);
	destroyAllWindows();
}
void affine_scale(const Mat& src)
{
	Mat dst1, dst2, dst3, dst4;
	resize(src, dst1, Size(640, 480), 4, 4, INTER_NEAREST);
	resize(src, dst2, Size(640, 480));
	resize(src, dst3, Size(640, 480), 0, 0, INTER_CUBIC);
	resize(src, dst4, Size(640, 480), 0, 0, INTER_LANCZOS4);

	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);
	imshow("dst4", dst4);

	waitKey(0);
	destroyAllWindows();
}
void affine_rotation(const Mat& src)
{
	Point2f cp(src.cols / 2.f, src.rows / 2.f);
	Mat m = getRotationMatrix2D(cp, 20, 1);

	Mat dst;
	warpAffine(src, dst, m, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey(0);
	destroyAllWindows();
}
void affine_flip(const Mat& src)
{
	imshow("src", src);

	Mat dst;
	int flipCode[] = { 1, 0, -1 };
	for (int i = 0; i < 3; i++) {
		flip(src, dst, flipCode[i]);

		String desc = format("flipCode: %d", flipCode[i]);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255, 0, 0), 1, LINE_AA);

		imshow("dst", dst);
		waitKey(0);
	}
	destroyAllWindows();
}
void on_mouse(int event, int x, int y, int flags, void*)
{
	static int cnt = 0;

	if (event == EVENT_LBUTTONDOWN) {
		if (cnt < 4) {
			srcQuad[cnt++] = Point2f(x, y);

			circle(src1, Point(x, y), 5, Scalar(0, 0, 255), -1);
			imshow("src", src1);

			if (cnt == 4) {
				int w = 200, h = 300;

				dstQuad[0] = Point2f(0, 0);
				dstQuad[1] = Point2f(w - 1, 0);
				dstQuad[2] = Point2f(w - 1, h - 1);
				dstQuad[3] = Point2f(0, h - 1);

				Mat pers = getPerspectiveTransform(srcQuad, dstQuad);

				Mat dst;
				warpPerspective(src1, dst, pers, Size(w, h));

				imshow("dst", dst);
			}
		}

	}
}
void perspective()
{
	namedWindow("src");
	setMouseCallback("src", on_mouse);

	imshow("src", src1);
	waitKey(0);
}

int main(void)
{
	Mat src = imread("C:\\Users\\wonwoo\\Downloads\\room.jpg",IMREAD_COLOR);
	src1 = imread("C:\\Users\\wonwoo\\Downloads\\card.bmp", IMREAD_COLOR);
	
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	Mat resizeSrc;
	resize(src, resizeSrc, Size(640, 480), 0, 0, INTER_AREA);

	//affine_transform(resizeSrc);
	//affine_translation(resizeSrc);
	//affine_shear(resizeSrc);
	//affine_scale(src);
	//affine_rotation(resizeSrc);
	//affine_flip(resizeSrc);

	perspective();

	return 0;
}