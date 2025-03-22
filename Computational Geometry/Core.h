#pragma once

#include <cmath>

#define TOLERANCE 0.0000001

static bool is_equal_1D(double x, double y){return std::fabs(x-y) < TOLERANCE;}