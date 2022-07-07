#ifndef _VECTOR3D_
#define _VECTOR3D_

#include <cmath>
#include <iostream>

namespace Core
{
    namespace Maths
    {
        class Vec3
        {
        public:
            float x{0};
            float y{0};
            float z{0};
        
            Vec3    ();
            Vec3    (float _x, float _y, float _z);
            ~Vec3   () {};
        
            float   GetMagnitude    () const;
            float   GetSqrMagnitude () const;
            Vec3    &Normalize      ();
            Vec3    Normalize       () const;

            static float AngleBetweenVector(const Vec3 &vect1, const Vec3 &vect2);

            friend std::ostream& operator<<(std::ostream& os, const Vec3& vec)
            {
                os << vec.x << std::endl;
                os << vec.y << std::endl;
                os << vec.z << std::endl;
            
                return os;
            }

            friend std::istream& operator>>(std::istream& is, Vec3& vec)
            {
                is >> vec.x;
                is >> vec.y;
                is >> vec.z;
            
                return is;
            }
        };
    }
} // namespace Core



Core::Maths::Vec3   operator+   (const Core::Maths::Vec3 &, const Core::Maths::Vec3 &);
Core::Maths::Vec3   operator-   (const Core::Maths::Vec3 &, const Core::Maths::Vec3 &);
Core::Maths::Vec3   operator*   (const Core::Maths::Vec3 &, float);
float               operator*   (const Core::Maths::Vec3 &, const Core::Maths::Vec3 &);
bool                operator==  (const Core::Maths::Vec3 &, const Core::Maths::Vec3 &);

float               DotProduct  (const Core::Maths::Vec3& v1, const Core::Maths::Vec3& v2);
Core::Maths::Vec3   CrossProduct(const Core::Maths::Vec3 &v1, const Core::Maths::Vec3 &v2);


using namespace Core::Maths;

inline Vec3::Vec3(): x{0}, y{0}, z{0}{}

inline Vec3::Vec3(float _x, float _y, float _z) : x{_x}, y{_y}, z{_z} {}

inline float Vec3::GetMagnitude() const
{
    return sqrt((x * x) + (y * y) + (z * z));
}

inline float Vec3::GetSqrMagnitude() const
{
    return (x * x) + (y * y) + (z * z);
}

inline Vec3& Vec3::Normalize()
{
    float length = GetMagnitude();

    x /= length;
    y /= length;
    z /= length;

    return *this;
}

inline Vec3 Vec3::Normalize() const
{
    float length = GetMagnitude();

    float x = this->x / length;
    float y = this->y / length;
    float z = this->z / length;

    return {x,y,z};
}

inline float Vec3::AngleBetweenVector(const Vec3 &vect1, const Vec3 &vect2)
{
    float angle = acos((DotProduct(vect1, vect2)) / (vect1.GetMagnitude() * vect2.GetMagnitude()));
    return angle;
}

inline Vec3 operator+(const Vec3 &vect1, const Vec3 &vect2)
{
    Vec3 result;

    result.x = vect1.x + vect2.x;
    result.y = vect1.y + vect2.y;
    result.z = vect1.z + vect2.z;

    return result;
}

inline Vec3 operator-(const Vec3 &vect1, const Vec3 &vect2)
{
    Vec3 result;

    result.x = vect1.x - vect2.x;
    result.y = vect1.y - vect2.y;
    result.z = vect1.z - vect2.z;

    return result;
}

inline Vec3 operator*(const Vec3 &vect, float scale)
{
    Vec3 result;

    result.x = vect.x * scale;
    result.y = vect.y * scale;
    result.z = vect.z * scale;

    return result;
}

inline float operator*(const Vec3& v1, const Vec3& v2)
{
    return v1.x * v2.x + v1.y * v2.y  + v1.z * v2.z;
}

inline float DotProduct(const Vec3& v1, const Vec3& v2)
{
    return v1.x * v2.x + v1.y * v2.y  + v1.z * v2.z;
}

inline Vec3 CrossProduct(const Vec3& v1, const Vec3& v2)
{
    Vec3 result;

    result.x = (v1.y * v2.z) - (v1.z * v2.y);
    result.y = (v1.z * v2.x) - (v1.x * v2.z);
    result.z = (v1.x * v2.y) - (v1.y * v2.x);

    return result;
}

inline bool operator==(const Vec3& v1, const Vec3& v2)
{
    return ((v1 - v2).GetSqrMagnitude() == 0);
}

#endif