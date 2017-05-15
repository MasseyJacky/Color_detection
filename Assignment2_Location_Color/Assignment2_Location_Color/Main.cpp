#include <opencv2\opencv.hpp>

using namespace cv;

int main(int argc, char args[]) {
	/**************************************************************************
	*SECTION NUMBER: 1
	*FUNCTION: Pre-process the picture
	*PURPOSE: To get better outcomes when detect colors
	***************************************************************************/

	//import 'Image 1.jpg' (which could also be anyone of the following: 'Image 1.jpg', 
	//'Image 2.jpg', 'Image 3.jpg', 'Image 4.jpg' or 'Image 5.jpg')
	Mat image1 = imread("Image 5.jpg", CV_LOAD_IMAGE_UNCHANGED);
	namedWindow("original image1", CV_WINDOW_NORMAL);
	imshow("original image1", image1);
	
	//blur image
	Mat image1_blur;
	GaussianBlur(image1, image1_blur, Size(3,3), 0,0);
	
	//change colorspace from BGR(RGB) to hvs
	Mat image1_hvs;
	cvtColor(image1_blur, image1_hvs, CV_BGR2HSV);
	
	/**************************************************************************
	*SECTION NUMBER: 2
	*FUNCTION: Location and Color Detection 
	*PURPOSE: Detect specific colors from the image, according to the user's input
	***************************************************************************/
	//detect colors accordingly
	while (1) {
		//choose a color, 'red', 'green', 'blue'
		std::string color_chosen;
		std::cout << "What color do you want to detect? Type 'red', 'green' or 'blue'. Or 'exit'." << std::endl;
		std::cin >> color_chosen;

		if (color_chosen == "red") {

			//set up threshold
			Mat red_lower = (Mat_<double>(1, 3) <<
				0, 170, 25);
			Mat red_upper = (Mat_<double>(1, 3) <<
				6, 255, 255);
			Mat red_lower_180 = (Mat_<double>(1, 3) <<
				174, 170, 25);
			Mat red_upper_180 = (Mat_<double>(1, 3) <<
				180, 255, 255);

			//detect red color
			Mat red_color_detection1, red_color_detection2, red_color_detection;
			inRange(image1_hvs, red_lower, red_upper, red_color_detection1);
			inRange(image1_hvs, red_lower_180, red_upper_180, red_color_detection2);
			addWeighted(red_color_detection1, 1, red_color_detection2, 1, 0, red_color_detection);
			
			//filter out the noise;
			erode(red_color_detection, red_color_detection, 0, Point(-1, -1), 2);
			dilate(red_color_detection, red_color_detection, 0, Point(-1, -1), 2);

			//display image
			namedWindow("Red color detection", CV_WINDOW_NORMAL);
			imshow("Red color detection", red_color_detection);

			//find contours
			std::vector<std::vector<Point>> contours;
			findContours(red_color_detection, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

			//draw contours
			Scalar color(0, 0, 255);// red
			drawContours(image1, contours, -1, color, CV_FILLED);

			//display contours on original image 
			namedWindow("result", CV_WINDOW_NORMAL);
			imshow("result", image1);
			waitKey(0);
		}
		else if (color_chosen == "green") {

			//set up threshold
			Mat green_lower = (Mat_<double>(1, 3) <<
				23, 40, 100);
			Mat green_upper = (Mat_<double>(1, 3) <<
				65, 255, 255);

			//detect green color
			Mat green_color_detection;
			inRange(image1_hvs, green_lower, green_upper, green_color_detection);

			//filter out the noise;
			erode(green_color_detection, green_color_detection, 0, Point(-1, -1), 2);
			dilate(green_color_detection, green_color_detection, 0, Point(-1, -1), 2);

			//display image
			namedWindow("Green color detection", CV_WINDOW_NORMAL);
			imshow("Green color detection", green_color_detection);
			
			//find contours
			std::vector<std::vector<Point>> contours;
			findContours(green_color_detection, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

			//drow contours
			Scalar color(0, 255, 0);//green
			drawContours(image1, contours, -1, color, CV_FILLED);

			//display contours on original image 
			namedWindow("result", CV_WINDOW_NORMAL);
			imshow("result", image1);
			waitKey(0);
		}
		else if (color_chosen == "blue") {

			//set up threshold
			Mat blue_lower = (Mat_<double>(1, 3) <<
				106, 127, 9);
			Mat blue_upper = (Mat_<double>(1, 3) <<
				170, 255, 209);//170, 255, 159

			//detect red color
			Mat blue_color_detection;
			inRange(image1_hvs, blue_lower, blue_upper, blue_color_detection);

			//filter out the noise;
			erode(blue_color_detection, blue_color_detection, 0, Point(-1, -1), 2);
			dilate(blue_color_detection, blue_color_detection, 0, Point(-1, -1), 2);

			//display image
			namedWindow("Blue color detection", CV_WINDOW_NORMAL);
			imshow("Blue color detection", blue_color_detection);

			//find contours
			std::vector<std::vector<Point>> contours;
			findContours(blue_color_detection, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

			//draw contours
			Scalar color(255, 0, 0);//blue
			drawContours(image1, contours, -1, color, CV_FILLED);

			//display contours on original image 
			namedWindow("result", CV_WINDOW_NORMAL);
			imshow("result", image1);
			waitKey(0);
		}
		else if (color_chosen == "exit") {
			//kill the program
			return -1;
		}
		else {
			continue;
		}
	}
	return 0;
}