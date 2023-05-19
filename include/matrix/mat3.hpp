#pragma once
#include <algorithm>
#include "../TGBasicTypes.hpp"
#include "../vector/vec3.hpp"
#include "../basicMath/basicMath.hpp"

namespace TGMath
{
    namespace intern
    {
        template <typename T>
        class mat3
        {
        private:
            vec3<T> data[3];
        public:
            constexpr mat3() = default;
            ~mat3() = default;

            /* CONSTRUCTORS */
            constexpr mat3(const vec3<T>& a, const vec3<T>& b, const vec3<T>& c)
            {
                this->data[0] = a;
                this->data[1] = b;
                this->data[2] = c;
            }
            mat3(T* existingDataPtr)
            {
                // First row.
                this->data[0].x = existingDataPtr[0];
                this->data[0].y = existingDataPtr[1];
                this->data[0].z = existingDataPtr[2];
                // Second row.
                this->data[1].x = existingDataPtr[3];
                this->data[1].y = existingDataPtr[4];
                this->data[1].z = existingDataPtr[5];
                // Third row.
                this->data[2].x = existingDataPtr[6];
                this->data[2].y = existingDataPtr[7];
                this->data[2].z = existingDataPtr[8];
            }
            void makeUnit()
            {
                this->data[0] = vec3<T>(1, 0, 0);
                this->data[1] = vec3<T>(0, 1, 0);
                this->data[2] = vec3<T>(0, 0, 1);
            }
            void scale(const vec3<T>& value)
            {
                mat3<T> cache(vec3<T>(1, 0, 0), vec3<T>(0, 1, 0), vec3<T>(0, 0, 1));
                cache.data[0].x = std::move(value.x);
                cache.data[1].y = std::move(value.y);
                cache.data[2].z = std::move(value.z);

                *this = cache * *this;
            }
            void scale(const T value)
            {
                mat3<T> cache(vec3<T>(1, 0, 0), vec3<T>(0, 1, 0), vec3<T>(0, 0, 1));
                cache.data[0].x = std::move(value);
                cache.data[1].y = std::move(value);
                cache.data[2].z = std::move(value);
                *this = cache * this;
            }
            void rotate(TGf32 angle, vec3<TGf32> perAxisMultiplier)
            {
                // Process input parameters.
                angle = TGMath::convertDigreesToRadians(angle);
                TGf32 preCompCos = cos(angle);
                TGf32 preCompSin = sin(angle);
                perAxisMultiplier = normalize(perAxisMultiplier);
                auto& X = perAxisMultiplier.x;
                auto& Y = perAxisMultiplier.y;
                auto& Z = perAxisMultiplier.z;

                // Compute.
                mat3<T> cache(vec3<T>(1, 0, 0), vec3<T>(0, 1, 0), vec3<T>(0, 0, 1));
                
                // First row.
                cache.data[0].x = preCompCos + (TGMath::sqr(X)) * (1.0f - preCompCos);
                cache.data[0].y = X * Y * (1.0f - preCompCos) - Z * preCompSin;
                cache.data[0].z = X * Z * (1.0f - preCompCos) + Y * preCompSin;

                // Second row.
                cache.data[1].x = Y * X * (1.0f - preCompCos) + Z * preCompSin;
                cache.data[1].y = preCompCos + TGMath::sqr(Y) * (1.0f - preCompCos);
                cache.data[1].z = Y * Z * (1.0f - preCompCos) - X * preCompSin;

                // Third row.
                cache.data[2].x = Z * X * (1.0f - preCompCos) - Y * preCompSin;
                cache.data[2].y = Z * Y * (1.0f - preCompCos) + X * preCompSin;
                cache.data[2].z = preCompCos + TGMath::sqr(Z) * (1.0f - preCompCos);

                *this = cache * *this;
            }
            void rotate(vec3<TGf32> angles)
            {
                mat3<T> axisX(vec3<T>(1, 0, 0), vec3<T>(0, 1, 0), vec3<T>(0, 0, 1));
                {
                    angles.x = TGMath::convertDigreesToRadians(angles.x);
                    TGf32 preCompSin = sin(angles.x);
                    TGf32 preCompCos = cos(angles.x);

                    axisX.data[1].y = preCompCos;
                    axisX.data[1].z = -preCompSin;
                    axisX.data[2].y = preCompSin;
                    axisX.data[2].z = preCompCos;
                }
                mat3<T> axisY(vec3<T>(1, 0, 0), vec3<T>(0, 1, 0), vec3<T>(0, 0, 1));
                {
                    angles.y = TGMath::convertDigreesToRadians(angles.y);
                    TGf32 preCompSin = sin(angles.y);
                    TGf32 preCompCos = cos(angles.y);

                    axisY.data[0].x = preCompCos;
                    axisY.data[0].z = preCompSin;
                    axisY.data[2].x = -preCompSin;
                    axisY.data[2].z = preCompCos;
                }

                mat3<T> axisZ(vec3<T>(1, 0, 0), vec3<T>(0, 1, 0), vec3<T>(0, 0, 1));
                {
                    angles.z = TGMath::convertDigreesToRadians(angles.z);
                    TGf32 preCompSin = sin(angles.z);
                    TGf32 preCompCos = cos(angles.z);

                    axisZ.data[0].x = preCompCos;
                    axisZ.data[0].y = -preCompSin;
                    axisZ.data[1].x = preCompSin;
                    axisZ.data[1].y = preCompCos;
                }

                *this = axisZ * axisY * axisX * *this;
            }
            void transpose()
            {
                std::swap(this->data[0].y, this->data[1].x);
                std::swap(this->data[2].x, this->data[0].z);
                std::swap(this->data[1].z, this->data[2].y);
                std::swap(this->data[2].y, this->data[1].z);
            }
            /* ARITHMETHIC WITH OTHER MATRICES */
            TGM_NODISCARD mat3<T> operator*(const mat3<T>& value)
            {
                return mat3<T>
                (
                    vec3<T>
                    (
                        this->data[0].x * value.data[0].x + this->data[0].y * value.data[1].x + this->data[0].z * value.data[2].x,
                        this->data[0].x * value.data[0].y + this->data[0].y * value.data[1].y + this->data[0].z * value.data[2].y,
                        this->data[0].x * value.data[0].z + this->data[0].y * value.data[1].z + this->data[0].z * value.data[2].z
                    ),
                    vec3<T>
                    (
                        this->data[1].x * value.data[0].x + this->data[1].y * value.data[1].x + this->data[1].z * value.data[2].x,
                        this->data[1].x * value.data[0].y + this->data[1].y * value.data[1].y + this->data[1].z * value.data[2].y,
                        this->data[1].x * value.data[0].z + this->data[1].y * value.data[1].z + this->data[1].z * value.data[2].z
                    ),
                    vec3<T>
                    (
                        this->data[2].x * value.data[0].x + this->data[2].y * value.data[1].x + this->data[2].z * value.data[2].x,
                        this->data[2].x * value.data[0].y + this->data[2].y * value.data[1].y + this->data[2].z * value.data[2].y,
                        this->data[2].x * value.data[0].z + this->data[2].y * value.data[1].z + this->data[2].z * value.data[2].z
                    )
                );
            }
            TGM_NODISCARD mat3<T> operator+(const mat3<T>& value)
            {
                return mat3<T>
                (
                    vec3<T>
                    (
                        this->data[0] + value.data[0]
                    ),
                    vec3<T>
                    (
                        this->data[1] + value.data[1]
                    ),
                    vec3<T>
                    (
                        this->data[2] + value.data[2]
                    )
                );
            }
            TGM_NODISCARD mat3<T> operator-(const mat3<T>& value)
            {
                return mat3<T>
                (
                    vec3<T>
                    (
                        this->data[0] - value.data[0]
                    ),
                    vec3<T>
                    (
                        this->data[1] - value.data[1]
                    ),
                    vec3<T>
                    (
                        this->data[2] - value.data[2]
                    )
                );
            }
            /* ARITHMETHIC WITH VECTOR */
            TGM_NODISCARD vec3<T> operator*(const vec3<T>& value)
            {
                return vec3<T>
                (
                    this->data[0].x * value.x + this->data[0].y * value.x + this->data[0].z * value.x,
                    this->data[1].x * value.y + this->data[1].y * value.y + this->data[1].z * value.y,
                    this->data[2].x * value.z + this->data[2].y * value.z + this->data[2].z * value.z
                );
            }
            static consteval mat3<T> unitMatrix()
            {
                return mat3<T>(vec3<T>(1, 0, 0), vec3<T>(0, 1, 0), vec3<T>(0, 0, 1));
            }
            TGM_NODISCARD T* get()
            {
                return &this->data[0].x;
            }
        };
    }
    using f32mat3 = intern::mat3<TGf32>;
    using f64mat3 = intern::mat3<TGf64>;

    using i8mat3 = intern::mat3<TGi8>;
    using i16mat3 = intern::mat3<TGi16>;
    using i32mat3 = intern::mat3<TGi32>;
    using i64mat3 = intern::mat3<TGi64>;

    using ui8mat3 = intern::mat3<TGui8>;
    using ui16mat3 = intern::mat3<TGui16>;
    using ui32mat3 = intern::mat3<TGui32>;
    using ui64mat3 = intern::mat3<TGui64>;
}