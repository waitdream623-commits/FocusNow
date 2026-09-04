#pragma once 
#include <raylib.h>
constexpr int MAX_TRAIL_LENGTH=30;
class mouse{
    public:
    void show();
    void ShowTrail();//实现一个移动轨迹
    
    private:
    
    Vector2 trailPositions[30]={0};
};
