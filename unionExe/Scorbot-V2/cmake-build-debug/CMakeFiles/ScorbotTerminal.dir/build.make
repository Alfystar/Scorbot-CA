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
CMAKE_SOURCE_DIR = /home/alfystar/Documenti/Scorbot-CA/unionExe/Scorbot-V2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alfystar/Documenti/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ScorbotTerminal.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ScorbotTerminal.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ScorbotTerminal.dir/flags.make

CMakeFiles/ScorbotTerminal.dir/main.cpp.o: CMakeFiles/ScorbotTerminal.dir/flags.make
CMakeFiles/ScorbotTerminal.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alfystar/Documenti/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ScorbotTerminal.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ScorbotTerminal.dir/main.cpp.o -c /home/alfystar/Documenti/Scorbot-CA/unionExe/Scorbot-V2/main.cpp

CMakeFiles/ScorbotTerminal.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ScorbotTerminal.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alfystar/Documenti/Scorbot-CA/unionExe/Scorbot-V2/main.cpp > CMakeFiles/ScorbotTerminal.dir/main.cpp.i

CMakeFiles/ScorbotTerminal.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ScorbotTerminal.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alfystar/Documenti/Scorbot-CA/unionExe/Scorbot-V2/main.cpp -o CMakeFiles/ScorbotTerminal.dir/main.cpp.s

# Object files for target ScorbotTerminal
ScorbotTerminal_OBJECTS = \
"CMakeFiles/ScorbotTerminal.dir/main.cpp.o"

# External object files for target ScorbotTerminal
ScorbotTerminal_EXTERNAL_OBJECTS =

ScorbotTerminal: CMakeFiles/ScorbotTerminal.dir/main.cpp.o
ScorbotTerminal: CMakeFiles/ScorbotTerminal.dir/build.make
ScorbotTerminal: scorbotMainWindows/libscorbotMainWindows.a
ScorbotTerminal: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.14.1
ScorbotTerminal: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.14.1
ScorbotTerminal: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.14.1
ScorbotTerminal: scorbotMainWindows/UI_useCase/libUI_useCase.a
ScorbotTerminal: /usr/lib/x86_64-linux-gnu/libQt5PrintSupport.so.5.14.1
ScorbotTerminal: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.14.1
ScorbotTerminal: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.14.1
ScorbotTerminal: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.14.1
ScorbotTerminal: scorbotMainWindows/UI_useCase/uiSrc/scorbotUi/libscorbotUi.a
ScorbotTerminal: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.14.1
ScorbotTerminal: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.14.1
ScorbotTerminal: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.14.1
ScorbotTerminal: boardComSrc/UtilityScorbot/libscoreUtiliy.a
ScorbotTerminal: boardComSrc/UartSubSystem/libUartSubSystem.a
ScorbotTerminal: boardComSrc/Common-src/uartDriver/libuartDriver.a
ScorbotTerminal: boardComSrc/Common-src/circularBuffer/libcircularBuffer.a
ScorbotTerminal: ctrlSrc/pidCtrl/libpidCtrl.a
ScorbotTerminal: boardComSrc/Common-src/DataTransfertPackge/libdataTransfert.a
ScorbotTerminal: boardComSrc/Common-src/timeOp/libtimeOp.a
ScorbotTerminal: CMakeFiles/ScorbotTerminal.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alfystar/Documenti/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ScorbotTerminal"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ScorbotTerminal.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ScorbotTerminal.dir/build: ScorbotTerminal

.PHONY : CMakeFiles/ScorbotTerminal.dir/build

CMakeFiles/ScorbotTerminal.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ScorbotTerminal.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ScorbotTerminal.dir/clean

CMakeFiles/ScorbotTerminal.dir/depend:
	cd /home/alfystar/Documenti/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alfystar/Documenti/Scorbot-CA/unionExe/Scorbot-V2 /home/alfystar/Documenti/Scorbot-CA/unionExe/Scorbot-V2 /home/alfystar/Documenti/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug /home/alfystar/Documenti/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug /home/alfystar/Documenti/Scorbot-CA/unionExe/Scorbot-V2/cmake-build-debug/CMakeFiles/ScorbotTerminal.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ScorbotTerminal.dir/depend

