#include "raylib.h"

int main(void)
{
    // create a window
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "El fruto del arbol envenenado");

    // Agregar textura
    Texture2D playerTex = LoadTexture("../../FAE/src/img/playerTexture.png");

    // Posición relativa del jugador, empieza en la esquina inferior izquierda
    Vector2 playerPosition = {playerTex.width, 450 - playerTex.height};

    // Velocidad del jugador
    const float playerSpeed = 4.0f;

    // wait 3 seconds
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        // Movimiento del jugador con validación de colisiones
        if (IsKeyDown(KEY_RIGHT) && playerPosition.x + playerTex.width < screenWidth)
            playerPosition.x += playerSpeed;
        if (IsKeyDown(KEY_LEFT) && playerPosition.x > 0)
            playerPosition.x -= playerSpeed;
        if (IsKeyDown(KEY_UP) && playerPosition.y > 0)
            playerPosition.y -= playerSpeed;
        if (IsKeyDown(KEY_DOWN) && playerPosition.y + playerTex.height < screenHeight)
            playerPosition.y += playerSpeed;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Dibujar textura en la ventana con movimiento
        DrawTextureV(playerTex, playerPosition, WHITE);

        EndDrawing();
    }
    CloseWindow();

    // exit
    return 0;
}
