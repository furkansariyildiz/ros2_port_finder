cmake_minimum_required(VERSION 3.5)
project(ros2_port_finder)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)


include_directories(include/ros2_port_finder) # to tell CMake to add the directory as -I to the compilation command line

set(HEADER_FILES include/ros2_port_finder/ros2_port_finder.hpp) # you can use just the file you're using but this is mostly used for multiple header files

add_library(ros2_port_finder_lib src/ros2_port_finder.cpp ${HEADER_FILES}) 



# this line to export the targets, in our case it's a library!
ament_export_targets(ros2_port_finder_lib HAS_LIBRARY_TARGET)

# install the include/the_library directory to the install/include/the_library
install(
  DIRECTORY include/ros2_port_finder
  DESTINATION include
)


install(
  TARGETS ros2_port_finder_lib
  EXPORT ros2_port_finder_lib
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

ament_package()