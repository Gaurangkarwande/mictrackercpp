cmake_minimum_required(VERSION 3.19)
project(mictrackercpp)
set(CMAKE_CXX_STANDARD 17)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.45.0 COMPONENTS filesystem)
find_package( OpenCV REQUIRED )
find_package(ITK REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories( ${OpenCV_INCLUDE_DIRS} )
include( ${ITK_USE_FILE} )

find_package(VTK COMPONENTS
        vtkCommonColor
        vtkCommonCore
        vtkIOImage
        vtkInteractionImage
        vtkInteractionStyle
        vtkRenderingContextOpenGL2
        vtkRenderingCore
        vtkRenderingFreeType
        vtkRenderingGL2PSOpenGL2
        vtkRenderingOpenGL2
        QUIET
        )

if (NOT VTK_FOUND)
    message("Skipping mictrackercpp: ${VTK_NOT_FOUND_MESSAGE}")
    return ()
endif()
message (STATUS "VTK_VERSION: ${VTK_VERSION}")
if (VTK_VERSION VERSION_LESS "8.90.0")
    # old system
    include(${VTK_USE_FILE})
    add_executable(mictrackercpp main.cpp import_data.cpp import_data.h)
    target_link_libraries( mictrackercpp ${OpenCV_LIBS} ${Boost_LIBRARIES} ${ITK_LIBRARIES} ${VTK_LIBRARIES})
else ()
    # include all components
    add_executable(mictrackercpp main.cpp import_data.cpp import_data.h)
    target_link_libraries( mictrackercpp ${OpenCV_LIBS} ${Boost_LIBRARIES} ${ITK_LIBRARIES} ${VTK_LIBRARIES})
    # vtk_module_autoinit is needed
    vtk_module_autoinit(
            TARGETS mictrackercpp
            MODULES ${VTK_LIBRARIES}
    )
endif ()

