#pragma once
#include <SDL3/SDL.h>
#include "imgui/imgui.h"
#include <string>
#include <map>
#include "json.hpp"

using json = nlohmann::json;

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

/**
 * @brief 匹配按键是否命中指定快捷键
 */
bool MatchHotkey(const Hotkey& hotkey, SDL_Keycode pressedKey, SDL_Keymod mod);

/**
 * @brief 处理所有SDL事件，全局快捷键、窗口关闭、大小变化
 * @param event SDL事件
 * @param window 主窗口指针
 * @param io ImGuiIO
 * @param state 程序状态
 * @param hotkeymaps 快捷键映射表，键为快捷键名称，值为Hotkey结构体
 */
void ProcessSDLEvent(const SDL_Event& event, SDL_Window* window, ImGuiIO& io, AppState& state, const std::map<std::string, Hotkey>& hotkeymaps);