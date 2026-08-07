#include "imgui/imgui.h"
#include "set_main_gui.h"
#include "settings_gui.h"

void BuildMainUIElements(ImGuiIO& io, ImVec4& bg_color)
{
    ImGui::SetNextWindowSize(ImVec2(1200, 700), ImGuiCond_Once);
    ImGui::Begin("main window", nullptr, ImGuiWindowFlags_NoSavedSettings);
    {
        if(ImGui::Button("设置", ImVec2(100, 30)))
        {
            //BuildSettingsUIElements(io, bg_color);
        }
    }
    ImGui::End();
}