#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#

CONFIG += c++11

DEFINES += CG3_QMAKE

CG3_STATIC {
    message(cg3 static)
    DEFINES += CG3_STATIC
}
else {
    CG3_VIEWER_STATIC {
        message("cg3 header only, viewer static")
    }
    else {
        message(cg3 header only)
    }
}

CG3_ALL {
	CONFIG += CG3_CORE CG3_CGAL CG3_CINOLIB CG3_LIBIGL CG3_VCGLIB CG3_VORO++ CG3_VIEWER
}

CG3_CORE {
    include (cg3/core.pri)
}

CG3_CGAL {
    include (cg3/cgal.pri)
}

CG3_CINOLIB {
     include (cg3/cinolib.pri)
}

CG3_LIBIGL {
    include (cg3/libigl.pri)
}

CG3_VCGLIB {
    include (cg3/vcglib.pri)
}

CG3_VORO++ {
    include (cg3/voro++.pri)
}

qt {
    CG3_VIEWER {
        include (cg3/viewer.pri)
    }
}

CG3_DEVELOPMENT {
    include (cg3/development.pri)
}

CG3_DEPRECATED {
    include (cg3/deprecated.pri)
}

DISTFILES += \
    $$PWD/LICENSE \
    $$PWD/README.md \
    $$PWD/TODO.md

INCLUDEPATH += $$PWD
