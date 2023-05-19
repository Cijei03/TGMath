#pragma once
#include <utility>
#include "../TGBasicTypes.hpp"
#include "vec2.hpp"

namespace TGMath
{
    namespace intern
    {
        template<typename T>
        class vec3
        {
        public:
            T x;
            T y;
            T z;
        public:
            /* ASSIGNMENT OPERATORS */
            TGM_NODISCARD vec3<T>& operator=(T v)
            {
                this->x = std::move(v);
                this->y = std::move(v);
                this->z = std::move(v);
                return *this;
            }
            /* BY SINGLE COMPONENTS CONSTRUCTORS */
            constexpr vec3(T x, T y, T z)
            {
                this->x = std::move(x);
                this->y = std::move(y);
                this->z = std::move(z);
            }
            constexpr vec3(T v)
            {
                this->x = std::move(v);
                this->y = std::move(v);
                this->z = std::move(v);
            }
            /* BY MULTI COMPONENTS CONSTRUCTORS */
            constexpr vec3(const vec2<T>& v, T z)
            {
                this->x = std::move(v.x);
                this->y = std::move(v.y);
                this->z = std::move(z);
            }
            constexpr vec3(T x, const vec2<T>& v)
            {
                this->x = std::move(x);
                this->y = std::move(v.x);
                this->z = std::move(v.y);
            }
            constexpr vec3() = default;
            ~vec3() = default;
        };
    }

    using f32vec3 = intern::vec3<TGf32>;
    using f64vec3 = intern::vec3<TGf64>;

    using i8vec3 = intern::vec3<TGi8>;
    using i16vec3 = intern::vec3<TGi16>;
    using i32vec3 = intern::vec3<TGi32>;
    using i64vec3 = intern::vec3<TGi64>;

    using ui8vec3 = intern::vec3<TGui8>;
    using ui16vec3 = intern::vec3<TGui16>;
    using ui32vec3 = intern::vec3<TGui32>;
    using ui64vec3 = intern::vec3<TGui64>;
}
/* CASTS */
template<typename T, typename U>
TGM_NODISCARD T TGVectorCast(TGMath::intern::vec3<U>& v)
{
    return T(v.x, v.y, v.z);
}

/* COMPARE OPERATORS */
template<typename T>
TGM_NODISCARD bool operator<(const TGMath::intern::vec3<T>& a, const TGMath::intern::vec3<T>& b)
{
    return (a.x < b.x && a.y < b.y && a.z < b.z);
}
template<typename T>
TGM_NODISCARD bool operator<=(const TGMath::intern::vec3<T>& a, const TGMath::intern::vec3<T>& b)
{
    return (a.x <= b.x && a.y <= b.y && a.z <= b.z);
}
template<typename T>
TGM_NODISCARD bool operator==(const TGMath::intern::vec3<T>& a, const TGMath::intern::vec3<T>& b)
{
    return (a.x == b.x && a.y == b.y && a.z == b.z);
}
template<typename T>
TGM_NODISCARD bool operator>=(const TGMath::intern::vec3<T>& a, const TGMath::intern::vec3<T>& b)
{
    return (a.x >= b.x && a.y >= b.y && a.z >= b.z);
}
template<typename T>
TGM_NODISCARD bool operator>(const TGMath::intern::vec3<T>& a, const TGMath::intern::vec3<T>& b)
{
    return (a.x > b.x && a.y > b.y && a.z > b.z);
}
/* ARITHMETHIC OPERATORS */
template<typename T>
TGM_NODISCARD TGMath::intern::vec3<T> operator+(const TGMath::intern::vec3<T>& a, const TGMath::intern::vec3<T>& b)
{
    return TGMath::intern::vec3<T>(a.x + b.x, a.y + b.y, a.z + b.z);
}
template<typename T>
TGM_NODISCARD TGMath::intern::vec3<T> operator-(const TGMath::intern::vec3<T>& a, const TGMath::intern::vec3<T>& b)
{
    return TGMath::intern::vec3<T>(a.x - b.x, a.y - b.y, a.z - b.z);
}
template<typename T>
TGM_NODISCARD TGMath::intern::vec3<T> operator*(const TGMath::intern::vec3<T>& a, const TGMath::intern::vec3<T>& b)
{
    return TGMath::intern::vec3<T>(a.x * b.x, a.y * b.y, a.z * b.z);
}
template<typename T>
TGM_NODISCARD TGMath::intern::vec3<T> operator/(const TGMath::intern::vec3<T>& a, const TGMath::intern::vec3<T>& b)
{
    return TGMath::intern::vec3<T>(a.x / b.x, a.y / b.y, a.z / b.z);
}
/* ARITHMETHIC OPERATORS WITH SINGLE VALUE */
template<typename T>
TGM_NODISCARD TGMath::intern::vec3<T> operator+(const TGMath::intern::vec3<T>& a, T b)
{
    return TGMath::intern::vec3<T>(a.x + b, a.y + b, a.z + b);
}
template<typename T>
TGM_NODISCARD TGMath::intern::vec3<T> operator-(const TGMath::intern::vec3<T>& a, T b)
{
    return TGMath::intern::vec3<T>(a.x - b, a.y - b, a.z - b);
}
template<typename T>
TGM_NODISCARD TGMath::intern::vec3<T> operator*(const TGMath::intern::vec3<T>& a, T b)
{
    return TGMath::intern::vec3<T>(a.x * b, a.y * b, a.z * b);
}
template<typename T>
TGM_NODISCARD TGMath::intern::vec3<T> operator/(const TGMath::intern::vec3<T>& a, T b)
{
    return TGMath::intern::vec3<T>(a.x / b, a.y / b, a.z / b);
}

namespace TGMath
{
    template<typename T>
    TGM_NODISCARD intern::vec3<T> absolute(const intern::vec3<T>& v)
    {
        return intern::vec3<T>(abs(v.x), abs(v.y), abs(v.z));
    }
    template<typename T>
    TGM_NODISCARD intern::vec3<T> normalize(const intern::vec3<T>& v)
    {
        return intern::vec3<T>(v / (abs(v.x) + abs(v.y) + abs(v.z)));
    }
    template<typename T>
    TGM_NODISCARD intern::vec3<T> cross(const intern::vec3<T>& a, const intern::vec3<T>& b)
    {
        return intern::vec3<T>
            (
                (a.y * b.z) - (a.z * b.y),
                (a.z * b.x) - (a.x * b.z),
                (a.x * b.y) - (a.y * b.x)
            );
    }
    template<typename T>
    TGM_NODISCARD T dot(const intern::vec3<T>& a, const intern::vec3<T>& b)
    {
        const intern::vec3<T> cache = a * b;
        return cache.x + cache.y + cache.z;
    }
    template<typename T>
    TGM_NODISCARD intern::vec3<T> distance(const intern::vec3<T>& a, const intern::vec3<T>& b)
    {
        return absolute<T>(a - b);
    }
}