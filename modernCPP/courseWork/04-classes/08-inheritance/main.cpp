#include <iostream>

class IRenderer {
    public:
        // This is a pure virtual function
        virtual void Draw() = 0;
        virtual void Update() = 0; 
        virtual void DrawOptimized() = 0;
};

class OpenGL : public IRenderer {
    public:
        void Draw() override {
            std::cout << "Using OpenGL::Draw\n";
        }
        void Update() override {
        }
        void DrawOptimized() override {
        }
};
class Vulkan : public IRenderer {
    public:
        void Draw() override {
            std::cout << "Using Vulkan::Draw\n";
        }
        void Update() override {
        }
        void DrawOptimized() override {
        }
};


int main() {

    IRenderer *myRenderer = new OpenGL;
    // IRenderer *myRenderer = new Vulkan;
    myRenderer->Update();
    myRenderer->Draw();

    return 0;
}
