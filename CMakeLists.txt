cmake_minimum_required(VERSION 3.26)
project(saper)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -pedantic -Werror=return-type -Werror=parentheses -Werror=vla -Werror=array-bounds -Wcast-qual -Wmaybe-uninitialized )
IF (WIN32)
    # Include local sfml cmake config
    set(SFML_DIR "C:/SFML-2.6.1/lib/cmake/SFML")
    # Link sfml statically (Optional)
    set(SFML_STATIC_LIBRARIES TRUE)
ENDIF()

find_package(SFML 2.6.1 COMPONENTS graphics audio REQUIRED)

add_executable(saper main.cpp
        MinesweeperBoard.cpp
        MinesweeperBoard.h
        MSBoardTextView.cpp
        MSBoardTextView.h
        MSTextController.cpp
        MSTextController.h
)

target_link_libraries(saper sfml-graphics
                            sfml-audio
)
