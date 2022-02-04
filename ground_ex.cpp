#include "ground_ex.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <math.h>

using namespace   std;
using namespace   cv;

void ground_ex(lines_zoom * zoom,Mat v)
{
    double tmp_dis=0;
    int tmp_num=0;
    Mat dst3(v.rows,v.cols,CV_8UC1,255);
    cvtColor(dst3,dst3,COLOR_GRAY2BGR);
    vector<one_k_clss_line>::iterator it;
    vector<one_k_clss_line>::iterator it_end;
    vector<Vec4f>::iterator it_4f;
  for(it=zoom->k_class.begin();it!=zoom->k_class.end();it++)
  {//遍历所有k_class 
      if((*it).k_present<5)
      {//筛选k_class   选出符合条件的k_class 的长度最长的那个
         //   斜率小于5 都符合   选出斜率小于5   长度最长的那个k_class 
          vector<Vec4f>::iterator it2;
          it2=(*it).line_point_data.begin();  
          cv::Vec4i line_point = *it2;
          double dis=sqrt(((line_point)[3]-(line_point)[1]) * ((line_point)[3]-(line_point)[1])+((line_point)[2]-(line_point)[0]) * ((line_point)[2]-(line_point)[0]));
          cout<<"k:"<<(*it).k_present<<endl;
          cout<<"d:"<<(*it).dis_preset<<endl;
          cout<<"dis:"<<dis<<endl;
          cout<<cv::Point(line_point[0],line_point[1])<<cv::Point(line_point[2],line_point[3])<<endl;
          cout<<"\n"<<endl;
          
          line(dst3,cv::Point(line_point[0],line_point[1]),cv::Point(line_point[2],line_point[3]), cv::Scalar(255, 0, 0), 2);
          
          if(tmp_num==0){//第一次tmp_dis    it_end 赋初值  
          tmp_dis=dis;
          it_end=it;
          }

          if(dis>tmp_dis){//找到更大的dis 更新tmp_dis  和 it_end
            it_end=it;
            tmp_dis=dis;
          }
          //更新tmp_num
          tmp_num++;
     }   
  }
    
    namedWindow("ground",WINDOW_FREERATIO);
    imshow("ground",dst3);
    it_4f = it_end->line_point_data.begin();
    cout<<*it_4f<<endl;
    





};




