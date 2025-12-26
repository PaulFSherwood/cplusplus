#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include <cmath>
#include <chrono>
#include <thread>
#include <vector>

using namespace ftxui;

// ======================
// Math Types
// ======================
struct Vec2 {
    float x, y;
};

struct Vec3 {
    float x, y, z;
};

// ======================
// Math Functions
// ======================
Vec3 scaleUniform(Vec3 v, float s) {
    return {v.x * s, v.y * s, v.z * s };
}

Vec3 scaleNonUniform(Vec3 v, float sx, float sy, float sz) {
    return {v.x * sx, v.y * sy, v.z * sz };
}

Vec3 translate_z(Vec3 v, float dz) {
    return { v.x, v.y, v.z + dz };
}

Vec3 rotate_xz(Vec3 v, float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    return {
        v.x * c - v.z * s,
        v.y,
        v.x * s + v.z * c
    };
}

Vec3 rotate_yz(Vec3 v, float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    return {
        v.x,
        v.y * c - v.z * s,
        v.y * s + v.z * c
    };
}

Vec2 project(Vec3 v) {
    return { v.x / v.z, v.y / v.z };
}

Vec2 to_screen(Vec2 p, int w, int h) {
    return {
        (p.x + 1.f) * 0.5f * w,
        (1.f - (p.y + 1.f) * 0.5f) * h
    };
}

// ======================
// Drawing (Bresenham)
// ======================
void draw_line(Canvas& c, Vec2 a, Vec2 b) {
    int x0 = int(a.x);
    int y0 = int(a.y);
    int x1 = int(b.x);
    int y1 = int(b.y);

    int dx = std::abs(x1 - x0);
    int dy = -std::abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;

    while (true) {
        c.DrawPoint(x0, y0, Color::Green);

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y0 += sy;
        }
    }
}

// ======================
// Main
// ======================
int main() {
    constexpr int WIDTH = 80;
    constexpr int HEIGHT = 40;
    constexpr float FPS = 60.f;

    Screen scr = Screen::Create(
        Dimension::Fixed(WIDTH),
        Dimension::Fixed(HEIGHT)
    );

    std::vector<Vec3> vs = {
        { 0.25f,  0.25f,  0.25f},
        {-0.25f,  0.25f,  0.25f},
        {-0.25f, -0.25f,  0.25f},
        { 0.25f, -0.25f,  0.25f},

        { 0.25f,  0.25f, -0.25f},
        {-0.25f,  0.25f, -0.25f},
        {-0.25f, -0.25f, -0.25f},
        { 0.25f, -0.25f, -0.25f},
    };

    std::vector<std::vector<int>> fs = {
        {0, 1, 2, 3},   // Front square
        {4, 5, 6, 7},   // Back square
        {0, 4},
        {1, 5},
        {2, 6},
        {3, 7}
    };

    float angle = 0.f;
    float dz = 2.f;

    while (true) {
        Canvas cvs(WIDTH, HEIGHT);

        angle += M_PI / FPS;

        for (auto& f : fs) {
            for (size_t i = 0; i < f.size(); ++i) {
                Vec3 a = vs[f[i]];
                Vec3 b = vs[f[(i + 1) % f.size()]];

                // Scale
                Vec3 a0 = scaleUniform(a, 2.8f);
                Vec3 b0 = scaleUniform(b, 2.8f);

                // add a tilt to the cube
                Vec3 ta = rotate_yz(rotate_xz(a0, angle), angle * 0.7f);
                Vec3 tb = rotate_yz(rotate_xz(b0, angle), angle * 0.7f);

                // normal projection
                Vec2 pa = to_screen(
                    project(translate_z(ta, dz)),
                    WIDTH, HEIGHT
                );

                Vec2 pb = to_screen(
                    project(translate_z(tb, dz)),
                    WIDTH, HEIGHT
                );

                draw_line(cvs, pa, pb);
            }
        }

        scr.Clear();
        Render(scr, canvas(cvs));
        scr.Print();

        std::this_thread::sleep_for(
            std::chrono::milliseconds(int(1000 / FPS))
        );
    }
}

