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
CMAKE_COMMAND = /home/alfyhack/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/193.6911.21/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/alfyhack/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/193.6911.21/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alfyhack/Scrivania/Scorbot-CA/unionExe/Scorbot-V2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alfyhack/Scrivania/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug

# Include any dependencies generated for this target.
include boardComSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/depend.make

# Include the progress variables for this target.
include boardComSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/progress.make

# Include the compile flags for this target's objects.
include boardComSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/flags.make

boardComSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/ScorCalc.cpp.o: boardComSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/flags.make
boardComSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/ScorCalc.cpp.o: ../boardComSrc/UtilityScorbot/ScorCalc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alfyhack/Scrivania/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object boardComSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/ScorCalc.cpp.o"
	cd /home/alfyhack/Scrivania/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/boardComSrc/UtilityScorbot && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/scoreUtiliy.dir/ScorCalc.cpp.o -c /home/alfyhack/Scrivania/Scorbot-CA/unionExe/Scorbot-V2/boardComSrc/UtilityScorbot/ScorCalc.cpp

boardComSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/ScorCalc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/scoreUtiliy.dir/ScorCalc.cpp.i"
	cd /home/alfyhack/Scrivania/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/boardComSrc/UtilityScorbot && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alfyhack/Scrivania/Scorbot-CA/unionExe/Scorbot-V2/boardComSrc/UtilityScorbot/ScorCalc.cpp > CMakeFiles/scoreUtiliy.dir/ScorCalc.cpp.i

boardComSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/ScorCalc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/scoreUtiliy.dir/ScorCalc.cpp.s"
	cd /home/alfyhack/Scrivania/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/boardComSrc/UtilityScorbot && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alfyhack/Scrivania/Scorbot-CA/unionExe/Scorbot-V2/boardComSrc/UtilityScorbot/ScorCalc.cpp -o CMakeFiles/scoreUtiliy.dir/ScorCalc.cpp.s

# Object files for target scoreUtiliy
scoreUtiliy_OBJECTS = \
"CMakeFiles/scoreUtiliy.dir/ScorCalc.cpp.o"

# External object files for target scoreUtiliy
scoreUtiliy_EXTERNAL_OBJECTS =

boardComSrc/UtilityScorbot/libscoreUtiliy.a: boardComSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/ScorCalc.cpp.o
boardComSrc/UtilityScorbot/libscoreUtiliy.a: boardComSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/build.make
boardComSrc/UtilityScorbot/libscoreUtiliy.a: boardComSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alfyhack/Scrivania/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libscoreUtiliy.a"
	cd /home/alfyhack/Scrivania/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/boardComSrc/UtilityScorbot && $(CMAKE_COMMAND) -P CMakeFiles/scoreUtiliy.dir/cmake_clean_target.cmake
	cd /home/alfyhack/Scrivania/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/boardComSrc/UtilityScorbot && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/scoreUtiliy.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
boardComSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/build: boardComSrc/UtilityScorbot/libscoreUtiliy.a

.PHONY : boardComSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/build

boardComSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/clean:
	cd /home/alfyhack/Scrivania/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/boardComSrc/UtilityScorbot && $(CMAKE_COMMAND) -P CMakeFiles/scoreUtiliy.dir/cmake_clean.cmake
.PHONY : boardComSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/clean

boardComSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/depend:
	cd /home/alfyhack/Scrivania/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alfyhack/Scrivania/Scorbot-CA/unionExe/Scorbot-V2 /home/alfyhack/Scrivania/Scorbot-CA/unionExe/Scorbot-V2/boardComSrc/UtilityScorbot /home/alfyhack/Scrivania/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug /home/alfyhack/Scrivania/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/boardComSrc/UtilityScorbot /home/alfyhack/Scrivania/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/boardComSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : boardComSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/depend

