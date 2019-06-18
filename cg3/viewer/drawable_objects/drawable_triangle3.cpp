/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "drawable_triangle3.h"
#include "../opengl_objects/opengl_objects3.h"

namespace cg3 {

DrawableTriangle3::DrawableTriangle3() :
    Triangle3d(),
    color(0,0,0),
    width(3),
    fill(false)
{
}

DrawableTriangle3::DrawableTriangle3(
        const Point3d &p1,
        const Point3d &p2,
        const Point3d &p3,
        Color c,
        unsigned int width,
        bool fill) :
    Triangle3d(p1, p2, p3),
    color(c),
    width(width),
    fill(fill)
{
}

void DrawableTriangle3::draw() const
{
    opengl::drawTriangle(_v1, _v2, _v3, color, width, fill);
}

Point3d DrawableTriangle3::sceneCenter() const
{
    return barycenter();
}

double DrawableTriangle3::sceneRadius() const
{
    return barycenter().dist(_v1);
}

} //namespace cg3