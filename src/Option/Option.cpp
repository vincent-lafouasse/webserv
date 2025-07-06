#include "Option.hpp"

namespace {
const char* badOptionAccessMessage = "Attempt to unwrap None value";
}

BadOptionAccessException::BadOptionAccessException()
    : std::runtime_error(badOptionAccessMessage) {}
