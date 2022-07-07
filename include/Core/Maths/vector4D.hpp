#ifndef _VECTOR4D_
#define _VECTOR4D_

#include "vector3D.hpp"

namespace Core
{
    namespace Maths
    {
        class Vec4
        {
        public:
            float x{0};
            float y{0};
            float z{0};
            float w{0};
        
            Vec4    (){};
            Vec4    (const Vec3 &, float _w = 1.0f);
            Vec4    (float _x, float _y, float _z, float _w);
            ~Vec4   (){};
        
            Vec4    Homogenize();
            float   GetMagnitude() const;
            void    Normalize();
        };
    }
} // namespace Core

using namespace Core::Maths;


inline Vec4::Vec4(const Vec3 &vect, float _w) : x {vect.x}, y{vect.y}, z{vect.z}, w{_w} {}

inline Vec4::Vec4 (float _x, float _y, float _z, float _w) : x{_x}, y{_y}, z{_z}, w{_w} {}


inline Vec4 Vec4::Homogenize()
{
    if (w != 0)
    {
        x /= w;
        y /= w;
        z /= w;
        w /= w;
    }
    
    return *this;
}

inline float Vec4::GetMagnitude() const
{
    Vec4 result;
    result.x = x;
    result.y = y;
    result.z = z;
    result.Homogenize();
    return sqrt((result.x * result.x) + (result.y * result.y) + (result.z * result.z));
}

inline void Vec4::Normalize()
{
    float length = GetMagnitude();

    x /= length;
    y /= length;
    z /= length;
}

inline Vec4 operator+(const Vec4 &vect1, const Vec4 &vect2)
{
    Vec4 result;

    result.x = vect1.x + vect2.x;
    result.y = vect1.y + vect2.y;
    result.z = vect1.z + vect2.z;
    result.w = vect1.w + vect2.w;

    return result;
}

inline Vec4 operator*(const Vec4 &vect, float scale)
{
    Vec4 result;

    result.x = vect.x * scale;
    result.y = vect.y * scale;
    result.z = vect.z * scale;
    result.w = vect.w * scale;

    return result;
}


#endif