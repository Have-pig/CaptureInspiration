#pragma once
#include "json.hpp"
#include <string>
#include <map>
#include "struct_define.h"

using json = nlohmann::json;


/**
 * @brief 从文件加载json，若没有文件则创建文件
 * @param file_path 文件路径
 * @param j json对象
 */
void load_setting_json(std::string file_path, json& j);

/**
 * @brief 保存json到文件
 * @param file_path 文件路径
 * @param j json对象
 */
void save_file_from_json(const std::string& file_path, const json& j);

/**
 * define in control_events.cpp
 *  @brief json转化为Setting
 *  @param j json对象
 *  @param settings Setting对象
 */
void load_setting_from_json(const json& j, Setting& settings);

/**
 *  @brief Setting转化为json
 *  @param j json对象
 *  @param settings Setting对象
 */
void load_json_from_setting(const Setting& settings, json& j);
