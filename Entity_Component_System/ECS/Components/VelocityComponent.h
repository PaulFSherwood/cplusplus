#pragma once

// VelocityComponent
// -----------------
// Stores movement state (inertia).
// This is what gives Sub-Terrania / Asteroids-style flight.
//
struct VelocityComponent
{
    float vx{0.0f};
    float vy{0.0f};
};

