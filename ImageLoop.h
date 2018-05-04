#ifndef IMAGELOOP_H
#define IMAGELOOP_H

#include <iostream>
#include <stdlib.h>
#include <unordered_map>
#include <string>
#include "ImageProcessor.h"

using namespace std;

/**
 * ImageLoop class that runs the overall loop functionality which will take in
 * inputs from the user and then call to the ImageProcessor to run the functions
 * @author Alberto Scicali
 */
class ImageLoop {
public:
    /**
     * Constuctor for the ImageLoop class
     * @param is Cin buffer stream to read in user input
     */
    ImageLoop(istream& is);

    /**
     * Runs the looping functionality of the program until the user enters the "quit" command
     */
    void MainLoop();

private:
    /**
     * Mains the curren input buffer stream to take in user commands
     */
    istream& _in;

    /**
     * ImageProcessor class which is called upon to process images
     */
    ImageProcessor _imageProcessor;

    /**
     * Unordered Map of commands which has lambda functions mapped to the users input
     */
    unordered_map<string, function<void ()>> _commands;
};


#endif //IMAGELOOP_H
