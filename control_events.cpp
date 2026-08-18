#include "control_events.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_sdl3.h"
#include <SDL3/SDL.h>
#include "struct_define.h"
#include "control_tray.h"
#include "control_taskbar.h"
#include <stdio.h>


void ProcessSDLEvent(const SDL_Event& event, ImGuiIO& io, AppState& state)
{
    // 事件转发给ImGui
    ImGui_ImplSDL3_ProcessEvent(&event);

    // 主窗口关闭事件
    if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
    {
        if (state.settings.is_hide_to_tray)
        {
            // 如果开启了隐藏到托盘，则隐藏窗口而不是退出
            HideWindowTaskbarButton(state.window);
            CreateSystemTray(state);
            SDL_HideWindow(state.window);
        }else
        {
            state.running = false;
        }
    }

    // 全局关闭
    if (event.type == SDL_EVENT_QUIT)
    {
        if(!state.main_tray)
        {
            state.running = false;
        }
    }
}
