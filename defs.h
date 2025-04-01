#include <vector>  // Thêm dòng này vào đầu file defs.h
#ifndef DEFS_H
#define DEFS_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>


// Kích thước cửa sổ
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

extern int hookAngle;  // Góc quay của móc
extern int hookDirection;  // Hướng quay (1: phải, -1: trái)
extern bool hookReturning;  // Trạng thái móc quay lại


// Biến toàn cục
extern SDL_Window* window;
extern SDL_Renderer* renderer;

// Biến cho móc câu
extern SDL_Rect hook;
extern bool hookMoving;
extern int hookSpeed;

// Cấu trúc lưu thông tin vàng
struct Gold {
    SDL_Rect rect;
    bool collected;
};

// Danh sách nhiều vàng
extern std :: vector<Gold> goldList;

bool init();
void close();

#endif
