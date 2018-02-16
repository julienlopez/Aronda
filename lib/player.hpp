#pragma once

#include "utils/strongtype.hpp"

#include <utility>

namespace Aronda
{

struct Player : private Utils::StrongType<std::size_t>
{
    explicit Player(const std::size_t index)
        : Utils::StrongType<std::size_t>(index)
    {
    }

    using Utils::StrongType<std::size_t>::operator std::size_t;
};
}
