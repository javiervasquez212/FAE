#include "raylib.h"

int main(void)
{

    /*Notas
    Lo ideal sería hacer un struct con la información del player, hay que definir las clases y structs.

    Quitar todos los "magicnumbers" y ponerlos como constantes.

    */

    // Crea la ventana (screenWidth y screenHeigth deben ser del tamaño de la imagen del background)

    const int screenWidth = 700;
    const int screenHeight = 598;

    InitWindow(screenWidth, screenHeight, "El fruto del arbol envenenado");

    // Inicializar el audio
    InitAudioDevice();

    // Agregar textura del jugador
    Texture2D playerTex = LoadTexture("../../FAE/src/img/playerTexture.png");

    // Agregar imagen del background
    Texture2D backgroundTex = LoadTexture("../../FAE/src/img/background.png");

    // Agregar el sountrack del background

    Sound backgroundSoundtrack = LoadSound("../../FAE/src/soundtracks/backgroundSountrack.wav");
    // Altura del piso
    const int floorHeight = screenHeight - playerTex.height;

    // Posición relativa del jugador, empieza en la esquina inferior izquierda
    Vector2 playerPosition = {playerTex.width, floorHeight};

    // Velocidad del jugador
    const float playerSpeed = 4.0f;
    // Salto del jugador
    const int jumpForce = 40.0f;
    bool isJumping = false;
    float gravity = 1.0f;

    // Ejecuta la musica

    PlaySound(backgroundSoundtrack);

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

        // Agregar background a la ventana
        DrawTexture(backgroundTex, 0, 0, WHITE);

        // Dibujar textura en la ventana
        DrawTextureV(playerTex, playerPosition, WHITE);

        EndDrawing();
    }

    // Unloading de las variables

    UnloadTexture(playerTex);
    UnloadTexture(backgroundTex);
    UnloadSound(backgroundSoundtrack);

    CloseAudioDevice();

    CloseWindow();

    // exit
    return 0;
}
