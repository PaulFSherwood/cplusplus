#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class EarthGlobe : public olc::PixelGameEngine
{
public:
    EarthGlobe() { sAppName = "Spinning Earth"; }

    // Textures
    olc::Sprite* earthTex = nullptr;
    olc::Sprite* skyTex   = nullptr;

    // Decals
    olc::Decal* skyDecal   = nullptr;
    // olc::Sprite* globeSpr  = nullptr;
    // olc::Decal* globeDecal = nullptr;
    olc::Decal* earthDecal = nullptr;

    float angle = 0.0f; // rotation angle


    bool OnUserCreate() override
    {
        // Load assets
        earthTex   = new olc::Sprite("earth_small.png");
        earthDecal = new olc::Decal(earthTex); // <-- assign to member, not new local


        skyTex   = new olc::Sprite("skymap_small.png");
        skyDecal = new olc::Decal(skyTex);

        // Create an empty sprite for the globe, same size as screen
        // globeSpr  = new olc::Sprite(ScreenWidth(), ScreenHeight());
        // globeDecal = new olc::Decal(globeSpr);
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        // Clear screen
        Clear(olc::BLACK);

        // --- Draw starfield first ---
        float sx = (float)ScreenWidth()  / (float)skyTex->width;
        float sy = (float)ScreenHeight() / (float)skyTex->height;
        DrawDecal({0.0f,0.0f}, skyDecal, {sx, sy});

        int radius = std::min(ScreenWidth(), ScreenHeight()) / 3;
        olc::vi2d center(ScreenWidth()/2, ScreenHeight()/2);

        // for (int y = -radius; y < radius; y++)
        //     for (int x = -radius; x < radius; x++)
        //         globeSpr->SetPixel(center.x+x, center.y+y, olc::BLANK);


        angle += fElapsedTime * 0.05f;
        float cosA = cos(angle);
        float sinA = sin(angle);

        int step = 2;
        for (int y=-radius; y<radius; y+= step)
        {
            for (int x=-radius; x<radius; x+= step)
            {
                float nx = (float)x / radius;
                float ny = (float)y / radius;
                float r2 = nx*nx + ny*ny;

                if (r2 <= 1.0f)
                {
                    float nz = sqrtf(1.0f - r2);

                    // Rotate around Y axis
                    float xr = cosA*nx + sinA*nz;
                    float zr = -sinA*nx + cosA*nz;

                    // Spherical coords
                    float lon = atan2(zr, xr);
                    float lat = asinf(ny);

                    // Map to texture coords
                    int u = (int)((-lon + 3.14159f) / (2.0f * 3.14159f) * earthTex->width);
                    int v = (int)((0.5f + lat / 3.14159f) * earthTex->height);

                    if (u >= 0 && u < earthTex->width && v >= 0 && v < earthTex->height)
                    {
                        // Screen destination: one pixel at globe location
                        olc::vf2d destPos  = { (float)(center.x + x), (float)(center.y + y) };
                        olc::vf2d destSize = { 1.0f, 1.0f };

                        // Source region in texture: 1x1 pixel at (u,v)
                        olc::vf2d srcPos   = { (float)u, (float)v };
                        olc::vf2d srcSize  = { 1.0f, 1.0f };

                        // DrawPartialDecal(destPos, destSize, earthDecal, srcPos, srcSize, olc::WHITE);
                        DrawPartialDecal(destPos, {(float)step,(float)step}, earthDecal, srcPos, {1.0f,1.0f}, olc::WHITE);
                    }
                }
            }
        }

        // --- Blit globe as decal ---
        // DrawDecal({0,0}, globeDecal);

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
