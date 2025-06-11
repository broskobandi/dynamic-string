# dynamic-string
Dynamic string written in C.

## Requirements
Either clang or gcc is needed for the compilation.
The entire library, apart from str_auto, is written in pure C.
The str_auto macro helps to create dynamic string variables that
automatically clean up their resources when they go out of scope.
This functionality relies on the gcc extension __attribute__((cleanup())) and
as such it can only be used with gcc or clang.
Bear needs to be installed for compiling and running the tests.

## Installation
```bash
git clone git@github.com:broskobandi/dynamic-string.git &&
cd dynamic-string &&
make &&
sudo make install
```

## Examples
For examples, please see examples/example.c

## Tests
Ensure bear is installed.
In the root of the git repository run:
```
make clean &&
make test
```
