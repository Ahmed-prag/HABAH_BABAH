#include "raylib.h"
int main() {
    int window = 800;
    InitWindow(window, window, "HABAH_BABAH");
    SetTargetFPS(60);
    // Propriete du Charactere
    int charWidth=40, charHeight=60;
    int charX=window/2-charWidth/2;  // milieu vers direction x
    // Ligne du sol
    int groundY=window-20;  // position du ligne du sol
    int charY=groundY-charHeight;  // charactere reste sur sol
    // vitesse du movement gauchhe ou droite
    int charSpeed=6;

    // physique du saut
    bool isJumping=false; // initielement, il ne saut pas. ou bien?
    float velocityY=0; // vitesse initial vers le haut est nul.
    float gravity=1.0f;      // force de la traction, diminue par 1
    float jumpStrength = -18;  // impulsion vers le haut, vers le haut, c'est negative
    // defiinition du couleur
    Color green = {20, 160, 133, 255}; // on essayes d'autres façons

    while (!WindowShouldClose()) {
        // 1. Gestion des evenements
        if (IsKeyDown(KEY_RIGHT)) charX+=charSpeed; // marche vers la droit
        else if (IsKeyDown(KEY_LEFT)) charX-=charSpeed; // marche vers la gauche

        // Jump trigger
        if (IsKeyPressed(KEY_SPACE) && !isJumping) { // enleve celui apres et, il vas sauter en l'air
            isJumping=true; // clui si rends sa vrai pur donc annule celui d'en haut
            velocityY=jumpStrength;
        }
        // 2. mise a jour du saut. il doit retourne au sol
        if (isJumping) {
            charY+=(int)velocityY;
            velocityY+=gravity;
            // verifie collision avec le sol
            if (charY>=groundY-charHeight) { // S'il arrive au sol, ça ne devrait pas le dépasser
                charY=groundY-charHeight;  // remets au sol
                isJumping=false; // on ta pas oublie
                velocityY=0; // et aussi
            }
        }
        // Garde charactere dans la fenetre horizontallement
        if (charX<0)
            charX=0;
        if (charX>window-charWidth)
            charX =window-charWidth;

        // 3. Dessin
        BeginDrawing();
        ClearBackground(green); // ou vert defini en haut
        // ligne du sol
        DrawLine(0, groundY, window, groundY, DARKGRAY);
        // rectangle du charactere
        DrawRectangle(charX, charY, charWidth, charHeight, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
