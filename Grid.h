
#include <vector>
#include "Tile.h"

class Grid {
public:
    void init(SDL_Renderer* renderer, int rows, int cols);
    void render();
    void handleClick(int x, int y);
    void placeShip();

private:
    SDL_Renderer* renderer;
    std::vector<std::vector<Tile>> tiles;
    int rows, cols;
};

