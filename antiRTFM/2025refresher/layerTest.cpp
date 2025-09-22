#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class LayerExample : public olc::PixelGameEngine
{
public:
    LayerExample() { sAppName = "Layer Example"; }

    int backLayer = 0;   // default
    int frontLayer = -1; // will create

    bool OnUserCreate() override
    {
        // Make layer 0 fully transparent
        SetDrawTarget((uint8_t)0);  // default layer


        Clear(olc::BLANK);

        // Background layer (blue)
        int backLayer = CreateLayer();
        EnableLayer(backLayer, true);
        SetDrawTarget(backLayer);
        Clear(olc::DARK_BLUE);

        // Foreground layer (bright green block + text)
        int frontLayer = CreateLayer();
        EnableLayer(frontLayer, true);
        SetDrawTarget(frontLayer);
        Clear(olc::BLANK);
        FillRect(50, 50, 200, 100, olc::GREEN); // giant block
        DrawString(60, 90, "Front Layer", olc::BLACK);

        // Reset back to default
        SetDrawTarget(nullptr);

        return true;
    }


    bool OnUserUpdate(float fElapsedTime) override
    {
        return true; // static
    }
};

int main()
{
    LayerExample demo;
    if (demo.Construct(400, 300, 2, 2))
        demo.Start();
    return 0;
}
