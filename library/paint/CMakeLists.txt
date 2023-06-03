#find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)

qt_add_library(paint STATIC
        paint.cpp
        paint/paint.hpp paint/paint_app.hpp paint_app.cpp palette_button.cpp paint/palette_button.hpp)

target_link_libraries(paint PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(paint INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})