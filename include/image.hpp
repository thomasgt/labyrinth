// image.hpp

#include <cstdint>
#include <string>
#include <memory>

namespace lr {
    typedef std::uint8_t byte;

    class Image {
    private:
        int height;
        int width;
        int num_channels;
        byte *data;

    public:
        // Create an uninitialized image with unspecified size
        Image();
        // Create an uninitialized image with specified size
        Image(int h, int w, int c);
        // Create an empty image initialized with value v
        Image(int h, int w, int c, byte v);
        // Create an image from a file
        Image(std::string filename);

        // Destroy the image
        ~Image();

        // Define access operators
        byte& operator() (int row, int col);
        byte operator() (int row, int col) const;

        byte& operator() (int row, int col, int channel);
        byte operator() (int row, int col, int channel) const;
    };
}

