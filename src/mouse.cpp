#include "mouse.h"

void mouse::show()
{
    ShowCursor();   // 确保鼠标可见
    SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);//手形
}

void mouse::ShowTrail()
{
     Vector2 mousePosition=GetMousePosition();
     for(int i=MAX_TRAIL_LENGTH-1;i>0;i--)
     {
        trailPositions[i]=trailPositions[i-1];
     }
     trailPositions[0]=mousePosition;

            for (int i = 0; i < MAX_TRAIL_LENGTH; i++)
            {
               
                if ((trailPositions[i].x != 0.0f) || (trailPositions[i].y != 0.0f))//跳过未装的
                {
                    
                    float ratio = (float)(MAX_TRAIL_LENGTH - i)/MAX_TRAIL_LENGTH;//计算距离比率
                    //距离越远越透明
                    // Fade (color, alpha) 
                    Color trailColor = Fade(SKYBLUE, ratio*0.5f + 0.5f);

                    // 远的更小
                    float trailRadius = 5.0f*ratio;

                    DrawCircleV(trailPositions[i], trailRadius, trailColor);
                }
            }

           
            DrawCircleV(mousePosition, 5.0f, WHITE);//最新位置在[0]处
}
