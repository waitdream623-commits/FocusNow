#pragma once
#include <string>
#include "data.h"

// 存档 / 读档（第⑦步）
namespace storage {

constexpr const char* kDefaultSavePath = "save.txt";//默认存档路径

void RecomputeLetterDerived(LetterData& d);//重算推导字段（错误次数/正确率/平均反应时间）
void AddSession(UserData& user, const SessionData& s);//累计一次训练进用户数据
bool Save(const UserData& user, const std::string& path);//保存到文件
bool Load(UserData& user, const std::string& path);//从文件读取

}
