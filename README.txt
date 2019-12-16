READ ME

The compiler used is Microsoft C/C++ Compiler.

The makefile is executed by entering on the command line: nmake test.mak

The makefile does the following:

	Compiles binary_tree.cpp and test.cpp.

	Creates a library from binary_tree.obj.

	Links test.obj and binary_tree.lib.

	Runs the application with 'test'.

	Deletes and cleans up any .obj, .exe or .lib files.