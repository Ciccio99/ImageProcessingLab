//
// Created by Alberto Scicali on 5/3/18.
//

#include <string>
#include "ImageLoop.h"

using namespace std;

/**
 * Commands to accept:
 * readImage: Read in the path to an image
 * displayImage: Displays the currently loaded image
 * applyMeanFilter: Displays a copy of the loaded image with a mean filter applied
 * applyGausFilter: Displays a copy of the loaded image with a guassian filter applied
 * applyCustomFilter: Displays a copy of the loaded image with a customer made filter applied
 */

ImageLoop::ImageLoop(istream &is) :
        _in{is},
        _imageProcessor{},
        _commands{} {

    /** Commands for user inputs*/
    _commands["help"] = []() {
        cout << "Commands:\n"
                "readImage: Read in the path to an image\n"
                "displayImage: Displays the currently loaded image\n"
                "applyMeanFilter: Displays a copy of the loaded image with a mean filter applied\n"
                "applyGausFilter: Displays a copy of the loaded image with a gaussian filter applied\n"
                "applyCustomFilter: Displays a copy of the loaded image with a custom made filter applied"
                "help: display this help message\n"
                "quit: exit the program"<< endl;
    };

    _commands["readImage"] = [this]() {
        string imagepath;
        _in >> imagepath;

        _imageProcessor.ReadImageFile(imagepath);
    };

    _commands["displayImage"] = [this]() {
        _imageProcessor.DisplayLoadedImage();
    };
    _commands["applyMeanFilter"] = [this]() {
        unsigned int size{0};
        cout << "Kernel Size: ";
        _in >> size;
        _in.ignore();
        if (size % 2 == 0 || size < 3) {
            cout << "Error: Kernel size must be an odd number starting at 3" << endl;
            return;
        }
        _imageProcessor.ApplyMeanFilter(size);
    };
    _commands["applyGausFilter"] = [this]() {
        unsigned int size{0};
        float sigma{0};
        cout << "Kernel Size: ";
        _in >> size;
        _in.ignore();
        if (size % 2 == 0 || size < 3) {
            cout << "Error: Kernel size must be an odd number starting at 3" << endl;
            return;
        }
        cout << "Sigma: ";
        _in >> sigma;
        _in.ignore();
        if (sigma <= 0) {
            cout << "Error: Sigma must be greater than 0" << endl;
            return;
        }

        _imageProcessor.ApplyGuassianFilter(size, sigma);
    };
    _commands["applyCustomFilter"] = [this]() {
        _imageProcessor.ApplyCustomFilter();
    };
}

void ImageLoop::MainLoop() {
    string cmd;

    while (true) {
        cout << "$ " << flush;
        _in >> cmd;

        if (cmd == "quit") {
            break;
        } else if (_commands.count(cmd) == 1) {
            _commands[cmd]();
        } else {
            cout << "unrecognized command!" << endl;
            // Consume rest of line
            string tmp;
            getline(_in, tmp);
        }
    } // End of while loop
}
