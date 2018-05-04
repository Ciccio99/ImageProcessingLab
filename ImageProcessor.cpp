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

void ImageProcessor::ApplyMeanFilter(unsigned int size) {
    if (!IsImageLoaded()) {
        cout << "Error: No image loaded" << endl;
        return;
    }

    Kernel meanKernel{Kernel::KernelType::LINEAR, size};

    cv::Mat modifiedImage = cv::Mat::ones(_loadedImage.rows, _loadedImage.cols, _loadedImage.type());

    // Local Mean Filter
    for (int r = meanKernel.anchor.x; r < _loadedImage.rows - meanKernel.anchor.x; ++r) {
        for (int c = meanKernel.anchor.y; c < _loadedImage.cols - meanKernel.anchor.y; ++c) {
            float redSum {0};
            float greenSum{0};
            float blueSum{0};
            int sKRow{meanKernel.kernelMatrix.rows / 2};
            int sKCol{meanKernel.kernelMatrix.cols / 2};
            for (int kr = -sKRow; kr <= sKRow; ++kr) {
                for (int kc = -sKCol; kc <= sKCol; ++kc) {
                    auto pixel = _loadedImage.at<cv::Vec3b>(r + kr, c + kc);
                    float kVal = meanKernel.kernelMatrix.at<float>(meanKernel.anchor.x + kr, meanKernel.anchor.y + kc);
                    redSum += static_cast<float>(pixel.val[2]) * kVal;
                    greenSum += static_cast<float>(pixel.val[1]) * kVal;
                    blueSum += static_cast<float>(pixel.val[0]) * kVal;
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
    cv::namedWindow(_imageWindowName, cv::WINDOW_AUTOSIZE) ;
    cv::imshow(_imageWindowName, modifiedImage);
    cv::waitKey(10);
}

void ImageProcessor::ApplyGuassianFilter(unsigned int size, float sigma) {
    if (!IsImageLoaded()) {
        cout << "Error: No image loaded" << endl;
        return;
    }

    Kernel gausKernel{Kernel::KernelType::GAUSSIAN, size, sigma};

    // Make a zeroed out matrix/image of the same dimensions as the loaded image
    cv::Mat modifiedImage = cv::Mat::ones(_loadedImage.rows, _loadedImage.cols, _loadedImage.type());
    // Gaussian filter
    for (int r = gausKernel.anchor.x; r < _loadedImage.rows - gausKernel.anchor.x; ++r) {
        for (int c = gausKernel.anchor.y; c < _loadedImage.cols - gausKernel.anchor.y; ++c) {
            int redSum {0};
            int greenSum{0};
            int blueSum{0};
            int sKRow{gausKernel.kernelMatrix.rows / 2};
            int sKCol{gausKernel.kernelMatrix.cols / 2};
            for (int kr = -sKRow; kr <= sKRow; ++kr) {
                for (int kc = -sKCol; kc <= sKCol; ++kc) {
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
    //https://en.wikipedia.org/wiki/Luma_(video)
    cv::Mat modifiedImage = cv::Mat::ones(_loadedImage.rows, _loadedImage.cols, CV_32F);
    for (int r = 0; r < _loadedImage.rows; ++r) {
        for (int c = 0; c < _loadedImage.cols; ++c) {
            cv::Vec3f pixelRGB = _loadedImage.at<cv::Vec3b>(r,c);
            pixelRGB = pixelRGB / 255.0;
            modifiedImage.at<float>(r,c) = pixelRGB[2] * 0.2126 + pixelRGB[1] * 0.7152 + pixelRGB[0] * 0.0722;
        }
    }

    //Display the the modified image
    cv::namedWindow(_imageWindowName, cv::WINDOW_AUTOSIZE);
    cv::imshow(_imageWindowName, modifiedImage);
    cv::waitKey(10);
}

bool ImageProcessor::IsImageLoaded() const {
    if (!_loadedImage.data) {
        return false;
    }
    return true;
}
