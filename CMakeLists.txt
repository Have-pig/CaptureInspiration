cmake_minimum_required(VERSION 3.18)
project(CaptureInspiration LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 输出配置：仅把exe输出到根目录output，不生成中间归档/库文件
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/output)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/output)

# 由于SDL3没有cmake预置，添加查找SDL3的.cmake路径
set(SDL_PREFIX "F:/mingw64/x86_64-w64-mingw32")
list(APPEND CMAKE_PREFIX_PATH ${SDL_PREFIX})

# ========== 源文件列表 ==========
set(SOURCES
    "main.cpp"
    "control_tray.cpp"
    "control_events.cpp"
    "control_json.cpp"
    "control_tray.cpp"
    "settings_gui.cpp"
    "set_main_gui.cpp"
    "control_taskbar.cpp"
    
    # ImGui 核心源码
    "imgui/imgui.cpp"
    "imgui/imgui_draw.cpp"
    "imgui/imgui_tables.cpp"
    "imgui/imgui_widgets.cpp"

    # SDL3 Renderer 后端
    "imgui/backends/imgui_impl_sdl3.cpp"
    "imgui/backends/imgui_impl_sdlrenderer3.cpp"

    # FreeType拓展
    "imgui/misc/freetype/imgui_freetype.cpp"

    # cppstd拓展
    "imgui/misc/cpp/imgui_stdlib.cpp"
)

# 加载SDL3
find_package(SDL3 REQUIRED)

# 查找FreeType
find_package(Freetype REQUIRED)

# 编译程序
add_executable(${PROJECT_NAME} ${SOURCES})

if(MINGW)
    # 源码文件UTF8编码
    target_compile_options(${PROJECT_NAME} PRIVATE
        -finput-charset=UTF-8
    )
    # 静态链接C/C++运行库，减少dll依赖
    target_link_options(${PROJECT_NAME} PRIVATE
        -static-libgcc -static-libstdc++
    )
endif()

# 头文件目录
target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/imgui
    ${PROJECT_SOURCE_DIR}/imgui/backends
    ${PROJECT_SOURCE_DIR}/imgui/misc/freetype
    ${PROJECT_SOURCE_DIR}/imgui/misc/cpp
)

# 链接
target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL3::SDL3
    Freetype::Freetype
    gdi32
)


if(WIN32)
    # 编译完成自动复制到output文件夹
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL3::SDL3>
            "F:/mingw64/x86_64-w64-mingw32/bin/libfreetype-6.dll"
            ${PROJECT_SOURCE_DIR}/output

        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "E:/cpp/CaptureInspiration/font_"
            ${PROJECT_SOURCE_DIR}/output/font_

        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "E:/cpp/CaptureInspiration/assets"
            ${PROJECT_SOURCE_DIR}/output/assets
    )

    #隐藏控制台
    #target_link_options(CaptureInspiration PRIVATE -mwindows)

endif()