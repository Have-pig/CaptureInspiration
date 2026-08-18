#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

#include <SDL3/SDL.h>
#include <SDL3/SDL_system.h>

#include "global_hotkey.h"
#include "control_tray.h"
#include "control_taskbar.h"
#include <stdio.h>

#ifdef _WIN32

// 热键 ID
static const int HOTKEY_ID_EXIT = 1;
static const int HOTKEY_ID_CALL_WINDOW = 2;

// 保存 AppState 指针，供消息钩子回调使用
static AppState* g_app_state = nullptr;

// 当前是否已经注册过（用于清理）
static bool g_registered = false;

// 把 SDL_Keycode 转为 Windows 虚拟键码（VK_*）
static UINT SDLKeycodeToVK(SDL_Keycode key)
{
    // 字母 A-Z：SDL 使用 0x61..0x7A，Windows VK_A..VK_Z 也是 0x41..0x5A
    if (key >= 'a' && key <= 'z')
        return (UINT)(key - 'a' + 'A'); // 字母键，VK 使用大写
    if (key >= 'A' && key <= 'Z')
        return (UINT)key; // 已是大写

    // 数字 0-9
    if (key >= '0' && key <= '9')
        return (UINT)key;

    switch (key)
    {
    case SDLK_SPACE:      return VK_SPACE;
    case SDLK_RETURN:     return VK_RETURN;
    case SDLK_ESCAPE:     return VK_ESCAPE;
    case SDLK_TAB:        return VK_TAB;
    case SDLK_BACKSPACE:  return VK_BACK;
    case SDLK_DELETE:     return VK_DELETE;
    case SDLK_INSERT:     return VK_INSERT;
    case SDLK_HOME:       return VK_HOME;
    case SDLK_END:        return VK_END;
    case SDLK_PAGEUP:     return VK_PRIOR;
    case SDLK_PAGEDOWN:   return VK_NEXT;
    case SDLK_UP:         return VK_UP;
    case SDLK_DOWN:       return VK_DOWN;
    case SDLK_LEFT:       return VK_LEFT;
    case SDLK_RIGHT:      return VK_RIGHT;
    case SDLK_F1:         return VK_F1;
    case SDLK_F2:         return VK_F2;
    case SDLK_F3:         return VK_F3;
    case SDLK_F4:         return VK_F4;
    case SDLK_F5:         return VK_F5;
    case SDLK_F6:         return VK_F6;
    case SDLK_F7:         return VK_F7;
    case SDLK_F8:         return VK_F8;
    case SDLK_F9:         return VK_F9;
    case SDLK_F10:        return VK_F10;
    case SDLK_F11:        return VK_F11;
    case SDLK_F12:        return VK_F12;
    default:
        // 无法映射的键（如 SDLK_UNKNOWN）返回 0
        return 0;
    }
}

// 把修饰键布尔值转为 RegisterHotKey 的 MOD_* 标志
static UINT MakeModifiers(const Hotkey& hk)
{
    UINT mod = 0;
    if (hk.ctrl)  mod |= MOD_CONTROL;
    if (hk.shift) mod |= MOD_SHIFT;
    if (hk.alt)   mod |= MOD_ALT;
    return mod;
}

// 尝试将一个快捷键注册为系统热键，失败返回 false
static bool TryRegisterHotkey(const Hotkey& hk, int id)
{
    if (!hk.is_use)
        return false;

    UINT vk = SDLKeycodeToVK(hk.key);
    if (vk == 0)
        return false;

    UINT mod = MakeModifiers(hk);
    BOOL ok = RegisterHotKey(nullptr, id, mod, vk);
    return ok != FALSE;
}

static void UnregisterAllGlobalHotkeys()
{
    if (!g_registered)
        return;

    UnregisterHotKey(nullptr, HOTKEY_ID_EXIT);
    UnregisterHotKey(nullptr, HOTKEY_ID_CALL_WINDOW);
    g_registered = false;
}

// Windows 消息钩子回调。注意：不要在这里做耗时操作，只处理 WM_HOTKEY。
static bool SDLCALL WindowsMessageHook(void* userdata, MSG* msg)
{
    (void)userdata;
    if (!msg || msg->message != WM_HOTKEY)
        return true; // 让消息继续正常处理

    if (!g_app_state)
        return true;

    AppState& state = *g_app_state;

    if (msg->wParam == HOTKEY_ID_EXIT)
    {
        state.running = false;
    }
    else if (msg->wParam == HOTKEY_ID_CALL_WINDOW)
    {
        Uint32 window_flags = SDL_GetWindowFlags(state.window);
        if (window_flags & SDL_WINDOW_HIDDEN)
        {
            ShowWindowTaskbarButton(state.window);
            SDL_ShowWindow(state.window);
            SDL_RestoreWindow(state.window);
            SDL_RaiseWindow(state.window);
        }
        else
        {
            HideWindowTaskbarButton(state.window);
            CreateSystemTray(state);
            SDL_HideWindow(state.window);
        }
    }

    // WM_HOTKEY 已处理，返回 true 让 SDL 继续走默认流程（无害）。

    return true;
}

void InitGlobalHotkeySystem(AppState& app)
{
    g_app_state = &app;
    SDL_SetWindowsMessageHook(WindowsMessageHook, nullptr);
    UpdateGlobalHotkeys(app);
}

void UpdateGlobalHotkeys(AppState& app)
{
    g_app_state = &app;

    // 全局开关关闭时，注销所有快捷键
    if (!app.settings.is_use_hotkey)
    {
        UnregisterAllGlobalHotkeys();
        return;
    }

    // 先全部注销，再根据最新配置重新注册
    UnregisterAllGlobalHotkeys();

    bool any_registered = false;

    auto it = app.hotkeymap.find("exit");
    if (it != app.hotkeymap.end())
    {
        if (TryRegisterHotkey(it->second, HOTKEY_ID_EXIT))
            any_registered = true;
    }

    auto it2 = app.hotkeymap.find("call_window");
    if (it2 != app.hotkeymap.end())
    {
        if (TryRegisterHotkey(it2->second, HOTKEY_ID_CALL_WINDOW))
            any_registered = true;
    }

    g_registered = any_registered;
}

void CleanupGlobalHotkeySystem()
{
    UnregisterAllGlobalHotkeys();
    SDL_SetWindowsMessageHook(nullptr, nullptr);
    g_app_state = nullptr;
}

#endif // _WIN32