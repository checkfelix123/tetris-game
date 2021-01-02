@IF "%SWO3_LIBS_DIR%"=="" set SWO3_LIBS_DIR=D:\FH\SWO3\UE\SWO3_LIBS
cmake.exe -DVCPKG_TARGET_TRIPLET="x64-windows" -DCMAKE_TOOLCHAIN_FILE="%SWO3_LIBS_DIR%\scripts\buildsystems\vcpkg.cmake" -G"Visual Studio 16 2019" ..
if not exist "./bin" mkdir "./bin"
if not exist "./bin/Debug" mkdir "./bin/Debug"
if not exist "./bin/Debug/songs" mkdir "./bin/Debug/songs"
if not exist "./songs" mkdir "./songs"
copy "..\additional\bin\ikpFlac.dll" ".\bin\Debug\ikpFlac.dll"
copy "..\additional\bin\ikpMP3.dll" ".bin\Debug\ikpMP3.dll"
copy "..\additional\bin\irrKlang.dll" ".\bin\Debug\irrKlang.dll"
copy "..\additional\songs\tetris.wav" ".\bin\Debug\songs\tetris.wav"
copy "..\additional\songs\tetris.wav" ".\songs\tetris.wav"