#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/highgui/highgui_c.h>
using namespace cv;
using namespace std;

#define WINDOW_NAME1 "【原始图窗口】"			 
#define WINDOW_NAME2 "【轮廓图】"					

Mat g_srcImage;
Mat g_grayImage;
int g_nThresh = 80;
int g_nThresh_max = 255;
RNG g_rng(12345);
Mat g_cannyMat_output;
vector<vector<Point>> g_vContours;
vector<Vec4i> g_vHierarchy;

//设置灰度图参数
Mat hsv;
Mat mask;
//色相
int hmin = 53;
int hmin_Max = 180;
int hmax = 126;
int hmax_Max = 180;
//饱和度
int smin = 73;
int smin_Max = 255;
int smax = 255;
int smax_Max = 255;
//色调
int vmin = 86;
int vmin_Max = 255;
int vmax = 255;
int vmax_Max = 255;
string dstName = "dst";

void on_ThreshChange(int, void*);
void callBack(int, void*);

int main(int argc, char** argv)
{
	g_srcImage = imread("C:/Users/杨朝斌/Desktop/机器人战队/YangChaoBin_RecruitTask/tag.png", 1); //生成BGR对象
	
	if (!g_srcImage.data) { printf("读取图片错误，请确定目录下是否有imread函数指定的图片存在~！ \n"); return false; }
	
	//对原来的图像进行颜色分割,只剩下颜色方块
	
	cvtColor(g_srcImage, hsv, CV_BGR2HSV);
	
	
	namedWindow(WINDOW_NAME1, CV_WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, g_srcImage);
	
	//blur(g_grayImage, g_grayImage, Size(3, 3));
	//定义输出图像的显示窗口
	namedWindow(dstName, WINDOW_GUI_EXPANDED);
	//每次调节色相的时候，都会调用回调函数
	createTrackbar("hmin", dstName, &hmin, hmin_Max, callBack);
	createTrackbar("hmax", dstName, &hmax, hmax_Max, callBack);

	//调节饱和度
	createTrackbar("smin", dstName, &smin, smin_Max, callBack);
	createTrackbar("smax", dstName, &smax, smax_Max, callBack);

	//调节亮度
	createTrackbar("vmin", dstName, &vmin, vmin_Max, callBack);
	createTrackbar("vmax", dstName, &vmax, vmax_Max, callBack);



	//createTrackbar("canny阈值", WINDOW_NAME1, &g_nThresh, g_nThresh_max, on_ThreshChange);
	//on_ThreshChange(0, 0);
	callBack(0, 0);
	waitKey(0);
	return(0);
}

void on_ThreshChange(int, void*)
{

	Canny(g_grayImage, g_cannyMat_output, g_nThresh, g_nThresh * 2, 3);

	findContours(g_cannyMat_output, g_vContours, g_vHierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	Mat drawing = Mat::zeros(g_cannyMat_output.size(), CV_8UC3);
	for (int i = 0; i < g_vContours.size(); i++)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));//任意值
		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
	}

	imshow(WINDOW_NAME2, drawing);
}

//回调函数
void callBack(int, void*)
{	
	//掩码：只有介于阈值之间的像素点会表示为黑色，否则白色
	inRange(hsv, Scalar(hmin, smin, vmin), Scalar(hmax, smax, vmax), mask); //这里是对HSV对象进行操作
	//将dst变成只有色块的图，其它区域都是黑色
	Mat dst = Mat::zeros(g_srcImage.size(), g_srcImage.type());
	for (int r = 0; r < g_srcImage.rows; r++)
	{
		for (int c = 0; c < g_srcImage.cols; c++)
		{
			if (mask.at<uchar>(r, c) == 255) //uchar代表单通道图像
			{
				dst.at<Vec3b>(r, c) = g_srcImage.at<Vec3b>(r, c); //Vec3f代表3通道图像
			}
		}
	}
	imwrite("C:/Users/杨朝斌/Desktop/机器人战队/YangChaoBin_RecruitTask/切割出的色块.jpg", dst);
	//寻找出色块的轮廓，并进行标记
	cvtColor(dst, g_grayImage, CV_BGR2GRAY);
	Canny(g_grayImage, g_cannyMat_output, g_nThresh, g_nThresh * 2, 3);

	findContours(g_cannyMat_output, g_vContours, g_vHierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	Mat drawing = Mat::zeros(g_cannyMat_output.size(), CV_8UC3);
	for (int i = 0; i < g_vContours.size(); i++)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));//任意值
		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
	}
	imshow(dstName, drawing);
	
}