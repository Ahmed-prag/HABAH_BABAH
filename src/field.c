#include "raylib.h"
#include "field.h"

// Helper function to draw a net stretching back toward the wall boundary
static void DrawGoalNet(Vector2 backBottom, Vector2 backTop, Vector2 frontTop, Vector2 frontBottom)
{
    Color netColor = (Color){ 255, 255, 255, 110 }; // Use this foramt atleast
    float netThick = 1.5f;
    int numGridLines = 10; // Grid density, can add or reduce

    // 1. Horizontal / Perspective depth lines (front goal line to back wall)
    for (int i = 0; i <= numGridLines; i++)
    {
        float t = (float)i / (float)numGridLines;
        
        Vector2 start = { 
            frontBottom.x + t * (frontTop.x - frontBottom.x), 
            frontBottom.y + t * (frontTop.y - frontBottom.y) 
        };
        Vector2 end = { 
            backBottom.x + t * (backTop.x - backBottom.x), 
            backBottom.y + t * (backTop.y - backBottom.y) 
        };

        DrawLineEx(start, end, netThick, netColor);
    }

    // 2. Vertical / Cross lines (roof to ground level)
    for (int i = 0; i <= numGridLines; i++)
    {
        float t = (float)i / (float)numGridLines;

        Vector2 start = { 
            frontTop.x + t * (backTop.x - frontTop.x), 
            frontTop.y + t * (backTop.y - frontTop.y) 
        };
        Vector2 end = { 
            frontBottom.x + t * (backBottom.x - frontBottom.x), 
            frontBottom.y + t * (backBottom.y - frontBottom.y) 
        };

        DrawLineEx(start, end, netThick, netColor);
    }
}


void DrawField(int windowX, int windowY)
{

    // Field corners
    int leftBottomX = (0.015*windowX); //20
    int leftTopX = (0.11112*windowX); //150
    int rightTopX = windowX - leftTopX;
    int rightBottomX = windowX - leftBottomX;
    int bottomY = (0.9375*windowY);
    int topY = (0.875*windowY);

    //Boundaries
    float LW =0, RW =(float)windowX, GND=(topY+bottomY)/2; //Left wall, ground

    //penalty box
    int BLX=(0.02963*windowX), BRX=(0.12667*windowX), //left bottom(top) left(right) x
        TRX=0.19259*windowX, TLX=0.09259*windowX;
    int BY=0.9275*windowY, TY=0.8875*windowY; // bottom(top) y

    // Small goalie box
    int SBLX=(0.044445*windowX), SBRX=(0.114815*windowX),  // Small Right bottom(top) left(right) x
        STRX=0.151852*windowX, STLX=0.0740741*windowX;
    int SBY=0.9175*windowY, STY=0.89875*windowY; // small bottom(top) y
    // =========================
    // Field outline
    // =========================
    DrawLineEx((Vector2){leftBottomX, bottomY}, (Vector2){leftTopX, topY}, 4.0f, WHITE);
    DrawLineEx((Vector2){leftTopX, topY}, (Vector2){rightTopX, topY}, 4.0f, WHITE);
    DrawLineEx((Vector2){rightTopX, topY}, (Vector2){rightBottomX, bottomY}, 4.0f, WHITE);
    DrawLineEx((Vector2){rightBottomX, bottomY}, (Vector2){leftBottomX, bottomY}, 4.0f, WHITE);

    // ==================================================
    // LEFT PENALTY BOX (Goalkeeper Box)
    // ==================================================
    DrawLineEx((Vector2){BLX, BY}, (Vector2){BRX, BY}, 4.0f, WHITE);
    DrawLineEx((Vector2){BRX, BY}, (Vector2){TRX, TY}, 4.0f, WHITE);
    DrawLineEx((Vector2){TRX, TY}, (Vector2){TLX, TY}, 4.0f, WHITE);
    DrawLineEx((Vector2){TLX, TY}, (Vector2){BLX, BY}, 4.0f, WHITE);

    // Small goal area left
    DrawLineEx((Vector2){SBLX, SBY}, (Vector2){SBRX, SBY}, 4.0f, WHITE);
    DrawLineEx((Vector2){SBRX, SBY}, (Vector2){STRX, STY}, 4.0f, WHITE);
    DrawLineEx((Vector2){STRX, STY}, (Vector2){STLX, STY}, 4.0f, WHITE);
    DrawLineEx((Vector2){STLX, STY}, (Vector2){SBLX, SBY}, 4.0f, WHITE);

    // ==================================================
    // RIGHT PENALTY BOX (Mirror)
    // ==================================================
    DrawLineEx((Vector2){windowX - BLX, BY}, (Vector2){windowX - BRX, BY}, 4.0f, WHITE);
    DrawLineEx((Vector2){windowX - BRX, BY}, (Vector2){windowX - TRX, TY}, 4.0f, WHITE);
    DrawLineEx((Vector2){windowX - TRX, TY}, (Vector2){windowX - TLX, TY}, 4.0f, WHITE);
    DrawLineEx((Vector2){windowX - TLX, TY}, (Vector2){windowX - BLX, BY}, 4.0f, WHITE);

    // Small goal area right
    DrawLineEx((Vector2){windowX - SBLX, SBY}, (Vector2){windowX - SBRX, SBY}, 4.0f, WHITE);
    DrawLineEx((Vector2){windowX - SBRX, SBY}, (Vector2){windowX - STRX, STY}, 4.0f, WHITE);
    DrawLineEx((Vector2){windowX - STRX, STY}, (Vector2){windowX - STLX, STY}, 4.0f, WHITE);
    DrawLineEx((Vector2){windowX - STLX, STY}, (Vector2){windowX - SBLX, SBY}, 4.0f, WHITE);
    //=========================
    // HALF-WAY LINE
    //=========================
    DrawLineEx((Vector2){windowX / 2, topY}, (Vector2){windowX / 2, bottomY}, 4.0f, WHITE);
    
    // Centre circle (looks like an ellipse because of perspective)
    //DrawEllipseLines(windowX / 2, (topY+bottomY)/2, (0.05185*windowX), (0.015*windowY), WHITE);
    for (int i = 0; i < 4; i++) {   // 4‑pixel thickness
        DrawEllipseLines(windowX / 2, (topY+bottomY)/2, (0.05185*windowX) - i, (0.015*windowY)-i, WHITE);
    }

    //==================================================//
    //====== Goal Frames (Posts and Crossbars) =========//
    //==================================================//
    // cage droite
    DrawLineEx((Vector2){windowX-BLX, BY}, (Vector2){windowX-BLX, BY-205}, 10.0f, WHITE);
    DrawLineEx((Vector2){windowX-BLX, BY-200}, (Vector2){windowX-TLX, TY-197}, 10.0f, WHITE);
    DrawLineEx((Vector2){windowX-TLX, TY-200}, (Vector2){windowX-TLX, TY}, 10.0f, WHITE);

    // cage gauche
    DrawLineEx((Vector2){BLX, BY}, (Vector2){BLX, BY-205}, 10.0f, WHITE);
    DrawLineEx((Vector2){BLX, BY-200}, (Vector2){TLX, TY-197}, 10.0f, WHITE);
    DrawLineEx((Vector2){TLX, TY-200}, (Vector2){TLX, TY}, 10.0f, WHITE);

    // ==================================================
    // GOAL NETS (Anchored backwards to the wall boundaries)
    // ==================================================
    // Left Net: Front sits at TLX (goal line), Rear stretches back to LW (left wall)
    Vector2 L_frontTop    = { TLX, (TY - 200) }; // Top of the front crossbar
    Vector2 L_frontBottom = { TLX, TY }; // Bottom of front post on goal line
    Vector2 L_backTop     = { LW, (BY - 205) }; // Top rear corner at left wall
    Vector2 L_backBottom  = { LW, BY }; // Bottom rear corner at left wall

    DrawGoalNet(L_backBottom, L_backTop, L_frontTop, L_frontBottom);

    // Right Net: Front sits at windowX - TLX, Rear stretches back to RW (right wall)
    Vector2 R_frontTop    = { (windowX - TLX), (TY - 200) }; // Similar, but now right side
    Vector2 R_frontBottom = { (windowX - TLX), TY };
    Vector2 R_backTop     = { RW, (BY - 205) };
    Vector2 R_backBottom  = { RW, BY };

    DrawGoalNet(R_backBottom, R_backTop, R_frontTop, R_frontBottom);
}