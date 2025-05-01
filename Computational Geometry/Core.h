#pragma once

#include <cmath>

#define TOLERANCE 0.0000001

enum class RELATIVE_POSITION{
    LEFT, RIGHT, BEHIND, BEYOND, BETWEEN, ORIGIN, DESTINATION
};

static bool is_equal_1D(double x, double y){return std::fabs(x-y) < TOLERANCE;}