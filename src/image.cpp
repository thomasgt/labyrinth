// image.cpp

#include "image.hpp"

#include <iostream>
#include <fstream>

lr::Image::Image(int h, int w, int c, byte v) : width(h), height(h), num_channels(c), data(h * w * c, v) {}

lr::Image::Image(std::string filename) {
    // Create an input stream
    std::ifstream in_file(filename, std::fstream::in | std::fstream::binary);

    // Check for errors
    if (!in_file) {
        std::cerr << "Error reading " << filename << std::endl;
    }


}
