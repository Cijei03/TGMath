#pragma once
#include <algorithm>
#include "../TGBasicTypes.hpp"
#include "../vector/vec2.hpp"
#include "../basicMath/basicMath.hpp"

namespace TGMath
{
    namespace intern
    {
        template <typename T>
        class mat2
        {
        private:
            vec2<T> data[2];
        public:
            constexpr mat2() = default;
            ~mat2() = default;

            /* CONSTRUCTORS */
            constexpr mat2(const vec2<T>& a, const vec2<T>& b)
            {
                this->data[0] = a;
                this->data[1] = b;
            }
            mat2(T* existingDataPtr)
            {
                this->data[0].x = existingDataPtr[0];
                this->data[0].y = existingDataPtr[1];
                this->data[1].x = existingDataPtr[2];
                this->data[1].y = existingDataPtr[3];
            }
            void makeUnit()
            {
                this->data[0] = vec2<T>(1, 0);
                this->data[1] = vec2<T>(0, 1);
            }
            void scale(const vec2<T>& value)
            {
                mat2<T> cache(vec2<T>(1, 0), vec2<T>(0, 1));
                cache.data[0].x = std::move(value.x);
                cache.data[1].y = std::move(value.y);
                *this = cache * *this;
            }
            void scale(const T value)
            {
                mat2<T> cache(vec2<T>(1, 0), vec2<T>(0, 1));
                cache.data[0].x *= std::move(value);
                cache.data[1].y *= std::move(value);
                *this = cache * *this;
            }
            void rotate(TGf32 angle) 
            {
                angle = convertDigreesToRadians(angle);
                mat2<T> cache(vec2<T>(cos(angle), -sin(angle)), vec2<T>(sin(angle), cos(angle)));
                *this = cache * *this;
            }
            void transpose()
            {
                std::swap(this->data[0].y, this->data[1].x);
            }
            /* ARITHMETHIC WITH OTHER MATRICES */
            TGM_NODISCARD mat2<T> operator*(const mat2<T>& value)
            {
                return mat2<T>
                (
                    vec2<T>
                    (
                        this->data[0].x * value.data[0].x + this->data[0].y * value.data[1].x,
                        this->data[0].x * value.data[0].y + this->data[0].y * value.data[1].y
                    ),
                    vec2<T>
                    (
                        this->data[1].x * value.data[0].x + this->data[1].y * value.data[1].x,
                        this->data[1].x * value.data[0].y + this->data[1].y * value.data[1].y
                    )
                );
            }
            TGM_NODISCARD mat2<T> operator+(const mat2<T>& value)
            {
                return mat2<T>
                (
                    vec2<T>
                    (
                        this->data[0] + value.data[0]
                    ),
                    vec2<T>
                    (
                        this->data[1] + value.data[1]
                    )
                );
            }
            TGM_NODISCARD mat2<T> operator-(const mat2<T>& value)
            {
                return mat2<T>
                (
                    vec2<T>
                    (
                        this->data[0] - value.data[0]
                    ),
                    vec2<T>
                    (
                        this->data[1] - value.data[1]
                    )
                );
            }
            /* ARITHMETHIC WITH VECTOR */
            TGM_NODISCARD vec2<T> operator*(const vec2<T>& a)
            {
                return vec2<T>
                (
                    this->data[0].x * a.x + this->data[0].y * a.x,
                    this->data[1].x * a.x + this->data[1].y * a.y
                );
            }
            static consteval mat2<T> unitMatrix()
            {
                return mat2<T>(vec2<T>(1, 0), vec2<T>(0, 1));
            }
            TGM_NODISCARD T* get()
            {
                return &this->data[0].x;
            }
        };
    }    
    using f32mat2 = intern::mat2<TGf32>;
    using f64mat2 = intern::mat2<TGf64>;

    using i8mat2 = intern::mat2<TGi8>;
    using i16mat2 = intern::mat2<TGi16>;
    using i32mat2 = intern::mat2<TGi32>;
    using i64mat2 = intern::mat2<TGi64>;

    using ui8mat2 = intern::mat2<TGui8>;
    using ui16mat2 = intern::mat2<TGui16>;
    using ui32mat2 = intern::mat2<TGui32>;
    using ui64mat2 = intern::mat2<TGui64>;
}