#include "Tile.h"

void Tile::init(SDL_Renderer* renderer_, int x_, int y_, int w_, int h_) {
    renderer = renderer_;
    rect = {x_, y_, w_, h_};
}

void Tile::setShip(bool val) {
    hasShip = val;
}

void Tile::guess() {
    if (!guessed) {
        guessed = true;
        if (hasShip)
            isHit = true;
    }
}

void Tile::render() {
    if (!guessed) {
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    } else if (isHit) {
        SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, 100, 100, 255, 255);
    }

    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderDrawRect(renderer, &rect);
}

