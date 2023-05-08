cmake_minimum_required(VERSION 3.14)

project(UDEMY-qt6cb-15-1-QObject LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(UDEMY-qt6cb-15-1-QObject
  main.cpp
  cat.h
  cat.cpp
  dog.h
  dog.cpp
)
target_link_libraries(UDEMY-qt6cb-15-1-QObject Qt${QT_VERSION_MAJOR}::Core)

install(TARGETS UDEMY-qt6cb-15-1-QObject
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
