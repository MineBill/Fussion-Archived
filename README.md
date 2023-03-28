# Fussion™
A very serious(not really) OpenGL Game™ Engine™

## Amazing high performance quad rendering(again, not really)
![image](https://user-images.githubusercontent.com/30367251/228143690-f045524d-f7fb-467b-8da0-2983b8a6b127.png)

# Building
### Prerequisites
- GCC / Clang / MSVC with C++20 support

To build:
```shell
$ cmake --preset linux-debug
$ cmake --build out/linux-debug --target run
```
## Libraries
Most dependecies are included in ThirdParty but some system libraries are required by glfw:
### Fedora
- libXrandr-devel
- libXinerama-devel
- libXcursor-devel
- libXi-devel
