// ImageLoader.cpp
// Copyright (c) 2020, Elhanan Flesch
// For terms of use and distribution, see copyright notice in LICENSE

#include "ImageLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace ImageLoader
{
    SDL_Surface* LoadImage(const char* fileName) 
    {
        return LoadImage(SDL_RWFromFile(fileName, "rb"));
    }
    
    SDL_Surface* LoadImage(SDL_RWops* imageSource, bool freeSource) 
    {
        size_t fileSize = SDL_RWsize(imageSource);
        unsigned char* fileData = new unsigned char[fileSize];

        if (SDL_RWread(imageSource, fileData, 1, fileSize) == 0)
        {
            SDL_SetError("ImageLoader could not read data from SDL_RWops");
            return nullptr;
        }

        int imageWidth;
        int imageHeight;
        int originalFormat;

        unsigned char* imageData = stbi_load_from_memory(fileData, fileSize,
            &imageWidth, &imageHeight, &originalFormat, STBI_rgb_alpha);
        
        delete fileData;

        if (imageData == nullptr)
        {
            SDL_SetError("stbi error: %s", stbi_failure_reason());
            return nullptr;
        }

        int depth = 32;
        int pitch = 4 * imageWidth;
        Uint32 pixelFormat = SDL_PIXELFORMAT_RGBA32;

        SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(imageData, imageWidth,
            imageHeight, depth, pitch, pixelFormat);

        if (freeSource)
        {
            SDL_RWclose(imageSource);
        }
        return surface;
    }
}