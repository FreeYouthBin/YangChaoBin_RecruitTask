#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/highgui/highgui_c.h>
using namespace cv;
using namespace std;

#define WINDOW_NAME1 "��ԭʼͼ���ڡ�"			 
#define WINDOW_NAME2 "������ͼ��"					

Mat g_srcImage;
Mat g_grayImage;
int g_nThresh = 80;
int g_nThresh_max = 255;
RNG g_rng(12345);
Mat g_cannyMat_output;
vector<vector<Point>> g_vContours;
vector<Vec4i> g_vHierarchy;

//���ûҶ�ͼ����
Mat hsv;
Mat mask;
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
int vmin = 86;
int vmin_Max = 255;
int vmax = 255;
int vmax_Max = 255;
string dstName = "dst";

void on_ThreshChange(int, void*);
void callBack(int, void*);

int main(int argc, char** argv)
{
	g_srcImage = imread("C:/Users/���/Desktop/������ս��/YangChaoBin_RecruitTask/tag.png", 1); //����BGR����
	
	if (!g_srcImage.data) { printf("��ȡͼƬ������ȷ��Ŀ¼���Ƿ���imread����ָ����ͼƬ����~�� \n"); return false; }
	
	//��ԭ����ͼ�������ɫ�ָ�,ֻʣ����ɫ����
	
	cvtColor(g_srcImage, hsv, CV_BGR2HSV);
	
	
	namedWindow(WINDOW_NAME1, CV_WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, g_srcImage);
	
	//blur(g_grayImage, g_grayImage, Size(3, 3));
	//�������ͼ�����ʾ����
	namedWindow(dstName, WINDOW_GUI_EXPANDED);
	//ÿ�ε���ɫ���ʱ�򣬶�����ûص�����
	createTrackbar("hmin", dstName, &hmin, hmin_Max, callBack);
	createTrackbar("hmax", dstName, &hmax, hmax_Max, callBack);

	//���ڱ��Ͷ�
	createTrackbar("smin", dstName, &smin, smin_Max, callBack);
	createTrackbar("smax", dstName, &smax, smax_Max, callBack);

	//��������
	createTrackbar("vmin", dstName, &vmin, vmin_Max, callBack);
	createTrackbar("vmax", dstName, &vmax, vmax_Max, callBack);



	//createTrackbar("canny��ֵ", WINDOW_NAME1, &g_nThresh, g_nThresh_max, on_ThreshChange);
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
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));//����ֵ
		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
	}

	imshow(WINDOW_NAME2, drawing);
}

//�ص�����
void callBack(int, void*)
{	
	//���룺ֻ�н�����ֵ֮������ص���ʾΪ��ɫ�������ɫ
	inRange(hsv, Scalar(hmin, smin, vmin), Scalar(hmax, smax, vmax), mask); //�����Ƕ�HSV������в���
	//��dst���ֻ��ɫ���ͼ�����������Ǻ�ɫ
	Mat dst = Mat::zeros(g_srcImage.size(), g_srcImage.type());
	for (int r = 0; r < g_srcImage.rows; r++)
	{
		for (int c = 0; c < g_srcImage.cols; c++)
		{
			if (mask.at<uchar>(r, c) == 255) //uchar����ͨ��ͼ��
			{
				dst.at<Vec3b>(r, c) = g_srcImage.at<Vec3b>(r, c); //Vec3f����3ͨ��ͼ��
			}
		}
	}
	imwrite("C:/Users/���/Desktop/������ս��/YangChaoBin_RecruitTask/�и����ɫ��.jpg", dst);
	//Ѱ�ҳ�ɫ��������������б��
	cvtColor(dst, g_grayImage, CV_BGR2GRAY);
	Canny(g_grayImage, g_cannyMat_output, g_nThresh, g_nThresh * 2, 3);

	findContours(g_cannyMat_output, g_vContours, g_vHierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	Mat drawing = Mat::zeros(g_cannyMat_output.size(), CV_8UC3);
	for (int i = 0; i < g_vContours.size(); i++)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));//����ֵ
		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
	}
	imshow(dstName, drawing);
	
}