cmake_minimum_required(VERSION 3.0.0)
project(U_test VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(U_test main.cpp U_V.cpp line_zoom.cpp ground_ex.cpp)
find_package(OpenCV REQUIRED)
target_link_libraries(U_test ${OpenCV_LIBS})



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
