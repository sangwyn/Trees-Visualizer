cmake_minimum_required(VERSION 3.21)
project(treesSFML)

set(CMAKE_CXX_STANDARD 20)

add_executable(treesSFML main.cpp AVLTree.cpp AVLTree.h AVLTreeNode.cpp AVLTreeNode.h TreeManager.cpp TreeManager.h)
