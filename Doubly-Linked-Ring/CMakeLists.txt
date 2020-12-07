# Please don't modify this file
cmake_minimum_required(VERSION 3.11)
project(Lab2 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)


Include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        origin/devel)
FetchContent_MakeAvailable(Catch2)
add_subdirectory(src)
