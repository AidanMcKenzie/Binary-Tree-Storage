# Binary Tree Storage

Submitted in April 2016 for the Programming Fundamentals module (SET07109), as part of the BEng Software Engineering (Hons) degree at Edinburgh Napier University.

## Description

This program is constituted of a class that supports a binary tree data structure for storing int data, in order to allow for fast retrieval of said data. The class also supports a number of additional methods and operator overloads for interacting with the binary tree.

## How to Use

To run this program, use a C++ compiler, such as Microsoft C/C++ Compiler.

Within the compiler's command line, navigate to the folder containing the project files and enter the following command and execute: 
```
nmake test.mak
```

### Description of Makefile

The makefile does the following:
* Compiles binary_tree.cpp and test.cpp.
* Creates a library from binary_tree.obj.
* Links test.obj and binary_tree.lib.
* Runs the application with 'test'.
* Deletes and cleans up any .obj, .exe or .lib files.
