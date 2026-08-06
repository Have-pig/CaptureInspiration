#include "control_events.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_sdl3.h"
#include <SDL3/SDL.h>
#include "struct_define.h"
#include "control_tray.h"


static bool MatchHotkey(const Hotkey& hotkey, SDL_Keycode pressedKey, SDL_Keymod mod)
{
    if (hotkey.key != pressedKey)
        return false;

    // 检查修饰键状态
    bool ctrlDown = (mod & SDL_KMOD_CTRL) != 0;
    bool shiftDown = (mod & SDL_KMOD_SHIFT) != 0;
    bool altDown = (mod & SDL_KMOD_ALT) != 0;

    return hotkey.ctrl == ctrlDown
        && hotkey.shift == shiftDown
        && hotkey.alt == altDown;
}

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
            if (state.is_hide_to_tray)
            {
                // 如果开启了隐藏到托盘，则隐藏窗口而不是退出
                CreateSystemTray(state, window, state.icon_surface);
                SDL_HideWindow(window);
            }else
            {
                state.running = false;
            }
           
        }
    }

    // 全局关闭
    if (event.type == SDL_EVENT_QUIT)
    {
        state.running = false;
    }

    // 键盘按下事件：全局快捷键
    if (event.type == SDL_EVENT_KEY_DOWN && !event.key.repeat && !imgui_capture_keyboard)
    {
        SDL_Keycode key = event.key.key;
        SDL_Keymod keymod = event.key.mod;

        // 遍历快捷键映射表，检查是否匹配
        for (auto const& [name, hk] : state.hotkeymap)
        {
            if(MatchHotkey(hk, key, keymod))
            {
                if(name == "exit")
                {
                    state.running = false;
                }
                else if(name == "toggle_window")
                {
                    Uint32 window_flags = SDL_GetWindowFlags(window);
                    if (window_flags & SDL_WINDOW_HIDDEN)
                    {
                        SDL_ShowWindow(window);
                    }
                    else
                    {
                        SDL_HideWindow(window);
                    }
                }
            }
        }
    }
}