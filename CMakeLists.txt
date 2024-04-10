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

find_package(SFML 2 COMPONENTS graphics audio REQUIRED)

configure_file(kaczuszka.wav ${CMAKE_CURRENT_BINARY_DIR}/kaczuszka.wav COPYONLY)
configure_file(saper_bg.jpg ${CMAKE_CURRENT_BINARY_DIR}/saper_bg.jpg COPYONLY)
configure_file(VT323-Regular.ttf ${CMAKE_CURRENT_BINARY_DIR}/VT323-Regular.ttf COPYONLY)
configure_file(mine.png ${CMAKE_CURRENT_BINARY_DIR}/mine.png COPYONLY)
configure_file(flag.png ${CMAKE_CURRENT_BINARY_DIR}/flag.png COPYONLY)

add_executable(saper main.cpp
        MinesweeperBoard.cpp
        MinesweeperBoard.h
        MSBoardTextView.cpp
        MSBoardTextView.h
        MSTextController.cpp
        MSTextController.h
        MSSFMLView.cpp
        MSSFMLView.h
)

add_executable(saper-sfml main.cpp
        MinesweeperBoard.cpp
        MinesweeperBoard.h
        MSSFMLView.cpp
        MSSFMLView.h)
target_link_libraries(saper-sfml sfml-graphics
                                sfml-audio
)

target_link_libraries(saper sfml-graphics
        sfml-audio
)