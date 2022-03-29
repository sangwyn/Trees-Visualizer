cmake_minimum_required(VERSION 3.21)
project(treesSFML)

set(CMAKE_CXX_STANDARD 20)

## If you want to link SFML statically
set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(treesSFML main.cpp AVLTree.cpp AVLTree.h AVLTreeNode.cpp AVLTreeNode.h TreeManager.cpp TreeManager.h Globals.h Globals.cpp Button.cpp Button.h Textbox.cpp Textbox.h)
target_link_libraries(treesSFML sfml-graphics sfml-audio)