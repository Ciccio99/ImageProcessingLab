#include <math.h>
#include <stdlib.h>
#include <iostream>

#include "Kernel.h"


using namespace std;

Kernel::Kernel(Kernel::KernelType kType, unsigned int kSize, float sigma) :
        anchor{0,0},
        size{kSize * kSize},
        kernelMatrix{} {

    switch(kType) {
        case KernelType::LINEAR: {
            kernelMatrix = cv::Mat::ones(kSize, kSize, CV_32F);
            kernelMatrix = kernelMatrix / static_cast<float>(kSize * kSize);
            anchor.x = kernelMatrix.rows / 2;
            anchor.y = kernelMatrix.cols / 2;
            break;
        }
        case KernelType::GAUSSIAN: {
            // formula to calculate here https://stackoverflow.com/questions/8204645/implementing-gaussian-blur-how-to-calculate-convolution-matrix-kernel
            // More info Here: https://en.wikipedia.org/wiki/Gaussian_blur
            cv::Mat h1 = _MeshgridVertical(kSize);
            cv::Mat h2 = _MeshgridHorizontal(kSize);

            // Square the individual elements in each initial matrix
            h1 = h1.mul(h1);
            h2 = h2.mul(h2);

            // Add the matrices together
            cv::Mat combo{h1 + h2};

            // Square the sigma and multiply it by two
            sigma = pow(sigma, 2) * 2;


            combo = -combo / sigma;

            float comboSum{0};

            // apply exponential function to each element of the matrix
            for (auto matIter = combo.begin<float>(); matIter != combo.end<float>(); ++matIter) {
                *matIter = exp(*matIter);
                comboSum += *matIter;
            }

            // Divide each element by the sum of the matrix
            for (auto matIter = combo.begin<float>(); matIter != combo.end<float>(); ++matIter) {
                *matIter = *matIter / comboSum;
            }

            kernelMatrix = combo;
            anchor.x = kernelMatrix.rows / 2;
            anchor.y = kernelMatrix.cols / 2;
            break;
        }
    }
}

cv::Mat Kernel::_MeshgridHorizontal(const int length) {
    cv::Mat gridMat = cv::Mat::zeros(length, length, CV_32F);

    for (int r = 0; r < length; ++r) {
        int val = -(length / 2);
        for (int c = 0; c < length; ++c) {
            gridMat.at<float>(r,c) = val++;
        }
    }
    return gridMat;
}

cv::Mat Kernel::_MeshgridVertical(const int length) {
    cv::Mat gridMat = cv::Mat::zeros(length, length, CV_32F);
    int val = -(length / 2);
    for (int r = 0; r < length; ++r) {
        for (int c = 0; c < length; ++c) {
            gridMat.at<float>(r,c) = val;
        }

        val++;
    }
    return gridMat;
}
