//
// Created by Alberto Scicali on 5/3/18.
//

#ifndef IMAGELOOP_H
#define IMAGELOOP_H
#include <iostream>
#include <stdlib.h>
#include <unordered_map>
#include <string>
#include "ImageProcessor.h"

using namespace std;

class ImageLoop {
public:
    ImageLoop(istream& is);

    void MainLoop();

private:
    istream& _in;
    ImageProcessor _imageProcessor;
    unordered_map<string, function<void ()>> _commands;
};


#endif //IMAGELOOP_H
