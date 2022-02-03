#include <iostream>
#include <opencv2/opencv.hpp>
#include "line_zoom.h"
#include <vector>
#include <math.h>

/**
 * @brief 
 * 直线聚合  斜率分类 聚合 
 * @param img 
 */

     lines_zoom *  line_zoom(vector<Vec4f>plines,double k_dis,double d_dis)
    {

        //斜率分类
           lines_zoom zoom1;
           lines_zoom zoom2;
            vector<one_k_clss_line>::iterator it_k_class_zoom2;
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
            //聚合
            std::vector<one_k_clss_line>::iterator it;
            for(it=zoom1.k_class.begin();it!=zoom1.k_class.end();it++)
            {
                //遍历所有k_class
                double dis=0;
                int num=0;
                vector<Vec4f>::iterator it2;
                double k_equ;
                double b_equ;
                for(it2=(*it).line_point_data.begin();it2!=(*it).line_point_data.end();it2++)
                {//遍历同一k范围内所有点
                    //距离分类
                    if(it2==(*it).line_point_data.begin())
                    {//y=kx+b  求出第一个直线的方程
                        k_equ=(*it).k_present;
                        //b=y-kx
                        b_equ=(*it2)[1]-k_equ*(*it2)[0];  
                        //将一个新的k_class 放入zoom2
                         one_k_clss_line tmp;
                         tmp.k_present=(*it).k_present;
                         tmp.dis_preset=0;
                         tmp.line_point_data.push_back((*it).line_point_data[0]);
                         zoom2.k_class.push_back(tmp);                    
                    }
                    //距离分类  1 计算距离 2 比较距离   3分类    D=kx+b-y|/(k^2+1)^(1/2)
                    //计算距离计算第一个点到直线的距离
                    double disp_line=(k_equ*(*it2)[0]+b_equ-(*it2)[1])/sqrt(k_equ*k_equ+1);                
                  //遍历zoom2的 dis_present     同一距离  分类      
                    for(it_k_class_zoom2=zoom2.k_class.begin();it_k_class_zoom2!=zoom2.k_class.end();it_k_class_zoom2++)
                    {  
                         if( disp_line-(*it_k_class_zoom2).dis_preset<=d_dis&&disp_line-(*it_k_class_zoom2).dis_preset>=-d_dis ){
                             //在范围内
                             (*it_k_class_zoom2).line_point_data.push_back((*it2));
                             break;
                         }
                         else{
                             //不再范围内
                             //新建一个k_class k_presrnt 相同 dis_present 不同
                         one_k_clss_line tmp_dis;
                         tmp_dis.k_present=(*it).k_present;
                         tmp_dis.dis_preset=disp_line;
                         tmp_dis.line_point_data.push_back((*it2));
                         zoom2.k_class.push_back(tmp_dis); 
                         break;      
                         }
                   }
                }


                /**
                 * @brief 
                 * double   this_dis=sqrt(((*it2)[3]-(*it2)[1]) * ((*it2)[3]-(*it2)[1])-((*it2)[2]-(*it2)[0]) * ((*it2)[2]-(*it2)[0]));
                   //计算长度权重
                   if(1)
                   {//长度权重求坐标
                    this_dis=this_dis/dis; 

                    x1_e+=this_dis*(*it2)[0]; 
                    y1_e+=this_dis*(*it2)[1];

                   x2_e+=this_dis*(*it2)[2];                 
                   y2_e+=this_dis*(*it2)[3];
                   }
                   else{
                       // this_dis=1;  //平均值 法求坐标
                        /*求平均值法计算坐标时       
                                        x1_e=x1_e/num;
                                        x2_e=x2_e/num;
                                        y1_e=y1_e/num;
                                        y2_e=y2_e/num;
        
                 *                //计算斜率代表  就算第一个点的斜率
                it2=(*it).line_point_data.begin();
                (*it2)[0]=x1_e;
                (*it2)[1]=y1_e;
                (*it2)[2]=x2_e;
                 (*it2)[3]=y2_e;
                 (*it).k_present=(y1_e-y2_e)/(x1_e-x2_e);                 
                 if((*it).k_present>900)
                 (*it).k_present=999;
                 //debug
                  cout<<(*it).k_present<<endl;
                 */
 
        }
           //返回 lines_zoom
       lines_zoom * zoom_back =new lines_zoom;
       (*zoom_back)=zoom2;
       return zoom_back;
}

/**
 * @brief 
 * 直线检测
 * @param img 
 */
void MethodOne(Mat img)//输入v 视图
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

	// 第四步：第一次霍夫直线检测
   vector<Vec4f>plines;
	HoughLinesP(grayImg, plines, 1, CV_PI/180 , 30,1, 100);
	Mat dst = img.clone();
    Mat dst2(dst.rows,dst.cols,CV_8UC1,255);
   cvtColor(dst2,dst2,COLOR_GRAY2BGR);
   //line_zoom( plines , 4, 0);
   //画第一次线
   int q=0;
   for (size_t p = 0; p < plines.size(); p++)
    {
        cv::Vec4i linex = plines[p];
        line(dst2, cv::Point(linex[0], linex[1]), cv::Point(linex[2], linex[3]), cv::Scalar(0, 0, 255), 1);
        q++;
    
    }
       imshow("first line ",dst2);

     //在空白图纸画第一次检测到的直线
     // 第二次检测直线
     cvtColor(dst2,dst2,COLOR_BGR2GRAY);
     //边缘检测
     Canny(dst2, dst2, 100, 200, 3, false);
     imshow("dst2",dst2);
     vector<Vec4f>plines2;
     //第二次直线检测
	HoughLinesP(dst2, plines2, 1, CV_PI/180 , 30,100, 100);

    //最终结果 第二次检测 聚合 dst3
    Mat dst3(dst2.rows,dst2.cols,CV_8UC1,255);
    cvtColor(dst3,dst3,COLOR_GRAY2BGR);
    //直线聚合
   lines_zoom* zoom=  line_zoom( plines2 ,4, 10);
   //画聚合后的线
  vector<one_k_clss_line>::iterator it;
  for(it=zoom->k_class.begin();it!=zoom->k_class.end();it++)
  {
      if((*it).k_present<9999)
      {
          vector<Vec4f>::iterator it2;
          it2=(*it).line_point_data.begin();  
          cv::Vec4i line_point = *it2;
          cout<<cv::Point(line_point[0],line_point[1])<<cv::Point(line_point[2],line_point[3])<<endl;
          line(dst3,cv::Point(line_point[0],line_point[1]),cv::Point(line_point[2],line_point[3]), cv::Scalar(255, 0, 0), 2);
      }
  }
	namedWindow("1",WINDOW_FREERATIO);
    //显示聚合后的结果
	imshow("1", dst3);
    
}
