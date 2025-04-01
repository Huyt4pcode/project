#define SDL_MAIN_HANDLED
#include "defs.h"
#include "graphics.h"
#include <vector>
#include <ctime>
// Biến toàn cục
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* minerTexture = nullptr;
SDL_Texture* goldTexture = nullptr;
SDL_Texture* hookTexture = nullptr;

// Biến cho móc câu
SDL_Rect hook = {390, 580, 40, 80};
bool hookMoving = false;
int hookSpeed = 10;

// Danh sách vàng
std::vector<Gold> goldList;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Không thể khởi tạo SDL! Lỗi: " << SDL_GetError() << std::endl;
        return false;
    }
    window = SDL_CreateWindow("Game Đào Vàng", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cout << "Không thể tạo cửa sổ! Lỗi: " << SDL_GetError() << std::endl;
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "Không thể tạo renderer! Lỗi: " << SDL_GetError() << std::endl;
        return false;
    }

    // Khởi tạo SDL2_image
    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG))) {
        std::cout << "Không thể khởi tạo SDL2_image! Lỗi: " << IMG_GetError() << std::endl;
        return false;
    }
    return true;
}

void close() {
    SDL_DestroyTexture(minerTexture);
    SDL_DestroyTexture(goldTexture);
    SDL_DestroyTexture(hookTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

// Hàm kiểm tra va chạm giữa móc câu và vàng
bool checkCollision(SDL_Rect a, SDL_Rect b) {
    return (a.x < b.x + b.w &&
            a.x + a.w > b.x &&
            a.y < b.y + b.h &&
            a.y + a.h > b.y);
}

int main(int argc, char* argv[]) {
    if (!init()) return -1;
    int hookAngle = 0;
int hookDirection = 1;
bool hookReturning = false;


    // Load ảnh nhân vật, vàng, và móc câu
    minerTexture = loadTexture("miner.jpg");
    goldTexture = loadTexture("gold.jpg");
    hookTexture = loadTexture("hook.png");

    if (!minerTexture || !goldTexture || !hookTexture) {
        std::cout << "Không thể tải ảnh nhân vật, vàng hoặc móc câu!\n";
        return -1;
    }

    // Tạo nhiều cục vàng với vị trí ngẫu nhiên
    srand(time(0));
    for (int i = 0; i < 20; i++) {
        Gold gold;
        gold.rect = {rand() % (SCREEN_WIDTH - 50), rand() % 400 + 100, 50, 50};
        gold.collected = false;
        goldList.push_back(gold);
    }

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = true;

            // Nhấn phím SPACE để thả móc câu
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_SPACE && !hookMoving) {
                    hookMoving = true;
                }
            }
        }


        if (!hookMoving) {  // Khi móc chưa được thả
    hookAngle += hookDirection * 2;  // Tăng góc quay
    if (hookAngle >= 60 || hookAngle <= -60) {
        hookDirection *= -1;  // Đổi hướng quay khi đạt giới hạn
    }
}

        // Di chuyển móc câu xuống
        if (hookMoving) {
            hook.y += hookSpeed;

            // Kiểm tra va chạm với vàng
            for (auto &gold : goldList) {
                if (!gold.collected && checkCollision(hook, gold.rect)) {
                    gold.collected = true;
                    hook.y = 800;  // Reset móc câu
                    hookMoving = false;
                    break;
                }
            }

            // Nếu móc chạm đáy, quay lại
            if (hook.y >= SCREEN_HEIGHT - 50) {
                hook.y = 500;
                hookMoving = false;
            }
        }

        // Vẽ màn hình
        SDL_RenderClear(renderer);

        // Vẽ nhân vật
        SDL_Rect minerRect = {350, 500, 100, 100};
        SDL_RenderCopy(renderer, minerTexture, NULL, &minerRect);

        // Vẽ vàng còn lại
        for (const auto &gold : goldList) {
            if (!gold.collected) {
                SDL_RenderCopy(renderer, goldTexture, NULL, &gold.rect);
            }
        }

        // Vẽ móc câu
        SDL_RenderCopy(renderer, hookTexture, NULL, &hook);

        SDL_RenderPresent(renderer);
    }

    close();
    return 0;
}
