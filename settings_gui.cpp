#include "settings_gui.h"
#include "imgui/imgui.h"


void BuildSettingsUIElements(ImGuiIO& io, ImVec4& bg_color, bool& show_settings,
                             const ImVec2& main_pos, const ImVec2& main_size,
                             float gap_left, float gap_right)
{
    if (gap_right >= gap_left)
    {
        // 贴主窗口右边，设置窗口左上角与主窗口左上角对齐
        ImGui::SetNextWindowPos(ImVec2(main_pos.x + main_size.x, main_pos.y),
                                ImGuiCond_Appearing);
    }
    else
    {
        // 贴主窗口左边，设置窗口右边缘对齐主窗口左边缘
        ImGui::SetNextWindowPos(main_pos, ImGuiCond_Appearing, ImVec2(1.0f, 0.0f));
    }

    ImGui::SetNextWindowSize(ImVec2(400, 700), ImGuiCond_Once);
    ImGui::Begin("settings", &show_settings, ImGuiWindowFlags_NoSavedSettings);
    {

    }
    ImGui::End();
}