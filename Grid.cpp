#include "Grid.h"
#include <cstdlib>
#include <ctime>

void Grid::init(SDL_Renderer* renderer_, int rows_, int cols_) {
    renderer = renderer_;
    rows = rows_;
    cols = cols_;
    tiles.resize(rows, std::vector<Tile>(cols));

    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            tiles[r][c].init(renderer, c * 100 + 50, r * 100 + 50, 80, 80);

    srand(time(nullptr));
    placeShip();
}

void Grid::render() {
    for (auto& row : tiles)
        for (auto& tile : row)
            tile.render();
}

void Grid::handleClick(int x, int y) {
    int col = (x - 50) / 100;
    int row = (y - 50) / 100;

    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        tiles[row][col].guess();
    }
}

void Grid::placeShip() {
    bool horizontal = rand() % 2;
    int r, c;

    if (horizontal) {
        r = rand() % rows;
        c = rand() % (cols - 2);
        for (int i = 0; i < 3; ++i)
            tiles[r][c + i].setShip(true);
    } else {
        r = rand() % (rows - 2);
        c = rand() % cols;
        for (int i = 0; i < 3; ++i)
            tiles[r + i][c].setShip(true);
    }
}

