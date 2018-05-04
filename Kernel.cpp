//
// Created by Alberto Scicali on 5/3/18.
//

#include <math.h>
#include <stdlib.h>
#include <iostream>

#include "Kernel.h"


using namespace std;
Kernel::Kernel(Kernel::KernelType kType) :
        anchor{0,0},
        size{0},
        kernelMatrix{} {
    switch(kType) {
        case KernelType::LINEAR: {
            anchor.x = 1;
            anchor.y = 1;
            kernelMatrix = cv::Mat::ones(3, 3, CV_32F);
            size = kernelMatrix.rows * kernelMatrix.cols;
            break;
        }
        case KernelType::GUASSIAN: {
            float h1_init[9] {-1, 0, -1, -1, 0, -1, -1, 0, -1};
            float h2_init[9] {-1, -1, -1, 0, 0, 0, -1, -1, -1};
            cv::Mat h1{3, 3, CV_32F, h1_init};
            cv::Mat h2{3, 3, CV_32F, h2_init};
            h1 = h1.mul(h1);
            h2 = h2.mul(h2);
            cv::Mat combo{ h1 + h2};
            float sigma {1000};
            sigma = pow(sigma, 2) * 2;

            combo = -combo / sigma;
            float comboSum{0};
            // apply exponential function to each element of the matrix
            for (auto matIter = combo.begin<float>(); matIter != combo.end<float>(); ++matIter) {
                *matIter = exp(*matIter);
                comboSum += *matIter;
            }

            // Divide each elemnt by the sum of the matrix
            for (auto matIter = combo.begin<float>(); matIter != combo.end<float>(); ++matIter) {
                *matIter = *matIter / comboSum;
            }

            anchor.x = 1;
            anchor.y = 1;
            kernelMatrix = combo;
            size = kernelMatrix.rows * kernelMatrix.cols;

            break;
        }
        case KernelType::CUSTOM: {
            break;
        }
    }
}
