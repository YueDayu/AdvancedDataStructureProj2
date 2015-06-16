Usage:

genfeatures.exe：

	genfeatures <image path> <image name list>

e.g.

	genfeatures .\ir\ irlist.txt

Feature file will be written to .\output\imagefeatures_out.txt

Compilation (Requires CMake, OpenCV, OpenCV_contrib):

	cmake .
	make

e.g. (with MinGW on Windows):

	cmake -G "MinGW Makefiles" .
	mingw32-make
