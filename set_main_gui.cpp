#include "imgui/imgui.h"
#include "set_main_gui.h"
#include "settings_gui.h"
#include "inslib_gui.h"
#include "struct_define.h"


void BuildMainUIElements(ImGuiIO& io, ImVec4& bg_color, ImGuiStyle& style, AppState& app)
{
    static bool show_settings = false;
    static bool show_ins_lib = false;
    ImVec2 main_pos;
    ImVec2 main_size;
    float  gap_left;
    float  gap_right;

    ImGui::SetNextWindowSize(ImVec2(700, 400), ImGuiCond_Once);
    ImGui::Begin("main window", nullptr, ImGuiWindowFlags_NoSavedSettings);
    {
        // 按钮颜色
        ImVec4 ButtonBg_color = ImVec4(0.39f, 0.68f, 0.55f, 1.00f);
        ImVec4 ButtonHvd_color = ImVec4(0.09f, 0.54f, 0.46f, 1.00f);
        ImVec4 ButtonAct_color = ImVec4(0.1f, 0.46f, 0.41f, 1.00f);

        ImGui::PushStyleColor(ImGuiCol_Button, ButtonBg_color);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ButtonHvd_color);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ButtonAct_color);
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.5f, 0.0f, 0.5f, 1.0f));

        if(ImGui::Button("灵感库", ImVec2(100, 30))){
            if(show_ins_lib)
            {
                show_ins_lib = false;
            }else{
                show_ins_lib = true;
            }
        }

        if(ImGui::Button("设置", ImVec2(100, 30)))
        {
            if(show_settings)
            {
                show_settings = false;
            }else{
                show_settings = true;
            }
            
        }

        ImGui::PopStyleColor(4);

        // 主窗口位置
        main_pos  = ImGui::GetWindowPos();
        main_size = ImGui::GetWindowSize();
        gap_left  = main_pos.x;
        gap_right = io.DisplaySize.x - (main_pos.x + main_size.x);
    }
    ImGui::End();

    if (show_settings)
    {   
        BuildSettingsUIElements(io, bg_color, show_settings,
                            main_pos, main_size, gap_left, gap_right, app, style);
    }

    if(show_ins_lib)
    {

    }
}