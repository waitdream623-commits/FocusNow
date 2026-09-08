#include "menu.h"

menu::menu(Font f)
{
    font = f;
}

int menu::Update()
{
    // 键盘：上下移动
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) selected = (selected - 1 + ITEM_COUNT) % ITEM_COUNT;
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) selected = (selected + 1) % ITEM_COUNT;

    // 鼠标：悬停高亮 + 点击确认
    Vector2 mp = GetMousePosition();
    const float itemHeight = 60.0f;
    const float startY = GetScreenHeight() / 2.0f - 100.0f;
    const float boxWidth = 340.0f;
    const float boxHeight = 52.0f;
    int hovered = -1;
    for (int i = 0; i < ITEM_COUNT; i++)
    {
        Rectangle r = { GetScreenWidth() / 2.0f - boxWidth / 2, startY + i * itemHeight - 6.0f, boxWidth, boxHeight };
        if (CheckCollisionPointRec(mp, r)) hovered = i;
    }
    if (hovered >= 0) selected = hovered;

    bool confirm = IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE);
    if (hovered >= 0 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) confirm = true;

    if (confirm)
    {
        int choice = selected + 1;
        if (choice >= 2 && choice <= 4) hint = "Coming soon";
        else hint.clear();
        return choice;
    }
    return 0;
}

void menu::Draw()
{
    const char* title = "FOCUS NOW";
    float titleSize = 80.0f;
    Vector2 ts = MeasureTextEx(font, title, titleSize, 1);
    DrawTextEx(font, title, { GetScreenWidth() / 2.0f - ts.x / 2, 120.0f }, titleSize, 1, RAYWHITE);

    const float itemHeight = 60.0f;
    const float startY = GetScreenHeight() / 2.0f - 100.0f;
    const float fontSize = 32.0f;
    for (int i = 0; i < ITEM_COUNT; i++)
    {
        Color color = (i == selected) ? YELLOW : RAYWHITE;
        Vector2 sz = MeasureTextEx(font, items[i], fontSize, 1);
        DrawTextEx(font, items[i], { GetScreenWidth() / 2.0f - sz.x / 2, startY + i * itemHeight }, fontSize, 1, color);
        if (i == selected)
        {
            DrawRectangleLines((int)(GetScreenWidth() / 2.0f - 170.0f), (int)(startY + i * itemHeight - 8.0f), 340, 56, YELLOW);
        }
    }

    if (!hint.empty())
    {
        Vector2 hz = MeasureTextEx(font, hint.c_str(), 30.0f, 1);
        DrawTextEx(font, hint.c_str(), { GetScreenWidth() / 2.0f - hz.x / 2, (float)GetScreenHeight() - 80.0f }, 30.0f, 1, ORANGE);
    }
}
