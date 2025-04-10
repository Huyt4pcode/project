
#include <SDL.h>

class Tile {
public:
    void init(SDL_Renderer* renderer_, int x_, int y_, int w_, int h_);
    void render();
    void guess();
    void setShip(bool val);

private:
    SDL_Renderer* renderer;
    SDL_Rect rect;
    bool hasShip = false;
    bool guessed = false;
    bool isHit = false;
};
