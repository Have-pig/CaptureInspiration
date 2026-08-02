#include "control_events.h"
#include <cstdio>
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_sdl3.h"
#include <SDL3/SDL.h>
#include "json.hpp"

using json = nlohmann::json;

void ProcessSDLEvent(const SDL_Event& event, SDL_Window* window, ImGuiIO& io, AppState& state)
{
    // 事件转发给ImGui
    ImGui_ImplSDL3_ProcessEvent(&event);

    // ImGui是否占用键盘，以屏蔽全局快捷键
    bool imgui_capture_keyboard = io.WantCaptureKeyboard;

    // 主窗口关闭事件
    if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
    {
        if (event.window.windowID == SDL_GetWindowID(window))
        {
            state.running = false;
        }
    }

    // 键盘按下事件：全局快捷键
    if (event.type == SDL_EVENT_KEY_DOWN && !imgui_capture_keyboard)
    {
        SDL_Keycode key = event.key.key;
        switch (key)
        {
        case SDLK_F1:
            state.show_sidebar = !state.show_sidebar;
            printf("快捷键 F1 : 切换侧边栏\n");
            break;
        case SDLK_F2:
            state.show_setting_window = !state.show_setting_window;
            printf("快捷键 F2 : 打开设置面板\n");
            break;
        case SDLK_ESCAPE:
            state.running = false;
            printf("快捷键 ESC : 退出程序\n");
            break;
        default:
            break;
        }
    }

    
}