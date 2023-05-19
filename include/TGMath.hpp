#pragma once
#if (!_WIN64 && _WIN32) || (__linux__ &&  !__x86_64__)
#error Library is not compatible with 32-bit systems!
#endif

#include "vector/vec2.hpp"
#include "vector/vec3.hpp"
#include "vector/vec4.hpp"

#include "matrix/mat2.hpp"
#include "matrix/mat3.hpp"
#include "matrix/mat4.hpp"

#include "basicMath/basicMath.hpp"

#include <type_traits>

static_assert(std::is_trivial_v<TGMath::f32vec2>, "NON TRIVIAL VECTOR 2");
static_assert(std::is_trivial_v<TGMath::f32vec3>, "NON TRIVIAL VECTOR 3");
static_assert(std::is_trivial_v<TGMath::f32vec4>, "NON TRIVIAL VECTOR 4");

static_assert(std::is_trivial_v<TGMath::f32mat2>, "NON TRIVIAL MATRIX 2");
static_assert(std::is_trivial_v<TGMath::f32mat3>, "NON TRIVIAL MATRIX 3");
static_assert(std::is_trivial_v<TGMath::f32mat4>, "NON TRIVIAL MATRIX 4");