#include <SDL3/SDL.h>
#include "struct_define.h"
#ifdef _WIN32
#include <windows.h>
#endif


// 隐藏任务栏
void HideWindowTaskbarButton(SDL_Window* win);

// 恢复任务栏显示
void ShowWindowTaskbarButton(SDL_Window* win);