# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.21

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.3.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.3.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\tomas\OneDrive\Documentos\GitHub\PPP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\tomas\OneDrive\Documentos\GitHub\PPP\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/projeto.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/projeto.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/projeto.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/projeto.dir/flags.make

CMakeFiles/projeto.dir/main.c.obj: CMakeFiles/projeto.dir/flags.make
CMakeFiles/projeto.dir/main.c.obj: ../main.c
CMakeFiles/projeto.dir/main.c.obj: CMakeFiles/projeto.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\tomas\OneDrive\Documentos\GitHub\PPP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/projeto.dir/main.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/projeto.dir/main.c.obj -MF CMakeFiles\projeto.dir\main.c.obj.d -o CMakeFiles\projeto.dir\main.c.obj -c C:\Users\tomas\OneDrive\Documentos\GitHub\PPP\main.c

CMakeFiles/projeto.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/projeto.dir/main.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\tomas\OneDrive\Documentos\GitHub\PPP\main.c > CMakeFiles\projeto.dir\main.c.i

CMakeFiles/projeto.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/projeto.dir/main.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\tomas\OneDrive\Documentos\GitHub\PPP\main.c -o CMakeFiles\projeto.dir\main.c.s

CMakeFiles/projeto.dir/structs.c.obj: CMakeFiles/projeto.dir/flags.make
CMakeFiles/projeto.dir/structs.c.obj: ../structs.c
CMakeFiles/projeto.dir/structs.c.obj: CMakeFiles/projeto.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\tomas\OneDrive\Documentos\GitHub\PPP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/projeto.dir/structs.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/projeto.dir/structs.c.obj -MF CMakeFiles\projeto.dir\structs.c.obj.d -o CMakeFiles\projeto.dir\structs.c.obj -c C:\Users\tomas\OneDrive\Documentos\GitHub\PPP\structs.c

CMakeFiles/projeto.dir/structs.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/projeto.dir/structs.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\tomas\OneDrive\Documentos\GitHub\PPP\structs.c > CMakeFiles\projeto.dir\structs.c.i

CMakeFiles/projeto.dir/structs.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/projeto.dir/structs.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\tomas\OneDrive\Documentos\GitHub\PPP\structs.c -o CMakeFiles\projeto.dir\structs.c.s

# Object files for target projeto
projeto_OBJECTS = \
"CMakeFiles/projeto.dir/main.c.obj" \
"CMakeFiles/projeto.dir/structs.c.obj"

# External object files for target projeto
projeto_EXTERNAL_OBJECTS =

projeto.exe: CMakeFiles/projeto.dir/main.c.obj
projeto.exe: CMakeFiles/projeto.dir/structs.c.obj
projeto.exe: CMakeFiles/projeto.dir/build.make
projeto.exe: CMakeFiles/projeto.dir/linklibs.rsp
projeto.exe: CMakeFiles/projeto.dir/objects1.rsp
projeto.exe: CMakeFiles/projeto.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\tomas\OneDrive\Documentos\GitHub\PPP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable projeto.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\projeto.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/projeto.dir/build: projeto.exe
.PHONY : CMakeFiles/projeto.dir/build

CMakeFiles/projeto.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\projeto.dir\cmake_clean.cmake
.PHONY : CMakeFiles/projeto.dir/clean

CMakeFiles/projeto.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\tomas\OneDrive\Documentos\GitHub\PPP C:\Users\tomas\OneDrive\Documentos\GitHub\PPP C:\Users\tomas\OneDrive\Documentos\GitHub\PPP\cmake-build-debug C:\Users\tomas\OneDrive\Documentos\GitHub\PPP\cmake-build-debug C:\Users\tomas\OneDrive\Documentos\GitHub\PPP\cmake-build-debug\CMakeFiles\projeto.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/projeto.dir/depend

