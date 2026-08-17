#include "inslib_gui.h"
#include "imgui/imgui.h"
#include "struct_define.h"


void BuildInsLibUIElements(ImGuiIO& io, ImVec4& bg_color, bool& show_ins_lib,
                             const ImVec2& main_pos, const ImVec2& main_size,
                             float gap_left, float gap_right, AppState& app,
                            ImGuiStyle& style);