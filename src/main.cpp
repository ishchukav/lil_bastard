#include <SDL.h>
#include <SDL_image.h>
#include "cleanup.h"
#include "field.h"
#include <iostream>
using namespace std;


int main (int argc, char* argv[]) {
    // Main window field
    Field m_window;

    // Initializing SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        logSDLError(cout, "SDL_Init");
        return 1;
    }

    // Creating window
    SDL_Window *win = SDL_CreateWindow("Li'l bastard", 100, 100, m_window.WIDTH,
		m_window.HEIGHT, SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        logSDLError(cout, "SDL_CreateWindow");
        SDL_Quit();
        return 1;
    }

    // Creating renderer
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
        logSDLError(cout, "SDL_CreateRenderer");
        cleanup(win);
        SDL_Quit();
        return 1;
    }

    // Loading image "hello.bmp"
    SDL_Texture *background = loadTexture("img/background.png", ren);
    SDL_Texture *image = loadTexture("img/man.png", ren);
    if (background == nullptr || image == nullptr) {
        cleanup(background, image, win, ren);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Event e;
    bool quit = false;
    int iW, iH;
    SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
    int x = 0;
    int y = 0;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN) {
                SDL_KeyboardEvent kEvent = e.key;
                if (kEvent.keysym.scancode == SDL_SCANCODE_A && x > 0)
                    x -= 40;
                if (kEvent.keysym.scancode == SDL_SCANCODE_S && y < m_window.HEIGHT - m_window.TILE_SIZE)
                    y += 40;
                if (kEvent.keysym.scancode == SDL_SCANCODE_D && x < m_window.WIDTH - m_window.TILE_SIZE)
                    x += 40;
                if (kEvent.keysym.scancode == SDL_SCANCODE_W && y > 0)
                    y -= 40;
            }
        }
        // Drawing texture
        // Cleaning renderer
        SDL_RenderClear(ren);

        // Rendering background
        // Determine how many times we'll ned to fill the screen
        int xTiles = m_window.WIDTH / m_window.TILE_SIZE;
        int yTiles = m_window.HEIGHT / m_window.TILE_SIZE;
        // Draw tiles by calculating their position
        for (int i = 0; i < xTiles * yTiles; ++i) {
            int x = i % xTiles;
            int y = i / xTiles;
            renderTexture(background, ren, x * m_window.TILE_SIZE, y * m_window.TILE_SIZE,
                          m_window.TILE_SIZE, m_window.TILE_SIZE);
        }

        // Rendering foreground image

        renderTexture(image, ren, x, y, m_window.TILE_SIZE, m_window.TILE_SIZE);
        // Show refreshed screen
        SDL_RenderPresent(ren);
        cout << x << " " << y << endl;
    }

    // Cleaning objects
    cleanup(background, image, ren, win);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
