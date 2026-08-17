#include "settings_gui.h"
#include "imgui/imgui.h"
#include "struct_define.h"
#include "json.hpp"
#include "setting_json.h"
#include "control_json.h"
#include <string.h>

using json = nlohmann::json;


void BuildSettingsUIElements(ImGuiIO& io, ImVec4& bg_color, bool& show_settings,
                             const ImVec2& main_pos, const ImVec2& main_size,
                             float gap_left, float gap_right, AppState& app, ImGuiStyle& style)
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

    enum SettingTagflag{
        STANDARD,
        HOTKEY,
    } Setting_flags;

    Setting_flags = STANDARD;
    static bool need_save = false;

    ImGui::SetNextWindowSize(ImVec2(400, 700), ImGuiCond_Once);
    ImGui::Begin("settings", &show_settings, ImGuiWindowFlags_NoSavedSettings);
    {
        ImVec4 ButtonBg_color = ImVec4(0.39f, 0.68f, 0.55f, 1.00f);
        ImVec4 ButtonHvd_color = ImVec4(0.09f, 0.54f, 0.46f, 1.00f);
        ImVec4 ButtonAct_color = ImVec4(0.1f, 0.46f, 0.41f, 1.00f);

        ImGui::PushStyleColor(ImGuiCol_Button, ButtonBg_color);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ButtonHvd_color);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ButtonAct_color);
        ImGui::PushStyleColor(ImGuiCol_Tab, ButtonBg_color);
        ImGui::PushStyleColor(ImGuiCol_TabHovered, ButtonHvd_color);
        ImGui::PushStyleColor(ImGuiCol_TabActive, ButtonAct_color);
        ImGui::PushStyleColor(ImGuiCol_CheckboxSelectedBg, ButtonAct_color);


        if (ImGui::BeginTabBar("设置组",  0))
        {
            if (ImGui::BeginTabItem("基础"))
            {
                if(ImGui::Checkbox("是否开启关闭窗口隐藏到托盘", &app.settings.is_hide_to_tray))
                {
                    need_save = true;
                }

                if(ImGui::Checkbox("是否使用快捷键", &app.settings.is_use_hotkey))
                {
                    need_save = true;
                }

                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("热键"))
            {
                // 设置热键
                ImGui::EndTabItem();
            }

        }
        ImGui::EndTabBar();

        if(need_save)
        {
            // 将保存按钮定位到窗口左下角
            const ImVec2 button_size(100.0f, 30.0f);
            ImVec2 window_size = ImGui::GetWindowSize();

            ImGui::SetCursorPos(ImVec2(
                style.WindowPadding.x,
                window_size.y - button_size.y - style.WindowPadding.y));

            if(ImGui::Button("保存", button_size))
            {
                json js_ht;
                json js_st;
                std::string hotkey_file_path = "hotkeys.json";
                std::string settings_file_path = "settings.json";
                load_json_from_hotkeymaps(app.hotkeymap, js_ht);
                load_json_from_setting(app.settings, js_st);
                save_file_from_json(hotkey_file_path, js_ht);
                save_file_from_json(settings_file_path, js_st);

                need_save = false;
            }
        }

        ImGui::PopStyleColor(7);
    }
    ImGui::End();
}