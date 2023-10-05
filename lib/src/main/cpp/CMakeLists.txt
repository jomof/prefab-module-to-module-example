project("other-lib")
add_library(${CMAKE_PROJECT_NAME} STATIC other-lib.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME})