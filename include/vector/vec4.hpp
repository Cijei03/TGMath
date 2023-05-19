#pragma once
#include <utility>
#include "../TGBasicTypes.hpp"
#include "vec2.hpp"
#include "vec3.hpp"

namespace TGMath
{
    namespace intern
    {
        template<typename T>
        class vec4
        {
        public:
            T x;
            T y;
            T z;
            T w;
        public:
            /* ASSIGNMENT OPERATORS */
            TGM_NODISCARD vec4<T>& operator=(T v)
            {
                this->x = std::move(v);
                this->y = std::move(v);
                this->z = std::move(v);
                this->w = std::move(v);
                return *this;
            }
            /* BY SINGLE COMPONENTS CONSTRUCTORS */
            constexpr vec4(T x, T y, T z, T w)
            {
                this->x = std::move(x);
                this->y = std::move(y);
                this->z = std::move(z);
                this->w = std::move(w);
            }
            constexpr vec4(T v)
            {
                this->x = std::move(v);
                this->y = std::move(v);
                this->z = std::move(v);
                this->w = std::move(v);
            }
            /* BY MULTI COMPONENTS CONSTRUCTORS */
            constexpr vec4(const vec2<T>& v, T z, T w)
            {
                this->x = std::move(v.x);
                this->y = std::move(v.y);
                this->z = std::move(z);
                this->w = std::move(w);
            }
            constexpr vec4(T x, const vec2<T>& v, T w)
            {
                this->x = std::move(x);
                this->y = std::move(v.x);
                this->z = std::move(v.y);
                this->w = std::move(w);
            }
            constexpr vec4(T x, T y, const vec2<T>& v)
            {
                this->x = std::move(x);
                this->y = std::move(y);
                this->z = std::move(v.x);
                this->w = std::move(v.y);
            }
            constexpr vec4(const vec2<T>& a, const vec2<T>& b)
            {
                this->x = std::move(a.x);
                this->y = std::move(a.y);
                this->z = std::move(b.x);
                this->w = std::move(b.y);
            }
            constexpr vec4(const vec3<T>& v, T w)
            {
                this->x = std::move(v.x);
                this->y = std::move(v.y);
                this->z = std::move(v.z);
                this->w = std::move(w);
            }
            constexpr vec4(T x, const vec3<T>& v)
            {
                this->x = std::move(x);
                this->y = std::move(v.x);
                this->z = std::move(v.y);
                this->w = std::move(v.z);
            }
            constexpr vec4() = default;
            ~vec4() = default;
        };
    }

    using f32vec4 = intern::vec4<TGf32>;
    using f64vec4 = intern::vec4<TGf64>;

    using i8vec4 = intern::vec4<TGi8>;
    using i16vec4 = intern::vec4<TGi16>;
    using i32vec4 = intern::vec4<TGi32>;
    using i64vec4 = intern::vec4<TGi64>;

    using ui8vec4 = intern::vec4<TGui8>;
    using ui16vec4 = intern::vec4<TGui16>;
    using ui32vec4 = intern::vec4<TGui32>;
    using ui64vec4 = intern::vec4<TGui64>;
}
/* CASTS */
template<typename T, typename U>
TGM_NODISCARD T TGVectorCast(TGMath::intern::vec4<U>& v)
{
    return T(v.x, v.y, v.z);
}

/* COMPARE OPERATORS */
template<typename T>
TGM_NODISCARD bool operator<(const TGMath::intern::vec4<T>& a, const TGMath::intern::vec4<T>& b)
{
    return (a.x < b.x && a.y < b.y && a.z < b.z && a.w < b.w);
}
template<typename T>
TGM_NODISCARD bool operator<=(const TGMath::intern::vec4<T>& a, const TGMath::intern::vec4<T>& b)
{
    return (a.x <= b.x && a.y <= b.y && a.z <= b.z && a.w <= b.w);
}
template<typename T>
TGM_NODISCARD bool operator==(const TGMath::intern::vec4<T>& a, const TGMath::intern::vec4<T>& b)
{
    return (a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w);
}
template<typename T>
TGM_NODISCARD bool operator>=(const TGMath::intern::vec4<T>& a, const TGMath::intern::vec4<T>& b)
{
    return (a.x >= b.x && a.y >= b.y && a.z >= b.z && a.w >= b.w);
}
template<typename T>
TGM_NODISCARD bool operator>(const TGMath::intern::vec4<T>& a, const TGMath::intern::vec4<T>& b)
{
    return (a.x > b.x && a.y > b.y && a.z > b.z && a.w > b.w);
}

/* ARITHMETHIC OPERATORS */
template<typename T>
TGM_NODISCARD TGMath::intern::vec4<T> operator+(const TGMath::intern::vec4<T>& a, const TGMath::intern::vec4<T>& b)
{
    return TGMath::intern::vec4<T>(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}
template<typename T>
TGM_NODISCARD TGMath::intern::vec4<T> operator-(const TGMath::intern::vec4<T>& a, const TGMath::intern::vec4<T>& b)
{
    return TGMath::intern::vec4<T>(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}
template<typename T>
TGM_NODISCARD TGMath::intern::vec4<T> operator*(const TGMath::intern::vec4<T>& a, const TGMath::intern::vec4<T>& b)
{
    return TGMath::intern::vec4<T>(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}
template<typename T>
TGM_NODISCARD TGMath::intern::vec4<T> operator/(const TGMath::intern::vec4<T>& a, const TGMath::intern::vec4<T>& b)
{
    return TGMath::intern::vec4<T>(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}

/* ARITHMETHIC OPERATORS WITH SINGLE VALUE */
template<typename T>
TGM_NODISCARD TGMath::intern::vec4<T> operator+(const TGMath::intern::vec4<T>& a, T b)
{
    return TGMath::intern::vec4<T>(a.x + b, a.y + b, a.z + b, a.w + b);
}
template<typename T>
TGM_NODISCARD TGMath::intern::vec4<T> operator-(const TGMath::intern::vec4<T>& a, T b)
{
    return TGMath::intern::vec4<T>(a.x - b, a.y - b, a.z - b, a.w - b);
}
template<typename T>
TGM_NODISCARD TGMath::intern::vec4<T> operator*(const TGMath::intern::vec4<T>& a, T b)
{
    return TGMath::intern::vec4<T>(a.x * b, a.y * b, a.z * b, a.w * b);
}
template<typename T>
TGM_NODISCARD TGMath::intern::vec4<T> operator/(const TGMath::intern::vec4<T>& a, T b)
{
    return TGMath::intern::vec4<T>(a.x / b, a.y / b, a.z / b, a.w / b);
}

namespace TGMath
{
    template<typename T>
    TGM_NODISCARD intern::vec4<T> absolute(const intern::vec4<T>& v)
    {
        return intern::vec4<T>(abs(v.x), abs(v.y), abs(v.z), abs(v.w));
    }
    template<typename T>
    TGM_NODISCARD intern::vec4<T> normalize(const intern::vec4<T>& v)
    {
        return intern::vec4<T>(v / (abs(v.x) + abs(v.y) + abs(v.z) + abs(v.w)));
    }
    template<typename T>
    TGM_NODISCARD T dot(const intern::vec4<T>& a, const intern::vec4<T>& b)
    {
        const intern::vec4<T> cache = a * b;
        return cache.x + cache.y + cache.z + cache.w;
    }
    template<typename T>
    TGM_NODISCARD intern::vec4<T> distance(const intern::vec4<T>& a, const intern::vec4<T>& b)
    {
        return absolute<T>(a - b);
    }
}