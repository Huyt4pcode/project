
#include <SDL.h>
#include "Grid.h"

class Game {
public:
    Game();
    ~Game();

    bool init(const char* title, int width, int height);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool isRunning() const;

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;

    Grid playerGrid;
};

