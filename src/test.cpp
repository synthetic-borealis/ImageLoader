#include <iostream>
#include <SDL2/SDL.h>
#include "ImageLoader.h"

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Error: Could not initialise SDL. " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Surface* imageSurface = ImageLoader::LoadImage("test_assets/Bricks001_Base_Color.jpg");

    SDL_Window* window = SDL_CreateWindow("TestWindow",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, SDL_WINDOW_BORDERLESS);
    if (window == nullptr)
    {
        std::cerr << "Error: cannot create SDL_Window" << std::endl;
        return -1;
    }
    else
    {
        std::cout << "Created SDL_Window" << std::endl;
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == nullptr)
    {
        std::cerr << "Error: cannot create SDL_Renderer" << std::endl;
        return -1;
    }
    else
    {
        std::cout << "Created SDL_Renderer" << std::endl;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, imageSurface);

    SDL_Rect srcRect, dstRect;
    srcRect.h = imageSurface->h;
    srcRect.w = imageSurface->w;
    srcRect.x = 0;
    srcRect.y = 0;

    dstRect.h = 600;
    dstRect.w = 600;
    dstRect.x = 0;
    dstRect.y = 0;

    bool isRunning = true;
    while(isRunning)
    {
        SDL_Event event;
        SDL_PollEvent(&event);

        switch (event.type)
        {
            case SDL_QUIT:
                isRunning = false;
                break;
            
            case SDL_KEYDOWN:
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    isRunning = false;
                }
                break;
            }

            default:
                break;
        }

        SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);

        SDL_RenderPresent(renderer);
    }

    return 0;
}