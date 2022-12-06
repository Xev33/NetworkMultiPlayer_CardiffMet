# Create a library called "Networking" which includes the source file "*.cxx".
# The extension is already found. Any number of sources could be listed here.

file(GLOB NETWORK_FILES *.cpp)
add_library (serialisation STATIC ${NETWORK_FILES})

# Includes only for this target.
target_include_directories (serialisation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Dependent on string utils for logging.
target_include_directories (serialisation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../maths)
target_link_libraries (serialisation LINK_PUBLIC strings)
