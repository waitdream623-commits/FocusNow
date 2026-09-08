#pragma once
#include <string>
#include <vector>
struct KeyEvent//记录每一次按键
{
    char expected;      // 目标字母
    char actual;        // 实际按下的字符
    double reactionTime;// 反应时间，先填 0，第⑧步再真正算
    bool correct;       // 这次按对了吗
};
struct LetterData//记录每一个字母的统计数据（= KeyStats）
{
    int correctCount = 0;   // 按对次数
    int totalCount = 0;     // 总共出现次数
    int errorCount = 0;     // 按错次数（= total - correct）
    double totalTime = 0.0; // 总共反应时间
    double accuracy = 0.0;      // 正确率（0~1）
    double avgReactionTime = 0.0;// 平均反应时间（秒）
};
struct MouseStats
{
    int total = 0;          // 鼠标判断总次数
    int correct = 0;        // 鼠标位置正确次数
    int errors = 0;         // 鼠标位置错误次数
};
struct SessionData//代表一次完整训练（第⑤步）
{
    long long timestamp = 0;    // 训练时间：Unix 时间戳（秒）
    double duration = 0.0;      // 训练时长（秒）
    double wpm = 0.0;           // 键盘表现：本局 WPM
    MouseStats mouse;           // 鼠标表现
    LetterData letters[26];     // A-Z 表现
};
struct UserData//一个用户的全部数据（第⑥步）
{
    std::string name = "Player1";  // 用户基本信息
    LetterData letters[26];        // 累计 A-Z 统计（所有局汇总）
    MouseStats mouse;              // 累计鼠标统计
    std::vector<SessionData> sessions;// 历史每次训练
};