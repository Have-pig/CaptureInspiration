#include "imgui/imconfig.h"
#include "imgui/imgui.h"
#include "imgui/misc/freetype/imgui_freetype.h"
#include "imgui/misc/cpp/imgui_stdlib.h"
#include <SDL3/SDL.h>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>


int main()
{
    //main window
    ImGui::Begin("CaptureInspiration");
    ImVec2 main_window_pos = {200, 200};
    ImVec2 main_window_size = {800, 600};
    ImGui::SetWindowPos("CaptureInspiration", main_window_pos);
    ImGui::SetWindowSize("CaptureInspiration", main_window_size);
    ImGui::StyleColorsLight();

    


    ImGui::End();

    return 0;
}

