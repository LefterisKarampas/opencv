#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <ros/ros.h>
#include <iostream>
using namespace cv;
using namespace std;


int main(int argc,char **argv)
{
   ros::init(argc, argv, "add");
   double alpha = 0.5; double beta; double input;
   Mat src1, src2, dst;
   cout << " Simple Linear Blender " << endl;
   cout << "-----------------------" << endl;
   cout << "* Enter alpha [0.0-1.0]: ";
   cin >> input;
   // We use the alpha provided by the user if it is between 0 and 1
   if( input >= 0 && input <= 1 )
     { alpha = input; }
   src1 = imread( "../data/lef.jpg" );
   src2 = imread( "../data/test.jpg" );
   if( src1.empty() ) { cout << "Error loading src1" << endl; return -1; }
   if( src2.empty() ) { cout << "Error loading src2" << endl; return -1; }
   beta = ( 1.0 - alpha );
   addWeighted( src1, alpha, src2, beta, 0.0, dst);
   imshow( "Linear Blend", dst );
   waitKey(0);
   ros::spin();
   return 0;
}