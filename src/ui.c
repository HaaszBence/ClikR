#include "ui.h"

bool UI_DrawButton(Rectangle rect, const char *text, int fontSize, Color baseColor, Color hoverColor, Sound clickSound) {
    Vector2 mouse = GetMousePosition();
    bool hover = CheckCollisionPointRec(mouse, rect);
    bool clicked = hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    if (clicked) {
        PlaySound(clickSound);
    }

    DrawRectangleRec(rect, hover ? hoverColor : baseColor);
    DrawRectangleLinesEx(rect, 2, WHITE);

    int textW = MeasureText(text, fontSize);
    float textX = rect.x + (rect.width - textW) / 2.0f;
    float textY = rect.y + (rect.height - fontSize) / 2.0f;
    DrawText(text, (int)textX, (int)textY, fontSize, WHITE);

    return clicked;
}

float UI_DrawSlider(Rectangle bar, float value, const char *label, int fontSize) {
    Vector2 mouse = GetMousePosition();
    bool hover = CheckCollisionPointRec(mouse, (Rectangle){ bar.x - 10, bar.y - 10, bar.width + 20, bar.height + 20 });

    if (hover && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        value = (mouse.x - bar.x) / bar.width;
        if (value < 0.0f) value = 0.0f;
        if (value > 1.0f) value = 1.0f;
    }

    DrawText(TextFormat("%s: %.0f%%", label, value * 100.0f), (int)bar.x, (int)(bar.y - fontSize - 8), fontSize, WHITE);

    DrawRectangleRec(bar, DARKGRAY);
    DrawRectangle((int)bar.x, (int)bar.y, (int)(bar.width * value), (int)bar.height, hover ? SKYBLUE : BLUE);
    DrawRectangleLinesEx(bar, 2, WHITE);

    return value;
}