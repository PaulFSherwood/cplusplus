#pragma once

// GravityComponent
// ----------------
// Presence = entity is affected by gravity.
// Absence = no gravity.
//
struct GravityComponent
{
    float strength{120.0f}; // pixels/sec²
};

