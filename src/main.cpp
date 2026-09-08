#include <raylib.h>
#include "type.h"
#include "mouse.h"
#include "storage.h"
#include "menu.h"

enum class Screen { Menu, Game };

int main() 
{
    const Color darkGreen = {20, 160, 133, 255};
    
    constexpr int screenWidth = 1280;
    constexpr int screenHeight = 960;
    
    InitWindow(screenWidth, screenHeight, "FcousNow");
    Font myFont = LoadFont("assets/font/monogram.ttf");
    mouse mouse;
    mouse.show();
    SetTargetFPS(60);
    type game(myFont);
    // 第⑦步：启动时读档
    TraceLog(LOG_INFO, "Load save %s", game.LoadUserData(storage::kDefaultSavePath) ? "OK" : "failed (using default user)");

    menu mainMenu(myFont);// 第⑧步：主菜单
    Screen screen = Screen::Menu;

    while (!WindowShouldClose())
    {
        if (screen == Screen::Menu)
        {
            int choice = mainMenu.Update();
            if (choice == 1)// 开始训练
            {
                game.StartSession();
                screen = Screen::Game;
            }
            else if (choice == 5)// 退出
            {
                break;
            }
            // choice 2~4（薄弱训练/数据统计/用户管理）后续步骤实现，目前只提示"开发中"
        }
        else // Game
        {
            game.IsPreesedCorret();//判定加生成新字母
            if (IsKeyPressed(KEY_ESCAPE)) screen = Screen::Menu;//ESC 返回菜单
        }

        BeginDrawing();
            ClearBackground(darkGreen);
            if (screen == Screen::Menu)
            {
                mainMenu.Draw();
            }
            else
            {
                game.Draw();
                mouse.ShowTrail();
            }
        EndDrawing();
    }
    
    UnloadFont(myFont);
    CloseWindow();
    return 0;
}