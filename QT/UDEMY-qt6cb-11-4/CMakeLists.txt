cmake_minimum_required(VERSION 3.14)

project(UDEMY-qt6cb-11-4 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(UDEMY-qt6cb-11-4
  main.cpp
  source.h
  source.cpp
  destination.h
  destination.cpp
)
target_link_libraries(UDEMY-qt6cb-11-4 Qt${QT_VERSION_MAJOR}::Core)

install(TARGETS UDEMY-qt6cb-11-4
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
