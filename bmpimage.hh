#ifndef __BMPIMAGE_HH__
#define __BMPIMAGE_HH__

#include <fstream>

#include "shapes.hh" // for RGB

class BMPImage {
private:
    struct BMPFileHeader {
        uint16_t id;
        uint32_t size;
        uint16_t reserved1;
        uint16_t reserved2;
        uint32_t off_bits;
    } _bf;

    struct BMPInfoHeader {
        uint32_t size;
        uint32_t width;
        uint32_t height;
        uint16_t planes;
        uint16_t bit_count;
        uint32_t compression;
        uint32_t size_image;
        uint32_t x_pels_per_meter;
        uint32_t y_pels_per_meter;
        uint32_t clr_used;
        uint32_t clr_mportant;
    } _bi;

    char *_data;
    unsigned long _line_bytes;
    unsigned long _pos;

    const char *_filename;
    std::ofstream _file;

public:
    BMPImage(const char *filename, int width, int height);
    ~BMPImage() {
        delete [] _data;
        if (_file.is_open())
            _file.close();
    }

    /**
     * Pushes another pixel (r, g, b) into the data of the image
     */
    void add(unsigned char r, unsigned char g, unsigned char b);
    void add(const RGB &rgb) { add(rgb.r, rgb.g, rgb.b); }
    void add(const Color &color) { add(RGB(color)); }

    /**
     * Writes the image to the file
     */
    void write();
};

#endif // __BMPIMAGE_HH__
