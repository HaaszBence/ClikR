#ifndef UI_H
#define UI_H

#include <raylib.h>
#include <stdbool.h>

// Kirajzol egy gombot, és true-t ad vissza, ha rákattintottak
bool UI_DrawButton(Rectangle rect, const char *text, int fontSize, Color baseColor, Color hoverColor, Sound clickSound);

// Kirajzol egy vízszintes csúszkát (0.0f - 1.0f), és visszaadja az új értéket
float UI_DrawSlider(Rectangle bar, float value, const char *label, int fontSize);

#endif