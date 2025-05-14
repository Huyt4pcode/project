#include "Dino.h"
#include "TextureManager.h"
#include <iostream>

Dino::Dino(SDL_Renderer* renderer)
    : renderer(renderer), velocityY(0), jumpSpeed(-10), isJumping(false), isFlying(false), isFalling(false) {
    texture = TextureManager::loadTexture("dino.png", renderer);
    rect = { 100, 250, 40, 50 };  // Vị trí ban đầu của Dino
}

Dino::~Dino() {
    SDL_DestroyTexture(texture);
}

void Dino::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        // SPACE để nhảy
        if (e.key.keysym.sym == SDLK_w && !isJumping && !isFlying) {
            isJumping = true;
            velocityY = jumpSpeed;
        }

        // E để bay
        if (e.key.keysym.sym == SDLK_SPACE && !isFlying) {
            isFlying = true;
            velocityY = jumpSpeed;
        }

        // D để bắt đầu rơi nhanh
        if (e.key.keysym.sym == SDLK_d && rect.y < 250) {
            isFalling = true;
        }
    }

    if (e.type == SDL_KEYUP) {
        // Thả E thì dừng bay
        if (e.key.keysym.sym == SDLK_SPACE) {
            isFlying = false;
        }
    }
}



void Dino::update() {
    if (isFlying) {
        velocityY = jumpSpeed;
    }
    else if (isFalling) {
        velocityY = 8;  // Rơi nhanh
    }
    else if (isJumping) {
        velocityY = jumpSpeed;
    }
    else if (rect.y < 250) {
        velocityY += 1;  // Trọng lực bình thường khi đang trên không
    }
    else {
        velocityY = 0;
        rect.y = 250;
        isJumping = false;
        isFlying = false;
        isFalling = false;  // Khi chạm đất thì reset hết trạng thái
    }

    rect.y += velocityY;

    // Giới hạn không vượt quá màn hình
    if (rect.y < 0) {
        rect.y = 0;
        velocityY = 0;
    }

    if (rect.y > 250) {
        rect.y = 250;
        velocityY = 0;
        isJumping = false;
        isFlying = false;
        isFalling = false;
    }
}


void Dino::render() {
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

SDL_Rect Dino::getRect() const {
    return rect;
}

void Dino::setSpeed(int newSpeed) {
    jumpSpeed = newSpeed;  // Cập nhật tốc độ nhảy nếu cần
}
