#include "type.h"
#include <random>
#include <time.h>
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
void type::IsPreesedCorret()
{
    // // 一局时间
    // double now = GetTime();
    // if (now - startTime >= SESSION_DURATION)
    // {
    //     keyEvents.clear();// 先清空，开始新的一局
    //     startTime = now;
    // }
    //不用按鼠标
    char a;//获取输入按键
    while((a=GetCharPressed())&&a!=0)
    {
        keyEvents.push_back({letters[0].letter, a, 0.0, a == letters[0].letter && IsRightPlace()}); // 记录按键事件

        if(a==letters[0].letter&&IsRightPlace())//比较第一个字母
        {
            letterStats[letters[0].letter - 'a'].correctCount++; // 更新按对次数
            mouseStats.correct++; // 更新鼠标位置正确次数
            mouseStats.total++;// 鼠标判断总次数
            for(int i=0;i<MAX_LETTER_LENGTH-1;i++)
            {
                letters[i]=letters[i+1];//将后续移动到前面
                
            }
            GetRandomLetter(MAX_LETTER_LENGTH-1);//新生成一个

        }
        else 
        {
            mouseStats.total++;
            mouseStats.errors++;// 鼠标位置错误次数
        }
    }
    //     // 只有鼠标左键按下才判定
    // if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    //     return;

    // char a = letters[0].letter;
    // bool correct = IsRightPlace();//先判定位置，避免消除后 letters[0] 改变

    // mouseStats.total++;                          // 鼠标判断总次数
    // letterStats[a - 'a'].totalCount++;    // 更新总出现次数

    // if (correct)//鼠标按下且位置正确才消除
    // {
    //     mouseStats.correct++;                          // 鼠标位置正确次数
    //     letterStats[a - 'a'].correctCount++;    // 更新按对次数

    //     // 消除当前字母：后续前移，末尾生成新字母
    //     for (int i = 0; i < MAX_LETTER_LENGTH - 1; i++)
    //     {
    //         letters[i] = letters[i + 1];
    //     }
    //     GetRandomLetter(MAX_LETTER_LENGTH - 1);
    // }
    // else
    // {
    //     mouseStats.errors++;// 鼠标位置错误次数
    // }

    // keyEvents.push_back({letters[0].letter, a, 0.0, correct}); // 记录本次操作

    TraceLog(LOG_INFO, "event count: %d", (int)keyEvents.size());
    TraceLog(LOG_INFO, "totalCount: %d", letterStats[letters[0].letter - 'a'].totalCount);
    TraceLog(LOG_INFO, "correct count: %d", letterStats[letters[0].letter - 'a'].correctCount);
    TraceLog(LOG_INFO, "mouse total: %d", mouseStats.total);
    TraceLog(LOG_INFO, "mouse correct: %d", mouseStats.correct);
    TraceLog(LOG_INFO, "mouse errors: %d", mouseStats.errors);
 
}
double type::GetWPM()
{
    double duration = GetTime() - startTime;//已经进行的秒数
    if (duration <= 0) return 0.0;//避免除零
    int correct = 0;
    for (int i = 0; i < 26; i++)
    {
        correct += letterStats[i].correctCount;
    }
    //WPM = (正确字数 / 5) / 分钟数
    return correct / 5.0 / (duration / 60.0);
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
