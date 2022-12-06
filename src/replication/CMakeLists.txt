# Create a library called "Replication" which includes the source file "*.cxx".
# The extension is already found. Any number of sources could be listed here.

file(GLOB REPLICATION_FILES *.cpp)
add_library (replication STATIC ${REPLICATION_FILES})

# Includes only for this target.
target_include_directories (replication PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Dependent on string utils for logging.
target_include_directories (replication PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../strings)
target_link_libraries (replication LINK_PUBLIC strings)

# Object Registry needs to know about game GameObjects :-p
target_include_directories (replication PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../engine)
target_link_libraries (replication LINK_PUBLIC engine)

# Network manager's got to network
target_include_directories (replication PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../networking)
target_link_libraries (replication LINK_PUBLIC networking)
