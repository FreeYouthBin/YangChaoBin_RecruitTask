/*
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>

#include<iostream>
#include<string>
using namespace std;
using namespace cv;

//����ͼ��
Mat img;
//�ҶȾ�һ
Mat bgr;
//HSVͼ��
Mat hsv;
//ɫ��
int hmin = 53;
int hmin_Max = 180;
int hmax = 126;
int hmax_Max = 180;
//���Ͷ�
int smin = 73;
int smin_Max = 255;
int smax = 255;
int smax_Max = 255;
//ɫ��
int vmin = 54;
int vmin_Max = 255;
int vmax = 255;
int vmax_Max = 255;

//��ʾԭͼ����
string windowName = "src";
//���ԭͼ�Ĵ���
string dstName = "dst";
//���ͼ��
Mat dst;

//�ص�����
void callBack(int, void*)
{
	//����һ�ź�ɫ��ͼƬ
	dst = Mat::zeros(img.size(), img.type());
	//���룺ֻ�н�����ֵ֮������ص���ʾΪ��ɫ�������ɫ
	Mat mask;
	inRange(hsv, Scalar(hmin, smin, vmin), Scalar(hmax, smax, vmax), mask);
	//������ת��Ϊԭͼ�����ǽ������ɫ�ĵ�ת��Ϊԭ���ĵ�
	//dstԭͼ����ȫ��ɫ�ģ�Ҳ����˵���˳����Ĳ��ֲű�ɫ
	for (int r = 0; r < bgr.rows; r++)
	{
		for (int c = 0; c < bgr.cols; c++)
		{
			if (mask.at<uchar>(r, c) == 255) //uchar����ͨ��ͼ��
			{
				dst.at<Vec3b>(r, c) = bgr.at<Vec3b>(r, c); //Vec3f����3ͨ��ͼ��
			}
		}
	}
	//��������˵�ͼ��
	imshow(dstName, dst);
	//����ͼ��
	//dst.convertTo(dst, CV_8UC3, 255.0, 0);
	imwrite("C:/Users/���/Desktop/������ս��/YangChaoBin_RecruitTask/people.jpg", dst);
}


int main()
{
	img = imread("C:/Users/���/Desktop/������ս��/YangChaoBin_RecruitTask/tag.png");
	if (!img.data || img.channels() != 3)
		return -1;  //�ж��Ƿ��ܶ�ȡͼƬ���Լ�ͼƬͨ�����Ƿ�Ϊ3

	imshow(windowName, img);
	bgr = img.clone();  //����ͼƬ

	//��ɫ�ռ�ת��ΪHSV(0,180)(0,255)(0,255)
	cvtColor(bgr, hsv, CV_BGR2HSV);
	
	//�������ͼ�����ʾ����
	namedWindow(dstName, WINDOW_GUI_EXPANDED);
	//����ɫ��
	//ÿ�ε���ɫ���ʱ�򣬶�����ûص�����
	createTrackbar("hmin", dstName, &hmin, hmin_Max, callBack);
	createTrackbar("hmax", dstName, &hmax, hmax_Max, callBack);
	
	//���ڱ��Ͷ�
	createTrackbar("smin", dstName, &smin, smin_Max, callBack);
	createTrackbar("smax", dstName, &smax, smax_Max, callBack);

	//��������
	createTrackbar("vmin", dstName, &vmin, vmin_Max, callBack);
	createTrackbar("vmax", dstName, &vmax, vmax_Max, callBack);

	callBack(0, 0);
	waitKey(0);
	return 0;
}
*/