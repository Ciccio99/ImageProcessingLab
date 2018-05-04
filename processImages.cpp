#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <stdlib.h>
#include "ImageLoop.h"

using namespace cv;
using namespace std;


/**
 * OpenCV install =  http://tilomitra.com/opencv-on-mac-osx/
 * @param argc argument count
 * @param argv provided arguments (None should be passed in)
 * @return
 */
int main(int argc, char** argv ) {

    if (argc > 1) {
        cerr << "\"" << argv[1] << "\" not a valid command - No starting commands necessary" << endl;
        cerr << "Usage: processImages" << endl;
        return 0;
    }

    // Pass in cin read buffer stream
    istream is (cin.rdbuf());
    ImageLoop imageLoop{is};

    // Initiate the loop
    imageLoop.MainLoop();

    return 0;

    Mat image;
    image = imread(argv[1], IMREAD_COLOR);

    if (!image.data) {
        cout << argv[1] << endl;
        cout << "Could not open of read file." << endl;
        return -1;
    }

    Mat kernel = Mat::ones(3, 3, CV_32F);
    float meow[9] {1, 0 , 1, 1, 0, 1, 1, 0, 1};
    Mat kernel1 = Mat(3,3, CV_32F, meow);
    int kCenter[2] {1,1};

    Mat blurredImage = Mat::zeros(image.rows, image.cols, image.type());
    // Local Average Filter
    for (int r = 1; r < image.rows - 1; ++r) {
        for (int c = 1; c < image.cols - 1; ++c) {
            int redSum {0};
            int greenSum{0};
            int blueSum{0};
            for (int kr = -1; kr < 2; ++kr) {
                for (int kc = -1; kc < 2; ++kc) {
                    auto pixel = image.at<Vec3b>(r + kr, c + kc);
                    float kVal = kernel1.at<float>(kCenter[0] + kr, kCenter[1] + kc);
                    redSum += pixel.val[2] * kVal;
                    greenSum += pixel.val[1] * kVal;
                    blueSum += pixel.val[0] * kVal;
                }
            }
            // Apply kernel to each pixel
            auto pixel = &blurredImage.at<Vec3b>(r,c);
            pixel->val[0] = blueSum / 9; // Blue
            pixel->val[1] = greenSum / 9; // Green
            pixel->val[2] = redSum / 9; // Red
        }
    }

    // pixel values: [0] = Blue, [1] = Green, [2] = Red
//    for (int r = 0; r < image.rows; ++r) {
//        for (int c = 0; c < image.cols; ++c) {
//            // Apply kernel to each pixel
//            auto pixel = &image.at<Vec3b>(r,c);
//            pixel->val[0] = 0;
//            pixel->val[1] = 0;
//        }
//    }


    namedWindow("test", WINDOW_AUTOSIZE) ;
    imshow("test", blurredImage);

//    Mat x(800, 800, CV_8UC3);
//    for (int i=0; i<100; i++) {
//        rectangle(x, Rect(rand()%500, rand()%500, rand()%300, rand()%300), Scalar(rand()%255, rand()%255, rand()%255), -1);
//    }

    waitKey(0);
    return 0;
}

//Mat kernel = getStructuringElement(
//            MORPH_ELLIPSE, Size( kernelWidth, kernelWidth ),
//            Point( kernelWidth / 2, kernelWidth / 2 )
//        );