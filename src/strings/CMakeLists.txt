# Create a library called "Strings" which includes the source file "*.cxx".
# The extension is already found. Any number of sources could be listed here.


file(GLOB STRINGS_FILES *.cpp)
add_library (strings STATIC ${STRINGS_FILES})

# Includes only for tihs target.
target_include_directories (strings PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# No dependencies on other modules but this is how it would look.
#target_include_directories (RigidMapNet PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../maths)
#target_link_libraries (RigidMapNet LINK_PUBLIC Maths)
