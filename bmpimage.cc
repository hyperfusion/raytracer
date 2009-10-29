#include "bmpimage.hh"

#include <cstring> // for memset

BMPImage::BMPImage(const char *filename, int width, int height) : _filename(filename) {
    // fill in the BMP header
    std::memset(reinterpret_cast<char *> (&_bf), 0, sizeof(BMPFileHeader));
    std::memset(reinterpret_cast<char *> (&_bi), 0, sizeof(BMPInfoHeader));

    // get the number of bytes in a line; pad to a multiple of 4
    _line_bytes = width * 3;
    if (_line_bytes & 0x0003) {
        _line_bytes |= 0x0003;
        ++_line_bytes;
    }

    _data = new char[_line_bytes * height];
    _pos = 0;

    _bf.id = 0x4d42;
    _bf.size = 54L + _line_bytes * height;
    _bf.off_bits = 54L;
    _bi.size = 40L;
    _bi.width = static_cast<uint32_t> (width);
    _bi.height = static_cast<uint32_t> (height);
    _bi.planes = 1;
    _bi.bit_count = 24;
    _bi.size_image = _line_bytes * height;
}

void BMPImage::add(unsigned char r, unsigned char g, unsigned char b) {
    // if adding this RGB triplet will cause the line to overflow,
    // add the padding and go to the next line
    if (_pos % _line_bytes + 3 > _line_bytes)
        _pos += _line_bytes - _bi.width * 3;

    // write the triplet
    _data[_pos++] = b;
    _data[_pos++] = g;
    _data[_pos++] = r;
}

void BMPImage::write() {
    _file.exceptions(std::ios::failbit | std::ios::badbit);
    _file.open(_filename, std::ios::out | std::ios::binary);

    // write the header
    _file.write(reinterpret_cast<char *> (&_bf.id), sizeof(_bf.id));
    _file.write(reinterpret_cast<char *> (&_bf.size), sizeof(_bf.size));
    _file.write(reinterpret_cast<char *> (&_bf.reserved1), sizeof(_bf.reserved1));
    _file.write(reinterpret_cast<char *> (&_bf.reserved2), sizeof(_bf.reserved2));
    _file.write(reinterpret_cast<char *> (&_bf.off_bits), sizeof(_bf.off_bits));

    _file.write(reinterpret_cast<char *> (&_bi), sizeof(BMPInfoHeader));

    // go backwards over the data
    for (uint32_t row = _bi.height; row > 0; --row)
        _file.write(_data + (row - 1) * _line_bytes, _line_bytes);

    _file.close();
}
