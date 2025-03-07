#include "raylib.h"


int main(){
    InitWindow(800, 600, "Raylib Template");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Update Game Logic here


        // Draw The Art here
        BeginDrawing();
        ClearBackground(WHITE);
        DrawText("Raylib Template By Haj4li.",400,300,20,PURPLE);
        EndDrawing();
    }
    CloseWindow();

    return 0;
}