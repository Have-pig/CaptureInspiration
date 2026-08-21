#include "inslib_gui.h"
#include "imgui/imgui.h"
#include "struct_define.h"


void BuildInsLibUIElements(ImGuiIO& io, ImVec4& bg_color, bool& show_ins_lib,
                             const ImVec2& main_pos, const ImVec2& main_size,
                             float gap_left, float gap_right, AppState& app,
                            ImGuiStyle& style)
{
    // 抑制未使用参数告警，保持与 settings_gui 相同的调用签名
    (void)bg_color;
    (void)main_pos;
    (void)main_size;
    (void)gap_left;
    (void)gap_right;
    (void)app;
    (void)style;

    // 将窗口创建在屏幕中间
    ImVec2 center_pos = ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f);
    ImGui::SetNextWindowPos(center_pos, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(700, 500), ImGuiCond_Once);

    ImGui::Begin("InspirationLibrary", &show_ins_lib, ImGuiWindowFlags_NoSavedSettings);
    {
        ImVec4 ButtonBg_color = ImVec4(0.39f, 0.68f, 0.55f, 1.00f);
        ImVec4 ButtonHvd_color = ImVec4(0.09f, 0.54f, 0.46f, 1.00f);
        ImVec4 ButtonAct_color = ImVec4(0.1f, 0.46f, 0.41f, 1.00f);

        ImGui::PushStyleColor(ImGuiCol_Button, ButtonBg_color);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ButtonHvd_color);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ButtonAct_color);
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.5f, 0.0f, 0.5f, 1.0f));

        if (ImGui::Button("新增", ImVec2(100, 30)))
        {
            // TODO: 新增条目逻辑
        }
        ImGui::SameLine();
        if (ImGui::Button("删除", ImVec2(100, 30)))
        {
            // TODO: 删除条目逻辑
        }

        ImGui::PopStyleColor(4);
    }
    ImGui::End();
}