:: Changing generator to working version
cmake -G "Visual Studio 12 2013 Win64" CMakeLists.txt 
:: Linking, building and creating .dll
cmake --build . --config Release 
:: move for using as a Python module
move Release\repeating_count.pyd
