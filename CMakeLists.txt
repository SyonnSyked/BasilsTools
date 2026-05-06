cmake_minimum_required(VERSION 3.20)

project(BasilsTools VERSION 0.1.0 LANGUAGES C)


set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)


add_library(BasilsTools STATIC src/DynamicArray.c src/DynamicArray2D.c src/DynamicArray3D.c)

target_include_directories(BasilsTools PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(BToolsTest test.c)

target_link_libraries(BToolsTest PRIVATE BasilsTools)
