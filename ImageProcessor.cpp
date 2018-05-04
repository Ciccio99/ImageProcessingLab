//
// Created by Alberto Scicali on 5/3/18.
//
#include "ImageProcessor.h"
#include "Kernel.h"

ImageProcessor::ImageProcessor() :
        _loadedImage{},
        _imageWindowName{"Image Viewer"} {}

void ImageProcessor::ReadImageFile(const string &imagepath) {
    _loadedImage = cv::imread(imagepath, cv::IMREAD_COLOR);

    if (!_loadedImage.data) {
        cout << "Could not read image from: " << imagepath << endl;
    }
}

void ImageProcessor::DisplayLoadedImage() const {
    cv::namedWindow(_imageWindowName, cv::WINDOW_AUTOSIZE) ;
    cv::imshow(_imageWindowName, _loadedImage);
    cv::waitKey(10);
}

void ImageProcessor::ApplyMeanFilter() {
    if (!IsImageLoaded()) {
        cout << "Error: No image loaded" << endl;
        return;
    }

    Kernel meanKernel{Kernel::KernelType::LINEAR};

    cv::Mat modifiedImage = cv::Mat::zeros(_loadedImage.rows, _loadedImage.cols, _loadedImage.type());

    // Local Average Filter
    for (int r = 1; r < _loadedImage.rows - 1; ++r) {
        for (int c = 1; c < _loadedImage.cols - 1; ++c) {
            int redSum {0};
            int greenSum{0};
            int blueSum{0};
            for (int kr = -1; kr < 2; ++kr) {
                for (int kc = -1; kc < 2; ++kc) {
                    auto pixel = _loadedImage.at<cv::Vec3b>(r + kr, c + kc);
                    float kVal = meanKernel.kernelMatrix.at<float>(meanKernel.anchor.x + kr, meanKernel.anchor.y + kc);
                    redSum += pixel.val[2] * kVal;
                    greenSum += pixel.val[1] * kVal;
                    blueSum += pixel.val[0] * kVal;
                }
            }

            // Apply kernel to each pixel for each R, G, B channel
            auto pixel = &modifiedImage.at<cv::Vec3b>(r,c);
            pixel->val[0] = blueSum / 9; // Blue
            pixel->val[1] = greenSum / 9; // Green
            pixel->val[2] = redSum / 9; // Red
        }
    }

    //Display the the modified image
    cv::namedWindow(_imageWindowName, cv::WINDOW_AUTOSIZE) ;
    cv::imshow(_imageWindowName, modifiedImage);
    cv::waitKey(10);
}

void ImageProcessor::ApplyGuassianFilter() {
    if (!IsImageLoaded()) {
        cout << "Error: No image loaded" << endl;
        return;
    }

    Kernel gausKernel{Kernel::KernelType::GUASSIAN};

    // Make a zeroed out matrix/image of the same dimensions as the loaded image
    cv::Mat modifiedImage = cv::Mat::zeros(_loadedImage.rows, _loadedImage.cols, _loadedImage.type());

    // Gaussian filter
    for (int r = 1; r < _loadedImage.rows - 1; ++r) {
        for (int c = 1; c < _loadedImage.cols - 1; ++c) {
            int redSum {0};
            int greenSum{0};
            int blueSum{0};
            for (int kr = -1; kr < 2; ++kr) {
                for (int kc = -1; kc < 2; ++kc) {
                    auto pixel = _loadedImage.at<cv::Vec3b>(r + kr, c + kc);
                    float kVal = gausKernel.kernelMatrix.at<float>(gausKernel.anchor.x + kr, gausKernel.anchor.y + kc);
                    redSum += pixel.val[2] * kVal;
                    greenSum += pixel.val[1] * kVal;
                    blueSum += pixel.val[0] * kVal;
                }
            }

            // Apply kernel to each pixel for each R, G, B channel
            auto pixel = &modifiedImage.at<cv::Vec3b>(r,c);
            pixel->val[0] = blueSum; // Blue
            pixel->val[1] = greenSum; // Green
            pixel->val[2] = redSum; // Red
        }
    }

    //Display the the modified image
    cv::namedWindow(_imageWindowName, cv::WINDOW_AUTOSIZE);
    cv::imshow(_imageWindowName, modifiedImage);
    cv::waitKey(10);
}

void ImageProcessor::ApplyCustomFilter() {

}

bool ImageProcessor::IsImageLoaded() const {
    if (!_loadedImage.data) {
        return false;
    }
    return true;
}
