#include <raylib.h>
#include "type.h"
#include "mouse.h"
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
    type type(myFont);
    while (!WindowShouldClose())
    {
        
        BeginDrawing();
            ClearBackground(darkGreen);
            type.IsPreesedCorret();//判定加生成新字母
            type.Draw();
            mouse.ShowTrail();
            
        EndDrawing();
    }
    
    CloseWindow();
}