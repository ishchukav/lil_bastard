#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
using namespace std;

class Engine {
    public:
        Engine();
        virtual ~Engine();
        void logSDLError (ostream, const string);
        SDL_Texture* loadTexture (const string, SDL_Renderer *);
        void renderTexture(SDL_Texture *, SDL_Renderer *, int, int, int, int);
        void renderTexture(SDL_Texture *, SDL_Renderer *, int, int);

    protected:

    private:
};

#endif // ENGINE_H
