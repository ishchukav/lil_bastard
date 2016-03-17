#ifndef ENGINE_H
#define ENGINE_H

#include "field.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Engine {
    public:
        Engine();
        virtual ~Engine();
        void logSDLError (const std::string &);
        SDL_Texture* loadTexture (const std::string &, SDL_Renderer *);
        void renderTexture(SDL_Texture *, SDL_Renderer *, int, int, int, int);
        void renderTexture(SDL_Texture *, SDL_Renderer *, int, int);
        int run ();
};

#endif // ENGINE_H
