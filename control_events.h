#pragma once
#include <SDL3/SDL.h>
#include "imgui/imgui.h"

// 程序运行状态，事件处理需要读写这些标记
struct AppState
{
    bool running = true;
    bool show_sidebar = false;
    bool show_setting_window = false;
};

/**
 * @brief 处理所有SDL事件，全局快捷键、窗口关闭、大小变化
 * @param event SDL事件
 * @param window 主窗口指针
 * @param io ImGuiIO
 * @param state 程序状态（读写）
 */
void ProcessSDLEvent(const SDL_Event& event, SDL_Window* window, ImGuiIO& io, AppState& state);