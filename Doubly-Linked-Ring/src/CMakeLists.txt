# Add your sources to the list below:
set(SRCS ring_test.cpp)
# Add your headers to the list below:
set(HDRS ring.hpp)

SET(GCC_WARNINGS_COMPILE_FLAGS "-Wall -Wextra -pedantic -Werror")
SET(GCC_UB_COMPILE_FLAGS    "-fsanitize=undefined")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_WARNINGS_COMPILE_FLAGS}")
# Uncomment the following line to find undefined behavior:
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_UB_COMPILE_FLAGS}")

add_executable(ring ${SRCS} ${HDRS})

target_link_libraries(ring Catch2::Catch2WithMain)

add_custom_target(run
    COMMAND ring
    DEPENDS ring
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
