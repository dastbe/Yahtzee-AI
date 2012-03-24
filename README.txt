Yahtzee Parser and AI
Created By: David Bell
March 24, 2012


Build Instructions:

	make clean && make 		=> Rebuilds the entire project for production
	make clean && make test => Rebuilds the entire project for testing
	make project 			=> Builds the executable in the bin/ directory from the c++ files in the project/ directory
	make scripts 			=> Reruns the python scripts in the scripts/ directory and outputs their results into files in the data/ directory
	make clean 				=> Removes all data files and executables


Program Execution Instructions:

	./bin/yai


Compiler Specifications:

	g++:
		i686-apple-darwin11-llvm-g++-4.2 (GCC) 4.2.1 (Based on Apple Inc. build 5658) (LLVM build 2336.10.00)

	python:
		Python 2.7.2 (default, Jan  7 2012, 15:32:53) 
		[GCC 4.2.1 Compatible Apple Clang 4.0 (tags/Apple/clang-418.0.20)] on darwin

	boost:
		boost 1.48.0
		installed with homebrew

