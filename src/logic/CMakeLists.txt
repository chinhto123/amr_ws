cmake_minimum_required(VERSION 3.0.2)
project(logic)

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs geometry_msgs )

catkin_package()
include_directories(${catkin_INCLUDE_DIRS})

add_executable(logic logic.cpp )
target_link_libraries(logic ${catkin_LIBRARIES} )

install(TARGETS logic
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
  
  
