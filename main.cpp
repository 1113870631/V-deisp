
#include <iostream>
#include <opencv2/opencv.hpp>
#include </usr/include/opencv2/calib3d/calib3d_c.h>
#include "omp.h"
#include <vector>


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


class one_k_clss_line
{
    public:
    double k_present;
    vector<cv::Vec4f>line_point_data;
};

class    lines_zoom
{
    public:
    vector<one_k_clss_line>k_class;
};


/**
 * @brief 
 * 直线聚合
 * 
 * @param img 
 */

    void  line_zoom(vector<Vec4f>plines,double k_dis,double d_dis)
    {
           lines_zoom  zoom1;

            for (size_t i = 0; i < plines.size(); i++)//遍历所有直线
                {
                    cv::Vec4i line = plines[i];
                  
                     double tmp_k=0;
                     //得到tmp_k
                     if((line[2]-line[0])==0)
                     {
                         tmp_k=999;
                     }
                     else{
                          tmp_k=((line[3]-line[1])/(line[2]-line[0]));
                     }
                    //判断是不是第一次
                    if(i==0)
                    {
                        one_k_clss_line one;
                        one.k_present=tmp_k;  
                        Vec4f data=line;
                        one.line_point_data.push_back(data);    
                        zoom1.k_class.push_back(one);
                    }
                    else{//不是第一次
                          //遍历k_present 判断k是不是在已有的k范围内
                          std::vector<one_k_clss_line>::iterator it;
                          for(it=zoom1.k_class.begin();it!=zoom1.k_class.end();it++)
                          {
                              if( tmp_k-(*it).k_present<k_dis&&tmp_k-(*it).k_present>-k_dis )
                              {//在it 的k范围内
                                  (*it).line_point_data.push_back(line);
                               //跳出遍历k_preset 的循环
                                break;
                              }                            
                          }
                          //检查it 是否的等于 end   如果不等于就算找到了相匹配的k  如果 等于就是没有找到相匹配的k
                          if(it==zoom1.k_class.end())
                          {
                              //没有符合的k范围
                              one_k_clss_line one;
                              one.k_present=tmp_k;
                              one.line_point_data.push_back(line);
                              zoom1.k_class.push_back(one);                         
                          }
                    }
                 }

            std::vector<one_k_clss_line>::iterator it;
            for(it=zoom1.k_class.begin();it!=zoom1.k_class.end();it++)
            {
                cout<<(*it).k_present<<endl;
            }
    }


void MethodOne(Mat img)
{
    double distance;
    Vec4f end_point=0;
	// 第一步：转化为灰度图像
	Mat grayImg=img;
	//cvtColor(img, grayImg, COLOR_BGR2GRAY);

	// 第二步：二值化。
	//threshold(grayImg, grayImg, 0, 255, THRESH_OTSU | THRESH_BINARY);

	// 第三步：边缘检测
	Canny(grayImg, grayImg, 100, 200, 3, false);

	// 第四步：霍夫直线检测
   vector<Vec4f>plines;
	HoughLinesP(grayImg, plines, 1, CV_PI/180 , 30,100, 100);
	Mat dst = img.clone();
    Mat dst2(dst.rows,dst.cols,CV_8UC1,255);
    //cv::cvColor(dst2,dst2,COLOR_GRAY2BGR);
   // dst.convertTo(dst,CV_8UC3);
   cvtColor(dst2,dst2,COLOR_GRAY2BGR);
   line_zoom( plines , 10, 0);
   int q=0;
   for (size_t p = 0; p < plines.size(); p++)
    {
        cv::Vec4i linex = plines[p];
        int dx=linex[2]-linex[0];
        int dy=linex[2]-linex[1];
      
    
        line(dst2, cv::Point(linex[0], linex[1]), cv::Point(linex[2], linex[3]), cv::Scalar(0, 0, 255), 2);
        q++;
    
    }


	namedWindow("1",WINDOW_FREERATIO);
	imshow("1", dst2);
    
}



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
MethodOne(VdispMap);
//line_zoom( plines , 0.5, 0, 100);
waitKey(0);

  return 0;
}

