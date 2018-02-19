#include "forbiddenmove.hpp"

namespace Aronda
{

ForbiddenMove::ForbiddenMove(const char* message)
    : std::runtime_error(message)
{
}
}
