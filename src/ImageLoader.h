// ImageLoader.h
// Copyright (c) 2020, Elhanan Flesch
// For terms of use and distribution, see copyright notice in LICENSE

#ifndef __IMAGELOADER_H__
#define __IMAGELOADER_H__
#include <SDL2/SDL.h>

namespace ImageLoader
{
    SDL_Surface* LoadImage(const char* fileName);
    SDL_Surface* LoadImage(SDL_RWops* imageSource, bool freeSource = true);
}
#endif // __IMAGELOADER_H__