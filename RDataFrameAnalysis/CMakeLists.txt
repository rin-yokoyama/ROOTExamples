###### Library for your custom class definition ######
# Generate a ROOT dictionary for ExampleDataClass and ExampleSelector.
ROOT_GENERATE_DICTIONARY(ExampleTwoDataDict
	${CMAKE_CURRENT_SOURCE_DIR}/include/ExampleTwoDataClass.h
	LINKDEF ${CMAKE_CURRENT_SOURCE_DIR}/include/LinkDef.h
)
# Generate a shared library for these objects.
add_library(ExampleTwoDataLib SHARED ExampleTwoDataDict.cxx)
target_include_directories(ExampleTwoDataLib
	PUBLIC
		$<INSTALL_INTERFACE:include/RDataFrameAnalysis>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(ExampleTwoDataLib ${ROOT_LIBRARIES})

# Install ExampleTwoDataLib
install(TARGETS ExampleTwoDataLib
	LIBRARY DESTINATION lib
	PUBLIC_HEADER DESTINATION include
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libExampleTwoDataDict_rdict.pcm
	DESTINATION lib
)

#################################################################
###### executables ######
# An execuable to fill a tree with two random numbers in Gaussian distribution
# stored in the custom class, ExampleTwoDataClass.
add_executable(TreeGen ${CMAKE_CURRENT_SOURCE_DIR}/source/GenerateTree.cpp)
target_include_directories(TreeGen PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(TreeGen ${ROOT_LIBRARIES} ExampleTwoDataLib)

# Install executables and root dictionaries.
install(TARGETS TreeGen
	RUNTIME DESTINATION bin
	PUBLIC_HEADER DESTINATION include
)

# An execuable to show how to define your analysis using RDataFrame
add_executable(RDataFrameAnalysis ${CMAKE_CURRENT_SOURCE_DIR}/source/RDataFrameAnalysis.cpp)
target_include_directories(RDataFrameAnalysis PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(RDataFrameAnalysis ${ROOT_LIBRARIES} ExampleTwoDataLib)

# Install executables and root dictionaries.
install(TARGETS RDataFrameAnalysis
	RUNTIME DESTINATION bin
	PUBLIC_HEADER DESTINATION include
)