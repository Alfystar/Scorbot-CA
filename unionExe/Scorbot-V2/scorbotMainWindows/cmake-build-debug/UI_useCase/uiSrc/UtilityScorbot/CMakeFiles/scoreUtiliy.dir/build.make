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
CMAKE_COMMAND = /home/alfystar/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/193.6911.21/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/alfystar/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/193.6911.21/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alfystar/Documenti/Scorbot-CA/unionExe/Scorbot-V2/scorbotMainWindows

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alfystar/Documenti/Scorbot-CA/unionExe/Scorbot-V2/scorbotMainWindows/cmake-build-debug

# Include any dependencies generated for this target.
include UI_useCase/uiSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/depend.make

# Include the progress variables for this target.
include UI_useCase/uiSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/progress.make

# Include the compile flags for this target's objects.
include UI_useCase/uiSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/flags.make

UI_useCase/uiSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/ScorCalc.o: UI_useCase/uiSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/flags.make
UI_useCase/uiSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/ScorCalc.o: ../UI_useCase/uiSrc/UtilityScorbot/ScorCalc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alfystar/Documenti/Scorbot-CA/unionExe/Scorbot-V2/scorbotMainWindows/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object UI_useCase/uiSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/ScorCalc.o"
	cd /home/alfystar/Documenti/Scorbot-CA/unionExe/Scorbot-V2/scorbotMainWindows/cmake-build-debug/UI_useCase/uiSrc/UtilityScorbot && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/scoreUtiliy.dir/ScorCalc.o -c /home/alfystar/Documenti/Scorbot-CA/unionExe/Scorbot-V2/scorbotMainWindows/UI_useCase/uiSrc/UtilityScorbot/ScorCalc.cpp

UI_useCase/uiSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/ScorCalc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/scoreUtiliy.dir/ScorCalc.i"
	cd /home/alfystar/Documenti/Scorbot-CA/unionExe/Scorbot-V2/scorbotMainWindows/cmake-build-debug/UI_useCase/uiSrc/UtilityScorbot && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alfystar/Documenti/Scorbot-CA/unionExe/Scorbot-V2/scorbotMainWindows/UI_useCase/uiSrc/UtilityScorbot/ScorCalc.cpp > CMakeFiles/scoreUtiliy.dir/ScorCalc.i

UI_useCase/uiSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/ScorCalc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/scoreUtiliy.dir/ScorCalc.s"
	cd /home/alfystar/Documenti/Scorbot-CA/unionExe/Scorbot-V2/scorbotMainWindows/cmake-build-debug/UI_useCase/uiSrc/UtilityScorbot && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alfystar/Documenti/Scorbot-CA/unionExe/Scorbot-V2/scorbotMainWindows/UI_useCase/uiSrc/UtilityScorbot/ScorCalc.cpp -o CMakeFiles/scoreUtiliy.dir/ScorCalc.s

# Object files for target scoreUtiliy
scoreUtiliy_OBJECTS = \
"CMakeFiles/scoreUtiliy.dir/ScorCalc.o"

# External object files for target scoreUtiliy
scoreUtiliy_EXTERNAL_OBJECTS =

UI_useCase/uiSrc/UtilityScorbot/libscoreUtiliy.a: UI_useCase/uiSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/ScorCalc.o
UI_useCase/uiSrc/UtilityScorbot/libscoreUtiliy.a: UI_useCase/uiSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/build.make
UI_useCase/uiSrc/UtilityScorbot/libscoreUtiliy.a: UI_useCase/uiSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alfystar/Documenti/Scorbot-CA/unionExe/Scorbot-V2/scorbotMainWindows/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libscoreUtiliy.a"
	cd /home/alfystar/Documenti/Scorbot-CA/unionExe/Scorbot-V2/scorbotMainWindows/cmake-build-debug/UI_useCase/uiSrc/UtilityScorbot && $(CMAKE_COMMAND) -P CMakeFiles/scoreUtiliy.dir/cmake_clean_target.cmake
	cd /home/alfystar/Documenti/Scorbot-CA/unionExe/Scorbot-V2/scorbotMainWindows/cmake-build-debug/UI_useCase/uiSrc/UtilityScorbot && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/scoreUtiliy.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
UI_useCase/uiSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/build: UI_useCase/uiSrc/UtilityScorbot/libscoreUtiliy.a

.PHONY : UI_useCase/uiSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/build

UI_useCase/uiSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/clean:
	cd /home/alfystar/Documenti/Scorbot-CA/unionExe/Scorbot-V2/scorbotMainWindows/cmake-build-debug/UI_useCase/uiSrc/UtilityScorbot && $(CMAKE_COMMAND) -P CMakeFiles/scoreUtiliy.dir/cmake_clean.cmake
.PHONY : UI_useCase/uiSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/clean

UI_useCase/uiSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/depend:
	cd /home/alfystar/Documenti/Scorbot-CA/unionExe/Scorbot-V2/scorbotMainWindows/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alfystar/Documenti/Scorbot-CA/unionExe/Scorbot-V2/scorbotMainWindows /home/alfystar/Documenti/Scorbot-CA/unionExe/Scorbot-V2/scorbotMainWindows/UI_useCase/uiSrc/UtilityScorbot /home/alfystar/Documenti/Scorbot-CA/unionExe/Scorbot-V2/scorbotMainWindows/cmake-build-debug /home/alfystar/Documenti/Scorbot-CA/unionExe/Scorbot-V2/scorbotMainWindows/cmake-build-debug/UI_useCase/uiSrc/UtilityScorbot /home/alfystar/Documenti/Scorbot-CA/unionExe/Scorbot-V2/scorbotMainWindows/cmake-build-debug/UI_useCase/uiSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : UI_useCase/uiSrc/UtilityScorbot/CMakeFiles/scoreUtiliy.dir/depend

