# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/chinh/autoxing/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chinh/autoxing/build

# Utility rule file for clean_test_results_nachi_description.

# Include the progress variables for this target.
include nachi_project/nachi_description/CMakeFiles/clean_test_results_nachi_description.dir/progress.make

nachi_project/nachi_description/CMakeFiles/clean_test_results_nachi_description:
	cd /home/chinh/autoxing/build/nachi_project/nachi_description && /usr/bin/python3 /opt/ros/noetic/share/catkin/cmake/test/remove_test_results.py /home/chinh/autoxing/build/test_results/nachi_description

clean_test_results_nachi_description: nachi_project/nachi_description/CMakeFiles/clean_test_results_nachi_description
clean_test_results_nachi_description: nachi_project/nachi_description/CMakeFiles/clean_test_results_nachi_description.dir/build.make

.PHONY : clean_test_results_nachi_description

# Rule to build all files generated by this target.
nachi_project/nachi_description/CMakeFiles/clean_test_results_nachi_description.dir/build: clean_test_results_nachi_description

.PHONY : nachi_project/nachi_description/CMakeFiles/clean_test_results_nachi_description.dir/build

nachi_project/nachi_description/CMakeFiles/clean_test_results_nachi_description.dir/clean:
	cd /home/chinh/autoxing/build/nachi_project/nachi_description && $(CMAKE_COMMAND) -P CMakeFiles/clean_test_results_nachi_description.dir/cmake_clean.cmake
.PHONY : nachi_project/nachi_description/CMakeFiles/clean_test_results_nachi_description.dir/clean

nachi_project/nachi_description/CMakeFiles/clean_test_results_nachi_description.dir/depend:
	cd /home/chinh/autoxing/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chinh/autoxing/src /home/chinh/autoxing/src/nachi_project/nachi_description /home/chinh/autoxing/build /home/chinh/autoxing/build/nachi_project/nachi_description /home/chinh/autoxing/build/nachi_project/nachi_description/CMakeFiles/clean_test_results_nachi_description.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : nachi_project/nachi_description/CMakeFiles/clean_test_results_nachi_description.dir/depend

