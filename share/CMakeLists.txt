# generate modulefile
configure_file("modulefiles/ROOTExamples" ROOTExamples @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ROOTExamples DESTINATION share/modulefiles/)

# generate a shell script to export environment variables to run this programs
configure_file("setup.sh.in" "setup.sh" @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/setup.sh DESTINATION share/)