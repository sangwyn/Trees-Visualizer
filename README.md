# Trees Visualizer

Trees Visualizer is a C++20/SFML desktop application for comparing several self-balancing binary search tree structures in one interactive window.

The app keeps the same set of keys across all supported trees, so you can insert or delete values once and then switch between tree views to see how each structure organizes the data.

## Supported Trees

- AVL tree
- Red-black tree
- Treap
- Splay tree

## Features

- Insert one or more integer keys manually.
- Generate random keys inside a configurable range.
- Delete one or more keys.
- Switch between tree implementations without losing the current key set.
- Pan and zoom the tree canvas.
- Click a rendered node to remove it.
- Visualize red and black nodes in the red-black tree view.

## Requirements

- CMake 3.21 or newer
- A C++20 compiler
- Ninja, Make, or another CMake-supported generator
- SFML 2.5

This repository includes an `SFML-2.5.1` directory and the current `CMakeLists.txt` points CMake at:

```cmake
SFML-2.5.1/lib/cmake/SFML
```

The bundled SFML package appears to be configured for MinGW/Windows builds. If you build on another platform, install a matching SFML package for your compiler and update `SFML_DIR` in `CMakeLists.txt` or pass it on the CMake command line.

## Build

From the repository root:

```sh
cmake -S . -B cmake-build-debug -G Ninja
cmake --build cmake-build-debug
```

For a release build:

```sh
cmake -S . -B cmake-build-release -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build cmake-build-release
```

If you use CLion, open the project directory and let CLion configure the existing CMake project.

## Run

The executable is named `treesSFML`.

On Windows:

```sh
cd cmake-build-debug
treesSFML.exe
```

On Unix-like systems:

```sh
cd cmake-build-debug
./treesSFML
```

Run the executable from a directory that contains the `Assets` folder, because the app loads:

- `Assets/logo.png`
- `Assets/Fonts/JetBrainsMono-Medium.ttf`

The existing `cmake-build-debug` and `cmake-build-release` directories contain an `Assets` folder. If you create a new build directory, copy `Assets` into it before running the app.

## Controls

- `AVL Tree`, `RB Tree`, `Treap`, `Splay tree`: switch the visible tree type.
- `Add random keys`: insert the number of random keys from `Node count`.
- `Add new nodes`: insert the space-separated keys from `Node keys (1 2 3...)`.
- `Delete nodes`: delete the space-separated keys from the delete field.
- `Min` and `Max`: set the random generation bounds. Empty fields default to `-1000` and `1000`.
- Arrow keys: pan the tree view.
- `+` / `=`: zoom in.
- `-`: zoom out.
- Click a node: delete that node.

Text boxes accept integers, spaces, and minus signs where appropriate.

## Project Structure

```text
.
├── main.cpp              # SFML window, event loop, and UI wiring
├── TreeManager.*         # Coordinates all tree implementations
├── AVLTree.*             # AVL tree implementation and drawing
├── RBTree.*              # Red-black tree implementation and drawing
├── Treap.*               # Treap implementation and drawing
├── SplayTree.*           # Splay tree implementation and drawing
├── Button.*              # UI button component
├── Textbox.*             # UI textbox component
├── Globals.*             # Shared colors, layout constants, and helpers
├── CMakeLists.txt        # CMake build configuration
└── SFML-2.5.1/           # Bundled SFML distribution
```

## Notes

- Duplicate inserts are rejected and displayed as an error in the UI.
- Random insertion may fail if the requested count exceeds the available values in the selected range.
- Tree rendering is based on the current tree depth and shared layout constants in `Globals.h`.
