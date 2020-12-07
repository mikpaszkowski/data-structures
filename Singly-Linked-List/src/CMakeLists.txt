# Add your sources to the list below:
set(SRCS test_sequence.cpp)
# Add your headers to the list below:
set(HDRS sequence.hpp)

SET(GCC_WARNINGS_COMPILE_FLAGS "-Wall -Wextra -pedantic -Werror")
SET(GCC_UB_COMPILE_FLAGS    "-fsanitize=undefined")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_WARNINGS_COMPILE_FLAGS}")
# Uncomment the following line to find undefined behavior:
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_UB_COMPILE_FLAGS}")

add_executable(sequence ${SRCS} ${HDRS})

target_link_libraries(sequence Catch2::Catch2WithMain)

add_custom_target(run
    COMMAND sequence
    DEPENDS sequence
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
