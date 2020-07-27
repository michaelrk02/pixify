#include "stdinc.h"

#include <algorithm>
#include <cmath>
#include <cstring>

// change to 3-bit-like RGB component (it's still actually 24-bit though :D)
#define CHANGE_COLOR(c) (((c) / 128) * 128 + 64)

bool pixelate(SDL_Surface *image, float scale) {
    if (image->format->BytesPerPixel != 3) {
        std::cerr << "Cannot pixelate other than 3-bytes/pixel surfaces (bpp: " << static_cast<unsigned int>(image->format->BytesPerPixel) << ")" << std::endl;
        return false;
    }

    unsigned int width = static_cast<unsigned int>(std::ceil(scale * image->w));
    unsigned int height = static_cast<unsigned int>(std::ceil(scale * image->h));
    unsigned int stride = static_cast<unsigned int>(std::ceil((float)image->h / height));
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            unsigned int left = i * stride;
            unsigned int top = j * stride;
            unsigned int right = std::min((i + 1) * stride, static_cast<unsigned int>(image->w));
            unsigned int bottom = std::min((j + 1) * stride, static_cast<unsigned int>(image->h));

#if SDL_BYTEORDER == SDL_LITTLE_ENDIAN
            unsigned int roffset = 0;
            unsigned int goffset = 8;
            unsigned int boffset = 16;
#else
            unsigned int roffset = 16;
            unsigned int goffset = 8;
            unsigned int boffset = 0;
#endif

            unsigned int rtotal = 0;
            unsigned int gtotal = 0;
            unsigned int btotal = 0;
            for (int x = left; x < right; x++) {
                for (int y = top; y < bottom; y++) {
                    unsigned int color = *reinterpret_cast<unsigned int *>(reinterpret_cast<unsigned char *>(image->pixels) + 3 * (y * image->w + x)) & 0xFFFFFF;
                    rtotal += (color >> roffset) & 0xFF;
                    gtotal += (color >> goffset) & 0xFF;
                    btotal += (color >> boffset) & 0xFF;
                }
            }

            unsigned int size = (right - left) * (bottom - top);
            unsigned int ravg = CHANGE_COLOR((rtotal / size) & 0xFF);
            unsigned int gavg = CHANGE_COLOR((gtotal / size) & 0xFF);
            unsigned int bavg = CHANGE_COLOR((btotal / size) & 0xFF);
            unsigned int color = ((ravg << roffset) | (gavg << goffset) | (bavg << boffset)) & 0xFFFFFF;
            for (int x = left; x < right; x++) {
                for (int y = top; y < bottom; y++) {
                    std::memcpy(reinterpret_cast<unsigned char *>(image->pixels) + 3 * (y * image->w + x), &color, 3);
                }
            }
        }
    }

    return true;
}

