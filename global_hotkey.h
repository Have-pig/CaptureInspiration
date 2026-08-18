#pragma once
#include "struct_define.h"

// 初始化全局热键系统（安装消息钩子并注册所有可用热键）
void InitGlobalHotkeySystem(AppState& app);

// 配置变化后调用，重新注册全局热键
void UpdateGlobalHotkeys(AppState& app);

// 清理全局热键系统（注销热键并移除消息钩子）
void CleanupGlobalHotkeySystem();