
#include <iostream>
#include <opencv2/opencv.hpp>
#include </usr/include/opencv2/calib3d/calib3d_c.h>
#include "omp.h"

  /**
     * @brief 
     * sgbm->setPreFilterCap(32);
    int SADWindowSize = 9;
    int sgbmWinSize = SADWindowSize > 0 ? SADWindowSize : 3;
    sgbm->setBlockSize(sgbmWinSize);
    int cn = grayLeft.channels();
    sgbm->setP1(8 * cn*sgbmWinSize*sgbmWinSize);
    sgbm->setP2(32 * cn*sgbmWinSize*sgbmWinSize);
    sgbm->setMinDisparity(0);  最小视差值。
    //sgbm->setNumDisparities(16);  最大视差减最小
    sgbm->setUniquenessRatio(10);uniquenessRatio 最佳（最小）计算成本函数值应该“赢”第二个最佳值以考虑找到的匹配正确的百分比保证金。通常，5-15范围内的值就足够了。
    sgbm->setSpeckleWindowSize(100);平滑视差区域的最大尺寸，以考虑其噪声斑点和无效。将其设置为0可禁用斑点过滤。否则，将其设置在50-200的范围内
    sgbm->setSpeckleRange(32);每个连接组件内的最大视差变化。如果你做斑点过滤，将参数设置为正值，它将被隐式乘以16.通常，1或2就足够好了。
    preFilterCap 预滤波图像像素的截断值
    sgbm->setDisp12MaxDiff(1);左右视差允许最大差异
      sgbm->setMode(cv::StereoSGBM::MODE_SGBM);mode 将其设置为StereoSGBM :: MODE_HH以运行全尺寸双通道动态编程算法。它将消耗O（W * H * numDisparities）字节，这对640x480立体声很大，对于HD尺寸的图片很大。默认情况下，它被设置为false。
     */
using namespace std;
using namespace cv;
int   setNumDisparities=1;//最大视差
int   setblock=1;//窗口大小
int   setUniquenessRatio,setSpeckleWindowSize,setSpeckleRange,setDisp12MaxDiff,p1=8,p2=32;
 // Mat im0 = cv::imread("../ALL/Baby1/view1.png");
  //Mat im1 = cv::imread("../ALL/Baby1/view5.png");
  Mat im0 = cv::imread("../im2.png");
  Mat im1 = cv::imread("../im6.png");


  Mat grayLeft,grayRight;
  Mat im3   = Mat(im1.rows, im1.cols, CV_16S);
cv::Ptr<cv::StereoSGBM> sgbm= cv::StereoSGBM::create(0,9, setblock);

void computeUDisparity(cv::Mat UdispMap,cv::Mat disp)
{
    UdispMap.setTo(0);
    int width=disp.cols;
    int height=disp.rows;
 
    for(int row=0;row<height;row++)
    {
        auto  pRowInDisp=disp.ptr<uchar>(row);
        for(int col=0;col<width;col++)
        {
            uint8_t currDisp=pRowInDisp[col];
            if(currDisp>0&&currDisp<128)
            {
                UdispMap.at<ushort>(currDisp,col)++;
            }
        }
    }
}


void computeVDisparity(cv::Mat &VdispMap,cv::Mat disp)
{
    VdispMap.setTo(0);
    int width=disp.cols;
    int height=disp.rows;
 
    for(int row=0;row<height;row++)
    {
        auto  pRowInDisp=disp.ptr<uchar>(row);
        for(int col=0;col<width;col++)
        {
            uint8_t currDisp=pRowInDisp[col];
            if(currDisp>0&&currDisp<128)
            {
                VdispMap.at<ushort>(row,currDisp)++;
            }
 
        }
    }
}

void MethodOne(Mat img)
{
	// 第一步：转化为灰度图像
	Mat grayImg=img;
	//cvtColor(img, grayImg, COLOR_BGR2GRAY);

	// 第二步：二值化。
	//threshold(grayImg, grayImg, 0, 255, THRESH_OTSU | THRESH_BINARY);

	// 第三步：边缘检测
	Canny(grayImg, grayImg, 100, 200, 3, false);

	// 第四步：霍夫直线检测
   vector<Vec4f>plines;
	HoughLinesP(grayImg, plines, 1, CV_PI/180 , 80,100, 20);
	Mat dst = img.clone();
   // dst.convertTo(dst,CV_8UC3);
    cvtColor(dst,dst,COLOR_BayerBG2BGR);
   Mat line3;
   int j=0;
	for (size_t i = 0; i < plines.size(); i++)
	{
		Vec4f hline = plines[i];
   
           
            double tmpy=0,tmpx=0;
            if((hline[3]- hline[1])<0)
            {
                tmpy=-(hline[3]- hline[1]);
            }
            else{
                     tmpy=(hline[3]- hline[1]);
            }
              if((hline[2]- hline[0])<0)
            {
                tmpx=-(hline[2]- hline[0]);
            }
            else{
                     tmpx=(hline[2]- hline[0]);
            }
             double tmp=(tmpy/tmpx);
            //cout<<tmpy<<endl;
            if(tmp<5){
                     line(dst, Point(hline[0], hline[1]), Point(hline[2], hline[3]), Scalar(0,0,255), 1, LINE_AA);
                     double distance =(hline[3]- hline[1])*(hline[3]- hline[1])+(hline[2]- hline[0])*(hline[2]- hline[0]);
                     j++;
                     cout<<j<<endl;
            }
           
        
		
	}

    namedWindow("1",WINDOW_FREERATIO);
	imshow("1", dst);
}



int main()
{

  double max,min;
  int x,y;
  Mat disp;

  disp=imread("../disp.png");
  //line(disp, Point(0,0), Point(disp.cols,disp.rows), Scalar(255,0,0), 10, LINE_AA);
  //imshow("line",disp);

  cvtColor(disp,disp,COLOR_BGR2GRAY);
  disp.convertTo(disp,CV_8UC1);

  cv::minMaxIdx 	( disp,&min,&max,&x,&y,noArray() ) ;
  cout<<max<<"\n";
  cv::Mat UdispMap=cv::Mat(max,disp.cols,CV_16UC1);
  cv::Mat VdispMap=cv::Mat(disp.rows,max,CV_16UC1);
  computeUDisparity(UdispMap,disp);
  computeVDisparity(VdispMap, disp);
  UdispMap.convertTo(UdispMap,CV_8UC1);
   VdispMap.convertTo(VdispMap,CV_8UC1);
  //namedWindow("win",WINDOW_FREERATIO);
  //imshow("win",UdispMap);
 //namedWindow("v",WINDOW_FREERATIO);
//imshow("v",VdispMap);
    MethodOne(VdispMap );
 


  waitKey(0);

  return 0;
}

