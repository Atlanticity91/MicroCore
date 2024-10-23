@echo off

set scriptpath=%~dp0

pushd ..
cls

echo === Micro Core Setup ===

IF EXIST MicroCore\MicroCore.sln del /f MicroCore\MicroCore.sln
IF EXIST MicroCore\bin rmdir /q /s MicroCore\bin
IF EXIST MicroCore\bin-int rmdir /q /s MicroCore\bin-int
IF EXIST MicroCore\Solution\ rmdir /q /s MicroCore\Solution\

MicroCore\Build\Premake\Windows\premake5.exe --file=MicroCore\Build\Build.lua vs2022

popd

pause
