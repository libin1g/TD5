# CMake training 
> [hello-world-introductions-to-cmake](http://derekmolloy.ie/hello-world-introductions-to-cmake/)
> [cmake-examples](https://github.com/ttroy50/cmake-examples)

## build the example

## steps to build your prj with cmake-ninja-clang toolchain

1. Edit CMakeLists.txt for your project
2. Select your generator which cmake support, for example ninja, visual studio 2010/2019 
- This is an example, for ninja generator, command export ninja build script
```
    cmake .. -GNinja -DCMAKE_EXPORT_COMPILE_COMMANDS=1  -DCMAKE_C_COMPILER_ID="Clang" -DCMAKE_CXX_COMPILER_ID="Clang" -DCMAKE_SYSTEM_NAME="Generic"
```

3. Build your the project according your generator, for example `ninja all`
