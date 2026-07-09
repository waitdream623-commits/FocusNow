#include <raylib.h>
#include "type.h"
int main() 
{
    const Color darkGreen = {20, 160, 133, 255};
    
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "FcousNow");
    SetTargetFPS(60);
    type type;
    while (!WindowShouldClose())
    {
        
        BeginDrawing();

            ClearBackground(darkGreen);
            type.Newletters();//生成新字母
            type.Draw();
        EndDrawing();
    }
    
    CloseWindow();
}