#ifndef UI_H
#define UI_H

#include <raylib.h>
#include <stdbool.h>
#include "assets.h"

#define PALETTE_GOLD       (Color){ 244, 190,  56, 255 }
#define PALETTE_LEMON      (Color){ 237, 218,  94, 255 }
#define PALETTE_MOSS_GREEN (Color){ 113, 149,  30, 255 }
#define PALETTE_DARK_OLIVE (Color){  88, 117,  41, 255 }
#define PALETTE_CHALK      (Color){ 248, 246, 236, 255 }

// Kirajzol egy gombot, és true-t ad vissza, ha rákattintottak
bool UI_DrawButton(Rectangle rect, const char *text, int fontSize, Color baseColor, Color hoverColor, Sound clickSound);

// Kirajzol egy vízszintes csúszkát (0.0f - 1.0f), és visszaadja az új értéket
float UI_DrawSlider(Rectangle bar, float value, const char *label, int fontSize);

// Kirajzolja az egyedi kurzort a képernyőn
void UI_DrawCursor(GameAssets *assets);

#endif