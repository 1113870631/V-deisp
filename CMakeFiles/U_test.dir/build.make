# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/share/cmake-3.22.1-linux-x86_64/bin/cmake

# The command to remove a file.
RM = /usr/share/cmake-3.22.1-linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ww/opencv/U_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ww/opencv/U_test

# Include any dependencies generated for this target.
include CMakeFiles/U_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/U_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/U_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/U_test.dir/flags.make

CMakeFiles/U_test.dir/main.cpp.o: CMakeFiles/U_test.dir/flags.make
CMakeFiles/U_test.dir/main.cpp.o: main.cpp
CMakeFiles/U_test.dir/main.cpp.o: CMakeFiles/U_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ww/opencv/U_test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/U_test.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/U_test.dir/main.cpp.o -MF CMakeFiles/U_test.dir/main.cpp.o.d -o CMakeFiles/U_test.dir/main.cpp.o -c /home/ww/opencv/U_test/main.cpp

CMakeFiles/U_test.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/U_test.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ww/opencv/U_test/main.cpp > CMakeFiles/U_test.dir/main.cpp.i

CMakeFiles/U_test.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/U_test.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ww/opencv/U_test/main.cpp -o CMakeFiles/U_test.dir/main.cpp.s

CMakeFiles/U_test.dir/U_V.cpp.o: CMakeFiles/U_test.dir/flags.make
CMakeFiles/U_test.dir/U_V.cpp.o: U_V.cpp
CMakeFiles/U_test.dir/U_V.cpp.o: CMakeFiles/U_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ww/opencv/U_test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/U_test.dir/U_V.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/U_test.dir/U_V.cpp.o -MF CMakeFiles/U_test.dir/U_V.cpp.o.d -o CMakeFiles/U_test.dir/U_V.cpp.o -c /home/ww/opencv/U_test/U_V.cpp

CMakeFiles/U_test.dir/U_V.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/U_test.dir/U_V.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ww/opencv/U_test/U_V.cpp > CMakeFiles/U_test.dir/U_V.cpp.i

CMakeFiles/U_test.dir/U_V.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/U_test.dir/U_V.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ww/opencv/U_test/U_V.cpp -o CMakeFiles/U_test.dir/U_V.cpp.s

CMakeFiles/U_test.dir/line_zoom.cpp.o: CMakeFiles/U_test.dir/flags.make
CMakeFiles/U_test.dir/line_zoom.cpp.o: line_zoom.cpp
CMakeFiles/U_test.dir/line_zoom.cpp.o: CMakeFiles/U_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ww/opencv/U_test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/U_test.dir/line_zoom.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/U_test.dir/line_zoom.cpp.o -MF CMakeFiles/U_test.dir/line_zoom.cpp.o.d -o CMakeFiles/U_test.dir/line_zoom.cpp.o -c /home/ww/opencv/U_test/line_zoom.cpp

CMakeFiles/U_test.dir/line_zoom.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/U_test.dir/line_zoom.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ww/opencv/U_test/line_zoom.cpp > CMakeFiles/U_test.dir/line_zoom.cpp.i

CMakeFiles/U_test.dir/line_zoom.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/U_test.dir/line_zoom.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ww/opencv/U_test/line_zoom.cpp -o CMakeFiles/U_test.dir/line_zoom.cpp.s

CMakeFiles/U_test.dir/ground_ex.cpp.o: CMakeFiles/U_test.dir/flags.make
CMakeFiles/U_test.dir/ground_ex.cpp.o: ground_ex.cpp
CMakeFiles/U_test.dir/ground_ex.cpp.o: CMakeFiles/U_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ww/opencv/U_test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/U_test.dir/ground_ex.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/U_test.dir/ground_ex.cpp.o -MF CMakeFiles/U_test.dir/ground_ex.cpp.o.d -o CMakeFiles/U_test.dir/ground_ex.cpp.o -c /home/ww/opencv/U_test/ground_ex.cpp

CMakeFiles/U_test.dir/ground_ex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/U_test.dir/ground_ex.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ww/opencv/U_test/ground_ex.cpp > CMakeFiles/U_test.dir/ground_ex.cpp.i

CMakeFiles/U_test.dir/ground_ex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/U_test.dir/ground_ex.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ww/opencv/U_test/ground_ex.cpp -o CMakeFiles/U_test.dir/ground_ex.cpp.s

# Object files for target U_test
U_test_OBJECTS = \
"CMakeFiles/U_test.dir/main.cpp.o" \
"CMakeFiles/U_test.dir/U_V.cpp.o" \
"CMakeFiles/U_test.dir/line_zoom.cpp.o" \
"CMakeFiles/U_test.dir/ground_ex.cpp.o"

# External object files for target U_test
U_test_EXTERNAL_OBJECTS =

U_test: CMakeFiles/U_test.dir/main.cpp.o
U_test: CMakeFiles/U_test.dir/U_V.cpp.o
U_test: CMakeFiles/U_test.dir/line_zoom.cpp.o
U_test: CMakeFiles/U_test.dir/ground_ex.cpp.o
U_test: CMakeFiles/U_test.dir/build.make
U_test: /usr/local/lib/libopencv_gapi.so.4.5.5
U_test: /usr/local/lib/libopencv_highgui.so.4.5.5
U_test: /usr/local/lib/libopencv_ml.so.4.5.5
U_test: /usr/local/lib/libopencv_objdetect.so.4.5.5
U_test: /usr/local/lib/libopencv_photo.so.4.5.5
U_test: /usr/local/lib/libopencv_stitching.so.4.5.5
U_test: /usr/local/lib/libopencv_video.so.4.5.5
U_test: /usr/local/lib/libopencv_videoio.so.4.5.5
U_test: /usr/local/lib/libopencv_imgcodecs.so.4.5.5
U_test: /usr/local/lib/libopencv_dnn.so.4.5.5
U_test: /usr/local/lib/libopencv_calib3d.so.4.5.5
U_test: /usr/local/lib/libopencv_features2d.so.4.5.5
U_test: /usr/local/lib/libopencv_flann.so.4.5.5
U_test: /usr/local/lib/libopencv_imgproc.so.4.5.5
U_test: /usr/local/lib/libopencv_core.so.4.5.5
U_test: CMakeFiles/U_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ww/opencv/U_test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable U_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/U_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/U_test.dir/build: U_test
.PHONY : CMakeFiles/U_test.dir/build

CMakeFiles/U_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/U_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/U_test.dir/clean

CMakeFiles/U_test.dir/depend:
	cd /home/ww/opencv/U_test && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ww/opencv/U_test /home/ww/opencv/U_test /home/ww/opencv/U_test /home/ww/opencv/U_test /home/ww/opencv/U_test/CMakeFiles/U_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/U_test.dir/depend

