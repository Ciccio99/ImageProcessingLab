//
// Created by Alberto Scicali on 5/3/18.
//

#ifndef KERNEL_H
#define KERNEL_H

#include <opencv2/core/mat.hpp>

struct Point {
    Point(int xPos, int yPos) :  x{xPos}, y{yPos} {}

    int x;
    int y;
};

class Kernel {
public:
    enum KernelType{LINEAR, GUASSIAN, CUSTOM};

    Kernel(KernelType kType);

    Point anchor;
    unsigned int size;
    cv::Mat kernelMatrix;
};


#endif //KERNEL_H
