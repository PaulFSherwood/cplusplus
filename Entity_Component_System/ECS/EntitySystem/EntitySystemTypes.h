#pragma once
#include <cstdint>

// In a simple ECS, an entity is just an ID.
// No vtables. No inheritance.
using EntityID = std::uint32_t;

