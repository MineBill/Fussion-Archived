# Fussion™
A very serious(not really) OpenGL Game™ Engine™

## Amazing high performance quad rendering(again, not really)
![quads_yay](https://user-images.githubusercontent.com/30367251/213934812-acf9c267-baab-481e-9c30-4e4b6b4a2177.png)

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