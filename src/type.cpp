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

}
type::type(Font f)
{
    srand(time(0));//种下种子
    lefthand="qwertasdfgzxcvb";
    for(int i=0;i<MAX_LETTER_LENGTH;i++)
    {
        GetRandomLetter(i);
    }
    font = f;
}
void type::GetRandomLetter(int i) // 新的补充在后面
{
    letters[i].letter=lefthand[rand()%15];
    letters[i].x=rand()%(GetScreenWidth()-RADIUS*2)+RADIUS;
    letters[i].y=rand()%(GetScreenHeight()-RADIUS*2-100)+RADIUS;
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
    char a;
    while((a=GetCharPressed())&&a!=0)
    {
        
        if(a==letters[0].letter&&IsRightPlace())
        {
            for(int i=0;i<MAX_LETTER_LENGTH-1;i++)
            {
                letters[i]=letters[i+1];//将后续移动到前面
                
            }
            GetRandomLetter(MAX_LETTER_LENGTH-1);//新生成一个

        }
    }
 
}
void type::Draw()
{
    //画顺序
      for (int i = 0; i < MAX_LETTER_LENGTH; i++)
    {
        char letter[2] = {letters[i].letter, '\0'};          // 单个字符 + 结束符
        DrawTextEx(font, letter, {300 + 40.0f * i, GetScreenHeight()-70}, 50, 1, GREEN);//画顺序
        DrawCircle(letters[i].x,letters[i].y,letters[i].radius,DARKBLUE);//画圆
        DrawTextEx(font,letter,{letters[i].x-MeasureTextEx(font,letter,letters[i].radius * 1.2f,1).x/2,
             letters[i].y-MeasureTextEx(font,letter,letters[i].radius * 1.2f,1).y/2}, letters[i].radius * 1.2f , 1 , WHITE);//画字母

    }
    
}
