# C++

## CMakeList file

## Google Test Framework

### Install

#### Download source code

[Download](https://github.com/google/googletest)

#### Build and install

In `googletest` folder:

```bash
cp -a include/gtest /usr/local/include

mkdir build
cd build

cmake ..
make
cp -a *.a /usr/local/lib 
```

In `googlemock` folder:

```bash
cp -a include/gmock /usr/local/include

mkdir build
cd build

cmake ..
make
cp -a *.a /usr/local/lib 
```

### How to use

In `CMakeList.txt` file, add:

```cmake
include_directories("/usr/local/include")
target_link_libraries(<EXECUTABLE_NAME> /usr/local/lib/libgtest.a)
```
