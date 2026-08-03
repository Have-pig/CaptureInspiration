#include <stdio.h>
#include <string.h>
#include <map>

#include <SDL3/SDL.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_sdl3.h"
#include "imgui/backends/imgui_impl_sdlrenderer3.h"
#include "imgui/misc/freetype/imgui_freetype.h"
#include "imgui/misc/cpp/imgui_stdlib.h"

#include "set_main_gui.h"
#include "control_events.h"
#include "control_json.h"


int main(int argc, char** argv)
{
    // 初始化SDL3
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
    {
        printf("Error: SDL_Init(): %s\n", SDL_GetError());
        return 1;
    }

    // 创建窗口
    float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());//获取系统缩放
    SDL_WindowFlags window_flags = SDL_WINDOW_RESIZABLE |
                                    SDL_WINDOW_HIDDEN |
                                    SDL_WINDOW_TRANSPARENT;//窗口特性
    SDL_Window* window = SDL_CreateWindow(
        "CaptureInspiration", 
        (int)(1200 * main_scale),
        (int)(700 * main_scale),
        window_flags
    );//窗口初始化
    if (!window)
    {
        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        return 1;
    }

    // 创建渲染器
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer)
    {
        printf("Error: SDL_CreateRenderer(): %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 初始化ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();// 获取ImGuiIO对象
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;// 键盘导航
    ImGui::StyleColorsLight();// 界面风格

    // 处理缩放问题
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale);// 缩放控件
    style.FontScaleDpi = main_scale;// 设置字体缩放

    // ImGui SDL3后端绑定
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    // ttf字体文件加载
    io.Fonts->ClearFonts(); // 清除默认字体
    io.Fonts->SetFontLoader(ImGuiFreeType::GetFontLoader());
    ImFontConfig font_cfg;
    font_cfg.SizePixels = 16.0f; // 设置字体大小
    //font_cfg.FontDataOwnedByAtlas = false;// 外部字体，不由字体图集管理
    ImGuiFreeTypeLoaderFlags font_loaderflags = ImGuiFreeTypeLoaderFlags_NoHinting | //关闭字体像素对齐微调
                                                ImGuiFreeTypeLoaderFlags_LoadColor; //彩色emoji
    font_cfg.FontLoaderFlags = font_loaderflags;
    const char* font_path = "font_/Karla-Regular.ttf"; 
    const ImWchar char_range[] = {
        0x0020, 0x007E,   // 半角ASCII
        0x3000, 0x303F,   // 中文全角标点符号
        0x4E00, 0x9FFF,   // 汉字
        0
        };// 字体区间

    // 加载字体
    ImFont* font = io.Fonts->AddFontFromFileTTF(
        font_path,
        font_cfg.SizePixels,
        &font_cfg,
        char_range
    );

    // 字体文件加载失败，回退默认字体
    if (!font){
        io.Fonts->AddFontDefault();
    }

    // 运行标志
    AppState app_state;
    
    // 背景色
    ImVec4 clear_color = ImVec4(0.68f, 0.82f, 0.95f, 1.00f);

    // 加载快捷键
    std::map<std::string, Hotkey> hotkeymap;
    std::string hotkey_file_path = "hotkeys.json";
    json hotkey_json;
    load_json_from_file(hotkey_file_path, hotkey_json);
    load_hotkeymaps_from_json(hotkey_json, hotkeymap);

    // 展示窗口
    SDL_ShowWindow(window);

    while (app_state.running)
    {
        // 处理事件
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ProcessSDLEvent(event, window, io, app_state, hotkeymap);
        }

        // 如果窗口最小化则跳过渲染
        if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED)
        {
            SDL_Delay(50);
            continue;
        }

        // 开始新帧
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        // UI代码
        BuildMainUIElements(io, clear_color);

        // 渲染ImGui界面
        ImGui::Render();
        SDL_SetRenderScale(
            renderer,
            io.DisplayFramebufferScale.x,
            io.DisplayFramebufferScale.y
        );
        SDL_SetRenderDrawColorFloat(
            renderer,
            clear_color.x,
            clear_color.y,
            clear_color.z,
            clear_color.w
        );
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);

    }

    // 资源释放
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

