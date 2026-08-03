#include "json.hpp"
#include <fstream>
#include <filesystem>
#include "control_json.h"
#include <string>
#include <map>
#include "struct_define.h"

using json = nlohmann::json;
namespace fs = std::filesystem;

// 将Hotkey结构体转换为json对象, 序列化函数
void to_json(json& j, const Hotkey& hk)
{
    j = {{"key",hk.key},{"ctrl",hk.ctrl},{"shift",hk.shift},{"alt",hk.alt},{"name",hk.name}};
}

// 将json对象转换为Hotkey结构体, 反序列化函数
void from_json(const json& j, Hotkey& hk)
{
    j.at("key").get_to(hk.key);
    j.at("ctrl").get_to(hk.ctrl);
    j.at("shift").get_to(hk.shift);
    j.at("alt").get_to(hk.alt);
    j.at("name").get_to(hk.name);
}

void load_json_from_file(const std::string& file_path, json& j)
{
    Hotkey default_hotkey;
    std::map<std::string, Hotkey> undefined_hotkeys = {{default_hotkey.name, default_hotkey}};

    if(!fs::exists(file_path))
    {
        // 文件不存在：写入默认热键到文件
        std::ofstream out(file_path);
        if (out.is_open())
        {
            json temp_json = undefined_hotkeys;
            out << temp_json.dump(4);
        }
        // 内存中的j直接赋值默认数据
        j = undefined_hotkeys;
        return;
    }

    std::ifstream in(file_path);
    if (!in.is_open())
    {
        // 文件无法打开，直接使用默认热键
        j = undefined_hotkeys;
        return;
    }
    try
    {
        in >> j;
    }
    catch (const json::parse_error& e)
    {
        // json损坏、解析失败，回退默认热键
        j = undefined_hotkeys;
    }
}

void load_hotkeymaps_from_json(const json& j, std::map<std::string, Hotkey>& hotkeymaps)
{
    hotkeymaps = j.get<std::map<std::string, Hotkey>>();
}

void load_json_from_hotkeymaps(const std::map<std::string, Hotkey>& hotkeymaps, json& j)
{
    j = hotkeymaps;
}

void save_file_from_json(const std::string& file_path, const json& j)
{
    std::ofstream out(file_path);
    if (!out.is_open())
    {
        // 文件打开失败
        return;
    }
    out << j.dump(4);
}