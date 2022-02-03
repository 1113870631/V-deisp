#include <iostream>
#include <opencv2/opencv.hpp>
#include </usr/include/opencv2/calib3d/calib3d_c.h>
#include "omp.h"
#include "U_V.h"
#include "line_zoom.h"

using namespace std;
using namespace cv;

int   setNumDisparities=1;//最大视差
int   setblock=1;//窗口大小
int   setUniquenessRatio,setSpeckleWindowSize,setSpeckleRange,setDisp12MaxDiff,p1=8,p2=32;

  Mat im0 = cv::imread("../im2.png");
  Mat im1 = cv::imread("../im6.png");
  Mat grayLeft,grayRight;
  Mat im3   = Mat(im1.rows, im1.cols, CV_16S);

  cv::Ptr<cv::StereoSGBM> sgbm= cv::StereoSGBM::create(0,9, setblock);

int main()
{

  double max,min;
  int x,y;
  Mat disp;

  disp=imread("../disp.png");

  cvtColor(disp,disp,COLOR_BGR2GRAY);
  disp.convertTo(disp,CV_8UC1);

  cv::minMaxIdx 	( disp,&min,&max,&x,&y,noArray() ) ;
  cv::Mat UdispMap=cv::Mat(max,disp.cols,CV_16UC1);
  cv::Mat VdispMap=cv::Mat(disp.rows,max,CV_16UC1);
  computeUDisparity(UdispMap,disp);
  computeVDisparity(VdispMap, disp);
  UdispMap.convertTo(UdispMap,CV_8UC1);
   VdispMap.convertTo(VdispMap,CV_8UC1);
//v图二值化
  threshold(VdispMap,VdispMap,200,255,THRESH_BINARY);
  //滤波
 //boxFilter( VdispMap, VdispMap,-1, Size(5,5),  Point(-1,-1),true,BORDER_DEFAULT );
 //medianBlur(VdispMap, VdispMap, 3 );
 namedWindow("u",WINDOW_FREERATIO);
 imshow("u",UdispMap);
 namedWindow("v",WINDOW_FREERATIO);
 imshow("v",VdispMap);
 //直线检测 直线聚合
 MethodOne(VdispMap);
 waitKey(0);

  return 0;
}

