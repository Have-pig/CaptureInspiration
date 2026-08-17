#include "setting_json.h"
#include "json.hpp"
#include <fstream>
#include <filesystem>
#include "struct_define.h"

using json = nlohmann::json;
namespace fs = std::filesystem;


// 将 Setting 结构体转换为 json 对象, 序列化函数
void to_json(json& j, const Setting& s)
{
    j = {{"is_hide_to_tray", s.is_hide_to_tray},
         {"is_use_hotkey", s.is_use_hotkey}};
}

// 反序列化
void from_json(const json& j, Setting& s)
{
    j.at("is_hide_to_tray").get_to(s.is_hide_to_tray);
    j.at("is_use_hotkey").get_to(s.is_use_hotkey);
}

void load_setting_json(std::string file_path, json &j)
{
    Setting default_setting;

    if(!fs::exists(file_path))
    {
        // 文件不存在：写入默认设置到文件
        std::ofstream out(file_path);
        if (out.is_open())
        {
            json temp_json = default_setting;
            out << temp_json.dump(4);
        }
        // 内存中的j直接赋值默认数据
        j = default_setting;
        return;
    }

    std::ifstream in(file_path);
    if (!in.is_open())
    {
        // 文件无法打开，直接使用默认设置
        j = default_setting;
        return;
    }
    try
    {
        in >> j;
    }
    catch (const json::parse_error& e)
    {
        // json损坏、解析失败，回退默认设置
        j = default_setting;
    }
}

void load_setting_from_json(const json& j, Setting& settings)
{
    settings = j.get<Setting>();
}

void load_json_from_setting(const Setting& settings, json& j)
{
    j = settings;
}

