#include "raylib.h"
#include "field.h"

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
    float LW =0, RW =windowX, GND=(topY+bottomY)/2; //Left wall, ground

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

    // cage droite
    DrawLineEx((Vector2){windowX-BLX, BY}, (Vector2){windowX-BLX, BY-205}, 10.0f, WHITE);
    DrawLineEx((Vector2){windowX-BLX, BY-200}, (Vector2){windowX-TLX, TY-197}, 10.0f, WHITE);
    DrawLineEx((Vector2){windowX-TLX, TY-200}, (Vector2){windowX-TLX, TY}, 10.0f, WHITE);

    // cage gauche
    DrawLineEx((Vector2){BLX, BY}, (Vector2){BLX, BY-205}, 10.0f, WHITE);
    DrawLineEx((Vector2){BLX, BY-200}, (Vector2){TLX, TY-197}, 10.0f, WHITE);
    DrawLineEx((Vector2){TLX, TY-200}, (Vector2){TLX, TY}, 10.0f, WHITE);

}