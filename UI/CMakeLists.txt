pkg_check_modules(gtkmm REQUIRED IMPORTED_TARGET gtkmm-3.0 glibmm-2.4)
add_library(UI App.cpp Window.cpp)
target_include_directories(UI PRIVATE ${GLIBMM_INCLUDE_DIRS} ${GTKMM_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/Fetcher)
target_compile_options(UI PRIVATE ${GTKMM_CFLAGS_OTHER} ${GLIBMM_CFLAGS_OTHER})
target_link_libraries(UI 
    PUBLIC ${GTKMM_LIBRARIES} ${GLIBMM_LIBRARIES}
    PRIVATE Fetcher)