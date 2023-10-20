# Source2Py
An early-stage platform for developing and running Python plugins on Valve's Source 2 game engine, using [Metamod:Source](https://www.metamodsource.net/downloads.php/?branch=master) as a host. 


## Building
### Requirements
+ [Python 3+](https://www.python.org/downloads/)
+ [CMake 3.18+](https://cmake.org/download/)

### Instructions
If all pre-requisites are met, building should go something like this: 
```bash
git clone --recursive https://github.com/s95rob/Source2Py && cd Source2Py
mkdir build && cd build
cmake ..
cmake --build .
```

## Installing
_Source2Py is built to be used with [Metamod:Source](https://www.metamodsource.net/downloads.php/?branch=master) (tested and working on build 1244). [Make sure you've installed it correctly before moving on.](https://cs2.poggu.me/metamod/installation/)_

Copy the contents of the generated `Package` folder from your build directory to Metamod's `addons` folder (i.e. `<cs2>/game/csgo/addons`). 
Then, copy the Python shared library (`.dll` on Windows, `.so` on Linux) that CMake linked from Python's binary directory to your game's binary directory (i.e. `<cs2>/game/bin/win64` on Windows). CMake will tell you which Python version it linked during the configure step. 

Finally, launch the plugin on your server: 
```bash
meta load addons/Source2Py/bin/Source2Py
```

## Using Plugins
Plugins shall be stored in the `addons/Source2Py/plugins` directory. Plugins can be enabled for loading by declaring their (relative) filepath in `pyplugins.ini`. 

*pyplugins.ini example:*
```
plugins/SamplePlugin.py
```

## Writing Plugins (wip)
Source2Py loads Python plugins by instantiating the class within the module that shares the same (case-sensitive) name as the module, minus the file extension. Therefore, the plugin `SamplePlugin.py` must define a class named `SamplePlugin` in order to be loaded *at all*. The class defines methods that Source2Py uses as callbacks whenever an engine hook is called. Engine types and functions are exposed to Python via the module `Source2Py`. 

*todo: provide Python API doc*

*SamplePlugin.py example:*
```python
import Source2Py

def SamplePlugin:
    # Called when Source2Py loads the plugin
    def Load(self): 
        Source2Py.Print("Hello world!") # Prints to console
    
    # Called when Source2Py unloads the plugin
    def Unload(self) 
        Source2Py.Print("Goodbye world!")
```