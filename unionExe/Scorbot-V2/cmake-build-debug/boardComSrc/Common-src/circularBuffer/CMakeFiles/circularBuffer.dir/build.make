# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/alfyhack/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/193.5662.56/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/alfyhack/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/193.5662.56/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug

# Include any dependencies generated for this target.
include boardComSrc/Common-src/circularBuffer/CMakeFiles/circularBuffer.dir/depend.make

# Include the progress variables for this target.
include boardComSrc/Common-src/circularBuffer/CMakeFiles/circularBuffer.dir/progress.make

# Include the compile flags for this target's objects.
include boardComSrc/Common-src/circularBuffer/CMakeFiles/circularBuffer.dir/flags.make

boardComSrc/Common-src/circularBuffer/CMakeFiles/circularBuffer.dir/CircularBuffer.cpp.o: boardComSrc/Common-src/circularBuffer/CMakeFiles/circularBuffer.dir/flags.make
boardComSrc/Common-src/circularBuffer/CMakeFiles/circularBuffer.dir/CircularBuffer.cpp.o: ../boardComSrc/Common-src/circularBuffer/CircularBuffer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object boardComSrc/Common-src/circularBuffer/CMakeFiles/circularBuffer.dir/CircularBuffer.cpp.o"
	cd /home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/boardComSrc/Common-src/circularBuffer && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/circularBuffer.dir/CircularBuffer.cpp.o -c /home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/boardComSrc/Common-src/circularBuffer/CircularBuffer.cpp

boardComSrc/Common-src/circularBuffer/CMakeFiles/circularBuffer.dir/CircularBuffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/circularBuffer.dir/CircularBuffer.cpp.i"
	cd /home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/boardComSrc/Common-src/circularBuffer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/boardComSrc/Common-src/circularBuffer/CircularBuffer.cpp > CMakeFiles/circularBuffer.dir/CircularBuffer.cpp.i

boardComSrc/Common-src/circularBuffer/CMakeFiles/circularBuffer.dir/CircularBuffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/circularBuffer.dir/CircularBuffer.cpp.s"
	cd /home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/boardComSrc/Common-src/circularBuffer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/boardComSrc/Common-src/circularBuffer/CircularBuffer.cpp -o CMakeFiles/circularBuffer.dir/CircularBuffer.cpp.s

# Object files for target circularBuffer
circularBuffer_OBJECTS = \
"CMakeFiles/circularBuffer.dir/CircularBuffer.cpp.o"

# External object files for target circularBuffer
circularBuffer_EXTERNAL_OBJECTS =

boardComSrc/Common-src/circularBuffer/libcircularBuffer.a: boardComSrc/Common-src/circularBuffer/CMakeFiles/circularBuffer.dir/CircularBuffer.cpp.o
boardComSrc/Common-src/circularBuffer/libcircularBuffer.a: boardComSrc/Common-src/circularBuffer/CMakeFiles/circularBuffer.dir/build.make
boardComSrc/Common-src/circularBuffer/libcircularBuffer.a: boardComSrc/Common-src/circularBuffer/CMakeFiles/circularBuffer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libcircularBuffer.a"
	cd /home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/boardComSrc/Common-src/circularBuffer && $(CMAKE_COMMAND) -P CMakeFiles/circularBuffer.dir/cmake_clean_target.cmake
	cd /home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/boardComSrc/Common-src/circularBuffer && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/circularBuffer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
boardComSrc/Common-src/circularBuffer/CMakeFiles/circularBuffer.dir/build: boardComSrc/Common-src/circularBuffer/libcircularBuffer.a

.PHONY : boardComSrc/Common-src/circularBuffer/CMakeFiles/circularBuffer.dir/build

boardComSrc/Common-src/circularBuffer/CMakeFiles/circularBuffer.dir/clean:
	cd /home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/boardComSrc/Common-src/circularBuffer && $(CMAKE_COMMAND) -P CMakeFiles/circularBuffer.dir/cmake_clean.cmake
.PHONY : boardComSrc/Common-src/circularBuffer/CMakeFiles/circularBuffer.dir/clean

boardComSrc/Common-src/circularBuffer/CMakeFiles/circularBuffer.dir/depend:
	cd /home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2 /home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/boardComSrc/Common-src/circularBuffer /home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug /home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/boardComSrc/Common-src/circularBuffer /home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/boardComSrc/Common-src/circularBuffer/CMakeFiles/circularBuffer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : boardComSrc/Common-src/circularBuffer/CMakeFiles/circularBuffer.dir/depend

