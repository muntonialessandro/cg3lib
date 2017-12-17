/**
  * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
  * This Source Code Form is subject to the terms of the GNU GPL 3.0
  *
  * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
  */

#include "remove_unreferenced_vertices.h"

#include "internal/eigenmesh_libigl_algorithms.h"

namespace cg3 {

namespace libigl {

inline void removeUnreferencedVertices(SimpleEigenMesh &input, Eigen::Matrix<int, Eigen::Dynamic, 1> &I) {
    internal::EigenMeshLibIglAlgorithms::removeUnreferencedVertices(input, I);
}

inline void removeUnreferencedVertices(SimpleEigenMesh &input) {
    Eigen::VectorXi I;
    internal::EigenMeshLibIglAlgorithms::removeUnreferencedVertices(input, I);
}

}

}
