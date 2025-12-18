#include "API.hpp"

API::API() {}
API::~API() {}

// Static functions can only use static member variables.
int API::GetMajorVersion() {
   // std::cout << this << std::endl;  // would cause an error as this is unavailable to static member functions.
   return MAJOR; //  + m_local;
}

// Definitions
int API::MAJOR = 7;
