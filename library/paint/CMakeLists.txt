find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_library(paint SHARED
        ${PROJECT_SOURCES})

set_property(TARGET paint PROPERTY CXX_STANDARD 20)
install(TARGETS paint)
