#include "raylib.h"

// Definición de constantes para evitar magicnumbers
const int screenWidth = 700;
const int screenHeight = 598;
const float playerSpeed = 4.0f;
const float jumpForce = 10.0f;
const float gravity = 0.5f;

int main(void)
{

    // Inicialización de la ventana y el audio
    InitWindow(screenWidth, screenHeight, "El fruto del árbol envenenado");
    InitAudioDevice();

    // Se cargan las texturas y el audio
    Texture2D playerTex = LoadTexture("../../FAE/src/img/playerTexture.png");
    Texture2D backgroundTex = LoadTexture("../../FAE/src/img/background.png");
    Sound backgroundSoundtrack = LoadSound("../../FAE/src/soundtracks/backgroundSountrack.wav");

    // Constante de la altura del piso, para validar movimiento
    const int floorHeight = screenHeight - playerTex.height;

    // Definimos los vectores, uno para la posición y otro para la velocidad(salto)
    Vector2 playerPosition = {playerTex.width, floorHeight};
    Vector2 playerVelocity = {0.0f, 0.0f}; // La velocidad comienza en 0

    // Variable para validar el salto
    bool isJumping = false;

    // Ejecutamos el sonido
    PlaySound(backgroundSoundtrack);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_RIGHT) && playerPosition.x + playerTex.width < screenWidth)
            playerPosition.x += playerSpeed;
        if (IsKeyDown(KEY_LEFT) && playerPosition.x > 0)
            playerPosition.x -= playerSpeed;

        // Validar si puede saltar
        if (IsKeyDown(KEY_UP) && !isJumping)
        {
            // Validar que caiga en el piso y no se hunda
            if (playerPosition.y >= floorHeight)
            {
                playerVelocity.y = -jumpForce;
                isJumping = true;
            }
        }

        // Ubicación segun velocidad y posición
        playerVelocity.y += gravity;
        playerPosition.x += playerVelocity.x;
        playerPosition.y += playerVelocity.y;

        // Validar si el jugador ha aterrizado
        if (playerPosition.y >= floorHeight)
        {
            playerPosition.y = floorHeight;
            isJumping = false;
            playerVelocity.y = 0.0f; // Resetea valores
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(backgroundTex, 0, 0, WHITE);
        DrawTextureV(playerTex, playerPosition, WHITE);
        EndDrawing();
    }

    UnloadTexture(playerTex);
    UnloadTexture(backgroundTex);
    UnloadSound(backgroundSoundtrack);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
