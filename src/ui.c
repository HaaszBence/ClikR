#include "ui.h"
#include "assets.h"

bool UI_DrawButton(Rectangle rect, const char *text, int fontSize, Color baseColor, Color hoverColor, Sound clickSound) {
    Vector2 mouse = GetMousePosition();
    bool hover = CheckCollisionPointRec(mouse, rect);
    bool pressed = hover && IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    bool clicked = hover && IsMouseButtonReleased(MOUSE_BUTTON_LEFT);

    if (clicked) {
        PlaySound(clickSound);
    }

    Rectangle visualRect = rect;
    if (hover) {
        visualRect.x -= 3.0f;
        visualRect.y -= 3.0f;
        visualRect.width += 6.0f;
        visualRect.height += 6.0f;
    }
    if (pressed) {
        visualRect.x += 2.0f;
        visualRect.y += 3.0f;
    }

    Rectangle shadowRect = visualRect;
    
    shadowRect.y += 5.0f;
    DrawRectangleRounded(shadowRect, 0.25f, 8, (Color){ 32, 46, 14, 170 });

    DrawRectangleRounded(visualRect, 0.25f, 8, hover ? PALETTE_GOLD : PALETTE_DARK_OLIVE);
    Rectangle innerRect = {
        visualRect.x + 2.0f,
        visualRect.y + 2.0f,
        visualRect.width - 4.0f,
        visualRect.height - 4.0f
    };
    DrawRectangleRounded(innerRect, 0.25f, 8, hover ? hoverColor : baseColor);

    const char *displayText = hover ? TextFormat("> %s <", text) : text;
    int textW = MeasureText(displayText, fontSize);
    float textX = visualRect.x + (visualRect.width - textW) / 2.0f;
    float textY = visualRect.y + (visualRect.height - fontSize) / 2.0f;
    DrawText(displayText, (int)textX, (int)textY, fontSize, hover ? PALETTE_DARK_OLIVE : PALETTE_CHALK);

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

    DrawText(TextFormat("%s: %.0f%%", label, value * 100.0f), (int)bar.x, (int)(bar.y - fontSize - 8), fontSize, PALETTE_CHALK);

    Color trackColor = { 45, 62, 20, 220 };
    Rectangle shadow = { bar.x + 3.0f, bar.y + 4.0f, bar.width, bar.height };
    DrawRectangleRounded(shadow, 0.5f, 8, (Color){ 32, 46, 14, 150 });
    DrawRectangleRounded(bar, 0.5f, 8, PALETTE_CHALK);
    Rectangle track = { bar.x + 2.0f, bar.y + 2.0f, bar.width - 4.0f, bar.height - 4.0f };
    DrawRectangleRounded(track, 0.5f, 8, trackColor);

    Rectangle fill = track;
    fill.width *= value;
    if (fill.width > 0.0f) DrawRectangleRounded(fill, 0.5f, 8, PALETTE_GOLD);

    float handleRadius = bar.height * 0.75f;
    if (handleRadius < 8.0f) handleRadius = 8.0f;
    Vector2 handle = { bar.x + bar.width * value, bar.y + bar.height / 2.0f };
    DrawCircleV((Vector2){ handle.x + 3.0f, handle.y + 4.0f }, handleRadius, (Color){ 32, 46, 14, 170 });
    DrawCircleV(handle, handleRadius, PALETTE_LEMON);
    DrawCircleLines((int)handle.x, (int)handle.y, handleRadius + 1.0f, PALETTE_DARK_OLIVE);

    return value;
}

void UI_DrawCursor(GameAssets *assets) {
    Vector2 mouse = GetMousePosition();
    float size = GetScreenHeight() * 0.045f;
    Texture2D activeTex = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? assets->cursorClick : assets->cursorIdle;

    Rectangle src  = { 0.0f, 0.0f, (float)activeTex.width, (float)activeTex.height };
    Rectangle dest = { mouse.x, mouse.y, size, size };
    DrawTexturePro(activeTex, src, dest, (Vector2){ 0.0f, 0.0f }, 0.0f, WHITE);
}