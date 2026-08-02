#include "control_events.h"
#include <cstdio>
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_sdl3.h"

void ProcessSDLEvent(const SDL_Event& event, SDL_Window* window, ImGuiIO& io, AppState& state)
{
    // 先把事件转发给ImGui
    ImGui_ImplSDL3_ProcessEvent(&event);

    // ImGui正在占用键盘，屏蔽全局快捷键
    bool imgui_capture_keyboard = io.WantCaptureKeyboard;

    // 窗口关闭事件
    if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
    {
        if (event.window.windowID == SDL_GetWindowID(window))
        {
            state.running = false;
        }
        return;
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

    // 你后续可以在这里继续扩展：鼠标、窗口缩放、文件拖入事件等
}