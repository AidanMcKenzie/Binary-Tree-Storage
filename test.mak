test:
	cl /c binary_tree.cpp test.cpp
	lib binary_tree.obj
	link test.obj binary_tree.lib
	test
	
	del *.obj
	del *.exe
	del *.lib