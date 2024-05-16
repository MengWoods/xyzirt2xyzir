## Add minimum required cmake version
cmake_minimum_required(VERSION 3.5)
project(xyzirt2xyzir)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unused-function -Wno-missing-field-initializers -Werror -Walloca -Wduplicated-cond -Wcast-align -Wlogical-op -fstrict-aliasing")
include_directories(SYSTEM "/usr/include/pcl-1.8")
set(MAKE_SHARED true CACHE BOOL "Build and use shared libraries")

## Find catkin
find_package(catkin REQUIRED)
## Include conan macros
if (EXISTS ${PROJECT_SOURCE_DIR}/conanbuildinfo.cmake)
  set(IGNORE_CONAN_PKGS "" CACHE STRING "These packages will be linked from current workspace instead of Conan cache")
  include(${PROJECT_SOURCE_DIR}/conanbuildinfo.cmake)
  conan_set_find_paths()
  foreach(ign_con_pkg ${IGNORE_CONAN_PKGS})
    message(STATUS "Ignoring Conan package: ${ign_con_pkg}")
    string(REPLACE "${ign_con_pkg}" "" CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}")
  endforeach(ign_con_pkg)
endif()

set(${PROJECT_NAME}_CATKIN_DEPS
    roscpp
    pcl_ros
    pcl_conversions
)

## Define settings for static build
if(NOT MAKE_SHARED)
  ## This is needed by find_package
  set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
  ## Link against static libs
  set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
  ## Produce static libs
  set(BUILD_SHARED_LIBS OFF)
endif()

find_package(catkin REQUIRED COMPONENTS
  ${${PROJECT_NAME}_CATKIN_DEPS}
)

find_package(PCL REQUIRED COMPONENTS common)
add_definitions(${PCL_DEFINITIONS})
link_directories(${PCL_LIBRARY_DIRS})

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS ${${PROJECT_NAME}_CATKIN_DEPS}
  DEPENDS
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
)

set(PROJECT_SOURCE
  src/xyzirt2xyzir.cpp
)

set(PROJECT_LIBS
  ${catkin_LIBRARIES}
  ${PCL_LIBRARIES}
)

# ## Declare a C++ library which will be linked to your project
if(MAKE_SHARED)
  add_library(${PROJECT_NAME} ${PROJECT_SOURCE})
else()
  add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCE})
endif()


add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(${PROJECT_NAME} ${PROJECT_LIBS} ${PCL_LIBRARIES})

# Node executables
add_executable(xyzirt2xyzir_node
 src/xyzirt2xyzir_node.cpp
 ${PROJECT_SOURCE}
)

add_dependencies(xyzirt2xyzir_node
 ${${PROJECT_NAME}_EXPORTED_TARGETS}
 ${catkin_EXPORTED_TARGETS}
)

target_link_libraries(xyzirt2xyzir_node
 ${PROJECT_NAME}
 ${PROJECT_LIBS}
)

install(TARGETS xyzirt2xyzir_node
        RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

## Mark executables and/or libraries for installation
install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

## Mark output header files for installation
install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

## Mark launch files for installation
install(DIRECTORY
  launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
