#pragma once

// TransformComponent
// ------------------
// Pure data: position + rotation.
// No logic. No SDL. No behavior.
//
// In ECS:
// - Systems READ and WRITE this
// - Components NEVER do work themselves
//
struct TransformComponent
{
    float x{400.0f};   // screen-space position
    float y{300.0f};
    float rotation{0.0f}; // radians
};

