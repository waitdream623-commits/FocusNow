#include "type.h"
#include <random>
#include <time.h>
type::type()
{
    srand(time(0));//种下种子
    s="";
    pressed=0;
    lefthand="qwertasdfgzxcvb";
}
void type::GetRandomLetter()
{
    for(int i=1;i<=5;i++)
    {
        int randomvalue=rand()%15;
        s+=lefthand[randomvalue];
    }
    
}
void type::IsPreesedCorret()
{
    char a;
    while((a=GetCharPressed())&&a!=0)
    {
        
        if(a==s[pressed])
        {
            pressed++;

        }
    }
 
}
void type::Draw()
{
    for (int i = 0; i < s.size(); i++)
    {
        char letter[2] = {s[i], '\0'};          // 单个字符 + 结束符
        Color col = (i < pressed) ? RED : WHITE;
        DrawText(letter, 300 + 40 * i, 300, 40, col);
    }
    
}
void type::Newletters()
{
    if(s.size()==0||pressed==s.size())
    {
        s="";
        pressed=0;
        GetRandomLetter();

    }
    IsPreesedCorret();
}