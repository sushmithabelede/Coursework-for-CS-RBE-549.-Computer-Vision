// opencv-test2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

//using namespace cv;
int main()
{
    std::string image_path = "C:/Users/ausmi/OneDrive/Desktop/WIN_20210821_10_28_28_Pro.jpg";
    cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
    
    //std::cout << "The image: "<<img<< std::endl;
    std::cout << "Size of the image is: " << img.size() << std::endl;

    if (img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }

    //only using the intensity values and binarizing
    cv::Mat gs_img;
    cv::cvtColor(img, gs_img, cv::COLOR_BGR2GRAY);
    cv::Mat bin_img;
    cv::threshold(gs_img, bin_img, 90, 255, cv::THRESH_BINARY);
    //cv::imshow("Picture_Grayscale", gs_img);
    //cv::imshow("Picture_Binarized", bin_img);
    
    //using the median pixel value for binarizing 50% | 50% 
    std::vector<int> flat_img = gs_img.reshape(0, 1);
    std::cout << flat_img.size() << "\n";
    std::sort(flat_img.begin(), flat_img.end());
    int k = flat_img.size() / 2;
    std::cout << "med " << flat_img[k] << "\n";
    cv::Mat bin_img_fifty;
    cv::threshold(gs_img, bin_img_fifty, flat_img[k], 255, cv::THRESH_BINARY);
    cv::imshow("Picture_Binarized_50%", bin_img);
    cv::waitKey(0);

    //CANNY:
    cv::Mat edges;
    cv::Canny(gs_img, edges, 100, 200, 3, false);
    cv::imshow("Canny edge detection", edges);
    cv::waitKey(0);

    //filtering:
    cv::Mat kernel = (cv::Mat_<float>(3, 3) <<
        1, 1, 1,
        1, -8, 1,
        1, 1, 1);
    cv::Mat imgLaplacian;
    cv::filter2D(gs_img, imgLaplacian, CV_32F, kernel);
    cv::Mat sharp;
    gs_img.convertTo(sharp, CV_32F);
    cv::Mat imgResult = sharp - imgLaplacian;
    cv::imshow("New Sharped Image", imgResult);
    cv::waitKey(0);

    //imshow("Display window", img);
    //int k = waitKey(0); // Wait for a keystroke in the window
    //if (k == 's')
    //{
    //    imwrite("xxx.png", img);
    //}


    //*** VIDEO CAPTURE *** 

    //VideoCapture cap("C:/Users/ausmi/OneDrive/Pictures/Camera Roll/WIN_20210901_18_25_44_Pro.mp4");
    
    //if (cap.isOpened() == true) {
    //    std::cout << "Could open the video yay!" << std::endl;
    //    //std::cin.get();
    //
    //}
    //else {
    //    std::cout << "Couldn't open the video :/" << std::endl;
    //    //std::cin.get();
    //}

    //double fps = cap.get(CAP_PROP_FPS);
    //std::cout << "frames per sec: " << fps << std::endl;

    //String win_name = "Painting!";
    //namedWindow(win_name, WINDOW_NORMAL); //WINDOW_NORMAL is a flag which makes the window resizable 
    
    //while (1) {

    //  
    //    Mat frame;
    //    bool b_read = cap.read(frame); //this reads a new frame from window

    //    if (b_read == false) {
    //        break;
    //    }

    //    imshow("painting",frame);

    //    if (waitKey(10) == 27) {
    //        break;
    //    }
    //}



    return 0;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
