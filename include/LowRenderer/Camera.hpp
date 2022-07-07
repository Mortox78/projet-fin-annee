#ifndef _CAMERA_
#define _CAMERA_

#include "matrix.hpp"
#include "vector3D.hpp"

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>

#define ORTHO 180
#define FORWARD  1.f
#define BACK    -1.f
#define RIGHT    2.f
#define LEFT     -2.f

#define CAM_TRANSLATION_SPEED 0.5f
#define CAM_ROTATION_SPEED 0.01f
#define MOUSE_SENSITIVITY 0.1f

using namespace Core;

#include <iostream>

namespace LowRenderer
{
    class Camera
    {
    public:
        GLFWwindow* window = nullptr;

        Maths::Vec3 pos {0.f, 0.f, 1.f};
        Maths::Vec3 rot {0.f, 0.f, 0.f};
        Maths::Vec3 aim;
        Maths::Vec3 Z       {0.f, 1.f, 0.f};
        
        Maths::Mat4 matCam;
        Maths::Mat4 matPerspective;
        Maths::Mat4 matOrtho;

        float yaw {0.f};
        float pitch {0.f};
        bool  firstPerson {false};
        bool initialized = false;

        Camera(){};
        Camera(float fov, float _width, float _height, float _near, float _far);
        ~Camera();
    
        void SetLookAt(Maths::Vec3 _aim, Maths::Vec3 _pos, Maths::Vec3 _Z); // Set the element use to create the lookAt matrix of the camera
        void Update();
        void UpdateRotation();
        void UpdateTranslation();
        Maths::Vec3 GetRaycast() const;

        bool FirstPersonMove(float direction, float distance); // move on the XZ plane
    };
}

#endif