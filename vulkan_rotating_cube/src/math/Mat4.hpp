#pragma once

#include <array>
#include <cmath>

namespace cube::math {

// Column-major 4x4 matrix matching GLSL's default matrix layout.
// Access pattern: m[column * 4 + row].
struct Mat4 final {
    std::array<float, 16> m{};

    [[nodiscard]] static Mat4 identity() noexcept {
        Mat4 out{};
        out.m[0] = 1.0F;
        out.m[5] = 1.0F;
        out.m[10] = 1.0F;
        out.m[15] = 1.0F;
        return out;
    }

    [[nodiscard]] static Mat4 translation(float x, float y, float z) noexcept {
        Mat4 out = identity();
        out.m[12] = x;
        out.m[13] = y;
        out.m[14] = z;
        return out;
    }

    [[nodiscard]] static Mat4 rotationX(float radians) noexcept {
        Mat4 out = identity();
        const float c = std::cos(radians);
        const float s = std::sin(radians);
        out.m[5] = c;
        out.m[6] = s;
        out.m[9] = -s;
        out.m[10] = c;
        return out;
    }

    [[nodiscard]] static Mat4 rotationY(float radians) noexcept {
        Mat4 out = identity();
        const float c = std::cos(radians);
        const float s = std::sin(radians);
        out.m[0] = c;
        out.m[2] = -s;
        out.m[8] = s;
        out.m[10] = c;
        return out;
    }

    [[nodiscard]] static Mat4 perspective(
        float verticalFovRadians,
        float aspectRatio,
        float nearPlane,
        float farPlane) noexcept {
        const float tanHalfFov = std::tan(verticalFovRadians / 2.0F);

        Mat4 out{};
        out.m[0] = 1.0F / (aspectRatio * tanHalfFov);
        out.m[5] = -1.0F / tanHalfFov; // Vulkan clip space has inverted Y vs. OpenGL.
        out.m[10] = farPlane / (nearPlane - farPlane);
        out.m[11] = -1.0F;
        out.m[14] = -(farPlane * nearPlane) / (farPlane - nearPlane);
        return out;
    }
};

[[nodiscard]] inline Mat4 operator*(const Mat4& lhs, const Mat4& rhs) noexcept {
    Mat4 out{};

    for (int col = 0; col < 4; ++col) {
        for (int row = 0; row < 4; ++row) {
            float sum = 0.0F;
            for (int i = 0; i < 4; ++i) {
                sum += lhs.m[i * 4 + row] * rhs.m[col * 4 + i];
            }
            out.m[col * 4 + row] = sum;
        }
    }

    return out;
}

} // namespace cube::math
