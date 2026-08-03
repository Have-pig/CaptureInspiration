#include "control_events.h"
#include "control_json.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_sdl3.h"
#include <SDL3/SDL.h>
#include "json.hpp"
#include <map>
#include <string>


using json = nlohmann::json;
namespace fs = std::filesystem;

bool MatchHotkey(const Hotkey& hotkey, SDL_Keycode pressedKey, SDL_Keymod mod)
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

void ProcessSDLEvent(const SDL_Event& event, SDL_Window* window, ImGuiIO& io, AppState& state, const std::map<std::string, Hotkey>& hotkeymaps)
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
    if (event.type == SDL_EVENT_KEY_DOWN && !event.key.repeat && !imgui_capture_keyboard)
    {
        SDL_Keycode key = event.key.key;
        SDL_Keymod keymod = event.key.mod;

        /*for ()
        {
            if (MatchHotkey(hk, key, keymod))
            {
                
                break;
            }
        }*/
    }
}