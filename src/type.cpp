#include "type.h"
#include "storage.h"
#include <random>
#include <time.h>
#include <cctype>

type::type()
{
    srand(time(0));//种下种子
    lefthand="qwertasdfgzxcvb";
    for(int i=0;i<MAX_LETTER_LENGTH;i++)
    {
        GetRandomLetter(i);
    }
    startTime=GetTime();//本局开始计时 

}
type::type(Font f)// 函数重载
{
    srand(time(0));//种下种子
    lefthand="qwertasdfgzxcvb";
    for(int i=0;i<MAX_LETTER_LENGTH;i++)
    {
        GetRandomLetter(i);
    }
    font = f;
    startTime=GetTime();//本局开始计时

}
void type::GetRandomLetter(int i) // 新的补充在后面
{
    //解决重复字母
    bool isUnique;
    do
    {
        letters[i].letter=lefthand[rand()%15];
        isUnique=true;
        for(int j=0;j<i;j++)
        {
            if(letters[j].letter==letters[i].letter)
            {
                isUnique=false;
                break;
            }
        }
    } while(!isUnique);
    //解决位置重复，范围不重叠
    bool isUniquePosition;
    do
    {
        letters[i].x=rand()%(GetScreenWidth()-RADIUS*2)+RADIUS;
        letters[i].y=rand()%(GetScreenHeight()-RADIUS*2-100)+RADIUS;
        isUniquePosition=true;
        for(int j=0;j<i;j++)
        {
            float dx=letters[j].x-letters[i].x;
            float dy=letters[j].y-letters[i].y;
            if(dx*dx+dy*dy<RADIUS*RADIUS*4)//两点距离小于半径2倍(平方比较)
            {
                isUniquePosition=false;
                break;
            }
        }
    } while(!isUniquePosition);
    letters[i].radius=RADIUS;
    
}
bool type::IsRightPlace()
{
    Vector2 mousePosition=GetMousePosition();
    //判定是否在圆圈内
    int x=letters[0].x;
    int y=letters[0].y;
    int r=letters[0].radius;
    if(mousePosition.x>=x-r&&mousePosition.x<=x+r&&mousePosition.y>=y-r&&mousePosition.y<=y+r)
    {
        return true;
    }
    return false;

}
void type::StartSession()
{
    keyEvents.clear();
    mouseStats = MouseStats{};
    startTime = GetTime();
}

void type::IsPreesedCorret()
{
    // 一局 60 秒：时间到 → 结束本局（第③步：结算时汇总字母统计，保存以后再做）
    double now = GetTime();
    if (now - startTime >= SESSION_DURATION)
    {
        ComputeLetterStats(letterStats);// 从 keyEvents 汇总每个字母统计

        // 第⑤步：组装本次训练 SessionData
        SessionData s;
        s.timestamp = (long long)time(nullptr);
        s.duration = now - startTime;
        s.wpm = GetWPM();                 // 必须在清空 keyEvents 之前算
        s.mouse = mouseStats;
        for (int i = 0; i < 26; i++) s.letters[i] = letterStats[i];

        // 第⑥步：追加到用户数据，并累计 A-Z / 鼠标统计
        storage::AddSession(userData, s);

        double mouseAcc = (mouseStats.total > 0) ? (double)mouseStats.correct / mouseStats.total * 100.0 : 0.0;
        TraceLog(LOG_INFO, "Session ended: keyEvents=%d, WPM=%.1f, A accuracy=%.1f%%, mouse accuracy=%.1f%%, sessions=%d",
                 (int)keyEvents.size(), s.wpm, letterStats[0].accuracy * 100.0, mouseAcc, (int)userData.sessions.size());

        // 第⑦步：每局结束后存档
        TraceLog(LOG_INFO, "Save %s", SaveUserData(storage::kDefaultSavePath) ? "OK" : "failed");
        keyEvents.clear();// 先清空，开始新的一局
        mouseStats = MouseStats{};// 清空本局鼠标统计
        startTime = now;
    }

    char a;//获取输入按键
    while((a=GetCharPressed())&&a!=0)
    {
        bool mouseOnTarget = IsRightPlace();//本帧鼠标是否在目标圆内
        bool keyCorrect = (a == letters[0].letter);//按键字母是否正确

        // 第④步：每次按键都是一次"鼠标注意力"判断，统计鼠标位置对错
        mouseStats.total++;
        if (mouseOnTarget) mouseStats.correct++;
        else mouseStats.errors++;

        // 唯一真相源：只记录事件，统计在需要时从 keyEvents 计算
        keyEvents.push_back({letters[0].letter, a, 0.0, keyCorrect && mouseOnTarget});

        if(keyCorrect && mouseOnTarget)//比较第一个字母
        {
            for(int i=0;i<MAX_LETTER_LENGTH-1;i++)
            {
                letters[i]=letters[i+1];//将后续移动到前面
            }
            GetRandomLetter(MAX_LETTER_LENGTH-1);//新生成一个
        }
    }
}

double type::GetWPM()
{
    double duration = GetTime() - startTime;//已经进行的秒数
    if (duration <= 0) return 0.0;//避免除零
    int correct = 0;
    for (const KeyEvent& e : keyEvents)
    {
        if (e.correct) correct++;
    }
    //WPM = (正确字数 / 5) / 分钟数
    return correct / 5.0 / (duration / 60.0);
}

void type::ComputeLetterStats(LetterData out[26]) const
{
    for (int i = 0; i < 26; i++) out[i] = LetterData{};// 清零
    for (const KeyEvent& e : keyEvents)
    {
        char expected = (char)std::tolower((unsigned char)e.expected);
        if (expected < 'a' || expected > 'z') continue;
        int idx = expected - 'a';
        out[idx].totalCount++;               // 该字母出现次数
        if (e.correct) out[idx].correctCount++;// 按对次数
        out[idx].totalTime += e.reactionTime;  // 反应时间（现在全是0）
    }
    // 补全推导字段：错误次数 / 正确率 / 平均反应时间
    for (int i = 0; i < 26; i++) storage::RecomputeLetterDerived(out[i]);
}

bool type::SaveUserData(const std::string& path) const
{
    return storage::Save(userData, path);
}

bool type::LoadUserData(const std::string& path)
{
    return storage::Load(userData, path);
}

void type::Draw()
{
    //画顺序
    for (int i = 0; i < MAX_LETTER_LENGTH; i++)
    {
        char letter[2] = {letters[i].letter, '\0'};          // 单个字符 + 结束符
        DrawTextEx(font, letter, {300 + 40.0f * i, (float)(GetScreenHeight()-70)}, 50, 1, GREEN);//画顺序
        DrawCircle(letters[i].x,letters[i].y,letters[i].radius,DARKBLUE);//画圆
        DrawTextEx(font,letter,{letters[i].x-MeasureTextEx(font,letter,letters[i].radius * 1.2f,1).x/2,
             letters[i].y-MeasureTextEx(font,letter,letters[i].radius * 1.2f,1).y/2}, letters[i].radius * 1.2f , 1 , WHITE);//画字母
    }

    //显示WPM
    DrawTextEx(font, TextFormat("WPM: %.1f", GetWPM()), {20.0f, 20.0f}, 40, 1, WHITE);
}
