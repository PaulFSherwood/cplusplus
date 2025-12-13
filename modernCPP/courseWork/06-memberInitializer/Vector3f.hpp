#pragma once
#define VECTOR3F_HPP
class Vector3f {
    public:

        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        // Constructor
        Vector3f() = default;
        Vector3f(float inX, float inY, float inZ);
};

