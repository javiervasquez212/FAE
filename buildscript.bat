conan profile detect --force
conan install . --output-folder=build --build=missing
cd build 
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake 
cmake --build . --config Release
.\Release\FAE.exe