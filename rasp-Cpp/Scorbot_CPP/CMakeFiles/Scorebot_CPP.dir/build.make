# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alfy/Documents/Scorbot-CA/rasp-Cpp/Scorbot_CPP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alfy/Documents/Scorbot-CA/rasp-Cpp/Scorbot_CPP

# Include any dependencies generated for this target.
include CMakeFiles/Scorebot_CPP.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Scorebot_CPP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Scorebot_CPP.dir/flags.make

CMakeFiles/Scorebot_CPP.dir/main.cpp.o: CMakeFiles/Scorebot_CPP.dir/flags.make
CMakeFiles/Scorebot_CPP.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alfy/Documents/Scorbot-CA/rasp-Cpp/Scorbot_CPP/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Scorebot_CPP.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Scorebot_CPP.dir/main.cpp.o -c /home/alfy/Documents/Scorbot-CA/rasp-Cpp/Scorbot_CPP/main.cpp

CMakeFiles/Scorebot_CPP.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Scorebot_CPP.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alfy/Documents/Scorbot-CA/rasp-Cpp/Scorbot_CPP/main.cpp > CMakeFiles/Scorebot_CPP.dir/main.cpp.i

CMakeFiles/Scorebot_CPP.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Scorebot_CPP.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alfy/Documents/Scorbot-CA/rasp-Cpp/Scorbot_CPP/main.cpp -o CMakeFiles/Scorebot_CPP.dir/main.cpp.s

CMakeFiles/Scorebot_CPP.dir/SPILib/spisend.cpp.o: CMakeFiles/Scorebot_CPP.dir/flags.make
CMakeFiles/Scorebot_CPP.dir/SPILib/spisend.cpp.o: SPILib/spisend.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alfy/Documents/Scorbot-CA/rasp-Cpp/Scorbot_CPP/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Scorebot_CPP.dir/SPILib/spisend.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Scorebot_CPP.dir/SPILib/spisend.cpp.o -c /home/alfy/Documents/Scorbot-CA/rasp-Cpp/Scorbot_CPP/SPILib/spisend.cpp

CMakeFiles/Scorebot_CPP.dir/SPILib/spisend.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Scorebot_CPP.dir/SPILib/spisend.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alfy/Documents/Scorbot-CA/rasp-Cpp/Scorbot_CPP/SPILib/spisend.cpp > CMakeFiles/Scorebot_CPP.dir/SPILib/spisend.cpp.i

CMakeFiles/Scorebot_CPP.dir/SPILib/spisend.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Scorebot_CPP.dir/SPILib/spisend.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alfy/Documents/Scorbot-CA/rasp-Cpp/Scorbot_CPP/SPILib/spisend.cpp -o CMakeFiles/Scorebot_CPP.dir/SPILib/spisend.cpp.s

# Object files for target Scorebot_CPP
Scorebot_CPP_OBJECTS = \
"CMakeFiles/Scorebot_CPP.dir/main.cpp.o" \
"CMakeFiles/Scorebot_CPP.dir/SPILib/spisend.cpp.o"

# External object files for target Scorebot_CPP
Scorebot_CPP_EXTERNAL_OBJECTS =

Scorebot_CPP: CMakeFiles/Scorebot_CPP.dir/main.cpp.o
Scorebot_CPP: CMakeFiles/Scorebot_CPP.dir/SPILib/spisend.cpp.o
Scorebot_CPP: CMakeFiles/Scorebot_CPP.dir/build.make
Scorebot_CPP: CMakeFiles/Scorebot_CPP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alfy/Documents/Scorbot-CA/rasp-Cpp/Scorbot_CPP/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Scorebot_CPP"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Scorebot_CPP.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Scorebot_CPP.dir/build: Scorebot_CPP

.PHONY : CMakeFiles/Scorebot_CPP.dir/build

CMakeFiles/Scorebot_CPP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Scorebot_CPP.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Scorebot_CPP.dir/clean

CMakeFiles/Scorebot_CPP.dir/depend:
	cd /home/alfy/Documents/Scorbot-CA/rasp-Cpp/Scorbot_CPP && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alfy/Documents/Scorbot-CA/rasp-Cpp/Scorbot_CPP /home/alfy/Documents/Scorbot-CA/rasp-Cpp/Scorbot_CPP /home/alfy/Documents/Scorbot-CA/rasp-Cpp/Scorbot_CPP /home/alfy/Documents/Scorbot-CA/rasp-Cpp/Scorbot_CPP /home/alfy/Documents/Scorbot-CA/rasp-Cpp/Scorbot_CPP/CMakeFiles/Scorebot_CPP.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Scorebot_CPP.dir/depend

