cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#uncomment if you have defined messages
#rosbuild_genmsg()
#uncomment if you have defined services
#rosbuild_gensrv()

#common commands for building c++ executables and librariesl
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
rosbuild_add_library(libMoroTF src/libMoroTF.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
rosbuild_add_executable(statepublisher src/publish_state.cpp)
#rosbuild_add_executable(tf_broadcaster src/tf_broadcaster.cpp)
rosbuild_add_executable(assemblescans src/assemble_scans.cpp)
#rosbuild_add_executable(tf_listener src/tf_listener.cpp)
#rosbuild_add_executable(taurob_state_publisher src/tf_robotstate_broadcaster.cpp)
#target_link_libraries(tf_broadcaster ${catkin_LIBRARIES})
#target_link_libraries(tf_listener ${catkin_LIBRARIES})
#target_link_libraries(taurob_state_publisher ${catkin_LIBRARIES})
target_link_libraries(statepublisher ${catkin_LIBRARIES} libMoroTF)
target_link_libraries(assemblescans ${catkin_LIBRARIES})
#target_link_libraries(example ${PROJECT_NAME})
