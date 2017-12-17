/**
  * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
  * This Source Code Form is subject to the terms of the GNU GPL 3.0
  *
  * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
  */

#ifndef CG3_CGAL_TRIANGULATION_H
#define CG3_CGAL_TRIANGULATION_H

#include "2d/cgal_triangulation2d.h"

namespace cg3 {

namespace cgal {

namespace triangulation {

namespace internal {

static bool dummy;
static std::vector< std::vector<Pointd> > dummy_holes;

}


    std::vector<std::array<Pointd, 3> > triangulate(const Vec3 &normal, const std::vector<Pointd>& polygon, const std::vector<std::vector<Pointd> >& holes = internal::dummy_holes, bool& nonRegularPolygon = internal::dummy);

}

}

}

#endif // CG3_CGAL_TRIANGULATION_H
