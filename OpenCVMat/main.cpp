#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;
void MatOp1()
{
	Mat img1; // empty

	Mat img2(480, 640, CV_8UC1); // unsigned char, 1 ch
	Mat img3(480, 640, CV_8UC3); // unsigned char, 3 ch
	Mat img4(Size(640, 480), CV_8UC3); // Size(width, height)

	Mat img5(480, 640, CV_8UC1, Scalar(128)); // initial value : 128
	Mat img6(480, 640, CV_8UC3, Scalar(0, 0, 255)); // initial values : red

	Mat mat1 = Mat::zeros(3, 3, CV_32SC1); // 0's matrix
	Mat mat2 = Mat::ones(3, 3, CV_32FC1); // 1's matrix
	Mat mat3 = Mat::eye(3, 3, CV_32FC1); // identity matrix

	float data[] = { 1,2,3,4,5,6 };
	Mat mat4(2, 3, CV_32FC1, data);

	Mat mat5 = (Mat_<float>(2, 3) << 1, 2, 3, 4, 5, 6);
	Mat mat6 = Mat_<uchar>({ 2,3 }, { 1,2,3,4,5,6 });

	mat4.create(256, 256, CV_8UC3); // uchar, 3 ch
	mat5.create(4, 4, CV_32FC1); // float, 1 ch

	mat4 = Scalar(255, 0, 0);
	mat5.setTo(1.f);
}
void MatOp2()
{
	Mat img1 = imread("dog.png");
	
	Mat img2 = img1;
	Mat img3;
	img3 = img1;

	Mat img4 = img1.clone();
	Mat img5;
	img1.copyTo(img5);

	img1.setTo(Scalar(0, 255, 255)); // yellow

	imshow("img1", img1);
	imshow("img2", img2);
	imshow("img3", img3);
	imshow("img4", img4);
	imshow("img5", img5);

	waitKey();
	destroyAllWindows();
}
void MatOp3()
{
	Mat img1 = imread("cat.bmp");

	if (img1.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat img2 = img1(Rect(220, 120, 340, 240));
	Mat img3 = img1(Rect(220, 120, 340, 240)).clone();

	img2 = ~img2;

	imshow("img1", img1);
	imshow("img2", img2);
	imshow("img3", img3);

	waitKey();
	destroyAllWindows();
}
void camera_in()
{
	VideoCapture cap(0);

	if (!cap.isOpened()) {
		cerr << "Camera open failed!" << endl;
		return;
	}
	
	cout << "Frame Width: " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << "Frame Height: " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;

	Mat frame, inversed;
	while (true) {
		cap >> frame;
		if (frame.empty())
			break;

		inversed = ~frame;

		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(10) == 27)
			break;
	}

	destroyAllWindows();
}
void video_in()
{
	VideoCapture cap("C:\\Users\\wonwoo\\Downloads\\rain.mp4");

	if (!cap.isOpened()) {
		cerr << "Video open failed!" << endl;
		return;
	}

	cout << "Frame W: " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << "Frame H: " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;
	cout << "Frame Count: " << cvRound(cap.get(CAP_PROP_FRAME_COUNT)) << endl;

	double fps = cap.get(CAP_PROP_FPS);
	cout << "FPS: " << fps << endl;

	int delay = cvRound(1000 / fps);

	Mat frame, inversed;
	while (true) {
		cap >> frame;
		if (frame.empty())
			break;

		inversed = ~frame;

		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(10) == 27)
			break;
	}

	destroyAllWindows();
}
void camera_in_video_out()
{
	VideoCapture cap(0);

	if (!cap.isOpened()) {
		cerr << "Camera open failed!" << endl;
		return;
	}

	int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));
	int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));
	double fps = cap.get(CAP_PROP_FPS);

	int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');
	int delay = cvRound(1000 / fps);

	VideoWriter outputVideo("output.avi", fourcc, fps, Size(w, h));

	if (!outputVideo.isOpened()) {
		cerr << "File open failed" << endl;
		return;
	}

	Mat frame, inversed;
	while (true) {
		cap >> frame;
		if (frame.empty())
			break;

		inversed = ~frame;

		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(10) == 27)
			break;
	}

	destroyAllWindows();
}
void mask_setTo()
{
	Mat src = imread("C:\\Users\\wonwoo\\Downloads\\room.jpg", IMREAD_COLOR);
	Mat mask = imread("C:\\Users\\wonwoo\\Downloads\\mask_smile.bmp", IMREAD_GRAYSCALE);

	if (src.empty() || mask.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	src.setTo(Scalar(0, 255, 255), mask);

	imshow("src", src);
	imshow("mask", mask);

	waitKey(0);
	destroyAllWindows();
}
int main(void)
{

	// 기본 출력
	/*
	cout << "Hello OpenCV " << CV_VERSION << endl;

	Mat img;
	img = imread("logo.png");

	if (img.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	namedWindow("logo");
	imshow("logo", img);

	waitKey();
	*/

	// Scalar
	/*
	Scalar gray = 128;
	cout << "gray: " << gray << endl;

	Scalar yellow(0, 255, 255);
	cout << "yellow: " << yellow << endl;

	Mat img1(256, 256, CV_8UC3, yellow);

	for (int i = 0; i < 4; i++)
		cout << yellow[i] << endl;

	namedWindow("yellow");
	imshow("yellow", img1);

	waitKey();
	return 0;
	*/

	//camera input
	//camera_in();

	// video input
	//video_in();

	// camera input & video output
	//camera_in_video_out();

	mask_setTo();
}