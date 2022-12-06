#-------------------
# Google Test
#-------------------
# Updated based on https://google.github.io/googletest/quickstart-cmake.html
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)

  # On Windows make sure you don't try and use pthreads 
  # Updated to new syntax with help https://www.fatalerrors.org/a/cmake-and-gtest-download-gtest-automatically-and-build-test-driven-environment.html
  if(WIN32)
	set(gtest_disable_pthreads ON CACHE BOOL "" FORCE)
	set(CMAKE_USE_WIN32_THREADS_INIT 1)
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  endif()

  # add the targets: gtest,gtest_main,gmock,gmock_main
  message(STATUS "GoogleTest source dir: ${googletest_SOURCE_DIR}")
  message(STATUS "GoogleTest binary dir: ${googletest_BINARY_DIR}")

  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

# requires cmake 3.14
#FetchContent_MakeAvailable(googletest)

include_directories(${COMMON_INCLUDES})

add_definitions(${MSVC_COMPILER_DEFS})

enable_testing()

set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test)
file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/src/gtest/*.cpp)

# Construct the testing executable
add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES})

# This forces glj3D & gtest to be built if mytests is the target.

#I'm not sure how your supposed to figure out target names, i did a cmake <tab>
#with no dependencies to get it work.
add_dependencies(${PROJECT_TEST_NAME} gtest) # google test target
add_dependencies(${PROJECT_TEST_NAME} strings) # my target(s)
add_dependencies(${PROJECT_TEST_NAME} maths) 
add_dependencies(${PROJECT_TEST_NAME} networking) 
add_dependencies(${PROJECT_TEST_NAME} serialisation) 
add_dependencies(${PROJECT_TEST_NAME} replication) 
add_dependencies(${PROJECT_TEST_NAME} engine) 

add_dependencies(${PROJECT_TEST_NAME} clientlib) 
add_dependencies(${PROJECT_TEST_NAME} serverlib) 

target_include_directories(${PROJECT_TEST_NAME} PUBLIC ${googletest_SOURCE_DIR}/googletest/include)

# this is target inside googletest
target_link_libraries(${PROJECT_TEST_NAME} PUBLIC gtest)

# this is my target under test
target_link_libraries (${PROJECT_TEST_NAME} LINK_PUBLIC strings)
target_link_libraries (${PROJECT_TEST_NAME} LINK_PUBLIC maths)
target_link_libraries (${PROJECT_TEST_NAME} LINK_PUBLIC networking)
target_link_libraries (${PROJECT_TEST_NAME} LINK_PUBLIC serialisation)
target_link_libraries(${PROJECT_TEST_NAME} LINK_PUBLIC replication)
target_link_libraries (${PROJECT_TEST_NAME} LINK_PUBLIC engine)

 target_link_libraries (${PROJECT_TEST_NAME} LINK_PUBLIC clientlib)
 target_link_libraries (${PROJECT_TEST_NAME} LINK_PUBLIC serverlib)

# Link SDL2

# target_include_directories(${PROJECT_TEST_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
# target_link_libraries(${PROJECT_TEST_NAME} LINK_PRIVATE ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(${PROJECT_TEST_NAME}  LINK_PRIVATE SDL2::Core)

# Link SDL2_image

# target_include_directories(${PROJECT_TEST_NAME} PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})
# target_link_libraries(${PROJECT_TEST_NAME} LINK_PRIVATE ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(${PROJECT_TEST_NAME}  LINK_PRIVATE SDL2::Image)

include(GoogleTest)
gtest_discover_tests(${PROJECT_TEST_NAME}
					 DISCOVERY_MODE PRE_TEST)

#-------------------
# INSTALL TARGET
#-------------------

message(STATUS "Where is everything going %s" ${CMAKE_CURRENT_BINARY_DIR})
message(STATUS "Where is everything going %s" ${PROJECT_BINARY_DIR})

set(APP ${PROJECT_TEST_NAME})


# post-build copy for win32
if(WIN32 AND NOT MINGW)
	add_custom_command( TARGET ${APP} PRE_BUILD
		COMMAND if not exist .\\dist\\bin mkdir .\\dist\\bin )
	add_custom_command( TARGET ${APP} POST_BUILD
		COMMAND copy \"$(TargetPath)\" .\\dist\\bin )
endif(WIN32 AND NOT MINGW)

if(MINGW OR UNIX)
	set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/dist/bin)
endif(MINGW OR UNIX)

message(STATUS "Value of APP " ${APP})

install(TARGETS ${APP}
	CONFIGURATIONS Release RelWithDebInfo Debug
	RUNTIME DESTINATION bin
	)

message(STATUS "Relative path" ${CMAKE_SOURCE_DIR})

install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/assets
	CONFIGURATIONS Release RelWithDebInfo Debug
	DESTINATION ./
	)

if(WIN32)
	# https://stackoverflow.com/questions/23950887/does-cmake-offer-a-method-to-set-the-working-directory-for-a-given-build-system
	# Ignored due to a VS issue https://developercommunity.visualstudio.com/content/problem/268817/debugger-no-longer-respects-localdebuggerworkingdi.html
	# Fix is due in the next version https://gitlab.kitware.com/cmake/cmake/-/merge_requests/6783
	set_target_properties(${APP} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_INSTALL_PREFIX}/bin")

	message(STATUS "Binary dir!" ${CMAKE_CURRENT_BINARY_DIR})

	# Get all the SDL2 files! 
	file(GLOB_RECURSE SDL2_DLL_FILES  ${SDL2_PATH}/*.dll)

	install(FILES ${SDL2_DLL_FILES}
		CONFIGURATIONS Release RelWithDebInfo Debug
		DESTINATION bin
		)

	# Get all the SDL2_image files! 
	file(GLOB_RECURSE SDL2_IMAGE_DLL_FILES  ${SDL2_IMAGE_PATH}/*.dll)

	install(FILES ${SDL2_IMAGE_DLL_FILES}
		CONFIGURATIONS Release RelWithDebInfo Debug
		DESTINATION bin
		)

	#message(STATUS "Directory I'm looking for google test binary files in %s" ${googletest_BINARY_DIR})

	# Get all the Gtest files! 
	#file(GLOB_RECURSE GTEST_DLL_FILES  ${googletest_BINARY_DIR}/*.dll)

	#install(FILES ${GTEST_DLL_FILES}
#		CONFIGURATIONS Release RelWithDebInfo Debug
#		DESTINATION bin	
#		)

endif()