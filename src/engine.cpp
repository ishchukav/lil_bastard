#include "engine.h"
#include "cleanup.h"
#include "player.h"
#include "spider.h"
#include <SDL2/SDL.h>
#include <string>


Engine::Engine() {}

Engine::~Engine() {}

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
void Engine::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y) {
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	renderTexture(tex, ren, x, y, w, h);
}


int Engine::run() {
    // Main window field
    Field field;
    // Player character
    Player player;
    player.set_tile_size(field.TILE_SIZE);
    // Spider mobs
    int mob_amount = 5;
    Spider *spider[mob_amount]{0};
    for (int i = 0; i < mob_amount; i++) {
        spider[i] = new Spider(&field);
        spider[i]->set_rand_xy();
    }

    // Initializing SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        logSDLError("SDL_Init");
        return 1;
    }

    // Creating window
    SDL_Window *win = SDL_CreateWindow("Li'l bastard", 100, 100, field.WIDTH,
		field.HEIGHT, SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        logSDLError("SDL_CreateWindow");
        SDL_Quit();
        return 1;
    }

    // Creating renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        logSDLError("SDL_CreateRenderer");
        cleanup(win);
        SDL_Quit();
        return 1;
    }

    // Loading textures
    SDL_Texture *tex_bckgrnd = loadTexture(field.get_tex_road(), renderer);
    SDL_Texture *tex_player = loadTexture(player.get_texture(), renderer);
    SDL_Texture *tex_wall = loadTexture(field.get_tex_wall(), renderer);
    SDL_Texture *tex_spider = loadTexture(spider[0]->get_texture(), renderer);
    if (tex_bckgrnd == nullptr || tex_player == nullptr || tex_wall == nullptr ||
            tex_spider == nullptr) {
        cleanup(tex_bckgrnd, tex_player, tex_wall, win, renderer);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Event e;
    SDL_KeyboardEvent kEvent;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            kEvent = e.key;
            if (e.type == SDL_QUIT || kEvent.keysym.scancode == SDL_SCANCODE_ESCAPE)
                quit = true;
            if (e.type == SDL_KEYUP) {
                if (kEvent.keysym.scancode == SDL_SCANCODE_A && player.get_x() > 0 &&
                        field.get_cell_val(player.get_x() - field.TILE_SIZE, player.get_y()) != 1)
                    player.set_x(player.get_x() - field.TILE_SIZE);
                if (kEvent.keysym.scancode == SDL_SCANCODE_S && player.get_y() < field.HEIGHT - field.TILE_SIZE &&
                        field.get_cell_val(player.get_x(), player.get_y() + field.TILE_SIZE) != 1)
                    player.set_y(player.get_y() + field.TILE_SIZE);
                if (kEvent.keysym.scancode == SDL_SCANCODE_D && player.get_x() < field.WIDTH - field.TILE_SIZE &&
                        field.get_cell_val(player.get_x() + field.TILE_SIZE, player.get_y()) != 1)
                   player.set_x(player.get_x() + field.TILE_SIZE);
                if (kEvent.keysym.scancode == SDL_SCANCODE_W && player.get_y() > 0 &&
                        field.get_cell_val(player.get_x(), player.get_y() - field.TILE_SIZE) != 1)
                    player.set_y(player.get_y() - field.TILE_SIZE);
            }
        }
        // Drawing texture
        // Cleaning renderer
        SDL_RenderClear(renderer);
        // Rendering background
        // Determine how many times we'll ned to fill the screen
        int xTiles = field.WIDTH / field.TILE_SIZE;
        int yTiles = field.HEIGHT / field.TILE_SIZE;
        // Draw tiles by calculating their position
        for (int i = 0; i < xTiles * yTiles; ++i) {
            int x = i % xTiles;
            int y = i / xTiles;
            if (field.get_cell_val(i) == 1) {
                renderTexture(tex_wall, renderer, x * field.TILE_SIZE, y * field.TILE_SIZE,
                          field.TILE_SIZE, field.TILE_SIZE);
                //std::cout << "Wall tex" << i << "loaded" << std::endl;
            } else {
                renderTexture(tex_bckgrnd, renderer, x * field.TILE_SIZE, y * field.TILE_SIZE,
                          field.TILE_SIZE, field.TILE_SIZE);
                //std::cout << "Road tex" << i << "loaded" << std::endl;
            }
        }

        // Rendering player character
        renderTexture(tex_player, renderer, player.get_x(), player.get_y(), field.TILE_SIZE, field.TILE_SIZE);
        // Rendering mobs Spider
        for (int i = 0; i < mob_amount; i++) {
            // killing mobs if player & mob are at the same pisition
            if (player.get_x() == spider[i]->get_x() && player.get_y() == spider[i]->get_y()) {
                --mob_amount;
                if (i < mob_amount) {
                    Spider *tmp = spider[i];
                    spider[i] = spider[mob_amount];
                    spider[mob_amount] = tmp;
                }
                delete spider[mob_amount];
            }
            else {
                spider[i]->move();
                renderTexture(tex_spider, renderer, spider[i]->get_x(), spider[i]->get_y(), field.TILE_SIZE, field.TILE_SIZE);
            }
        }
        // Show refreshed screen
        SDL_RenderPresent(renderer);
    }

    // Cleaning objects
    cleanup(tex_bckgrnd, tex_player, renderer, win);
    IMG_Quit();
    SDL_Quit();
    for (int i = 0; i < mob_amount; i++) {
        delete spider[i];
    }

    return 0;
}
