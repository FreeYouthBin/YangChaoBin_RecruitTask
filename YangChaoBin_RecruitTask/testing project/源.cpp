/*
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>

#include<iostream>
#include<string>
using namespace std;
using namespace cv;

//输入图像
Mat img;
//灰度均一
Mat bgr;
//HSV图像
Mat hsv;
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
int vmin = 54;
int vmin_Max = 255;
int vmax = 255;
int vmax_Max = 255;

//显示原图窗口
string windowName = "src";
//输出原图的窗口
string dstName = "dst";
//输出图像
Mat dst;

//回调函数
void callBack(int, void*)
{
	//创建一张黑色的图片
	dst = Mat::zeros(img.size(), img.type());
	//掩码：只有介于阈值之间的像素点会表示为黑色，否则白色
	Mat mask;
	inRange(hsv, Scalar(hmin, smin, vmin), Scalar(hmax, smax, vmax), mask);
	//将掩码转换为原图，就是将掩码黑色的点转换为原来的点
	//dst原图是完全黑色的，也就是说过滤出来的部分才变色
	for (int r = 0; r < bgr.rows; r++)
	{
		for (int c = 0; c < bgr.cols; c++)
		{
			if (mask.at<uchar>(r, c) == 255) //uchar代表单通道图像
			{
				dst.at<Vec3b>(r, c) = bgr.at<Vec3b>(r, c); //Vec3f代表3通道图像
			}
		}
	}
	//输出过滤了的图像
	imshow(dstName, dst);
	//保存图像
	//dst.convertTo(dst, CV_8UC3, 255.0, 0);
	imwrite("C:/Users/杨朝斌/Desktop/机器人战队/YangChaoBin_RecruitTask/people.jpg", dst);
}


int main()
{
	img = imread("C:/Users/杨朝斌/Desktop/机器人战队/YangChaoBin_RecruitTask/tag.png");
	if (!img.data || img.channels() != 3)
		return -1;  //判断是否能读取图片，以及图片通道数是否为3

	imshow(windowName, img);
	bgr = img.clone();  //复制图片

	//颜色空间转换为HSV(0,180)(0,255)(0,255)
	cvtColor(bgr, hsv, CV_BGR2HSV);
	
	//定义输出图像的显示窗口
	namedWindow(dstName, WINDOW_GUI_EXPANDED);
	//调节色相
	//每次调节色相的时候，都会调用回调函数
	createTrackbar("hmin", dstName, &hmin, hmin_Max, callBack);
	createTrackbar("hmax", dstName, &hmax, hmax_Max, callBack);
	
	//调节饱和度
	createTrackbar("smin", dstName, &smin, smin_Max, callBack);
	createTrackbar("smax", dstName, &smax, smax_Max, callBack);

	//调节亮度
	createTrackbar("vmin", dstName, &vmin, vmin_Max, callBack);
	createTrackbar("vmax", dstName, &vmax, vmax_Max, callBack);

	callBack(0, 0);
	waitKey(0);
	return 0;
}
*/