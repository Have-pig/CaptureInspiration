#pragma once
#include <SDL3/SDL.h>
#include "struct_define.h"

// 创建系统托盘，传入窗口指针与app状态引用
void CreateSystemTray(AppState& state, SDL_Window* win, SDL_Surface* icon_surface);

// 销毁托盘，程序退出调用
void DestroySystemTray(AppState& state);
