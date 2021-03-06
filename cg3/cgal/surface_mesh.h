/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#ifndef CG3_CGAL_SURFACEMESH_H
#define CG3_CGAL_SURFACEMESH_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>

namespace cg3 {

class Dcel;

class SimpleEigenMesh;

namespace cgal {

/**
 * @ingroup cg3cgal
 * @brief The SurfaceMesh class
 */
typedef CGAL::Surface_mesh<CGAL::Exact_predicates_inexact_constructions_kernel::Point_3> SurfaceMesh;

Dcel dcelFromSurfaceMesh(const SurfaceMesh& poly);
SurfaceMesh surfaceMeshFromDcel(const Dcel& d);

} //namespace cg3::cgal
} //namespace cg3

#ifndef CG3_STATIC
#define CG3_CGAL_SURFACEMESH_CPP "surface_mesh.cpp"
#include CG3_CGAL_SURFACEMESH_CPP
#undef CG3_CGAL_SURFACEMESH_CPP
#endif //CG3_STATIC

#endif // CG3_CGAL_SURFACEMESH_H
