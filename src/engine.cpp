#include "engine.h"
#include "cleanup.h"
#include <SDL.h>
#include <string>


Engine::Engine() {
    //ctor
}

Engine::~Engine() {
    //dtor
}

// SDL Error Logger
void Engine::logSDLError (const std::string &msg) {
    std::cout << msg << " error: " << SDL_GetError() << std::endl;
}


/**
* Loads an image into a texture on the rendering device
* @param file The image file to load
* @param ren The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/
SDL_Texture* Engine::loadTexture (const std::string &file, SDL_Renderer *ren) {
    SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
    if (texture == nullptr) {
        logSDLError("IMG_LoadTexture");
    }
    return texture;
}


/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, with some desired
* width and height
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param x The x coordinate to draw to
* @param y The y coordinate to draw to
* @param w The width of the texture to draw
* @param h The height of the texture to draw
*/
void Engine::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h) {
    //Setup the destination rectangle to be at the position we want
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;
    SDL_RenderCopy(ren, tex, NULL, &dst);
}


/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
* the texture's width and height
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param x The x coordinate to draw to
* @param y The y coordinate to draw to
*/
void Engine::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	renderTexture(tex, ren, x, y, w, h);
}


int Engine::cell_value(Field &f, int x_pos, int y_pos) {
    // tiles per line
    int x_factor = f.WIDTH / f.TILE_SIZE;
    // target tile position in field array
    int tile_pos = (x_factor * (y_pos / f.TILE_SIZE)) + x_pos / f.TILE_SIZE;
    // target
    int value = f.get_cell(tile_pos);
    return value;
}


int Engine::run() {
    // Main window field
    Field m_window;

    // Initializing SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        logSDLError("SDL_Init");
        return 1;
    }

    // Creating window
    SDL_Window *win = SDL_CreateWindow("Li'l bastard", 100, 100, m_window.WIDTH,
		m_window.HEIGHT, SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        logSDLError("SDL_CreateWindow");
        SDL_Quit();
        return 1;
    }

    // Creating renderer
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
        logSDLError("SDL_CreateRenderer");
        cleanup(win);
        SDL_Quit();
        return 1;
    }

    // Loading image "hello.bmp"
    SDL_Texture *background = loadTexture("img/road.png", ren);
    SDL_Texture *image = loadTexture("img/man.png", ren);
    SDL_Texture *wall = loadTexture("img/wall.png", ren);
    if (background == nullptr || image == nullptr) {
        cleanup(background, image, wall, win, ren);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Event e;
    bool quit = false;
    int x = 0;
    int y = 0;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN) {
                SDL_KeyboardEvent kEvent = e.key;
                if (kEvent.keysym.scancode == SDL_SCANCODE_A && x > 0 &&
                    cell_value(m_window, x - 40, y) != 1)
                    x -= 40;
                if (kEvent.keysym.scancode == SDL_SCANCODE_S && y < m_window.HEIGHT - m_window.TILE_SIZE &&
                    cell_value(m_window, x, y + 40) != 1)
                    y += 40;
                if (kEvent.keysym.scancode == SDL_SCANCODE_D && x < m_window.WIDTH - m_window.TILE_SIZE &&
                    cell_value(m_window, x + 40, y) != 1)
                    x += 40;
                if (kEvent.keysym.scancode == SDL_SCANCODE_W && y > 0 &&
                    cell_value(m_window, x, y - 40) != 1)
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
            if (m_window.get_cell(i) == 1) {
                renderTexture(wall, ren, x * m_window.TILE_SIZE, y * m_window.TILE_SIZE,
                          m_window.TILE_SIZE, m_window.TILE_SIZE);
            } else {
                renderTexture(background, ren, x * m_window.TILE_SIZE, y * m_window.TILE_SIZE,
                          m_window.TILE_SIZE, m_window.TILE_SIZE);
            }
        }

        // Rendering foreground image

        renderTexture(image, ren, x, y, m_window.TILE_SIZE, m_window.TILE_SIZE);
        // Show refreshed screen
        SDL_RenderPresent(ren);
        std::cout << x << " " << y << std::endl;
    }

    // Cleaning objects
    cleanup(background, image, ren, win);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
