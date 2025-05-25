# SDL2 C Project Template

A simple template for starting a C project using SDL2.

## Prerequisites

Before you can build and run this project, you need to have the following installed:

- GCC (GNU Compiler Collection)
- SDL2 development libraries

### Installing SDL2

#### Windows

1. Download the SDL2 development libraries from [SDL's official website](https://www.libsdl.org/download-2.0.php)
2. Extract the files to a location on your system
3. Add the SDL2 include directory to your include path
4. Add the SDL2 library directory to your library path

#### Linux

```bash
sudo apt-get install libsdl2-dev
```

#### macOS

```bash
brew install sdl2
```

## Building the Project

To build the project, simply run:

```bash
make
```

To clean the build files:

```bash
make clean
```

## Running the Project

After building, run the executable:

```bash
./game
```

## Project Structure

- `main.c`: Contains the main game loop and SDL2 initialization
- `Makefile`: Build configuration
- `README.md`: This file

## Adding Your Code

The main game loop in `main.c` is where you'll add your game logic. Look for the comment "Add your rendering code here" to start adding your own code.

## License

This template is free to use for any purpose.
