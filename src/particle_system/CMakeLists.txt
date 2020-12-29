cmake_minimum_required(VERSION 3.0.2)
project(particle_system)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

# for SDL
find_package(SDL2 REQUIRED)


catkin_package(
  INCLUDE_DIRS include
  LIBRARIES particle_system
  CATKIN_DEPENDS roscpp rospy std_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${SDL2_INCLUDE_DIRS}
)


add_executable(particle_system_node src/main.cpp src/FireExplosion.cpp src/Particle.cpp src/Swarm.cpp)
target_link_libraries(particle_system_node ${catkin_LIBRARIES} ${SDL2_LIBRARIES})

