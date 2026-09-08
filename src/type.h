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
    void StartSession();//第⑧步：开始新的一局（重置计时与统计）
    double GetWPM();//计算打字速度(WPM)
    void ComputeLetterStats(LetterData out[26]) const;//从 keyEvents 汇总每个字母统计
    bool SaveUserData(const std::string& path) const;//第⑦步：存档
    bool LoadUserData(const std::string& path);//第⑦步：读档


    private:
    Font font;
    void GetRandomLetter(int newLetter);
    std::string lefthand;
    letterBall letters[MAX_LETTER_LENGTH];
    bool IsRightPlace();//检测鼠标位置
    bool IsFits();//检查
    std::vector<KeyEvent> keyEvents;//记录每次按键
    LetterData letterStats[26];//从 keyEvents 汇总出的每个字母统计（第③步结算时填）
    double startTime = 0.0;//本局开始时刻（秒）
    MouseStats mouseStats;//统计鼠标操作情况（第④步再填数据）
    UserData userData;//当前用户全部数据（第⑥步）
};