#pragma once
#include "imgui/imgui.h"
#include "struct_define.h"


// 仅负责构建界面控件、排版
void BuildMainUIElements(ImGuiIO& io, ImVec4& bg_color, ImGuiStyle& style, AppState& app);