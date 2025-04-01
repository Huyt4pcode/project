#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "defs.h"

// Hàm load texture từ file ảnh
SDL_Texture* loadTexture(const char* path) {
    SDL_Surface* surface = IMG_Load(path);
    if (!surface) {
        std::cout << "Không thể tải ảnh: " << path << " - Lỗi: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

#endif
