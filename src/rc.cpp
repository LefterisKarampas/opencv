#include <ros/ros.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;

void Sharpen(const Mat& myImage,Mat& Result)
{
    CV_Assert(myImage.depth() == CV_8U);  // accept only uchar images
    const int nChannels = myImage.channels();
    Result.create(myImage.size(),myImage.type());
    for(int j = 1 ; j < myImage.rows-1; ++j)
    {
        const uchar* previous = myImage.ptr<uchar>(j - 1);
        const uchar* current  = myImage.ptr<uchar>(j    );
        const uchar* next     = myImage.ptr<uchar>(j + 1);
        uchar* output = Result.ptr<uchar>(j);
        for(int i= nChannels;i < nChannels*(myImage.cols-1); ++i)
        {
            *output++ = saturate_cast<uchar>(5*current[i]
                         -current[i-nChannels] - current[i+nChannels] - previous[i] - next[i]);
        }
    }
    Result.row(0).setTo(Scalar(0));
    Result.row(Result.rows-1).setTo(Scalar(0));
    Result.col(0).setTo(Scalar(0));
    Result.col(Result.cols-1).setTo(Scalar(0));
}

class ImageConverter{
	public:
	 ImageConverter(){
		Mat img = imread("../data/lef.jpg");
		if(! img.data )                              // Check for invalid input
	    {
	        cout <<  "Could not open or find the image" << std::endl ;
	        exit(1);
	    }
		namedWindow("image", CV_WINDOW_AUTOSIZE);
		imshow("image", img);
		Mat new_img;
		Sharpen( img, new_img );
		namedWindow("new_image", CV_WINDOW_AUTOSIZE);
		imshow("new_image", img);
		waitKey();
	}
	~ImageConverter(){
    	cv::destroyWindow("image");
    	cv::destroyWindow("new_image");
	}
};


int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_converter");
  ImageConverter ic;
  ros::spin();
  return 0;
}