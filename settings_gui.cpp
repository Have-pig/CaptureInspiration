#include "settings_gui.h"
#include "imgui/imgui.h"
#include "struct_define.h"
#include "json.hpp"
#include "setting_json.h"
#include "control_json.h"
#include "global_hotkey.h"
#include "imgui/misc/cpp/imgui_stdlib.h"

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

    ImGui::SetNextWindowSize(ImVec2(700, 500), ImGuiCond_Once);
    ImGui::Begin("Settings", &show_settings, ImGuiWindowFlags_NoSavedSettings);
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
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.5f, 0.0f, 0.5f, 1.0f));

        bool hotkey_active = false;
        ImVec2 tab_bar_pos = ImGui::GetCursorPos(); // 标签栏顶部的窗口局部坐标
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
            hotkey_active = ImGui::BeginTabItem("热键");
            if (hotkey_active)
            {
                // 设置热键
                ImGui::Text("快速呼出或隐藏窗口");
                ImGui::SameLine();

                if(ImGui::Checkbox("是否启用##1", &app.hotkeymap["call_window"].is_use))
                {
                    need_save = true;
                }
                ImGui::SameLine();
                if(ImGui::Checkbox("Ctrl##1", &app.hotkeymap["call_window"].ctrl))
                {
                    need_save = true;
                }
                ImGui::SameLine();
                if(ImGui::Checkbox("Shift##1", &app.hotkeymap["call_window"].shift))
                {
                    need_save = true;
                }
                ImGui::SameLine();
                if(ImGui::Checkbox("Alt##1", &app.hotkeymap["call_window"].alt))
                {
                    need_save = true;
                }
                ImGui::SameLine();

                static char call_trigger_key_buf[32] = {};
                static SDL_Keycode call_displayed_key = (SDL_Keycode)-1;
                if (call_displayed_key != app.hotkeymap["call_window"].key)
                {
                    call_displayed_key = app.hotkeymap["call_window"].key;
                    const char* key_name = SDL_GetKeyName(call_displayed_key);
                    SDL_strlcpy(call_trigger_key_buf, key_name ? key_name : "", sizeof(call_trigger_key_buf));
                }
                ImGui::SetNextItemWidth(60.0f);
                if (ImGui::InputText("##call_trigger_key", call_trigger_key_buf, sizeof(call_trigger_key_buf),
                                     ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll))
                {
                    SDL_Keycode key = SDL_GetKeyFromName(call_trigger_key_buf);
                    if (key != SDLK_UNKNOWN)
                    {
                        app.hotkeymap["call_window"].key = key;
                        need_save = true;
                    }else
                    {
                        const char* key_name = SDL_GetKeyName(call_displayed_key);
                        SDL_strlcpy(call_trigger_key_buf, key_name ? key_name : "", sizeof(call_trigger_key_buf));
                    }
                }
                ImGui::SameLine();

                ImGui::Text("触发键");

                ImGui::Text("快速关闭程序          ");
                ImGui::SameLine();

                if(ImGui::Checkbox("是否启用##2", &app.hotkeymap["exit"].is_use))
                {
                    need_save = true;
                }
                ImGui::SameLine();
                if(ImGui::Checkbox("Ctrl##2", &app.hotkeymap["exit"].ctrl))
                {
                    need_save = true;
                }
                ImGui::SameLine();
                if(ImGui::Checkbox("Shift##2", &app.hotkeymap["exit"].shift))
                {
                    need_save = true;
                }
                ImGui::SameLine();
                if(ImGui::Checkbox("Alt##2", &app.hotkeymap["exit"].alt))
                {
                    need_save = true;
                }
                ImGui::SameLine();

                static char exit_trigger_key_buf[32] = {};
                static SDL_Keycode exit_displayed_key = (SDL_Keycode)-1;
                if (exit_displayed_key != app.hotkeymap["exit"].key)
                {
                    exit_displayed_key = app.hotkeymap["exit"].key;
                    const char* key_name = SDL_GetKeyName(exit_displayed_key);
                    SDL_strlcpy(exit_trigger_key_buf, key_name ? key_name : "", sizeof(exit_trigger_key_buf));
                }
                ImGui::SetNextItemWidth(60.0f);
                if (ImGui::InputText("##exit_trigger_key", exit_trigger_key_buf, sizeof(exit_trigger_key_buf),
                                     ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll))
                {
                    SDL_Keycode key = SDL_GetKeyFromName(exit_trigger_key_buf);
                    if (key != SDLK_UNKNOWN)
                    {
                        app.hotkeymap["exit"].key = key;
                        need_save = true;
                    }else
                    {
                        const char* key_name = SDL_GetKeyName(exit_displayed_key);
                        SDL_strlcpy(exit_trigger_key_buf, key_name ? key_name : "", sizeof(exit_trigger_key_buf));
                    }
                }
                ImGui::SameLine();

                ImGui::Text("触发键");
                
                ImGui::EndTabItem();
            }
        }
        ImGui::EndTabBar();

        // 仅当“热键”页激活时，显示在窗口右上角
        if (hotkey_active)
        {
            const char* hint = "按Enter确认录入触发键";
            ImVec2 hint_size = ImGui::CalcTextSize(hint);
            float content_max_x = ImGui::GetWindowContentRegionMax().x;
            float hint_y = tab_bar_pos.y + (ImGui::GetFrameHeight() - hint_size.y) * 0.5f;
            ImGui::SetCursorPos(ImVec2(content_max_x - hint_size.x, hint_y));
            ImGui::Text(hint);
        }

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

                // 保存后立即重新注册全局快捷键
                UpdateGlobalHotkeys(app);

                need_save = false;
            }
        }

        ImGui::PopStyleColor(8);
    }
    ImGui::End();
}