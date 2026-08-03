#pragma once
#include <SDL3/SDL.h>
#include <string>


// 程序运行状态
struct AppState
{
    bool running = true;
};

// 快捷键定义结构体
struct Hotkey
{
    SDL_Keycode key = SDLK_UNKNOWN;
    bool ctrl = false;
    bool shift = false;
    bool alt = false;
    std::string name = "default"; // 快捷键名称
};