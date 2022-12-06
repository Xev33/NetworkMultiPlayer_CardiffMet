

# Add executable called "helloDemo" that is built from the source files
# "demo.cxx" and "demo_b.cxx". The extensions are automatically found.

file(GLOB SERVER_FILES *.cpp)

list(REMOVE_ITEM SERVER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/ServerMain.cpp")

add_library (serverlib ${SERVER_FILES})

# Link SDL2

# target_include_directories(serverlib PRIVATE ${SDL2_INCLUDE_DIRS})
# target_link_libraries(serverlib LINK_PRIVATE ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(serverlib  LINK_PRIVATE SDL2::Core)

# Link SDL2_image

# target_include_directories(serverlib PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})
# target_link_libraries(serverlib LINK_PRIVATE ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(serverlib  LINK_PRIVATE SDL2::Image)

#Includes only for this target - these could possibly be for all targets but...
target_include_directories (serverlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories (serverlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../strings)
target_include_directories (serverlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../maths)
target_include_directories (serverlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../networking)
target_include_directories (serverlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../serialisation)
target_include_directories (serverlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../engine)
target_include_directories (serverlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../replication)

# Link the executable to the Hello library. Since the Hello library has
# public include directories we will use those link directories when building

#Server Library liniks
target_link_libraries (serverlib LINK_PUBLIC strings)
target_link_libraries (serverlib LINK_PUBLIC maths)
target_link_libraries (serverlib LINK_PUBLIC networking)
target_link_libraries (serverlib LINK_PUBLIC serialisation)
target_link_libraries (serverlib LINK_PUBLIC engine)
target_link_libraries (serverlib LINK_PUBLIC replication)

add_executable (Server ServerMain.cpp)

#-------------------
# Fix for Console 
#-------------------

if(WIN32)
   set_target_properties(Server PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
   set_target_properties(Server PROPERTIES COMPILE_DEFINITIONS_DEBUG "_CONSOLE")
   set_target_properties(Server PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:CONSOLE")
   set_target_properties(Server PROPERTIES COMPILE_DEFINITIONS_RELWITHDEBINFO "_CONSOLE")
   set_target_properties(Server PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:CONSOLE")
   set_target_properties(Server PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:CONSOLE")
endif(WIN32)


#Includes only for this target - these could possibly be for all targets but...
target_include_directories (Server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories (Server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../strings)
target_include_directories (Server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../maths)
target_include_directories (Server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../networking)
target_include_directories (Server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../serialisation)
target_include_directories (Server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../engine)
target_include_directories (Server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../replication)

# Link the executable to the Hello library. Since the Hello library has
# public include directories we will use those link directories when building

#Server link libraries
target_link_libraries (Server LINK_PUBLIC strings)
target_link_libraries (Server LINK_PUBLIC maths)
target_link_libraries (Server LINK_PUBLIC networking)
target_link_libraries (Server LINK_PUBLIC serialisation)
target_link_libraries (Server LINK_PUBLIC engine)
target_link_libraries (Server LINK_PUBLIC replication)
target_link_libraries (Server LINK_PUBLIC serverlib)

# Link SDL2

# target_include_directories(Server PRIVATE ${SDL2_INCLUDE_DIRS})
# target_link_libraries(Server LINK_PRIVATE ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(Server  LINK_PRIVATE SDL2::Core)

# Link SDL2_image

# target_include_directories(Server PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})
# target_link_libraries(Server LINK_PRIVATE ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(Server  LINK_PRIVATE SDL2::Image)

#-------------------
# INSTALL TARGET
#-------------------

message(STATUS "Where is everything going %s" ${CMAKE_CURRENT_BINARY_DIR})

set(APP Server)

message(STATUS "Value of APP " ${APP})

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

	# Get all the Gtest files! 
	# file(GLOB_RECURSE GTEST_DLL_FILES  ${GTEST_DIR}/*.dll)

	#install(FILES ${GTEST_DLL_FILES}
	#	DESTINATION bin
	#	CONFIGURATIONS Release RelWithDebInfo Debug)

endif()