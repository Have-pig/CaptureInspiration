#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <map>


// 快捷键定义结构体
struct Hotkey
{
    SDL_Keycode key = SDLK_UNKNOWN;
    bool ctrl = false;
    bool shift = false;
    bool alt = false;
    std::string name = "default"; // 快捷键名称
};

// 自定义标记，用来区分托盘菜单项
struct Tray_MenuItemTag {
    enum TrayMenuItemTags 
    {
        TRAY_ITEM_SHOW,
        TRAY_ITEM_QUIT
    } state;
    SDL_Window* window;
};


// 程序运行状态
struct AppState
{
    bool running = true; // 运行状态
    SDL_Tray* main_tray = nullptr; // 托盘对象
    SDL_Surface* icon_surface = nullptr; // 图标
    SDL_Window* window = nullptr; // 窗口指针
    std::map<std::string, Hotkey> hotkeymap; // 热键映射
    bool is_hide_to_tray = true; // 开启关闭窗口隐藏到托盘
};