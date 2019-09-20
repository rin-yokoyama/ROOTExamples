# Generate a ROOT dictionary for ExampleDataClass and ExampleSelector.
ROOT_GENERATE_DICTIONARY(ExampleDataDict
	../include/ExampleDataClass.h
	../include/ExampleSelector.h
	LINKDEF ../include/ExampleDataLinkDef.h
)
# Generate a shared library for these objects.
add_library(ExampleDataLib SHARED ExampleDataDict.cxx ExampleSelector.cpp)
target_link_libraries(ExampleDataLib ${ROOT_LIBRARIES})

# An object for filling a tree with random Gaussian distribution
add_library(FillGausObjects OBJECT FillGaus.cpp)
# An object for proof analysis using TSelector
add_library(ProofTreeAnalysisObjects OBJECT ProofTreeAnalysis.cpp)

# Install ExampleDataLib
install(TARGETS ExampleDataLib
	LIBRARY DESTINATION lib
	PUBLIC_HEADER DESTINATION include
)
