#include "imgui/imconfig.h"
#include "imgui/imgui.h"
#include <SDL3/SDL.h>

int main()
{
    //main window
    ImGui::Begin("CaptureInspiration");
    ImVec2 main_window_pos = {200, 200};
    ImVec2 main_window_size = {800, 600};
    ImGui::SetWindowPos("CaptureInspiration", main_window_pos);
    ImGui::SetWindowSize("CaptureInspiration", main_window_size);










    ImGui::End();

    return 0;
}

