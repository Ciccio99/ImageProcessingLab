//
// Created by Alberto Scicali on 5/3/18.
//

#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <stdlib.h>
#include <string>
#include <memory>
// Include OpenCV headers
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
class ImageProcessor {
public:
    ImageProcessor();

    virtual ~ImageProcessor() = default;

    void ReadImageFile(const string &imagepath);

    void DisplayLoadedImage() const;

    void ApplyMeanFilter();

    void ApplyGuassianFilter();

    void ApplyCustomFilter();

private:
    bool IsImageLoaded() const;

    cv::Mat _loadedImage;
    const string _imageWindowName;
};


#endif //IMAGEPROCESSOR_H
