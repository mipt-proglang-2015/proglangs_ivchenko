:: Changing generator to working version
cmake -G "Visual Studio 12 2013 Win64" CMakeLists.txt 
:: Linking, building and creating .dll
cmake --build . --config Release 
:: move and rename library for using as Python module
move Release\Proj.dll 
rename Proj.dll repeating_count.pyd :: move