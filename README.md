# Source2Py
An early stage platform for developing and running Python plugins on Valve's Source 2 game engine, using [Metamod:Source](https://www.metamodsource.net/downloads.php/?branch=master) as a host. 


## Building
### Requirements
+ [Python](https://www.python.org/downloads/)
+ [CMake](https://cmake.org/download/)

### Instructions
There are 3 configure flags that _must_ be set to build correctly: 

+ **PYTHON_INCLUDE_DIR** The path to Python's include directory
+ **PYTHON_LIB_DIR** The path to Python's libs directory (where the static libraries are installed)
+ **PYTHON_LIB** The static Python library you want to target (exclude the file extension, for example: python311)

It should go something like this: 
```bash
git clone --recursive https://github.com/s95rob/Source2Py && cd Source2Py
mkdir build && cd build
cmake .. -DPYTHON_INCLUDE_DIR=/path/to/python/include -DPYTHON_LIB_DIR/path/to/python/libs -PYTHON_LIB=python311
cmake --build .
```

## Installing
_Source2Py is built to be used with [Metamod:Source](https://www.metamodsource.net/downloads.php/?branch=master) (tested and working on build 1244). [Make sure you've installed it correctly before moving on.](https://cs2.poggu.me/metamod/installation/)_

Copy the contents of the generated `Package` folder from your build directory to your game's `addons` folder (`<cs2>/game/csgo/addons`). 
Launch the plugin on your server: 
```bash
meta load addons/Source2Py/bin/Source2Py
```