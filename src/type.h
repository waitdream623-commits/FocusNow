#pragma once
#include <raylib.h>
#include <string>
constexpr int MAX_LETTER_LENGTH=4;
constexpr int RADIUS=30;
struct letterBall{
    char letter;
    float x,y;
    float radius;
};
class type{
    public: 
    type();//初始化
    type(Font f);
    void Draw();
    void IsPreesedCorret();


    private:
    Font font;
    void GetRandomLetter(int newLetter);
    std::string lefthand;
    letterBall letters[MAX_LETTER_LENGTH];
    bool IsRightPlace();//检测鼠标位置

};