#pragma once
struct KeyEvent//记录每一次按键
{
    char expected;      // 目标字母
    char actual;        // 实际按下的字符
    double reactionTime;// 反应时间，先填 0，第⑧步再真正算
    bool correct;       // 这次按对了吗
};
struct LetterData//记录每一个字母的统计数据
{
    int correctCount = 0;   // 按对次数
    int totalCount = 0;     // 总共出现次数
    double totalTime = 0.0; // 总共反应时间
};
struct MouseStats
{
    int total = 0;          // 鼠标判断总次数
    int correct = 0;        // 鼠标位置正确次数
    int errors = 0;         // 鼠标位置错误次数
};