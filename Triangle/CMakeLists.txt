cmake_minimum_required (VERSION 3.20)

project(Triangle)

#add_definitions('-g')

include_directories("/boot/system/develop/headers/agg2/")

add_executable(Triangle
	src/App.cpp
	src/MainWindow.cpp
	src/TriangleView.cpp
	src/SmoothSlider.cpp
)

set_property(TARGET Triangle PROPERTY CXX_STANDARD 11)

target_link_libraries(Triangle be agg translation)

add_custom_command(TARGET Triangle POST_BUILD
	COMMAND rc -o Resources.rsrc ${CMAKE_SOURCE_DIR}/Resources.rdef
	COMMAND xres -o ${CMAKE_BINARY_DIR}/Triangle Resources.rsrc
	COMMAND mimeset -f ${CMAKE_BINARY_DIR}/Triangle
	DEPENDS Triangle/Resources.rdef
)
