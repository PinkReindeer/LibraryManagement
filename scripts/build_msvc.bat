@echo off

call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x86

set SRC_DIR=%~dp0..\src
set BUILD_DIR=%SRC_DIR%\build
IF NOT EXIST %BUILD_DIR% mkdir %BUILD_DIR%

pushd %BUILD_DIR%

set BUILD_FLAGS=/W3 /Od /Z7 /EHsc /wd4996 /nologo /link
cl %SRC_DIR%/main.cpp %BUILD_FLAGS%

popd