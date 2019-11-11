@echo off

if not exist build mkdir build
pushd build

set TARGET=%1

if [%TARGET%]==[clean] (
    cd ..
    rmdir /s /q build
) else ( 
    cmake -G "Visual Studio 15 2017 Win64" ..
)

popd