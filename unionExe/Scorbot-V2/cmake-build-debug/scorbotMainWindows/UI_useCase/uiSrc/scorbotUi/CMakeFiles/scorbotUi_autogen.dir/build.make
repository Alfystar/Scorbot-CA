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

# Utility rule file for scorbotUi_autogen.

# Include the progress variables for this target.
include scorbotMainWindows/UI_useCase/uiSrc/scorbotUi/CMakeFiles/scorbotUi_autogen.dir/progress.make

scorbotMainWindows/UI_useCase/uiSrc/scorbotUi/CMakeFiles/scorbotUi_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/alfyhack/Scrivania/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target scorbotUi"
	cd /home/alfyhack/Scrivania/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/scorbotMainWindows/UI_useCase/uiSrc/scorbotUi && /home/alfyhack/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/193.6911.21/bin/cmake/linux/bin/cmake -E cmake_autogen /home/alfyhack/Scrivania/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/scorbotMainWindows/UI_useCase/uiSrc/scorbotUi/CMakeFiles/scorbotUi_autogen.dir/AutogenInfo.cmake Debug

scorbotUi_autogen: scorbotMainWindows/UI_useCase/uiSrc/scorbotUi/CMakeFiles/scorbotUi_autogen
scorbotUi_autogen: scorbotMainWindows/UI_useCase/uiSrc/scorbotUi/CMakeFiles/scorbotUi_autogen.dir/build.make

.PHONY : scorbotUi_autogen

# Rule to build all files generated by this target.
scorbotMainWindows/UI_useCase/uiSrc/scorbotUi/CMakeFiles/scorbotUi_autogen.dir/build: scorbotUi_autogen

.PHONY : scorbotMainWindows/UI_useCase/uiSrc/scorbotUi/CMakeFiles/scorbotUi_autogen.dir/build

scorbotMainWindows/UI_useCase/uiSrc/scorbotUi/CMakeFiles/scorbotUi_autogen.dir/clean:
	cd /home/alfyhack/Scrivania/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/scorbotMainWindows/UI_useCase/uiSrc/scorbotUi && $(CMAKE_COMMAND) -P CMakeFiles/scorbotUi_autogen.dir/cmake_clean.cmake
.PHONY : scorbotMainWindows/UI_useCase/uiSrc/scorbotUi/CMakeFiles/scorbotUi_autogen.dir/clean

scorbotMainWindows/UI_useCase/uiSrc/scorbotUi/CMakeFiles/scorbotUi_autogen.dir/depend:
	cd /home/alfyhack/Scrivania/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alfyhack/Scrivania/Scorbot-CA/unionExe/Scorbot-V2 /home/alfyhack/Scrivania/Scorbot-CA/unionExe/Scorbot-V2/scorbotMainWindows/UI_useCase/uiSrc/scorbotUi /home/alfyhack/Scrivania/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug /home/alfyhack/Scrivania/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/scorbotMainWindows/UI_useCase/uiSrc/scorbotUi /home/alfyhack/Scrivania/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/scorbotMainWindows/UI_useCase/uiSrc/scorbotUi/CMakeFiles/scorbotUi_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : scorbotMainWindows/UI_useCase/uiSrc/scorbotUi/CMakeFiles/scorbotUi_autogen.dir/depend

