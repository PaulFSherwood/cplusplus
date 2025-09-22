#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

// g++ globe.cpp -o globe -std=c++17 -lGL -lX11 -lpthread -lpng -lstdc++fs
class EarthGlobe : public olc::PixelGameEngine
{
public:
    EarthGlobe() { sAppName = "Spinning Earth"; }

    olc::Sprite* earthTex = nullptr;
    olc::Sprite* skyTex = nullptr;
    olc::Decal* skyDecal = nullptr;
    float angle = 0.0f; // rotation angle

    int starLayer = -1;
    int globeLayer = -1;

    bool OnUserCreate() override
    {
        // Load assets
        earthTex = new olc::Sprite("earth.png");
        skyTex   = new olc::Sprite("skymap.png");
        skyDecal = new olc::Decal(skyTex);

        // Create 2 extra layers above default layer 0
        starLayer  = CreateLayer();
        globeLayer = CreateLayer();

        EnableLayer(starLayer, true);
        EnableLayer(globeLayer, true);

        // Draw stars ONCE into starLayer
        SetDrawTarget(starLayer);
        Clear(olc::BLACK); // black background for empty space
        float sx = (float)ScreenWidth()  / (float)skyTex->width;
        float sy = (float)ScreenHeight() / (float)skyTex->height;
        DrawDecal({0,0}, skyDecal, {sx, sy});  // starfield
        SetDrawTarget(nullptr); // <- critical: back to default (layer 0)

        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        // Always clear layer 0 (default buffer) to black
        Clear(olc::BLACK);

        // Draw globe into globeLayer
        SetDrawTarget(globeLayer);
        Clear(olc::BLANK); // blank = transparent, so stars shine through

        int radius = std::min(ScreenWidth(), ScreenHeight()) / 3;
        olc::vi2d center(ScreenWidth()/2, ScreenHeight()/2);

        angle += fElapsedTime * 0.05f;
        float cosA = cos(angle);
        float sinA = sin(angle);

        for (int y=-radius; y<radius; y++)
        for (int x=-radius; x<radius; x++)
        {
            float nx = (float)x / radius;
            float ny = (float)y / radius;
            float r2 = nx*nx + ny*ny;

            if (r2 <= 1.0f)
            {
                float nz = sqrtf(1.0f - r2);
                float xr = cosA*nx + sinA*nz;
                float zr = -sinA*nx + cosA*nz;

                float lon = atan2(zr, xr);
                float lat = asinf(ny);

                int u = (int)((-lon + 3.14159f) / (2.0f * 3.14159f) * earthTex->width);
                int v = (int)((0.5f + lat / 3.14159f) * earthTex->height);

                if (u>=0 && u<earthTex->width && v>=0 && v<earthTex->height)
                    Draw(center.x+x, center.y+y, earthTex->GetPixel(u,v));
            }
        }

        SetDrawTarget(nullptr); // back to default
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
