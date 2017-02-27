// image.hpp

#include <cstdint>
#include <string>
#include <memory>
#include <vector>

namespace lr {
    typedef std::uint8_t byte;

    class Image {
    private:
        int height;
        int width;
        int num_channels;
        std::vector<byte> data;

    public:
        // Create empty image
        Image(int h = 0, int w = 0, int c = 0, byte v = 0);
        // Create an image from a file
        Image(std::string filename);

        // Destroy the image
        ~Image();

        // Define access operators
        byte& operator()(int row, int col, int channel);
        byte operator()(int row, int col, int channel) const;
    };
}

