#Set CMAKE and CPP version/standard
cmake_minimum_required(VERSION 3.26)
project(saper)
set(CMAKE_CXX_STANDARD 17)

#Add compiler options
add_compile_options(-Wall -Wextra -pedantic -Werror=return-type -Werror=parentheses -Werror=vla -Werror=array-bounds -Wcast-qual -Wmaybe-uninitialized )

#SFML setup for Windows
IF (WIN32)
    # Include local sfml cmake config
    set(SFML_DIR "C:/SFML-2.6.1/lib/cmake/SFML")
    # Link sfml statically (Optional)
    set(SFML_STATIC_LIBRARIES TRUE)
ENDIF()

#SFML setup - graphics and audio
find_package(SFML 2 COMPONENTS graphics audio REQUIRED)

#Copying all assets from assets/ to build directory
configure_file(assets/sounds/flagSound.wav ${CMAKE_CURRENT_BINARY_DIR}/flagSound.wav COPYONLY)
configure_file(assets/sounds/winSound.wav ${CMAKE_CURRENT_BINARY_DIR}/winSound.wav COPYONLY)
configure_file(assets/sounds/bombSound.wav ${CMAKE_CURRENT_BINARY_DIR}/bombSound.wav COPYONLY)
configure_file(assets/sounds/clickSound.wav ${CMAKE_CURRENT_BINARY_DIR}/clickSound.wav COPYONLY)
configure_file(assets/textures/saper_bg.jpg ${CMAKE_CURRENT_BINARY_DIR}/saper_bg.jpg COPYONLY)
configure_file(assets/fonts/VT323-Regular.ttf ${CMAKE_CURRENT_BINARY_DIR}/VT323-Regular.ttf COPYONLY)
configure_file(assets/textures/mine.png ${CMAKE_CURRENT_BINARY_DIR}/mine.png COPYONLY)
configure_file(assets/textures/flag.png ${CMAKE_CURRENT_BINARY_DIR}/flag.png COPYONLY)
configure_file(assets/textures/icon.png ${CMAKE_CURRENT_BINARY_DIR}/icon.png COPYONLY)

#Minesweeper - text mode
add_executable(saper main.cpp
        MinesweeperBoard.cpp
        MinesweeperBoard.h
        MSBoardTextView.cpp
        MSBoardTextView.h
        MSTextController.cpp
        MSTextController.h
)

#Minesweeper - GUI mode made with SFML
add_executable(saper-sfml sfml_main.cpp
        MinesweeperBoard.cpp
        MinesweeperBoard.h
        MSSFMLView.cpp
        MSSFMLView.h
        MSSFMLController.cpp
        MSSFMLController.h)
target_link_libraries(saper-sfml sfml-graphics
                                sfml-audio
)