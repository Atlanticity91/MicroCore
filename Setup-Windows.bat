@echo off

set scriptpath=%~dp0

pushd ..
cls

echo === Micro Core Setup ===

IF EXIST "MicroCore\Micro Solution.sln" del /f "MicroCore\Micro Solution.sln"
IF EXIST MicroCore\MicroCore.vcxproj del /f MicroCore\MicroCore.vcxproj
IF EXIST MicroCore\MicroCore.vcxproj.filters del /f MicroCore\MicroCore.vcxproj.filters
IF EXIST MicroCore\MicroCore.vcxproj.user del /f MicroCore\MicroCore.vcxproj.user
IF EXIST MicroCore\bin rmdir /q /s MicroCore\bin
IF EXIST MicroCore\bin-int rmdir /q /s MicroCore\bin-int
IF EXIST MicroCore\Solution\ rmdir /q /s MicroCore\Solution\

MicroCore\Build\Premake\Windows\premake5.exe --file=MicroCore\Build\Build.lua vs2022

popd

pause
