#pragma once
#include "imgui/imgui.h"

// 开启设置窗口
void BuildSettingsUIElements(ImGuiIO& io, ImVec4& bg_color, bool& show_settings,
                             const ImVec2& main_pos, const ImVec2& main_size,
                             float gap_left, float gap_right);