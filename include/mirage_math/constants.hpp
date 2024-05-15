#pragma once

#include <limits>

namespace Mirage::Math {

constexpr float FLOAT_MIN = std::numeric_limits<float>::min();
constexpr float EPSILON   = std::numeric_limits<float>::epsilon();
constexpr float UNIT      = 1.0F;
constexpr float PI        = 3.1415926535897932384626433832795F;

constexpr float SQRT_TWO          = 1.4142135623730950488016887242097F;
constexpr float ONE_OVER_SQRT_TWO = 0.70710678118654752440084436210485F;

} // namespace Mirage::Math
