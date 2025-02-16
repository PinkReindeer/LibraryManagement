@echo off

set PATH=C:\msys64\ucrt64\bin;%PATH%
set SRC_DIR=%~dp0..\src
set BUILD_DIR=%SRC_DIR%\build
IF NOT EXIST %BUILD_DIR% mkdir %BUILD_DIR%

pushd %BUILD_DIR%

set BUILD_FLAGS=
C:\msys64\ucrt64\bin\g++.exe %SRC_DIR%\main.cpp %BUILD_FLAGS%

popd