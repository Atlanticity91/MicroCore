# MicroCore
---
This repository contains the code for the Micro Core Library, this project defined Assertion, File wrapper, math types definitions and functions, platform's specific wrapper function, Multi-threading work management and Yaml file support.

> [!CAUTION]
> This repository use submodules for Thirdparty. Make sure to setup submodules before any action.
> `git submodule update --init --recursive`

# Build System
MicroCore as part of the Micro project use the Premake5 build system. Premake5 instance is present in this repository under Build/Premake5.

Build files for Premake5 are inside Build folder under :

| File  					    | Usage 							|
| ----------------------------- | --------------------------------- |
| `Build/Build.lua`  		 	| Define global solution build. 	|
| `Build/Build-MicroCore.lua`   | Define MicroCore solution build.  |
| `Build/Build-Thirdparty.lua`  | Define Thirdparty solution build. |

## Windows
For Windows build you need at least visual studio 2022 community edition or visual studio C++.

To build the project files simply run Setup-Windows.bat

## Linux
> [!CAUTION]
> Linux isn't implemented yet.

To build the project files simply run Setup-Linux.sh

# Documentation
Documentation for the library can be found under [Documentation/index.html](./Documentation/index.html)
