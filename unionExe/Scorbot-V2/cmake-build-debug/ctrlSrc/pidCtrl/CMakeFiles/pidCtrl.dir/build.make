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
include ctrlSrc/pidCtrl/CMakeFiles/pidCtrl.dir/depend.make

# Include the progress variables for this target.
include ctrlSrc/pidCtrl/CMakeFiles/pidCtrl.dir/progress.make

# Include the compile flags for this target's objects.
include ctrlSrc/pidCtrl/CMakeFiles/pidCtrl.dir/flags.make

ctrlSrc/pidCtrl/CMakeFiles/pidCtrl.dir/PIDScorbot.cpp.o: ctrlSrc/pidCtrl/CMakeFiles/pidCtrl.dir/flags.make
ctrlSrc/pidCtrl/CMakeFiles/pidCtrl.dir/PIDScorbot.cpp.o: ../ctrlSrc/pidCtrl/PIDScorbot.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object ctrlSrc/pidCtrl/CMakeFiles/pidCtrl.dir/PIDScorbot.cpp.o"
	cd /home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/ctrlSrc/pidCtrl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pidCtrl.dir/PIDScorbot.cpp.o -c /home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/ctrlSrc/pidCtrl/PIDScorbot.cpp

ctrlSrc/pidCtrl/CMakeFiles/pidCtrl.dir/PIDScorbot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pidCtrl.dir/PIDScorbot.cpp.i"
	cd /home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/ctrlSrc/pidCtrl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/ctrlSrc/pidCtrl/PIDScorbot.cpp > CMakeFiles/pidCtrl.dir/PIDScorbot.cpp.i

ctrlSrc/pidCtrl/CMakeFiles/pidCtrl.dir/PIDScorbot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pidCtrl.dir/PIDScorbot.cpp.s"
	cd /home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/ctrlSrc/pidCtrl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/ctrlSrc/pidCtrl/PIDScorbot.cpp -o CMakeFiles/pidCtrl.dir/PIDScorbot.cpp.s

# Object files for target pidCtrl
pidCtrl_OBJECTS = \
"CMakeFiles/pidCtrl.dir/PIDScorbot.cpp.o"

# External object files for target pidCtrl
pidCtrl_EXTERNAL_OBJECTS =

ctrlSrc/pidCtrl/libpidCtrl.a: ctrlSrc/pidCtrl/CMakeFiles/pidCtrl.dir/PIDScorbot.cpp.o
ctrlSrc/pidCtrl/libpidCtrl.a: ctrlSrc/pidCtrl/CMakeFiles/pidCtrl.dir/build.make
ctrlSrc/pidCtrl/libpidCtrl.a: ctrlSrc/pidCtrl/CMakeFiles/pidCtrl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libpidCtrl.a"
	cd /home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/ctrlSrc/pidCtrl && $(CMAKE_COMMAND) -P CMakeFiles/pidCtrl.dir/cmake_clean_target.cmake
	cd /home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/ctrlSrc/pidCtrl && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pidCtrl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ctrlSrc/pidCtrl/CMakeFiles/pidCtrl.dir/build: ctrlSrc/pidCtrl/libpidCtrl.a

.PHONY : ctrlSrc/pidCtrl/CMakeFiles/pidCtrl.dir/build

ctrlSrc/pidCtrl/CMakeFiles/pidCtrl.dir/clean:
	cd /home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/ctrlSrc/pidCtrl && $(CMAKE_COMMAND) -P CMakeFiles/pidCtrl.dir/cmake_clean.cmake
.PHONY : ctrlSrc/pidCtrl/CMakeFiles/pidCtrl.dir/clean

ctrlSrc/pidCtrl/CMakeFiles/pidCtrl.dir/depend:
	cd /home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2 /home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/ctrlSrc/pidCtrl /home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug /home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/ctrlSrc/pidCtrl /home/alfyhack/Documenti/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/ctrlSrc/pidCtrl/CMakeFiles/pidCtrl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ctrlSrc/pidCtrl/CMakeFiles/pidCtrl.dir/depend

