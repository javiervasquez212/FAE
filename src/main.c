#include "raylib.h"

int main(void)
{

    // Lo ideal sería hacer un struct con la información del player, hay que definir las clases y structs.

    // create a window
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "El fruto del arbol envenenado");

    // Agregar textura
    Texture2D playerTex = LoadTexture("../../FAE/src/img/playerTexture.png");

    // Altura del piso
    const int floorHeight = 450 - playerTex.height;

    // Posición relativa del jugador, empieza en la esquina inferior izquierda
    Vector2 playerPosition = {playerTex.width, floorHeight};

    // Velocidad del jugador
    const float playerSpeed = 4.0f;
    // Salto del jugador
    const int jumpForce = 40.0f;
    bool isJumping = false;
    float gravity = 1.0f;

    // wait 3 seconds
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Movimiento del jugador con validación de colisiones, derecha e izquierda
        if (IsKeyDown(KEY_RIGHT) && playerPosition.x + playerTex.width < screenWidth)
            playerPosition.x += playerSpeed;
        if (IsKeyDown(KEY_LEFT) && playerPosition.x > 0)
            playerPosition.x -= playerSpeed;

        // Salto del jugador
        if (IsKeyDown(KEY_UP) && !isJumping)
        {
            // Verificar que el jugador esté en el suelo antes de saltar
            if (playerPosition.y >= floorHeight)
            {
                playerPosition.y -= jumpForce;
                isJumping = true;
            }
        }

        // Aplicar gravedad
        if (playerPosition.y < floorHeight)
        {
            playerPosition.y += gravity;
        }
        else
        {
            // El jugador ha tocado el suelo, restablecer el estado de salto
            isJumping = false;
        }

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
