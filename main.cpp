#include <iostream>
#include <raylib.h>
#include <random>

using namespace std;

void DrawCircleOutline(float centerX, float centerY, float radius, int thickness, Color color)
{
    for (int i = 0; i < thickness; i++)
    {
        DrawCircleLines(centerX, centerY, radius + i, color);
    }
}


int main () {

    const int screenWidth = 1000;
    const int screenHeight = 600;
    double pi_value = 0;
    float total = 0;
    double in_value = 0;
    double out_value = 0;
    float radius = screenHeight/2;
    
    float ball_x = screenHeight/2;
    float ball_y = screenHeight/2;

    // Seed for random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dis(0.0, 600.0);

    InitWindow(screenWidth, screenHeight, "PI Estimation");
    SetTargetFPS(60);

    DrawRectangle(0, 0, radius*2, screenHeight, Color{255, 255, 255, 255});

    while (WindowShouldClose() == false){
        BeginDrawing();
        // ClearBackground(BLACK);

        DrawRectangle(screenHeight, 0, screenWidth - screenHeight, screenHeight, Color{215, 215, 215, 255});
        
        DrawRectangleLinesEx(Rectangle {0, 0, screenHeight, screenHeight}, 2, Color{94, 94, 94, 255});     
        DrawCircleOutline(ball_x,ball_y,radius - 3, 3, Color{94, 94, 94, 255});

        DrawText(TextFormat("MONTE CARLO"), screenHeight + 20, 20, 30, BLACK);
        DrawText(TextFormat("PI ESTIMATION"), screenHeight + 20, 60, 40, BLACK);

        DrawText(TextFormat("# of points: %0.f", total), screenHeight + 20, 200, 30, BLACK);
        
        DrawText(TextFormat("# inside circle: %0.f", in_value), screenHeight + 20, 250, 30, BLACK);

        DrawText(TextFormat("# outside circle: %0.f", out_value), screenHeight + 20, 300, 30, BLACK);
        
        DrawText(TextFormat("Apx pi value"), screenHeight + (screenWidth - screenHeight)/4, 400, 30, BLACK);

        pi_value = 4 * (in_value/total);

        DrawText(TextFormat("%.5f", pi_value), screenHeight + (screenWidth - screenHeight)/4, 450, 50, BLACK);

        float randomValue1 = dis(gen);
        float randomValue2 = dis(gen);
        
        if(CheckCollisionPointCircle(Vector2 {randomValue1, randomValue2}, Vector2 {ball_x, ball_y}, radius)) {
            DrawCircle(randomValue1, randomValue2, 2, Color{255, 81, 81, 255});
            in_value++;
            total++;
        } else {
            DrawCircle(randomValue1, randomValue2, 2, Color{51, 51, 255, 255});
            out_value++;
            total++;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}