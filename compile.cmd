@echo off
if not exist ".\bin" mkdir ".\bin"
pushd ".\bin"
g++ -std=c++17 -O3 -mwindows "..\src\main.cpp" -o "taskbar-toggle.exe"
popd