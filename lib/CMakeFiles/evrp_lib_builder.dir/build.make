# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /snap/cmake/1288/bin/cmake

# The command to remove a file.
RM = /snap/cmake/1288/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hienvq/Desktop/Lab/EVRP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hienvq/Desktop/Lab/EVRP

# Include any dependencies generated for this target.
include lib/CMakeFiles/evrp_lib_builder.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/CMakeFiles/evrp_lib_builder.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/evrp_lib_builder.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/evrp_lib_builder.dir/flags.make

lib/CMakeFiles/evrp_lib_builder.dir/src/EVRP.cpp.o: lib/CMakeFiles/evrp_lib_builder.dir/flags.make
lib/CMakeFiles/evrp_lib_builder.dir/src/EVRP.cpp.o: lib/src/EVRP.cpp
lib/CMakeFiles/evrp_lib_builder.dir/src/EVRP.cpp.o: lib/CMakeFiles/evrp_lib_builder.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hienvq/Desktop/Lab/EVRP/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/CMakeFiles/evrp_lib_builder.dir/src/EVRP.cpp.o"
	cd /home/hienvq/Desktop/Lab/EVRP/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/CMakeFiles/evrp_lib_builder.dir/src/EVRP.cpp.o -MF CMakeFiles/evrp_lib_builder.dir/src/EVRP.cpp.o.d -o CMakeFiles/evrp_lib_builder.dir/src/EVRP.cpp.o -c /home/hienvq/Desktop/Lab/EVRP/lib/src/EVRP.cpp

lib/CMakeFiles/evrp_lib_builder.dir/src/EVRP.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/evrp_lib_builder.dir/src/EVRP.cpp.i"
	cd /home/hienvq/Desktop/Lab/EVRP/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hienvq/Desktop/Lab/EVRP/lib/src/EVRP.cpp > CMakeFiles/evrp_lib_builder.dir/src/EVRP.cpp.i

lib/CMakeFiles/evrp_lib_builder.dir/src/EVRP.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/evrp_lib_builder.dir/src/EVRP.cpp.s"
	cd /home/hienvq/Desktop/Lab/EVRP/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hienvq/Desktop/Lab/EVRP/lib/src/EVRP.cpp -o CMakeFiles/evrp_lib_builder.dir/src/EVRP.cpp.s

lib/CMakeFiles/evrp_lib_builder.dir/src/stats.cpp.o: lib/CMakeFiles/evrp_lib_builder.dir/flags.make
lib/CMakeFiles/evrp_lib_builder.dir/src/stats.cpp.o: lib/src/stats.cpp
lib/CMakeFiles/evrp_lib_builder.dir/src/stats.cpp.o: lib/CMakeFiles/evrp_lib_builder.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hienvq/Desktop/Lab/EVRP/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lib/CMakeFiles/evrp_lib_builder.dir/src/stats.cpp.o"
	cd /home/hienvq/Desktop/Lab/EVRP/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/CMakeFiles/evrp_lib_builder.dir/src/stats.cpp.o -MF CMakeFiles/evrp_lib_builder.dir/src/stats.cpp.o.d -o CMakeFiles/evrp_lib_builder.dir/src/stats.cpp.o -c /home/hienvq/Desktop/Lab/EVRP/lib/src/stats.cpp

lib/CMakeFiles/evrp_lib_builder.dir/src/stats.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/evrp_lib_builder.dir/src/stats.cpp.i"
	cd /home/hienvq/Desktop/Lab/EVRP/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hienvq/Desktop/Lab/EVRP/lib/src/stats.cpp > CMakeFiles/evrp_lib_builder.dir/src/stats.cpp.i

lib/CMakeFiles/evrp_lib_builder.dir/src/stats.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/evrp_lib_builder.dir/src/stats.cpp.s"
	cd /home/hienvq/Desktop/Lab/EVRP/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hienvq/Desktop/Lab/EVRP/lib/src/stats.cpp -o CMakeFiles/evrp_lib_builder.dir/src/stats.cpp.s

lib/CMakeFiles/evrp_lib_builder.dir/src/individual.cpp.o: lib/CMakeFiles/evrp_lib_builder.dir/flags.make
lib/CMakeFiles/evrp_lib_builder.dir/src/individual.cpp.o: lib/src/individual.cpp
lib/CMakeFiles/evrp_lib_builder.dir/src/individual.cpp.o: lib/CMakeFiles/evrp_lib_builder.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hienvq/Desktop/Lab/EVRP/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object lib/CMakeFiles/evrp_lib_builder.dir/src/individual.cpp.o"
	cd /home/hienvq/Desktop/Lab/EVRP/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/CMakeFiles/evrp_lib_builder.dir/src/individual.cpp.o -MF CMakeFiles/evrp_lib_builder.dir/src/individual.cpp.o.d -o CMakeFiles/evrp_lib_builder.dir/src/individual.cpp.o -c /home/hienvq/Desktop/Lab/EVRP/lib/src/individual.cpp

lib/CMakeFiles/evrp_lib_builder.dir/src/individual.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/evrp_lib_builder.dir/src/individual.cpp.i"
	cd /home/hienvq/Desktop/Lab/EVRP/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hienvq/Desktop/Lab/EVRP/lib/src/individual.cpp > CMakeFiles/evrp_lib_builder.dir/src/individual.cpp.i

lib/CMakeFiles/evrp_lib_builder.dir/src/individual.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/evrp_lib_builder.dir/src/individual.cpp.s"
	cd /home/hienvq/Desktop/Lab/EVRP/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hienvq/Desktop/Lab/EVRP/lib/src/individual.cpp -o CMakeFiles/evrp_lib_builder.dir/src/individual.cpp.s

lib/CMakeFiles/evrp_lib_builder.dir/src/HMAGS.cpp.o: lib/CMakeFiles/evrp_lib_builder.dir/flags.make
lib/CMakeFiles/evrp_lib_builder.dir/src/HMAGS.cpp.o: lib/src/HMAGS.cpp
lib/CMakeFiles/evrp_lib_builder.dir/src/HMAGS.cpp.o: lib/CMakeFiles/evrp_lib_builder.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hienvq/Desktop/Lab/EVRP/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object lib/CMakeFiles/evrp_lib_builder.dir/src/HMAGS.cpp.o"
	cd /home/hienvq/Desktop/Lab/EVRP/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/CMakeFiles/evrp_lib_builder.dir/src/HMAGS.cpp.o -MF CMakeFiles/evrp_lib_builder.dir/src/HMAGS.cpp.o.d -o CMakeFiles/evrp_lib_builder.dir/src/HMAGS.cpp.o -c /home/hienvq/Desktop/Lab/EVRP/lib/src/HMAGS.cpp

lib/CMakeFiles/evrp_lib_builder.dir/src/HMAGS.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/evrp_lib_builder.dir/src/HMAGS.cpp.i"
	cd /home/hienvq/Desktop/Lab/EVRP/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hienvq/Desktop/Lab/EVRP/lib/src/HMAGS.cpp > CMakeFiles/evrp_lib_builder.dir/src/HMAGS.cpp.i

lib/CMakeFiles/evrp_lib_builder.dir/src/HMAGS.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/evrp_lib_builder.dir/src/HMAGS.cpp.s"
	cd /home/hienvq/Desktop/Lab/EVRP/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hienvq/Desktop/Lab/EVRP/lib/src/HMAGS.cpp -o CMakeFiles/evrp_lib_builder.dir/src/HMAGS.cpp.s

lib/CMakeFiles/evrp_lib_builder.dir/src/SACO.cpp.o: lib/CMakeFiles/evrp_lib_builder.dir/flags.make
lib/CMakeFiles/evrp_lib_builder.dir/src/SACO.cpp.o: lib/src/SACO.cpp
lib/CMakeFiles/evrp_lib_builder.dir/src/SACO.cpp.o: lib/CMakeFiles/evrp_lib_builder.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hienvq/Desktop/Lab/EVRP/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object lib/CMakeFiles/evrp_lib_builder.dir/src/SACO.cpp.o"
	cd /home/hienvq/Desktop/Lab/EVRP/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/CMakeFiles/evrp_lib_builder.dir/src/SACO.cpp.o -MF CMakeFiles/evrp_lib_builder.dir/src/SACO.cpp.o.d -o CMakeFiles/evrp_lib_builder.dir/src/SACO.cpp.o -c /home/hienvq/Desktop/Lab/EVRP/lib/src/SACO.cpp

lib/CMakeFiles/evrp_lib_builder.dir/src/SACO.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/evrp_lib_builder.dir/src/SACO.cpp.i"
	cd /home/hienvq/Desktop/Lab/EVRP/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hienvq/Desktop/Lab/EVRP/lib/src/SACO.cpp > CMakeFiles/evrp_lib_builder.dir/src/SACO.cpp.i

lib/CMakeFiles/evrp_lib_builder.dir/src/SACO.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/evrp_lib_builder.dir/src/SACO.cpp.s"
	cd /home/hienvq/Desktop/Lab/EVRP/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hienvq/Desktop/Lab/EVRP/lib/src/SACO.cpp -o CMakeFiles/evrp_lib_builder.dir/src/SACO.cpp.s

lib/CMakeFiles/evrp_lib_builder.dir/src/GreedySearch.cpp.o: lib/CMakeFiles/evrp_lib_builder.dir/flags.make
lib/CMakeFiles/evrp_lib_builder.dir/src/GreedySearch.cpp.o: lib/src/GreedySearch.cpp
lib/CMakeFiles/evrp_lib_builder.dir/src/GreedySearch.cpp.o: lib/CMakeFiles/evrp_lib_builder.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hienvq/Desktop/Lab/EVRP/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object lib/CMakeFiles/evrp_lib_builder.dir/src/GreedySearch.cpp.o"
	cd /home/hienvq/Desktop/Lab/EVRP/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/CMakeFiles/evrp_lib_builder.dir/src/GreedySearch.cpp.o -MF CMakeFiles/evrp_lib_builder.dir/src/GreedySearch.cpp.o.d -o CMakeFiles/evrp_lib_builder.dir/src/GreedySearch.cpp.o -c /home/hienvq/Desktop/Lab/EVRP/lib/src/GreedySearch.cpp

lib/CMakeFiles/evrp_lib_builder.dir/src/GreedySearch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/evrp_lib_builder.dir/src/GreedySearch.cpp.i"
	cd /home/hienvq/Desktop/Lab/EVRP/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hienvq/Desktop/Lab/EVRP/lib/src/GreedySearch.cpp > CMakeFiles/evrp_lib_builder.dir/src/GreedySearch.cpp.i

lib/CMakeFiles/evrp_lib_builder.dir/src/GreedySearch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/evrp_lib_builder.dir/src/GreedySearch.cpp.s"
	cd /home/hienvq/Desktop/Lab/EVRP/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hienvq/Desktop/Lab/EVRP/lib/src/GreedySearch.cpp -o CMakeFiles/evrp_lib_builder.dir/src/GreedySearch.cpp.s

lib/CMakeFiles/evrp_lib_builder.dir/src/SA.cpp.o: lib/CMakeFiles/evrp_lib_builder.dir/flags.make
lib/CMakeFiles/evrp_lib_builder.dir/src/SA.cpp.o: lib/src/SA.cpp
lib/CMakeFiles/evrp_lib_builder.dir/src/SA.cpp.o: lib/CMakeFiles/evrp_lib_builder.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hienvq/Desktop/Lab/EVRP/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object lib/CMakeFiles/evrp_lib_builder.dir/src/SA.cpp.o"
	cd /home/hienvq/Desktop/Lab/EVRP/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/CMakeFiles/evrp_lib_builder.dir/src/SA.cpp.o -MF CMakeFiles/evrp_lib_builder.dir/src/SA.cpp.o.d -o CMakeFiles/evrp_lib_builder.dir/src/SA.cpp.o -c /home/hienvq/Desktop/Lab/EVRP/lib/src/SA.cpp

lib/CMakeFiles/evrp_lib_builder.dir/src/SA.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/evrp_lib_builder.dir/src/SA.cpp.i"
	cd /home/hienvq/Desktop/Lab/EVRP/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hienvq/Desktop/Lab/EVRP/lib/src/SA.cpp > CMakeFiles/evrp_lib_builder.dir/src/SA.cpp.i

lib/CMakeFiles/evrp_lib_builder.dir/src/SA.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/evrp_lib_builder.dir/src/SA.cpp.s"
	cd /home/hienvq/Desktop/Lab/EVRP/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hienvq/Desktop/Lab/EVRP/lib/src/SA.cpp -o CMakeFiles/evrp_lib_builder.dir/src/SA.cpp.s

lib/CMakeFiles/evrp_lib_builder.dir/src/utils.cpp.o: lib/CMakeFiles/evrp_lib_builder.dir/flags.make
lib/CMakeFiles/evrp_lib_builder.dir/src/utils.cpp.o: lib/src/utils.cpp
lib/CMakeFiles/evrp_lib_builder.dir/src/utils.cpp.o: lib/CMakeFiles/evrp_lib_builder.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hienvq/Desktop/Lab/EVRP/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object lib/CMakeFiles/evrp_lib_builder.dir/src/utils.cpp.o"
	cd /home/hienvq/Desktop/Lab/EVRP/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/CMakeFiles/evrp_lib_builder.dir/src/utils.cpp.o -MF CMakeFiles/evrp_lib_builder.dir/src/utils.cpp.o.d -o CMakeFiles/evrp_lib_builder.dir/src/utils.cpp.o -c /home/hienvq/Desktop/Lab/EVRP/lib/src/utils.cpp

lib/CMakeFiles/evrp_lib_builder.dir/src/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/evrp_lib_builder.dir/src/utils.cpp.i"
	cd /home/hienvq/Desktop/Lab/EVRP/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hienvq/Desktop/Lab/EVRP/lib/src/utils.cpp > CMakeFiles/evrp_lib_builder.dir/src/utils.cpp.i

lib/CMakeFiles/evrp_lib_builder.dir/src/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/evrp_lib_builder.dir/src/utils.cpp.s"
	cd /home/hienvq/Desktop/Lab/EVRP/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hienvq/Desktop/Lab/EVRP/lib/src/utils.cpp -o CMakeFiles/evrp_lib_builder.dir/src/utils.cpp.s

# Object files for target evrp_lib_builder
evrp_lib_builder_OBJECTS = \
"CMakeFiles/evrp_lib_builder.dir/src/EVRP.cpp.o" \
"CMakeFiles/evrp_lib_builder.dir/src/stats.cpp.o" \
"CMakeFiles/evrp_lib_builder.dir/src/individual.cpp.o" \
"CMakeFiles/evrp_lib_builder.dir/src/HMAGS.cpp.o" \
"CMakeFiles/evrp_lib_builder.dir/src/SACO.cpp.o" \
"CMakeFiles/evrp_lib_builder.dir/src/GreedySearch.cpp.o" \
"CMakeFiles/evrp_lib_builder.dir/src/SA.cpp.o" \
"CMakeFiles/evrp_lib_builder.dir/src/utils.cpp.o"

# External object files for target evrp_lib_builder
evrp_lib_builder_EXTERNAL_OBJECTS =

lib/libevrp_lib_builder.a: lib/CMakeFiles/evrp_lib_builder.dir/src/EVRP.cpp.o
lib/libevrp_lib_builder.a: lib/CMakeFiles/evrp_lib_builder.dir/src/stats.cpp.o
lib/libevrp_lib_builder.a: lib/CMakeFiles/evrp_lib_builder.dir/src/individual.cpp.o
lib/libevrp_lib_builder.a: lib/CMakeFiles/evrp_lib_builder.dir/src/HMAGS.cpp.o
lib/libevrp_lib_builder.a: lib/CMakeFiles/evrp_lib_builder.dir/src/SACO.cpp.o
lib/libevrp_lib_builder.a: lib/CMakeFiles/evrp_lib_builder.dir/src/GreedySearch.cpp.o
lib/libevrp_lib_builder.a: lib/CMakeFiles/evrp_lib_builder.dir/src/SA.cpp.o
lib/libevrp_lib_builder.a: lib/CMakeFiles/evrp_lib_builder.dir/src/utils.cpp.o
lib/libevrp_lib_builder.a: lib/CMakeFiles/evrp_lib_builder.dir/build.make
lib/libevrp_lib_builder.a: lib/CMakeFiles/evrp_lib_builder.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hienvq/Desktop/Lab/EVRP/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX static library libevrp_lib_builder.a"
	cd /home/hienvq/Desktop/Lab/EVRP/lib && $(CMAKE_COMMAND) -P CMakeFiles/evrp_lib_builder.dir/cmake_clean_target.cmake
	cd /home/hienvq/Desktop/Lab/EVRP/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/evrp_lib_builder.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/CMakeFiles/evrp_lib_builder.dir/build: lib/libevrp_lib_builder.a
.PHONY : lib/CMakeFiles/evrp_lib_builder.dir/build

lib/CMakeFiles/evrp_lib_builder.dir/clean:
	cd /home/hienvq/Desktop/Lab/EVRP/lib && $(CMAKE_COMMAND) -P CMakeFiles/evrp_lib_builder.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/evrp_lib_builder.dir/clean

lib/CMakeFiles/evrp_lib_builder.dir/depend:
	cd /home/hienvq/Desktop/Lab/EVRP && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hienvq/Desktop/Lab/EVRP /home/hienvq/Desktop/Lab/EVRP/lib /home/hienvq/Desktop/Lab/EVRP /home/hienvq/Desktop/Lab/EVRP/lib /home/hienvq/Desktop/Lab/EVRP/lib/CMakeFiles/evrp_lib_builder.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/evrp_lib_builder.dir/depend
