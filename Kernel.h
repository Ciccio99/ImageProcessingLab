#ifndef KERNEL_H
#define KERNEL_H

/**
 * Used to acces openCV matrices
 */
#include <opencv2/core/mat.hpp>

/**
 * Point stuct to hold the anchor location of the kernel
 * Anchor point is equal to the center indices of the kernel
 * @author Alberto Scicali
 */
struct Point {
    /**
     * Constructor for the Point struct
     * @param xPos Row index of the center of the kernel
     * @param yPos Col index of the center of the kernel
     */
    Point(int xPos, int yPos) :  x{xPos}, y{yPos} {}

    /**
     * Holds the row index of the center of the kernel
     */
    int x;

    /**
     * Holds the column index of the center of the kernel
     */
    int y;
};

/**
 * Kernel class which maintains the shape, values and anchor indices of the kernl
 * Kernels are used to apply various forms of blur to an image by passing them over an image
 *  pixel by pixel
 *  @author Alberto Scicali
 */
class Kernel {
public:
    /**
     * Enum used to represent which type of kernel should be constructed
     */
    enum KernelType{LINEAR, GAUSSIAN};

    /**
     * Constructor to create a kernel object
     * @param kType Type of kernel to be created (determined the values that fill the kernel)
     * @param size dimensions of the kernel (kernels are square, so only one dimension is needed)
     * @param sigma sigma value uses in the calculation of some kernel values, equals zero if not parameter is passed
     */
    Kernel(Kernel::KernelType kType, unsigned int size, float sigma = 1);

    /**
     * Point struct to hold the center indices of the kernel
     */
    Point anchor;

    /**
     * Size of the kernel (kernels are square, so only one dimension is needed)
     */
    unsigned int size;

    /**
     * Matrix to hold the kernel shape and its values
     */
    cv::Mat kernelMatrix;

    /**
     * Constructs a matrix which holds the starting horizontal values to create the Gaussian kernel
     * i.e.: For a 3x3 matrix
     * -1, 0, 1
     * -1, 0, 1
     * -1, 0, 1
     * @param length Size of the kernel (kernels are square, so only one dimension is needed)
     * @return A matrix with initial starting values
     */
    cv::Mat _MeshgridHorizontal(const int length);

    /**
     * Constructs a matrix which holds the starting vertical values to create the Gaussian kernel
     * i.e.: For a 3x3 Matrix
     * -1, -1, -1
     *  0,  0,  0
     *  1,  1,  1
     * @param length Size of the kernel (kernels are square, so only one dimension is needed)
     * @return A matrix with initial starting values
     */
    cv::Mat _MeshgridVertical(const int length);
};

#endif //KERNEL_H
