#ifndef _TRANSFORM_
#define _TRANSFORM_

#include "matrix.hpp"
#include "referential.hpp"
namespace Physics
{
    class Transform
    {
    public:
        Core::Maths::Referential ref;
        
        Core::Maths::Vec3 position {0,0,0};
        Core::Maths::Vec3 scale    {1,1,1};
        Core::Maths::Vec3 rotation {0,0,0};

        Core::Maths::Mat4 matrix;
        
        Transform();
        Transform(const Core::Maths::Vec3 &_position, const Core::Maths::Vec3 &_scale, const Core::Maths::Vec3 &_rotation);
        ~Transform();
        
        const Core::Maths::Vec3 &Position();
        const Core::Maths::Vec3 &Scale();
        const Core::Maths::Vec3 &Rotation();

        void setPosition(const Core::Maths::Vec3 &_position);
        void setScale(const Core::Maths::Vec3 &_scale);
        void setRotation(const Core::Maths::Vec3 &_rotation);

        void ResetMatrix();

        void setMatrix(const Core::Maths::Vec3 &_position, const Core::Maths::Vec3 &_scale, const Core::Maths::Vec3 &_rotation);
        const Core::Maths::Mat4 &getMatrix(); // use the element of transforamtion to create a TRS matrix

        friend std::ostream& operator<<(std::ostream& os, const Transform& transform)
        {
            os << transform.ref;
            os << transform.position;
            os << transform.scale;
            os << transform.rotation;

            return os;
        }

        friend std::istream& operator>>(std::istream& is, Transform& transform)
        {
            is >> transform.ref;
            is >> transform.position;
            is >> transform.scale;
            is >> transform.rotation;

            return is;
        }
    };
}

#endif