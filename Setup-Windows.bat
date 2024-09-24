@echo off

set scriptpath=%~dp0

pushd ..
cls

echo === Micro Core Setup ===

MicroCore\Build\Premake\Windows\premake5.exe --file=MicroCore\Build\Build.lua vs2022

popd

pause
