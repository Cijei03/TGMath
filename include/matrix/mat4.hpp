#pragma once
#include <algorithm>
#include <type_traits>
#include "../TGBasicTypes.hpp"
#include "../vector/vec4.hpp"
#include "../basicMath/basicMath.hpp"

namespace TGMath
{
    namespace intern
    {
        template<typename T>
        class mat4
        {
        private:
            vec4<T> data[4];
        public:
            constexpr mat4() = default;
            ~mat4() = default;

            /* CONSTRUCTORS */
            constexpr mat4(const vec4<T>& a, const vec4<T>& b, const vec4<T>& c, const vec4<T>& d)
            {
                this->data[0] = a;
                this->data[1] = b;
                this->data[2] = c;
                this->data[3] = d;
            }
            mat4(T* existingDataPtr)
            {
                // First row.
                this->data[0].x = existingDataPtr[0];
                this->data[0].y = existingDataPtr[1];
                this->data[0].z = existingDataPtr[2];
                this->data[0].w = existingDataPtr[3];
                // Second row.
                this->data[1].x = existingDataPtr[4];
                this->data[1].y = existingDataPtr[5];
                this->data[1].z = existingDataPtr[6];
                this->data[1].w = existingDataPtr[7];
                // Third row.
                this->data[2].x = existingDataPtr[8];
                this->data[2].y = existingDataPtr[9];
                this->data[2].z = existingDataPtr[10];
                this->data[2].w = existingDataPtr[11];
                // Forth row.
                this->data[3].x = existingDataPtr[12];
                this->data[3].y = existingDataPtr[13];
                this->data[3].z = existingDataPtr[14];
                this->data[3].w = existingDataPtr[15];
            }
            void makeUnit()
            {
                this->data[0] = vec4<T>(1, 0, 0, 0);
                this->data[1] = vec4<T>(0, 1, 0, 0);
                this->data[2] = vec4<T>(0, 0, 1, 0);
                this->data[3] = vec4<T>(0, 0, 0, 1);
            }
            void scale(const vec4<T>& value)
            {
                mat4<T> cache(vec4<T>(1, 0, 0, 0), vec4<T>(0, 1, 0, 0), vec4<T>(0, 0, 1, 0), vec4<T>(0, 0, 0, 1));
                cache.data[0].x = std::move(value.x);
                cache.data[1].y = std::move(value.y);
                cache.data[2].z = std::move(value.z);
                cache.data[3].w = std::move(value.w);

                *this = cache * *this;
            }
            void scale(const T value)
            {
                mat4<T> cache(vec4<T>(1, 0, 0, 0), vec4<T>(0, 1, 0, 0), vec4<T>(0, 0, 1, 0), vec4<T>(0, 0, 0, 1));
                cache.data[0].x = std::move(value.x);
                cache.data[1].y = std::move(value.y);
                cache.data[2].z = std::move(value.z);
                cache.data[3].w = std::move(value.w);

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
                mat4<T> cache(vec4<T>(1, 0, 0, 0), vec4<T>(0, 1, 0, 0), vec4<T>(0, 0, 1, 0), vec4<T>(0, 0, 0, 1));

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
                mat4<T> axisX(vec4<T>(1, 0, 0, 0), vec4<T>(0, 1, 0, 0), vec4<T>(0, 0, 1, 0), vec4<T>(0, 0, 0, 1));
                {
                    angles.x = TGMath::convertDigreesToRadians(angles.x);
                    TGf32 preCompSin = sin(angles.x);
                    TGf32 preCompCos = cos(angles.x);

                    axisX.data[1].y = preCompCos;
                    axisX.data[1].z = -preCompSin;
                    axisX.data[2].y = preCompSin;
                    axisX.data[2].z = preCompCos;
                }
                mat4<T> axisY(vec4<T>(1, 0, 0, 0), vec4<T>(0, 1, 0, 0), vec4<T>(0, 0, 1, 0), vec4<T>(0, 0, 0, 1));
                {
                    angles.y = TGMath::convertDigreesToRadians(angles.y);
                    TGf32 preCompSin = sin(angles.y);
                    TGf32 preCompCos = cos(angles.y);

                    axisY.data[0].x = preCompCos;
                    axisY.data[0].z = preCompSin;
                    axisY.data[2].x = -preCompSin;
                    axisY.data[2].z = preCompCos;
                }
                mat4<T> axisZ(vec4<T>(1, 0, 0, 0), vec4<T>(0, 1, 0, 0), vec4<T>(0, 0, 1, 0), vec4<T>(0, 0, 0, 1));
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
            void translate(const vec3<T>& value)
            {
                mat4<T> cache(vec4<T>(1, 0, 0, value.x), vec4<T>(0, 1, 0, value.y), vec4<T>(0, 0, 1, value.z), vec4<T>(0, 0, 0, 1));
                *this = cache * *this;
            }
            void transpose()
            {
                std::swap(this->data[0].y, this->data[1].x);
                std::swap(this->data[0].z, this->data[2].x);
                std::swap(this->data[0].w, this->data[3].x);
                std::swap(this->data[1].z, this->data[2].y);
                std::swap(this->data[1].w, this->data[3].y);
                std::swap(this->data[2].w, this->data[3].z);
                std::swap(this->data[3].z, this->data[2].w);
            }
            void makePerspective(const T FOV, const vec2<T>& screenDimensions, const T zNear, const T zFar) requires(std::is_floating_point_v<T>)
            {
                const T aspectRatio = screenDimensions.x / screenDimensions.y;
                const T tangens = tan(TGMath::convertDigreesToRadians(FOV) * 0.5f);
                const T zRange = zNear - zFar;

                this->data[0] = vec4<T>(1.0f / (aspectRatio * tangens), 0, 0, 0);
                this->data[1] = vec4<T>(0, 1.0f / tangens, 0, 0);
                this->data[2] = vec4<T>(0, 0, (-zNear - zFar) / zRange, (2.0f * zNear * zFar) / zRange);
                this->data[3] = vec4<T>(0, 0, 1.0f, 0);
            }
            void makeOrthogonal(const vec2<T>& frustumDimensions, const T zNear, const T zFar)
            {
                const T zRange = zFar - zNear;

                this->data[0] = f32vec4(1.0f / frustumDimensions.x, 0, 0, 0);
                this->data[1] = f32vec4(0, 1.0f / frustumDimensions.y, 0, 0);
                this->data[2] = f32vec4(0, 0, -(2.0f / zRange), (zFar + zNear) / zRange);
                this->data[3] = f32vec4(0, 0, 0, 1.0f);
            }
            void makeOrthogonal(const T leftEdge, const T rightEdge, const T bottomEdge, const T topEdge, const T zNear, const T zFar)
            {
                const T zRange = zFar - zNear;

                this->data[0] = f32vec4(1.0f / (rightEdge - leftEdge), 0, 0, 0);
                this->data[1] = f32vec4(0, 1.0f / (topEdge - bottomEdge), 0, 0);
                this->data[2] = f32vec4(0, 0, -(2.0f / zRange), (zFar + zNear) / zRange);
                this->data[3] = f32vec4(0, 0, 0, 1.0f);
            }
            void makeLookAt(const vec3<T>& eye, const vec3<T>& target, const vec3<T>& up)
            {
                const vec3<T> cameraForward = normalize(eye - target);
                const vec3<T> cameraRight = normalize(cross(up, cameraForward));
                const vec3<T> cameraUp = normalize(cross(cameraForward, cameraRight));

                this->data[0] = vec4<T>(cameraRight, 0);
                this->data[1] = vec4<T>(cameraUp, 0);
                this->data[2] = vec4<T>(cameraForward, 0);
                this->data[3] = vec4<T>(vec3<T>(0.0f), 1.0f);

                this->translate(vec3<T>(-eye.x, -eye.y, -eye.z));
            }
            /* ARITHMETHIC WITH OTHER MATRICES */
            TGM_NODISCARD mat4<T> operator*(const mat4<T>& value)
            {
                return mat4<T>
                    (
                        vec4<T>
                        (
                            this->data[0].x * value.data[0].x + this->data[0].y * value.data[1].x + this->data[0].z * value.data[2].x + this->data[0].w * value.data[3].x,
                            this->data[0].x * value.data[0].y + this->data[0].y * value.data[1].y + this->data[0].z * value.data[2].y + this->data[0].w * value.data[3].y,
                            this->data[0].x * value.data[0].z + this->data[0].y * value.data[1].z + this->data[0].z * value.data[2].z + this->data[0].w * value.data[3].z,
                            this->data[0].x * value.data[0].w + this->data[0].y * value.data[1].w + this->data[0].z * value.data[2].w + this->data[0].w * value.data[3].w
                        ),
                        vec4<T>
                        (
                            this->data[1].x * value.data[0].x + this->data[1].y * value.data[1].x + this->data[1].z * value.data[2].x + this->data[1].w * value.data[3].x,
                            this->data[1].x * value.data[0].y + this->data[1].y * value.data[1].y + this->data[1].z * value.data[2].y + this->data[1].w * value.data[3].y,
                            this->data[1].x * value.data[0].z + this->data[1].y * value.data[1].z + this->data[1].z * value.data[2].z + this->data[1].w * value.data[3].z,
                            this->data[1].x * value.data[0].w + this->data[1].y * value.data[1].w + this->data[1].z * value.data[2].w + this->data[1].w * value.data[3].w
                        ),
                        vec4<T>
                        (
                            this->data[2].x * value.data[0].x + this->data[2].y * value.data[1].x + this->data[2].z * value.data[2].x + this->data[2].w * value.data[3].x,
                            this->data[2].x * value.data[0].y + this->data[2].y * value.data[1].y + this->data[2].z * value.data[2].y + this->data[2].w * value.data[3].y,
                            this->data[2].x * value.data[0].z + this->data[2].y * value.data[1].z + this->data[2].z * value.data[2].z + this->data[2].w * value.data[3].z,
                            this->data[2].x * value.data[0].w + this->data[2].y * value.data[1].w + this->data[2].z * value.data[2].w + this->data[2].w * value.data[3].w
                        ),
                        vec4<T>
                        (
                            this->data[3].x * value.data[0].x + this->data[3].y * value.data[1].x + this->data[3].z * value.data[2].x + this->data[3].w * value.data[3].x,
                            this->data[3].x * value.data[0].y + this->data[3].y * value.data[1].y + this->data[3].z * value.data[2].y + this->data[3].w * value.data[3].y,
                            this->data[3].x * value.data[0].z + this->data[3].y * value.data[1].z + this->data[3].z * value.data[2].z + this->data[3].w * value.data[3].z,
                            this->data[3].x * value.data[0].w + this->data[3].y * value.data[1].w + this->data[3].z * value.data[2].w + this->data[3].w * value.data[3].w
                        )
                    );
            }
            TGM_NODISCARD mat4<T> operator+(const mat4<T>& value)
            {
                return mat4<T>
                    (
                        vec4<T>
                        (
                            this->data[0] + value.data[0]
                        ),
                        vec4<T>
                        (
                            this->data[1] + value.data[1]
                        ),
                        vec4<T>
                        (
                            this->data[2] + value.data[2]
                        ),
                        vec4<T>
                        (
                            this->data[3] + value.data[3]
                        )
                    );
            }
            TGM_NODISCARD mat4<T> operator-(const mat4<T>& value)
            {
                return mat4<T>
                    (
                        vec4<T>
                        (
                            this->data[0] - value.data[0]
                        ),
                        vec4<T>
                        (
                            this->data[1] - value.data[1]
                        ),
                        vec4<T>
                        (
                            this->data[2] - value.data[2]
                        ),
                        vec4<T>
                        (
                            this->data[3] - value.data[3]
                        )
                    );
            }
            /* ARITHMETHIC WITH VECTOR */
            TGM_NODISCARD vec4<T> operator*(const vec4<T>& value)
            {
                return vec4<T>
                    (
                        this->data[0].x * value.x + this->data[0].y * value.x + this->data[0].z * value.x + this->data[0].w * value.x,
                        this->data[1].x * value.y + this->data[1].y * value.y + this->data[1].z * value.y + this->data[1].w * value.y,
                        this->data[2].x * value.z + this->data[2].y * value.z + this->data[2].z * value.z + this->data[2].w * value.z,
                        this->data[3].x * value.w + this->data[3].y * value.w + this->data[3].z * value.w + this->data[3].w * value.w
                    );
            }
            static consteval mat4<T> unitMatrix()
            {
                return mat4<T>(vec4<T>(1, 0, 0, 0), vec4<T>(0, 1, 0, 0), vec4<T>(0, 0, 1, 0), vec4<T>(0, 0, 0, 1));
            }
            TGM_NODISCARD T* get()
            {
                return &this->data[0].x;
            }

        };
    }
    using f32mat4 = intern::mat4<TGf32>;
    using f64mat4 = intern::mat4<TGf64>;

    using i8mat4 = intern::mat4<TGi8>;
    using i16mat4 = intern::mat4<TGi16>;
    using i32mat4 = intern::mat4<TGi32>;
    using i64mat4 = intern::mat4<TGi64>;

    using ui8mat4 = intern::mat4<TGui8>;
    using ui16mat4 = intern::mat4<TGui16>;
    using ui32mat4 = intern::mat4<TGui32>;
    using ui64mat4 = intern::mat4<TGui64>;
}