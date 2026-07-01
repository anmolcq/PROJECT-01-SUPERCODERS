- Date- 30 June 2026 (Session 1)
Duration: 2 hours 20 mins

Goal():
To configure the gtest and run the testcases for dynamic array and linked list.

Error1:


D:\googletest\build>mingw32-make
[ 12%] Building CXX object googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.obj
In file included from D:\googletest\googletest\src\gtest-all.cc:38:0:
D:/googletest/googletest/include/gtest/gtest.h:60:23: fatal error: string_view: No such file or directory
 #include <string_view>
                       ^
compilation terminated.
googletest\CMakeFiles\gtest.dir\build.make:78: recipe for target 'googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.obj' failed
mingw32-make[2]: *** [googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.obj] Error 1
CMakeFiles\Makefile2:197: recipe for target 'googletest/CMakeFiles/gtest.dir/all' failed
mingw32-make[1]: *** [googletest/CMakeFiles/gtest.dir/all] Error 2
Makefile:144: recipe for target 'all' failed
mingw32-make: *** [all] Error 2

The error says that mingwcc compiler is of old versionand is not compiling in C++ 17 mode.

```std::string_view``` was introduced in C++17. GoogleTest versions 1.13+ require a compiler that supports it

Steps: Cheching the version of compiler :
```g++ --version ```

then we run 
```cmake ..```
after this we will build it again using the command 
```mingw32-make```
 Running the mingw32-make command.


Error 2:
-- Build files have been written to: D:/GITN/PROJECT-01-SUPERCODERS/build
MSBuild version 17.14.23+b0019275e for .NET Framework

  1>Checking Build System
  Building Custom Rule D:/GITN/PROJECT-01-SUPERCODERS/CMakeLists.txt
  Redislite.cpp
  RedisLite.vcxproj -> D:\GITN\PROJECT-01-SUPERCODERS\build\Debug\RedisLite.exe
  Building Custom Rule D:/GITN/PROJECT-01-SUPERCODERS/CMakeLists.txt
  test_append.cpp
  test_assignment.cpp
  test_capacity.cpp
  test_constructor.cpp
  test_coopy_constructor.cpp
  test_empty.cpp
  test_get.cpp
  test_insert.cpp
  test_operator_access.cpp
  test_pop_back.cpp
  test_remove.cpp
  test_size.cpp
  Generating Code...
LINK : fatal error LNK1104: cannot open file 'gtest.lib' [D:\GITN\PROJECT-01-SUPERCODERS\build\RedisLiteTests.vcxproj]

This means compiler found the google test header but not able to find the linker ie., gtest.lib
I ran this command to check whether the gtest.lib exisits in the directory.

```dir D:\ -Recurse gtest.lib```
running this command i didnt get something and therefore this means that gtest.lib doesnt exists.

Then i had to the google test folder and then going inside i ran this command for the configuring

```cmake ..```
then I build the files with 
``` cmake --build . --config Release```
D:\googletest\build>cmake --build . --config Release 
[ 25%] Built target gtest
[ 50%] Built target gmock 
[ 75%] Built target gmock_main 
[100%] Built target gtest_main 

after builiding check using
```dir /s gtest*.lib```
D:\googletest\build>dir /s gtest*.lib 
Volume in drive D is New Volume 
Volume Serial Number is 4A1B-A24C 
File Not Found
If it is coming file not found.
it can be bause we are using mingw geerator due to which there might be instead of .lib .a files are created 
it may be that googletest might be build on some on other extension.

To check this we have ran this command 
```cd D:\googletest\build```

```cmake --system-information | findstr CMAKE_GENERATOR```
D:\googletest\build>cmake --system-information | findstr CMAKE_GENERATOR C
MAKE_GENERATOR "Visual Studio 17 2022" 
CMAKE_GENERATOR_INSTANCE "C:/Program Files (x86)/Microsoft Visual Studio/2022/BuildTools" 
CMAKE_GENERATOR_NO_COMPILER_ENV "1" 
CMAKE_GENERATOR_PLATFORM "" CMAKE_GENERATOR_RC "rc" 
CMAKE_GENERATOR_TOOLSET "" 
CMAKE_GENERATOR:INTERNAL=MinGW Makefiles
CMAKE_GENERATOR_INSTANCE:INTERNAL= 
CMAKE_GENERATOR_PLATFORM:INTERNAL= 
CMAKE_GENERATOR_TOOLSET:INTERNAL=

after running this it made clear that it was firslty been made my mingw and configured by visual studio due to which it get mixed or corrupted
