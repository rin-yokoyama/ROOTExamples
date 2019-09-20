configure_file("modulefiles/ROOTExamples" ROOTExamples @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ROOTExamples DESTINATION share/modulefiles/)
