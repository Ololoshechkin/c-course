# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/Vadim/Documents/coding/c++ course/Huffman console utility/Huffman"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/Vadim/Documents/coding/c++ course/Huffman console utility/Huffman"

# Include any dependencies generated for this target.
include CMakeFiles/huffman_lib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/huffman_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/huffman_lib.dir/flags.make

CMakeFiles/huffman_lib.dir/binary_code.cpp.o: CMakeFiles/huffman_lib.dir/flags.make
CMakeFiles/huffman_lib.dir/binary_code.cpp.o: binary_code.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/Vadim/Documents/coding/c++ course/Huffman console utility/Huffman/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/huffman_lib.dir/binary_code.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/huffman_lib.dir/binary_code.cpp.o -c "/Users/Vadim/Documents/coding/c++ course/Huffman console utility/Huffman/binary_code.cpp"

CMakeFiles/huffman_lib.dir/binary_code.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/huffman_lib.dir/binary_code.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/Vadim/Documents/coding/c++ course/Huffman console utility/Huffman/binary_code.cpp" > CMakeFiles/huffman_lib.dir/binary_code.cpp.i

CMakeFiles/huffman_lib.dir/binary_code.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/huffman_lib.dir/binary_code.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/Vadim/Documents/coding/c++ course/Huffman console utility/Huffman/binary_code.cpp" -o CMakeFiles/huffman_lib.dir/binary_code.cpp.s

CMakeFiles/huffman_lib.dir/binary_code.cpp.o.requires:

.PHONY : CMakeFiles/huffman_lib.dir/binary_code.cpp.o.requires

CMakeFiles/huffman_lib.dir/binary_code.cpp.o.provides: CMakeFiles/huffman_lib.dir/binary_code.cpp.o.requires
	$(MAKE) -f CMakeFiles/huffman_lib.dir/build.make CMakeFiles/huffman_lib.dir/binary_code.cpp.o.provides.build
.PHONY : CMakeFiles/huffman_lib.dir/binary_code.cpp.o.provides

CMakeFiles/huffman_lib.dir/binary_code.cpp.o.provides.build: CMakeFiles/huffman_lib.dir/binary_code.cpp.o


CMakeFiles/huffman_lib.dir/huffman_tree.cpp.o: CMakeFiles/huffman_lib.dir/flags.make
CMakeFiles/huffman_lib.dir/huffman_tree.cpp.o: huffman_tree.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/Vadim/Documents/coding/c++ course/Huffman console utility/Huffman/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/huffman_lib.dir/huffman_tree.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/huffman_lib.dir/huffman_tree.cpp.o -c "/Users/Vadim/Documents/coding/c++ course/Huffman console utility/Huffman/huffman_tree.cpp"

CMakeFiles/huffman_lib.dir/huffman_tree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/huffman_lib.dir/huffman_tree.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/Vadim/Documents/coding/c++ course/Huffman console utility/Huffman/huffman_tree.cpp" > CMakeFiles/huffman_lib.dir/huffman_tree.cpp.i

CMakeFiles/huffman_lib.dir/huffman_tree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/huffman_lib.dir/huffman_tree.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/Vadim/Documents/coding/c++ course/Huffman console utility/Huffman/huffman_tree.cpp" -o CMakeFiles/huffman_lib.dir/huffman_tree.cpp.s

CMakeFiles/huffman_lib.dir/huffman_tree.cpp.o.requires:

.PHONY : CMakeFiles/huffman_lib.dir/huffman_tree.cpp.o.requires

CMakeFiles/huffman_lib.dir/huffman_tree.cpp.o.provides: CMakeFiles/huffman_lib.dir/huffman_tree.cpp.o.requires
	$(MAKE) -f CMakeFiles/huffman_lib.dir/build.make CMakeFiles/huffman_lib.dir/huffman_tree.cpp.o.provides.build
.PHONY : CMakeFiles/huffman_lib.dir/huffman_tree.cpp.o.provides

CMakeFiles/huffman_lib.dir/huffman_tree.cpp.o.provides.build: CMakeFiles/huffman_lib.dir/huffman_tree.cpp.o


CMakeFiles/huffman_lib.dir/huffman_archiver.cpp.o: CMakeFiles/huffman_lib.dir/flags.make
CMakeFiles/huffman_lib.dir/huffman_archiver.cpp.o: huffman_archiver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/Vadim/Documents/coding/c++ course/Huffman console utility/Huffman/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/huffman_lib.dir/huffman_archiver.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/huffman_lib.dir/huffman_archiver.cpp.o -c "/Users/Vadim/Documents/coding/c++ course/Huffman console utility/Huffman/huffman_archiver.cpp"

CMakeFiles/huffman_lib.dir/huffman_archiver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/huffman_lib.dir/huffman_archiver.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/Vadim/Documents/coding/c++ course/Huffman console utility/Huffman/huffman_archiver.cpp" > CMakeFiles/huffman_lib.dir/huffman_archiver.cpp.i

CMakeFiles/huffman_lib.dir/huffman_archiver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/huffman_lib.dir/huffman_archiver.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/Vadim/Documents/coding/c++ course/Huffman console utility/Huffman/huffman_archiver.cpp" -o CMakeFiles/huffman_lib.dir/huffman_archiver.cpp.s

CMakeFiles/huffman_lib.dir/huffman_archiver.cpp.o.requires:

.PHONY : CMakeFiles/huffman_lib.dir/huffman_archiver.cpp.o.requires

CMakeFiles/huffman_lib.dir/huffman_archiver.cpp.o.provides: CMakeFiles/huffman_lib.dir/huffman_archiver.cpp.o.requires
	$(MAKE) -f CMakeFiles/huffman_lib.dir/build.make CMakeFiles/huffman_lib.dir/huffman_archiver.cpp.o.provides.build
.PHONY : CMakeFiles/huffman_lib.dir/huffman_archiver.cpp.o.provides

CMakeFiles/huffman_lib.dir/huffman_archiver.cpp.o.provides.build: CMakeFiles/huffman_lib.dir/huffman_archiver.cpp.o


# Object files for target huffman_lib
huffman_lib_OBJECTS = \
"CMakeFiles/huffman_lib.dir/binary_code.cpp.o" \
"CMakeFiles/huffman_lib.dir/huffman_tree.cpp.o" \
"CMakeFiles/huffman_lib.dir/huffman_archiver.cpp.o"

# External object files for target huffman_lib
huffman_lib_EXTERNAL_OBJECTS =

libhuffman_lib.a: CMakeFiles/huffman_lib.dir/binary_code.cpp.o
libhuffman_lib.a: CMakeFiles/huffman_lib.dir/huffman_tree.cpp.o
libhuffman_lib.a: CMakeFiles/huffman_lib.dir/huffman_archiver.cpp.o
libhuffman_lib.a: CMakeFiles/huffman_lib.dir/build.make
libhuffman_lib.a: CMakeFiles/huffman_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/Vadim/Documents/coding/c++ course/Huffman console utility/Huffman/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libhuffman_lib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/huffman_lib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/huffman_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/huffman_lib.dir/build: libhuffman_lib.a

.PHONY : CMakeFiles/huffman_lib.dir/build

CMakeFiles/huffman_lib.dir/requires: CMakeFiles/huffman_lib.dir/binary_code.cpp.o.requires
CMakeFiles/huffman_lib.dir/requires: CMakeFiles/huffman_lib.dir/huffman_tree.cpp.o.requires
CMakeFiles/huffman_lib.dir/requires: CMakeFiles/huffman_lib.dir/huffman_archiver.cpp.o.requires

.PHONY : CMakeFiles/huffman_lib.dir/requires

CMakeFiles/huffman_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/huffman_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/huffman_lib.dir/clean

CMakeFiles/huffman_lib.dir/depend:
	cd "/Users/Vadim/Documents/coding/c++ course/Huffman console utility/Huffman" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/Vadim/Documents/coding/c++ course/Huffman console utility/Huffman" "/Users/Vadim/Documents/coding/c++ course/Huffman console utility/Huffman" "/Users/Vadim/Documents/coding/c++ course/Huffman console utility/Huffman" "/Users/Vadim/Documents/coding/c++ course/Huffman console utility/Huffman" "/Users/Vadim/Documents/coding/c++ course/Huffman console utility/Huffman/CMakeFiles/huffman_lib.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/huffman_lib.dir/depend
