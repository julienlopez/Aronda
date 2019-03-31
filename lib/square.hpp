#pragma once

#include "utils/strongtype.hpp"

#include <utility>

namespace Aronda
{

struct Square : private Utils::StrongType<std::size_t>
{
    explicit Square(const std::size_t index);

    using Utils::StrongType<std::size_t>::operator std::size_t;
};
}
