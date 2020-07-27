#include "stdinc.h"

#include <cstring>

int main(int argc, char **argv) {
    float scale = 0.0625;
    if (argc == 1) {
        std::cerr << "Usage: " << argv[0] << " <file> [scale]" << std::endl;
        return 1;
    }
    if (argc == 3) {
        scale = (float)std::atof(argv[2]);
        if ((scale <= 0.0f) || (scale >= 1.0f)) {
            std::cerr << "Scale must be in (0,1) range" << std::endl;
            return 1;
        }
    }

    if (SDL_Init(0) == 0) {
        SDL_Surface *fresh = IMG_Load(argv[1]);
        if (fresh != NULL) {
#if SDL_BYTEORDER == SDL_LITTLE_ENDIAN
            SDL_PixelFormatEnum format = SDL_PIXELFORMAT_RGB24; // 0xBBGGRR
#else
            SDL_PixelFormatEnum format = SDL_PIXELFORMAT_BGR24; // 0xRRGGBB
#endif
            SDL_Surface *image = SDL_ConvertSurfaceFormat(fresh, format, 0);
            if (image != NULL) {
                if (pixelate(image, scale)) {
                    std::string output = argv[1];
                    output = output + ".pixified.jpg";
                    if (IMG_SaveJPG(image, output.c_str(), 75) == 0) {
                        std::cout << "Successfully saved to " << output << std::endl;
                    } else {
                        std::cerr << "Failed saving to " << output << std::endl;
                    }
                }
                SDL_FreeSurface(image);
            } else {
                std::cerr << "Cannot convert image surface format" << std::endl;
            }
            SDL_FreeSurface(fresh);
        } else {
            std::cerr << "Cannot load image: " << argv[1] << std::endl;
        }
        SDL_Quit();
    } else {
        std::cerr << "Failed initializing SDL!" << std::endl;
    }

    return 0;
}

