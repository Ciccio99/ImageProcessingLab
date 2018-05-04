#include <iostream>
#include <stdlib.h>
#include "ImageLoop.h"

using namespace cv;
using namespace std;


/**
 * Initiates the loop for the program
 * @param argc argument count
 * @param argv provided arguments (None should be passed in)
 * @return 0
 */
int main(int argc, char** argv ) {

    if (argc > 1) {
        cerr << "\"" << argv[1] << "\" not a valid command - No starting commands necessary" << endl;
        cerr << "Usage: processImages" << endl;
        return 0;
    }

    // Pass in cin read buffer stream
    istream is(cin.rdbuf());
    ImageLoop imageLoop{is};

    // Initiate the loop
    imageLoop.MainLoop();

    return 0;
}