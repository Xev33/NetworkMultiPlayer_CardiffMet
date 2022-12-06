# Create a library called "engine" which includes the source file "*.cxx".
# The extension is already found. Any number of sources could be listed here.


file(GLOB ENGINE_FILES *.cpp)
add_library (engine STATIC ${ENGINE_FILES})

# Link SDL2

target_include_directories(engine PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(engine LINK_PRIVATE ${SDL2_LIBRARIES})

# Link SDL2_image

target_include_directories(engine PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(engine LINK_PRIVATE ${SDL2_IMAGE_LIBRARIES})

# Link SDL2_gfx

target_include_directories(engine PRIVATE ${SDL2_GFX_INCLUDE_DIRS})
target_link_libraries(engine LINK_PRIVATE ${SDL2_GFX_LIBRARIES})

# Includes only for this target.
target_include_directories (engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories (engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../strings)
target_include_directories (engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../maths)
#target_include_directories (engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../networking)
target_include_directories (engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../serialisation)
target_include_directories (engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../replication)

#Engine
target_link_libraries (engine LINK_PUBLIC strings)
target_link_libraries (engine LINK_PUBLIC maths)
#target_link_libraries (engine LINK_PUBLIC networking)
target_link_libraries (engine LINK_PUBLIC serialisation)
target_link_libraries (engine LINK_PUBLIC replication)
