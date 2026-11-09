#include <stdio.h>
#include <raylib.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900
#define TARGET_FPS 240

int main(void) {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game Window");
    SetTargetFPS(TARGET_FPS);
    Color bgColor = (Color){ 247, 207, 141, 255 };

    while (!WindowShouldClose()) {
        
        if(IsKeyPressed(KEY_ESCAPE)) {
            break;
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            printf("Left mouse button pressed!\n");
        }

        BeginDrawing();

        ClearBackground(bgColor);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}