set(PROJECT_SOURCES
        main.cpp
)

qt_add_executable(PaintTest
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)
target_link_libraries(PaintTest PRIVATE paint Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(PaintTest PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS PaintTest
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
