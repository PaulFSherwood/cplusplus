#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class EarthGlobe : public olc::PixelGameEngine
{
public:
    EarthGlobe() { sAppName = "Spinning Earth"; }

    olc::Sprite* earthTex = nullptr;
    float angle = 0.0f; // rotation angle

    bool OnUserCreate() override
    {
        // Load texture (must be in same folder as exe)
        earthTex = new olc::Sprite("earth.png");
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        Clear(olc::BLACK);

        int radius = std::min(ScreenWidth(), ScreenHeight()) / 3;
        olc::vi2d center(ScreenWidth() / 2, ScreenHeight() / 2);

        angle += fElapsedTime * 0.05f; // rotate slowly

        // Render globe with simple sphere mapping
        for (int y = -radius; y < radius; y++)
        {
            for (int x = -radius; x < radius; x++)
            {
                float nx = (float)x / radius;
                float ny = (float)y / radius;
                float r2 = nx*nx + ny*ny;

                if (r2 <= 1.0f) // inside circle
                {
                    float nz = sqrtf(1.0f - r2);

                    // Rotate around Y axis
                    float xr = cos(angle)*nx + sin(angle)*nz;
                    float zr = -sin(angle)*nx + cos(angle)*nz;

                    // Convert to lon/lat
                    float lon = atan2(zr, xr);
                    float lat = asinf(ny);

                    // Map to texture coords
                    int u = (int)((-lon + 3.14159f) / (2.0f * 3.14159f) * earthTex->width);
                    int v = (int)((0.5f + lat / 3.14159f) * earthTex->height);

                    // Clamp
                    if (u >= 0 && u < earthTex->width && v >= 0 && v < earthTex->height)
                    {
                        Draw(center.x + x, center.y + y, earthTex->GetPixel(u, v));
                    }
                }
            }
        }

        return true;
    }
};

int main()
{
    EarthGlobe demo;
    if (demo.Construct(800, 600, 1, 1))
        demo.Start();
    return 0;
}
