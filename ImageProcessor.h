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

/**
 * ImageProcessor class which handles the image manipulation operations
 * @author Alberto Scicali
 */
class ImageProcessor {
public:
    /**
     * Constructor for ImageProcessor
     */
    ImageProcessor();

    /**
     * Default Destructor for ImageProcessor
     */
    virtual ~ImageProcessor() = default;

    /**
     * Given a a file path to an image, attempt to read and store the image
     * @param imagepath Path to the image file
     */
    void ReadImageFile(const string &imagepath);

    /**
     * Displays the currently loaded image
     * If no image is loaded, then display an error message
     */
    void DisplayLoadedImage() const;

    /**
     * Creates a new image of the currently loaded image with the Local Mean Filter applied
     * @param size The kernel size which will scan over the image
     */
    void ApplyMeanFilter(unsigned int size);

    /**
     * Creates a new image of the currently loaded image with the Gaussian Filter applied
     * @param size The kernel size which will scan over the image
     * @param sigma Sigma value used in the gaussian distribution calculation when creating the kernel
     */
    void ApplyGuassianFilter(unsigned int size, float sigma);


    /**
     * Creates a new image of the currently loaded image with the students custom filter applied to it
     * This example Custom Filter convers the image to a grayscale image using the conversion seen here:
     * https://en.wikipedia.org/wiki/Luma_(video)
     */
    void ApplyCustomFilter();

private:
    /**
     * Checks if any image is currently loaded into the ImageProcessor object
     * @return True if loaded, false otherwise
     */
    bool IsImageLoaded() const;

    /**
     * Holds the image to be manipulated/displayed
     */
    cv::Mat _loadedImage;

    /**
     * Const string that holds the name of the display window
     * OpenCV uses the window name to ensure that specific window is display w/e image is passed in
     */
    const string _imageWindowName;
};


#endif //IMAGEPROCESSOR_H
