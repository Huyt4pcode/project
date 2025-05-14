#ifndef DINO_H
#define DINO_H

#include <SDL.h>

class Dino {
public:
    Dino(SDL_Renderer* renderer);
    ~Dino();

    void handleEvent(SDL_Event& e);
    void update();
    void render();
    SDL_Rect getRect() const;
    void setSpeed(int newSpeed);

private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect rect;

    int velocityY;       // Vận tốc theo trục Y (quản lý nhảy và rơi)
    int jumpSpeed;       // Tốc độ nhảy (hay bay lên)
    bool isJumping;      // Cờ để kiểm tra nếu đang nhảy
    bool isFlying;       // Cờ để kiểm tra nếu đang bay
    bool isFalling;      // Cờ để kiểm tra nếu đang rơi
};

#endif
