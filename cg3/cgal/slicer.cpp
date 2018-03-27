/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include "slicer.h"

namespace cg3 {

namespace cgal {

namespace internal {
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Surface_mesh<K::Point_3> Mesh;
typedef std::vector<K::Point_3> Polyline_type;
typedef std::list< Polyline_type > Polylines;
typedef CGAL::AABB_halfedge_graph_segment_primitive<Mesh> HGSP;
typedef CGAL::AABB_traits<K, HGSP>    AABB_traits;
typedef CGAL::AABB_tree<AABB_traits>  AABB_tree;
}
}

std::vector<std::vector<Pointd>> cgal::getPolylines(
        const std::string& inputOffFile,
        const Vec3& norm,
        double d)
{
    std::ifstream input(inputOffFile.c_str());
    SurfaceMesh mesh;
    if (!input || !(input >> mesh) || mesh.is_empty()) {
        std::cerr << "Not a valid off file." << std::endl;
        exit(1);
    }
    return getPolylines(mesh, norm, d);
}


std::vector<std::vector<Pointd>> cgal::getPolylines(const SurfaceMesh &mesh,
        const Vec3& norm,
        double d)
{

    // Slicer constructor from the mesh
    internal::Polylines polylines;
    internal::AABB_tree tree(edges(mesh).first, edges(mesh).second, mesh);
    CGAL::Polygon_mesh_slicer<SurfaceMesh, internal::K> slicer_aabb(mesh, tree);
    slicer_aabb(internal::K::Plane_3(norm.x(), norm.y(), norm.z(), d), std::back_inserter(polylines));
    std::vector< std::vector<Pointd> > result;
    for (std::vector<internal::K::Point_3> singlePolyline : polylines){
        std::vector<Pointd> v;
        for (internal::K::Point_3 point : singlePolyline){
            Pointd pres(point.x(), point.y(), point.z());
            v.push_back(pres);
        }
        result.push_back(v);
    }
    return result;
}

#ifdef CG3_DCEL_DEFINED
std::vector<std::vector<Pointd> > cgal::getPolylines(
        const Dcel &mesh,
        const Plane &p)
{
    return getPolylines(mesh, p.getNormal(), p.getD());
}

std::vector<std::vector<Pointd> > cgal::getPolylines(
        const Dcel &mesh,
        const Vec3 &norm,
        double d)
{
    SurfaceMesh m = cgal::getSurfaceMeshFromDcel(mesh);
    return getPolylines(m, norm, d);
}
#endif

}
