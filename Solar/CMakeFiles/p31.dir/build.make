# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.9.5/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.9.5/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/heoju/ComputerGraphics/practice

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/heoju/ComputerGraphics/practice

# Include any dependencies generated for this target.
include CMakeFiles/p31.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/p31.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/p31.dir/flags.make

CMakeFiles/p31.dir/practice3_1.cpp.o: CMakeFiles/p31.dir/flags.make
CMakeFiles/p31.dir/practice3_1.cpp.o: practice3_1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/heoju/ComputerGraphics/practice/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/p31.dir/practice3_1.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/p31.dir/practice3_1.cpp.o -c /Users/heoju/ComputerGraphics/practice/practice3_1.cpp

CMakeFiles/p31.dir/practice3_1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/p31.dir/practice3_1.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/heoju/ComputerGraphics/practice/practice3_1.cpp > CMakeFiles/p31.dir/practice3_1.cpp.i

CMakeFiles/p31.dir/practice3_1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/p31.dir/practice3_1.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/heoju/ComputerGraphics/practice/practice3_1.cpp -o CMakeFiles/p31.dir/practice3_1.cpp.s

CMakeFiles/p31.dir/practice3_1.cpp.o.requires:

.PHONY : CMakeFiles/p31.dir/practice3_1.cpp.o.requires

CMakeFiles/p31.dir/practice3_1.cpp.o.provides: CMakeFiles/p31.dir/practice3_1.cpp.o.requires
	$(MAKE) -f CMakeFiles/p31.dir/build.make CMakeFiles/p31.dir/practice3_1.cpp.o.provides.build
.PHONY : CMakeFiles/p31.dir/practice3_1.cpp.o.provides

CMakeFiles/p31.dir/practice3_1.cpp.o.provides.build: CMakeFiles/p31.dir/practice3_1.cpp.o


# Object files for target p31
p31_OBJECTS = \
"CMakeFiles/p31.dir/practice3_1.cpp.o"

# External object files for target p31
p31_EXTERNAL_OBJECTS =

p31: CMakeFiles/p31.dir/practice3_1.cpp.o
p31: CMakeFiles/p31.dir/build.make
p31: /usr/local/lib/libglfw.dylib
p31: /usr/local/lib/libfreeimage.dylib
p31: CMakeFiles/p31.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/heoju/ComputerGraphics/practice/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable p31"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/p31.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/p31.dir/build: p31

.PHONY : CMakeFiles/p31.dir/build

CMakeFiles/p31.dir/requires: CMakeFiles/p31.dir/practice3_1.cpp.o.requires

.PHONY : CMakeFiles/p31.dir/requires

CMakeFiles/p31.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/p31.dir/cmake_clean.cmake
.PHONY : CMakeFiles/p31.dir/clean

CMakeFiles/p31.dir/depend:
	cd /Users/heoju/ComputerGraphics/practice && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/heoju/ComputerGraphics/practice /Users/heoju/ComputerGraphics/practice /Users/heoju/ComputerGraphics/practice /Users/heoju/ComputerGraphics/practice /Users/heoju/ComputerGraphics/practice/CMakeFiles/p31.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/p31.dir/depend
