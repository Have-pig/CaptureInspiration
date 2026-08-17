#pragma once
#include <SDL3/SDL.h>
#include "struct_define.h"


// 创建系统托盘
void CreateSystemTray(AppState& state);

// 销毁托盘，程序退出调用
void DestroySystemTray(AppState& state);
