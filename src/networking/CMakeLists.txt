# Create a library called "Networking" which includes the source file "*.cxx".
# The extension is already found. Any number of sources could be listed here.

file(GLOB NETWORK_FILES *.cpp)
add_library (networking STATIC ${NETWORK_FILES})

# Includes only for this target.
target_include_directories (networking PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Dependent on string utils for logging.
target_include_directories (networking PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../strings)
target_link_libraries (networking LINK_PUBLIC strings)

if(WIN32)
  target_link_libraries(networking LINK_PUBLIC wsock32 ws2_32)
endif()
