@echo off

:: Compiler Warning Flags
set "FLAGS=-Wall -Wextra -Wconversion -pedantic -Werror"

:: Set the C++ Compiler
set "COMPILER=clang++" 

:: Create output dir if necessary
if not exist bin mkdir bin

:: Compile
echo [INFO]: Building....
%COMPILER% %FLAGS% -std=c++23 src/*.cpp -Iincludes -o bin/Tundra.exe
:: Check compilation result
if errorlevel 1 (
   echo [ERROR]: Build failed!
   exit /b 1
)
echo [INFO]: Build success!
echo [INFO]: Running....

powershell.exe ./bin/Tundra.exe
