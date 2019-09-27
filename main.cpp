#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

Mat g_img; 
Mat g_templ; 
Mat g_result;

int g_match_method = 0;
int g_max_trackbar = 5;

const char*g_sourceWindowName="Source Window";
const char*g_resultWindowName="Result Window";

void MatchingMethod( int, void* )
{

  Mat img_display;

  // 将 img的内容拷贝到 img_display
  g_img.copyTo( img_display ); 

  // 创建输出结果的矩阵
  //计算用于储存匹配结果的输出图像矩阵的大小。
  int result_cols =  g_img.cols - g_templ.cols + 1;     
  int result_rows = g_img.rows - g_templ.rows + 1;
  
  //被创建矩阵的列数，行数，以CV_32FC1形式储存。
  g_result.create( result_cols, result_rows, CV_32FC1 );

  // 进行匹配和标准化
  //待匹配图像，模版图像，输出结果图像，匹配方法（由滑块数值给定。）
  matchTemplate( g_img, g_templ, g_result, g_match_method ); 

  //输入数组，输出数组，range normalize的最小值，
  //range normalize的最大值，归一化类型，
  //当type为负数的时候输出的type和输入的type相同。
  normalize( g_result, g_result, 0, 1, NORM_MINMAX, -1, Mat() );

  // 通过函数 minMaxLoc 定位最匹配的位置
  double minVal,maxVal; 
  Point minLoc, maxLoc, matchLoc;
  //用于检测矩阵中最大值和最小值的位置
  
  minMaxLoc( g_result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );


  // 对于方法 SQDIFF 和 SQDIFF_NORMED, 越小的数值代表更高的匹配结果. 
  //而对于其他方法, 数值越大匹配越好
  if( g_match_method  == CV_TM_SQDIFF || g_match_method == CV_TM_SQDIFF_NORMED )
    { matchLoc = minLoc; }
  else
    { matchLoc = maxLoc; }


  // 原图上标记矩形框
  rectangle( img_display, matchLoc, 
    Point( matchLoc.x + g_templ.cols , matchLoc.y + g_templ.rows ), 
    Scalar(0,0,255), 
    2, 8, 0 ); 


  // 结果图上标记矩形框
  rectangle( g_result, matchLoc, 
    Point( matchLoc.x + g_templ.cols , matchLoc.y + g_templ.rows ), 
    Scalar(0,0,255), 
    2, 8, 0 );
	
  // 输出最终的到的结果
  imshow( g_sourceWindowName, img_display );
  //将得到的结果写到源代码目录下。
  imwrite("result.jpg",img_display); 
  // 输出匹配结果矩阵。
  imshow( g_resultWindowName, g_result );   

  return;
}

int main( int argc, char** argv )
{
  // 载入待匹配图像
  g_img = imread("original.jpg");
  // 载入模版图像
  g_templ = imread("template.jpg");
  

  // 创建窗口
  // 窗口名称，窗口标识CV_WINDOW_AUTOSIZE是自动调整窗口大小以适应图片尺寸。
  namedWindow( g_sourceWindowName, CV_WINDOW_AUTOSIZE ); 
  namedWindow( g_resultWindowName, CV_WINDOW_AUTOSIZE );

  // 创建滑动条
  //滑动条提示信息，滑动条所在窗口名，匹配方式通过滑动条赋值（滑块移动之后将移动到的值赋予该变量），
  //回调函数。
  createTrackbar("jackchen", g_sourceWindowName, &g_match_method, 
    g_max_trackbar, MatchingMethod ); 
	
  // 初始化显示
  MatchingMethod( 0, 0 );
  // 等待按键事件，如果值0为则永久等待。
  int logo = waitKey(0); 
  return 0;
}