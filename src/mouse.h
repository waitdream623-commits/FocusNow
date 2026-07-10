#pragma once 
#include <raylib.h>
constexpr int MAX_TRAIL_LENGTH=30;
class mouse{
    public:
    void show();
    void ShowTrail();
    private:
    
    Vector2 trailPositions[30]={0};
};
