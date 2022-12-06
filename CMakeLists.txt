# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required(VERSION 3.1)

set(PROJECT_NAME_STR NetworkGame)
project(${PROJECT_NAME_STR} C CXX)

if (CMAKE_BUILD_TYPE STREQUAL "")
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  # differentiation between debug and release builds.
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/dist)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/bin)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/assets)

#from
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# For older CMake versions 
#from - https://stackoverflow.com/questions/44478492/cmake-failed-to-run-msbuild-command-msbuild-exe
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Should work for versions 3.1 on!
# set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD 14)


if(CMAKE_COMPILER_IS_GNUCXX)
  # New CMakeOnly
  # add_definitions(-Wall -ansi -Wno-deprecated -pthread)
  # Note: -ansi reinforces C90, will override c++11
  set(GNU_EXTRA_STUFF "-Wall -Wno-deprecated -Wno-multichar -pthread")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GNU_EXTRA_STUFF}")
endif()

if(MSVC)
    #vc 2012 fix for vararg templates
    set(MSVC_COMPILER_DEFS "-D_VARIADIC_MAX=10")
endif()

#-------------------
# set common include folder for module
#-------------------

# message(STATUS "Source dir:" ${PROJECT_SOURCE_DIR})
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/strings ${PROJECT_SOURCE_DIR}/maths ${PROJECT_SOURCE_DIR}/networking ${PROJECT_SOURCE_DIR}/serialisation ${PROJECT_SOURCE_DIR}/replication ${PROJECT_SOURCE_DIR}/client ${PROJECT_SOURCE_DIR}/server)
set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)

#-------------------
# Configure Threads 
#-------------------
find_package(Threads REQUIRED)

if(Threads_FOUND)
	message(STATUS "Threads found is true ")
endif()


#if(Threads_FOUND)
#	message(STATUS "Threads found is true?")
#endif()


#-------------------
# Configure SDL2
#-------------------
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2-glj)
Message(STATUS ${CMAKE_MODULE_PATH})
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
#find_package(SDL2_gfx REQUIRED)

# Remove this if windows tests work. 
#message(STATUS "SDL Libraries seem to be bugged?:" ${SDL2_LIBRARIES})
#list(REMOVE_ITEM SDL2_LIBRARIES "1")
#message(STATUS "SDL Libraries hacked?:" ${SDL2_LIBRARIES})

#set(CMAKE_THREAD_LIBS_INIT ${CMAKE_THREAD_LIBS_INIT_STORED})
#message(STATUS "Reset THREAD_LIBS_INIT")

# Recurse into the "maths" etc subdirectories. This does not actually
# cause another cmake executable to run. The same process will walk through
# the project's entire directory structure.

add_subdirectory (src/maths)
add_subdirectory (src/strings)
add_subdirectory (src/networking)
add_subdirectory (src/serialisation)
add_subdirectory (src/replication)
add_subdirectory (src/engine)

add_subdirectory (src/client)
add_subdirectory (src/server)


add_subdirectory(src/gtest)

message(STATUS "DONE!")
