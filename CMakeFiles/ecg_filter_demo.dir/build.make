# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/heath/ENG5059P

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/heath/ENG5059P

# Include any dependencies generated for this target.
include CMakeFiles/ecg_filter_demo.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ecg_filter_demo.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ecg_filter_demo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ecg_filter_demo.dir/flags.make

CMakeFiles/ecg_filter_demo.dir/ecg_filter_demo.cpp.o: CMakeFiles/ecg_filter_demo.dir/flags.make
CMakeFiles/ecg_filter_demo.dir/ecg_filter_demo.cpp.o: ecg_filter_demo.cpp
CMakeFiles/ecg_filter_demo.dir/ecg_filter_demo.cpp.o: CMakeFiles/ecg_filter_demo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/heath/ENG5059P/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ecg_filter_demo.dir/ecg_filter_demo.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ecg_filter_demo.dir/ecg_filter_demo.cpp.o -MF CMakeFiles/ecg_filter_demo.dir/ecg_filter_demo.cpp.o.d -o CMakeFiles/ecg_filter_demo.dir/ecg_filter_demo.cpp.o -c /home/heath/ENG5059P/ecg_filter_demo.cpp

CMakeFiles/ecg_filter_demo.dir/ecg_filter_demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ecg_filter_demo.dir/ecg_filter_demo.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/heath/ENG5059P/ecg_filter_demo.cpp > CMakeFiles/ecg_filter_demo.dir/ecg_filter_demo.cpp.i

CMakeFiles/ecg_filter_demo.dir/ecg_filter_demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ecg_filter_demo.dir/ecg_filter_demo.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/heath/ENG5059P/ecg_filter_demo.cpp -o CMakeFiles/ecg_filter_demo.dir/ecg_filter_demo.cpp.s

CMakeFiles/ecg_filter_demo.dir/ecg_filter.cpp.o: CMakeFiles/ecg_filter_demo.dir/flags.make
CMakeFiles/ecg_filter_demo.dir/ecg_filter.cpp.o: ecg_filter.cpp
CMakeFiles/ecg_filter_demo.dir/ecg_filter.cpp.o: CMakeFiles/ecg_filter_demo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/heath/ENG5059P/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ecg_filter_demo.dir/ecg_filter.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ecg_filter_demo.dir/ecg_filter.cpp.o -MF CMakeFiles/ecg_filter_demo.dir/ecg_filter.cpp.o.d -o CMakeFiles/ecg_filter_demo.dir/ecg_filter.cpp.o -c /home/heath/ENG5059P/ecg_filter.cpp

CMakeFiles/ecg_filter_demo.dir/ecg_filter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ecg_filter_demo.dir/ecg_filter.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/heath/ENG5059P/ecg_filter.cpp > CMakeFiles/ecg_filter_demo.dir/ecg_filter.cpp.i

CMakeFiles/ecg_filter_demo.dir/ecg_filter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ecg_filter_demo.dir/ecg_filter.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/heath/ENG5059P/ecg_filter.cpp -o CMakeFiles/ecg_filter_demo.dir/ecg_filter.cpp.s

# Object files for target ecg_filter_demo
ecg_filter_demo_OBJECTS = \
"CMakeFiles/ecg_filter_demo.dir/ecg_filter_demo.cpp.o" \
"CMakeFiles/ecg_filter_demo.dir/ecg_filter.cpp.o"

# External object files for target ecg_filter_demo
ecg_filter_demo_EXTERNAL_OBJECTS =

ecg_filter_demo: CMakeFiles/ecg_filter_demo.dir/ecg_filter_demo.cpp.o
ecg_filter_demo: CMakeFiles/ecg_filter_demo.dir/ecg_filter.cpp.o
ecg_filter_demo: CMakeFiles/ecg_filter_demo.dir/build.make
ecg_filter_demo: DNF/libCLDL.a
ecg_filter_demo: CMakeFiles/ecg_filter_demo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/heath/ENG5059P/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ecg_filter_demo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ecg_filter_demo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ecg_filter_demo.dir/build: ecg_filter_demo
.PHONY : CMakeFiles/ecg_filter_demo.dir/build

CMakeFiles/ecg_filter_demo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ecg_filter_demo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ecg_filter_demo.dir/clean

CMakeFiles/ecg_filter_demo.dir/depend:
	cd /home/heath/ENG5059P && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/heath/ENG5059P /home/heath/ENG5059P /home/heath/ENG5059P /home/heath/ENG5059P /home/heath/ENG5059P/CMakeFiles/ecg_filter_demo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ecg_filter_demo.dir/depend
