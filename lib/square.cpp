#include "square.hpp"

namespace Aronda
{

Square::Square(const std::size_t index)
    : Utils::StrongType<std::size_t>(index)
{
}
}
