#ifdef _WIN32
#include <windows.h>
#endif

#include <SDL3/SDL.h>
#include "struct_define.h"

#ifdef _WIN32
// 隐藏任务栏
void HideWindowTaskbarButton(SDL_Window* win)
{
    HWND hwnd = (HWND)SDL_GetPointerProperty(
    SDL_GetWindowProperties(win),
    SDL_PROP_WINDOW_WIN32_HWND_POINTER,
    NULL); // 拿到窗口句柄

    if (!hwnd) return;

    LONG_PTR exstyle = GetWindowLongPtrW(hwnd, GWL_EXSTYLE);
    exstyle |= WS_EX_TOOLWINDOW; // 工具窗口，不在任务栏显示图标
    exstyle &= ~WS_EX_APPWINDOW;
    SetWindowLongPtrW(hwnd, GWL_EXSTYLE, exstyle);

    // 强制刷新窗口样式生效
    SetWindowPos(hwnd, nullptr, 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}

// 恢复任务栏显示
void ShowWindowTaskbarButton(SDL_Window* win)
{
    HWND hwnd = (HWND)SDL_GetPointerProperty(
    SDL_GetWindowProperties(win),
    SDL_PROP_WINDOW_WIN32_HWND_POINTER,
    NULL); // 拿到窗口句柄
    if (!hwnd) return;

    LONG_PTR exstyle = GetWindowLongPtrW(hwnd, GWL_EXSTYLE);
    exstyle &= ~WS_EX_TOOLWINDOW;
    exstyle |= WS_EX_APPWINDOW;
    SetWindowLongPtrW(hwnd, GWL_EXSTYLE, exstyle);

    SetWindowPos(hwnd, nullptr, 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}
#endif
