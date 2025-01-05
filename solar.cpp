#include <iostream>
#include <raylib.h>
#include <vector>
#include <string>
#include <cmath>

using std::cout;
using std::cin;
using std::string;
using std::vector;

struct Planet 
{
    float orbitRadius{0.0};
    float orbitSpeed{0.0};
    float angle{0.0};
    float size{0.0};
    Color color;

    void Update()
    {
        // Update planet angle position in orbit
        angle += orbitSpeed;
        if (angle > 2 * PI) angle -= 2 * PI;
    }
    
    // Draw planet at current position
    void Draw(Vector2 sunPosition, float zoom) const {
        Vector2 planetPosition = {
            sunPosition.x + orbitRadius * cos(angle) * zoom,
            sunPosition.y + orbitRadius * sin(angle) * zoom
        };
        DrawCircleV(planetPosition, size * zoom, color);
    }
};

int main()
{
    // Window init
    const int screenWidth{1200};
    const int screenHeight{900};
    int targetFPS{60};

    InitWindow(screenWidth, screenHeight, "Solar System Simulation");
    SetTargetFPS(60);

    Vector2 sunPosition = {screenWidth / 2.0f, screenHeight / 2.0f};
    float sunRadius{50.0f};
    // Zoom factor
    float zoom{1.0f};

    vector<Planet> planets = {
        {100.0f, 0.02f, 0.0f, 10.0f, RED},    // Planet 1
        {150.0f, 0.015f, 1.0f, 15.0f, BLUE},   // Planet 2
        {200.0f, 0.01f, 2.0f, 20.0f, BROWN},  // Planet 3
        {250.0f, 0.005f, 3.0f, 25.0f, ORANGE} // Planet 4
    };

    while (!WindowShouldClose())
    {
        //Zoom
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            zoom += 0.01f;
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            zoom -= 0.01f;
            if (zoom < 0.1f) zoom = 0.1f;
        }

        // Update planets
        for (auto& planet : planets)
        {
            planet.Update();
        }

        BeginDrawing();
        ClearBackground(BLACK);

        // Draw the sun
        DrawCircleV(sunPosition, sunRadius * zoom, YELLOW);

        // Draw the planets
        for (const auto& planet : planets) {
            planet.Draw(sunPosition, zoom);
        }

        // Display zoom level
        DrawText(TextFormat("Zoom: %.2fx", zoom), 10, 10, 20, WHITE);
        //draw FPS 
        DrawText(TextFormat("TARGET FPS: %i", targetFPS), GetScreenWidth() - 220, 10, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

