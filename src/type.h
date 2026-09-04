#pragma once
#include <raylib.h>
#include <string>
#include <vector>
#include "data.h"
constexpr int MAX_LETTER_LENGTH=4;//生成个数
constexpr int RADIUS=30;//球的大小
constexpr double SESSION_DURATION=60.0;//一局秒数
struct letterBall{
    char letter;
    float x,y;
    float radius;
};
class type{
    public: 
    type();//初始化
    type(Font f);// 函数重载
    void Draw();
    void IsPreesedCorret();
    double GetWPM();//计算打字速度(WPM)


    private:
    Font font;
    void GetRandomLetter(int newLetter);
    std::string lefthand;
    letterBall letters[MAX_LETTER_LENGTH];
    bool IsRightPlace();//检测鼠标位置
    bool IsFits();//检查
    std::vector<KeyEvent> keyEvents;//记录每次按键
    double startTime = 0.0;//本局开始时刻（秒）
    LetterData letterStats[26];//统计每个字母的情况
    MouseStats mouseStats;//统计鼠标操作情况
};