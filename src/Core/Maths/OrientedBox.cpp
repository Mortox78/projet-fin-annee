#include <iostream>
#include <vector>

#include "OrientedBox.hpp"

using namespace Core::Maths;

OrientedBox::OrientedBox() {}
OrientedBox::OrientedBox(Referential _ref, float _extend) : ref{_ref}, extendX{_extend}, extendY{_extend}, extendZ{_extend} {}
OrientedBox::~OrientedBox() {}

std::vector<Vec3> OrientedBox::GetWorldPoints()
{
    std::vector<Vec3> points;

    points.push_back(ref.origin + ref.i * extendX + ref.j * extendY + ref.k * extendZ);
    points.push_back(ref.origin + ref.i * -extendX + ref.j * extendY + ref.k * extendZ);
    points.push_back(ref.origin + ref.i * extendX + ref.j * -extendY + ref.k * extendZ);
    points.push_back(ref.origin + ref.i * extendX + ref.j * extendY + ref.k * -extendZ);
    points.push_back(ref.origin + ref.i * -extendX + ref.j * -extendY + ref.k * extendZ);
    points.push_back(ref.origin + ref.i * extendX + ref.j * -extendY + ref.k * -extendZ);
    points.push_back(ref.origin + ref.i * -extendX + ref.j * extendY + ref.k * -extendZ);
    points.push_back(ref.origin + ref.i * -extendX + ref.j * -extendY + ref.k * -extendZ);

    return points;
}