#pragma once
#include <raylib.h>
#include <string>

// 主菜单（第⑧步）
class menu
{
public:
    menu(Font f);   // 复用游戏字体，不负责卸载
    int Update();   // 返回本帧确认的选择：0=无，1~5=菜单项
    void Draw();    // 绘制菜单

private:
    static constexpr int ITEM_COUNT = 5;
    const char* items[ITEM_COUNT] = {"Start Training", "Weak Training", "Statistics", "User Management", "Quit"};
    int selected = 0;    // 当前高亮项 0..4
    Font font;           // 菜单字体
    std::string hint;    // 底部提示（如"Coming soon"）
};
