#pragma once

#include <stdexcept>

namespace Aronda
{

class ForbiddenMove : public std::runtime_error
{
public:
    ForbiddenMove(const char* message);

    virtual ~ForbiddenMove() = default;
};
}
