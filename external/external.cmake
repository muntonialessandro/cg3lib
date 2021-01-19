find_package(Qt5
	COMPONENTS
	Core)

find_package(Eigen3)

if (TARGET Eigen3::Eigen)
	add_definitions(-DCG3_WITH_EIGEN)
	include_directories(${EIGEN3_INCLUDE_DIR})
endif()
