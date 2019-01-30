#pragma once

#include "utils/strongtype.hpp"

#include <utility>

namespace Aronda
{

struct Player : private Utils::StrongType<std::size_t>
{
    constexpr explicit Player(const std::size_t index)
        : Utils::StrongType<std::size_t>(index)
    {
    }

    using Utils::StrongType<std::size_t>::operator std::size_t;

    // constexpr Player black{0};
    // static constexpr Player white{1};
};

constexpr Player black{0};
constexpr Player white{1};

} // namespace Aronda
