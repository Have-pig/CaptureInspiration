#pragma once
#include "json.hpp"
#include <string>
#include <map>
#include "control_events.h"

using json = nlohmann::json;

/**
 * @brief 从文件加载json，若没有文件则创建文件
 * @param file_path 文件路径
 * @param j json对象
 */
void load_json_from_file(const std::string& file_path, json& j);

/**
 * @brief 从json加载hotkeymaps
 * @param j json对象
 * @param hotkeymaps hotkeymaps对象
 */
void load_hotkeymaps_from_json(const json& j, std::map<std::string, Hotkey>& hotkeymaps);

/**
 * @brief 从hotkeymaps加载json
 * @param hotkeymaps hotkeymaps对象
 * @param j json对象
 */
void load_json_from_hotkeymaps(const std::map<std::string, Hotkey>& hotkeymaps, json& j);

/**
 * @brief 保存json到文件
 * @param file_path 文件路径
 * @param j json对象
 */
void save_file_from_json(const std::string& file_path, const json& j);