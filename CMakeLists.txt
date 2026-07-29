cmake_minimum_required(VERSION 3.18)
project(CaptureInspiration LANGUAGES C CXX)

# C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 输出配置：仅把exe输出到根目录output，不生成中间归档/库文件
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/output)
# 把静态库/动态库输出路径设为output，避免产生obj子文件夹
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/output)

# MinGW 参数：中文不乱码 + 静态标准库
if(MINGW)
    add_compile_options(-fexec-charset=GBK -finput-charset=UTF-8)
    add_link_options(-static-libgcc -static-libstdc++)
endif()

# 加载系统MinGW自带SDL3
find_package(SDL3 REQUIRED)

# ImGui 源码收集
file(GLOB IMGUI_CORE ${PROJECT_SOURCE_DIR}/imgui/*.cpp)
file(GLOB IMGUI_BACKEND
    ${PROJECT_SOURCE_DIR}/imgui/backends/imgui_impl_sdl3.cpp
    ${PROJECT_SOURCE_DIR}/imgui/backends/imgui_impl_sdlrenderer3.cpp
)
set(ALL_IMGUI ${IMGUI_CORE} ${IMGUI_BACKEND})
set(SRC_LIST main.cpp ${ALL_IMGUI})

# 编译程序
add_executable(${PROJECT_NAME} ${SRC_LIST})

# 头文件目录
target_include_directories(${PROJECT_NAME}
    PRIVATE ${PROJECT_SOURCE_DIR}
    PRIVATE ${PROJECT_SOURCE_DIR}/imgui
    PRIVATE ${PROJECT_SOURCE_DIR}/imgui/backends
)

# 链接SDL3
target_link_libraries(${PROJECT_NAME} SDL3::SDL3)

# 编译完成自动复制SDL3.dll到output文件夹
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL3::SDL3>
        ${PROJECT_SOURCE_DIR}/output
    )
endif()