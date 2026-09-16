cmake_minimum_required(VERSION 3.22)
project(QUICKLOOK)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include
                    ${PROJECT_SOURCE_DIR}/src)

add_executable(template src/template.cpp)
add_executable(designatedInit src/designatedInit.cpp)
add_executable(lambda src/lambda.cpp)