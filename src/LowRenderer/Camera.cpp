#include "Camera.hpp"
#include "InputManager.hpp"
#include "TimeManager.hpp"
#include "math.h"
#include "Assertion.hpp"
#include "vector3D.hpp"

#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>

using namespace LowRenderer;
using namespace Core::Maths;

Camera::Camera(float _fov, float _width, float _height, float _near, float _far)
{
    aim = {0, 0, -1};
    pos = {0, 0, 0};
    rot = {0, 0, 0};
    Z   = {0, 1, 0};
    matPerspective = Maths::Mat4::CreatePerspectiveProjectionMatrix(_width, _height, _near, _far, _fov);
    matOrtho = Maths::Mat4::CreateOrthographicMatrix(_width, _height, _near, _far);
}

Camera::~Camera()
{
}

void Camera::SetLookAt(Maths::Vec3 _aim, Maths::Vec3 _pos, Maths::Vec3 _Z) // matrix use for the camera
{
    aim         = _aim;
    pos         = _pos;
    Z           = _Z;
}

bool Camera::FirstPersonMove(float direction, float distance)
{
    if (!firstPerson)
        return false;

    Maths::Vec3 aimPoint;
    aimPoint.x = sinf(yaw) * cosf(pitch);
    aimPoint.y = sinf(yaw) * sinf(pitch);
    aimPoint.z = -cosf(yaw);
    Maths::Vec3 mouvement = aimPoint.Normalize();

    if (direction == FORWARD)
    {
        pos.x += mouvement.x * distance;
        pos.z += mouvement.z * distance;
    }
    
    else if (direction == BACK)
    {    
        pos.x -= mouvement.x * distance;
        pos.z -= mouvement.z * distance;
    }

    else if (direction == RIGHT)
    {
        pos.x += (mouvement.x * cosf(PI / 2) - mouvement.z * sinf(PI / 2)) * distance;
        pos.z += (mouvement.x * sinf(PI / 2) + mouvement.z * cosf(PI / 2)) * distance;
    }
    else if (direction == LEFT)
    {
        pos.x -= (mouvement.x * cosf(PI / 2) - mouvement.z * sinf(PI / 2)) * distance;
        pos.z -= (mouvement.x * sinf(PI / 2) + mouvement.z * cosf(PI / 2)) * distance;
    }

    return true;

}

void Camera::Update()
{
    if (window == nullptr)
    {
        Debug::Assertion::Check(HIGH, true, "window == nullptr");
        return;
    }
    if (initialized)
    {
        UpdateRotation();
        UpdateTranslation();
    }
    else
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        initialized = true;
    }

    if (!firstPerson)
    {
        matCam = Maths::Mat4::CreateCameraMatrix(aim, pos, Z);
    }
    else
    {
        matCam =  Maths::Matrix::GetMatrixInverse(Maths::Matrix(Maths::Mat4::CreateTransformMatrix(rot, pos, {1.f, 1.f, 1.f})));
        //matCam = Maths::Mat4::CreateTransformMatrix(rot, pos * -(1.f), {1, 1, 1,});
    }

    glfwSetCursorPos(window, 800 / 2, 600 / 2);
}

void Camera::UpdateRotation()
{
    Tools::Time& timeManager = Tools::Time::Summon();

    double xPos, yPos;

    glfwGetCursorPos(window, &xPos, &yPos);

    float speed = /*timeManager.deltaTime * */  CAM_ROTATION_SPEED * MOUSE_SENSITIVITY;

    float yaw     = speed * ((800  / 2) - xPos);
    float pitch   = speed * ((600 / 2) - yPos);
    
    rot.x += pitch;
    rot.y += yaw;
    
    // limit vertical rotation

    float limit = PI / 2.f;

    if (rot.x > limit)
        rot.x = limit;
    else if (rot.x < -limit)
        rot.x = -limit;
}

void Camera::UpdateTranslation()
{
    InputManager& inputs = InputManager::Summon();
    Tools::Time& timeManager = Tools::Time::Summon();

    float speed = timeManager.DeltaTime() * CAM_TRANSLATION_SPEED;

    float strafe = 0.f, forward = 0.f, fly = 0.f;

    if (inputs.IsActionTriggered(Actions::Forward))
    {
        forward += -speed;
    }
    if (inputs.IsActionTriggered(Actions::Backwards))
    {
        forward += speed;
    }
    if (inputs.IsActionTriggered(Actions::Left))
    {
        strafe += -speed;
    }
    if (inputs.IsActionTriggered(Actions::Right))
    {
        strafe += speed;
    }
    if (inputs.IsActionTriggered(Actions::Up))
    {
        fly += speed;
    }
    if (inputs.IsActionTriggered(Actions::Down))
    {
        fly += -speed;
    }

    // change pos of camera
    double rotAngleY = rot.y;

    pos.x += forward *  sin(rotAngleY);
    pos.z += forward *  cos(rotAngleY);
    pos.x += strafe  *  cos(rotAngleY);
    pos.z += strafe  * -sin(rotAngleY);
    pos.y += fly;

}

Vec3 Camera::GetRaycast() const
{
    Vec3 rayCast;

    rayCast.x = -sin(rot.y);
    rayCast.z = -cos(rot.y);
    rayCast.y = tan(rot.x);
    
    return rayCast.Normalize();
}