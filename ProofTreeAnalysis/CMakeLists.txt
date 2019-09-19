# CMakeLists.txt for ProofTreeAnalysis 

# Add include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Configure and generate LibraryConfig.h where the getExampleDataLibDir() function is defined.
# The generated function will return a string of the path to ${CMAKE_INSTALL_DIR}/lib/
# This function is used when you load libraries to the PROOF session where you need to give
# the absolute path to the libraries.
configure_file(include/LibraryConfig.h.in ${CMAKE_BINARY_DIR}/generated/LibraryConfig.h)
include_directories(${CMAKE_BINARY_DIR}/generated)

add_subdirectory(source)

# Executable for filling a tree with random Gaussian distribution
add_executable (FillGaus $<TARGET_OBJECTS:FillGausObjects>)
target_link_libraries(FillGaus ${ROOT_LIBRARIES} ExampleDataLib)

# Executable for processing tree data using PROOF
add_executable (ProofTreeAnalysis $<TARGET_OBJECTS:ProofTreeAnalysisObjects>)
target_link_libraries(ProofTreeAnalysis ${ROOT_LIBRARIES} ExampleDataLib)

# Install executables and root dictionaries.
install(TARGETS FillGaus
	RUNTIME DESTINATION bin
	PUBLIC_HEADER DESTINATION include
)
install(TARGETS ProofTreeAnalysis
	RUNTIME DESTINATION bin
	PUBLIC_HEADER DESTINATION include
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/source/libExampleDataDict_rdict.pcm DESTINATION lib)
