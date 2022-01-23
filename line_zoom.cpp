#include <iostream>
#include <opencv2/opencv.hpp>
#include "line_zoom.h"
#include <vector>
#include <math.h>

/**
 * @brief 
 * 直线聚合 
 * @param img 
 */

     lines_zoom *  line_zoom(vector<Vec4f>plines,double k_dis,double d_dis)
    {
           lines_zoom zoom1;
           int k=0;

            for (size_t i = 0; i < plines.size(); i++)//遍历所有直线
                {
                    k++;
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


            //同一斜率范围内的所有直线 以长度为权重进行整合
            std::vector<one_k_clss_line>::iterator it;
            for(it=zoom1.k_class.begin();it!=zoom1.k_class.end();it++)
            {
                double dis=0;
                double x1_e=0,x2_e=0;
                double y1_e=0,y2_e=0;
                int num=0;
                vector<Vec4f>::iterator it2;
                for(it2=(*it).line_point_data.begin();it2!=(*it).line_point_data.end();it2++)
                {//遍历同一k范围内所有点
                     dis+=  sqrt(((*it2)[3]-(*it2)[1]) * ((*it2)[3]-(*it2)[1])-((*it2)[2]-(*it2)[0]) * ((*it2)[2]-(*it2)[0]));
                     num++;
                }
                for(it2=(*it).line_point_data.begin();it2!=(*it).line_point_data.end();it2++)
                {//遍历同一k范围内所有点

                   double   this_dis=sqrt(((*it2)[3]-(*it2)[1]) * ((*it2)[3]-(*it2)[1])-((*it2)[2]-(*it2)[0]) * ((*it2)[2]-(*it2)[0]));
                   this_dis=this_dis/dis;
                   this_dis=1;
                   x1_e+=this_dis*(*it2)[0]; 
                   y1_e+=this_dis*(*it2)[1];

                   x2_e+=this_dis*(*it2)[2];                 
                   y2_e+=this_dis*(*it2)[3];

                }
                x1_e=x1_e/num;
                x2_e=x2_e/num;
                y1_e=y1_e/num;
                y2_e=y2_e/num;
                it2=(*it).line_point_data.begin();
                (*it2)[0]=x1_e;
                (*it2)[1]=y1_e;
                (*it2)[2]=x2_e;
                 (*it2)[3]=y2_e;
                 (*it).k_present=(y1_e-y2_e)/(x1_e-x2_e);
                cout<<(*it).k_present<<endl;
            }
       lines_zoom * zoom_back =new lines_zoom;
       (*zoom_back)=zoom1;
       return zoom_back;
    }

/**
 * @brief 
 * 直线检测
 * @param img 
 */
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
   line_zoom( plines , 4, 0);
   int q=0;
   for (size_t p = 0; p < plines.size(); p++)
    {
        cv::Vec4i linex = plines[p];
        line(dst2, cv::Point(linex[0], linex[1]), cv::Point(linex[2], linex[3]), cv::Scalar(0, 0, 255), 1);
        q++;
    
    }
     
     //在空白图纸画第一次检测到的直线
     // 第二次检测直线
     imshow("first line ",dst2);
     cvtColor(dst2,dst2,COLOR_BGR2GRAY);
     //边缘检测
     Canny(dst2, dst2, 100, 200, 3, false);
     imshow("dst2",dst2);
     vector<Vec4f>plines2;
	HoughLinesP(dst2, plines2, 1, CV_PI/180 , 30,100, 100);//在第一次画完直线的图上再次检测

    Mat dst3(dst2.rows,dst2.cols,CV_8UC1,255);
    cvtColor(dst3,dst3,COLOR_GRAY2BGR);
    //直线聚合
  lines_zoom* zoom=  line_zoom( plines2 ,2, 0);
   //画线
  vector<one_k_clss_line>::iterator it;
  for(it=zoom->k_class.begin();it!=zoom->k_class.end();it++)
  {
      if((*it).k_present<9999)
      {
          vector<Vec4f>::iterator it2;
          it2=(*it).line_point_data.begin();  
          cv::Vec4i line_point = *it2;
          line(dst3,cv::Point(line_point[0],line_point[1]),cv::Point(line_point[2],line_point[3]), cv::Scalar(255, 0, 0), 2);
      }
  }
	namedWindow("1",WINDOW_FREERATIO);
	imshow("1", dst3);
    
}
