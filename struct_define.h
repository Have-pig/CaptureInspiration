#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <map>


// 程序运行状态
struct AppState
{
    bool running = true;
    SDL_Tray* main_tray = nullptr;
    SDL_Surface* icon_surface = nullptr;
    std::map<std::string, Hotkey> hotkeymap;
    bool is_hide_to_tray = false; // 开启关闭窗口隐藏到托盘
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