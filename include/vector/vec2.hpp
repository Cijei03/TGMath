#pragma once
#include <utility>
#include "../TGBasicTypes.hpp"

namespace TGMath
{
    namespace intern
    {
        template<typename T>
        class vec2
        {
        public:
            T x;
            T y;
        public:
            /* ASSIGNMENT OPERATORS */
            TGM_NODISCARD vec2<T>& operator=(T v)
            {
                this->x = std::move(v);
                this->y = std::move(v);
                return *this;
            }
            /* BY SINGLE COMPONENTS CONSTRUCTORS */
            constexpr vec2(T x, T y)
            {
                this->x = std::move(x);
                this->y = std::move(y);
            }
            constexpr vec2(T v)
            {
                this->x = std::move(v);
                this->y = std::move(v);
            }
            constexpr vec2() = default;
            ~vec2() = default;
        };
    }

    using f32vec2 = intern::vec2<TGf32>;
    using f64vec2 = intern::vec2<TGf64>;

    using i8vec2 = intern::vec2<TGi8>;
    using i16vec2 = intern::vec2<TGi16>;
    using i32vec2 = intern::vec2<TGi32>;
    using i64vec2 = intern::vec2<TGi64>;

    using ui8vec2 = intern::vec2<TGui8>;
    using ui16vec2 = intern::vec2<TGui16>;
    using ui32vec2 = intern::vec2<TGui32>;
    using ui64vec2 = intern::vec2<TGui64>;
}

template<typename T, typename U>
TGM_NODISCARD T TGVectorCast(const TGMath::intern::vec2<U>& v)
{
    return T(v.x, v.y);
}


/* COMPARE OPERATORS */
template<typename T>
TGM_NODISCARD bool operator<(const TGMath::intern::vec2<T>& a, const TGMath::intern::vec2<T>& b)
{
    return (a.x < b.x && a.y < b.y);
}
template<typename T>
TGM_NODISCARD bool operator<=(const TGMath::intern::vec2<T>& a, const TGMath::intern::vec2<T>& b)
{
    return (a.x <= b.x && a.y <= b.y);
}
template<typename T>
TGM_NODISCARD bool operator==(const TGMath::intern::vec2<T>& a, const TGMath::intern::vec2<T>& b)
{
    return (a.x == b.x && a.y == b.y);
}
template<typename T>
TGM_NODISCARD bool operator>=(const TGMath::intern::vec2<T>& a, const TGMath::intern::vec2<T>& b)
{
    return (a.x >= b.x && a.y >= b.y);
}
template<typename T>
TGM_NODISCARD bool operator>(const TGMath::intern::vec2<T>& a, const TGMath::intern::vec2<T>& b)
{
    return (a.x > b.x && a.y > b.y);
}
/* ARITHMETHIC OPERATORS */
template<typename T>
TGM_NODISCARD TGMath::intern::vec2<T> operator+(const TGMath::intern::vec2<T>& a, const TGMath::intern::vec2<T>& b)
{
    return TGMath::intern::vec2<T>(a.x + b.x, a.y + b.y);
}
template<typename T>
TGM_NODISCARD TGMath::intern::vec2<T> operator-(const TGMath::intern::vec2<T>& a, const TGMath::intern::vec2<T>& b)
{
    return TGMath::intern::vec2<T>(a.x - b.x, a.y - b.y);
}
template<typename T>
TGM_NODISCARD TGMath::intern::vec2<T> operator*(const TGMath::intern::vec2<T>& a, const TGMath::intern::vec2<T>& b)
{
    return TGMath::intern::vec2<T>(a.x * b.x, a.y * b.y);
}
template<typename T>
TGM_NODISCARD TGMath::intern::vec2<T> operator/(const TGMath::intern::vec2<T>& a, const TGMath::intern::vec2<T>& b)
{
    return TGMath::intern::vec2<T>(a.x / b.x, a.y / b.y);
}
/* ARITHMETHIC OPERATORS WITH SINGLE VALUE */
template<typename T>
TGM_NODISCARD TGMath::intern::vec2<T> operator+(const TGMath::intern::vec2<T>& a, T b)
{
    return TGMath::intern::vec2<T>(a.x + b, a.y + b, a.z + b);
}
template<typename T>
TGM_NODISCARD TGMath::intern::vec2<T> operator-(const TGMath::intern::vec2<T>& a, T b)
{
    return TGMath::intern::vec2<T>(a.x - b, a.y - b, a.z - b);
}
template<typename T>
TGM_NODISCARD TGMath::intern::vec2<T> operator*(const TGMath::intern::vec2<T>& a, T b)
{
    return TGMath::intern::vec2<T>(a.x * b, a.y * b, a.z * b);
}
template<typename T>
TGM_NODISCARD TGMath::intern::vec2<T> operator/(const TGMath::intern::vec2<T>& a, T b)
{
    return TGMath::intern::vec2<T>(a.x / b, a.y / b, a.z / b);
}

namespace TGMath
{
    template<typename T>
    TGM_NODISCARD intern::vec2<T> absolute(const intern::vec2<T>& v)
    {
        return intern::vec2<T>(abs(v.x), abs(v.y));
    }
    template<typename T>
    TGM_NODISCARD intern::vec2<T> normalize(const intern::vec2<T>& v)
    {
        return intern::vec2<T>(v / (abs(v.x) + abs(v.y)));
    }
    template<typename T>
    TGM_NODISCARD T dot(const intern::vec2<T>& a, const intern::vec2<T>& b)
    {
        const intern::vec2<T> cache = a * b;
        return cache.x + cache.y;
    }
    template<typename T>
    TGM_NODISCARD intern::vec2<T> distance(const intern::vec2<T>& a, const intern::vec2<T>& b)
    {
        return absolute<T>(a - b);
    }
}