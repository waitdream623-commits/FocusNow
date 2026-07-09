#pragma once
#include <raylib.h>
#include <string>
class type{
    private:
    void IsPreesedCorret();
    void GetRandomLetter();
    std::string s;
    std::string lefthand;
    int pressed;
    public:
    
    type();//初始化
    void Draw();
    void Newletters();
};