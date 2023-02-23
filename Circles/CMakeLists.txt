cmake_minimum_required (VERSION 3.20)

project(Circles)

#add_definitions('-g')

include_directories("/boot/system/develop/headers/agg2/")

add_executable(Circles
	src/App.cpp
	src/MainWindow.cpp
	src/CirclesView.cpp
	src/SmoothSlider.cpp
	src/PngIo.cpp
)

set_property(TARGET Circles PROPERTY CXX_STANDARD 11)

target_link_libraries(Circles be agg png)

add_custom_command(TARGET Circles POST_BUILD
	COMMAND rc -o Resources.rsrc ${CMAKE_SOURCE_DIR}/Resources.rdef
	COMMAND xres -o ${CMAKE_BINARY_DIR}/Circles Resources.rsrc
	COMMAND mimeset -f ${CMAKE_BINARY_DIR}/Circles
	DEPENDS Circles/Resources.rdef
)
