# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/d/Desktop/U/pi-redes-sistemas-operativos

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/Desktop/U/pi-redes-sistemas-operativos/build

# Include any dependencies generated for this target.
include lego-client/CMakeFiles/lego-client.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lego-client/CMakeFiles/lego-client.dir/compiler_depend.make

# Include the progress variables for this target.
include lego-client/CMakeFiles/lego-client.dir/progress.make

# Include the compile flags for this target's objects.
include lego-client/CMakeFiles/lego-client.dir/flags.make

lego-client/CMakeFiles/lego-client.dir/main/src/LegoClient.cpp.o: lego-client/CMakeFiles/lego-client.dir/flags.make
lego-client/CMakeFiles/lego-client.dir/main/src/LegoClient.cpp.o: ../lego-client/main/src/LegoClient.cpp
lego-client/CMakeFiles/lego-client.dir/main/src/LegoClient.cpp.o: lego-client/CMakeFiles/lego-client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/Desktop/U/pi-redes-sistemas-operativos/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lego-client/CMakeFiles/lego-client.dir/main/src/LegoClient.cpp.o"
	cd /mnt/d/Desktop/U/pi-redes-sistemas-operativos/build/lego-client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lego-client/CMakeFiles/lego-client.dir/main/src/LegoClient.cpp.o -MF CMakeFiles/lego-client.dir/main/src/LegoClient.cpp.o.d -o CMakeFiles/lego-client.dir/main/src/LegoClient.cpp.o -c /mnt/d/Desktop/U/pi-redes-sistemas-operativos/lego-client/main/src/LegoClient.cpp

lego-client/CMakeFiles/lego-client.dir/main/src/LegoClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lego-client.dir/main/src/LegoClient.cpp.i"
	cd /mnt/d/Desktop/U/pi-redes-sistemas-operativos/build/lego-client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/Desktop/U/pi-redes-sistemas-operativos/lego-client/main/src/LegoClient.cpp > CMakeFiles/lego-client.dir/main/src/LegoClient.cpp.i

lego-client/CMakeFiles/lego-client.dir/main/src/LegoClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lego-client.dir/main/src/LegoClient.cpp.s"
	cd /mnt/d/Desktop/U/pi-redes-sistemas-operativos/build/lego-client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/Desktop/U/pi-redes-sistemas-operativos/lego-client/main/src/LegoClient.cpp -o CMakeFiles/lego-client.dir/main/src/LegoClient.cpp.s

lego-client/CMakeFiles/lego-client.dir/main/src/controller/FigureController.cpp.o: lego-client/CMakeFiles/lego-client.dir/flags.make
lego-client/CMakeFiles/lego-client.dir/main/src/controller/FigureController.cpp.o: ../lego-client/main/src/controller/FigureController.cpp
lego-client/CMakeFiles/lego-client.dir/main/src/controller/FigureController.cpp.o: lego-client/CMakeFiles/lego-client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/Desktop/U/pi-redes-sistemas-operativos/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lego-client/CMakeFiles/lego-client.dir/main/src/controller/FigureController.cpp.o"
	cd /mnt/d/Desktop/U/pi-redes-sistemas-operativos/build/lego-client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lego-client/CMakeFiles/lego-client.dir/main/src/controller/FigureController.cpp.o -MF CMakeFiles/lego-client.dir/main/src/controller/FigureController.cpp.o.d -o CMakeFiles/lego-client.dir/main/src/controller/FigureController.cpp.o -c /mnt/d/Desktop/U/pi-redes-sistemas-operativos/lego-client/main/src/controller/FigureController.cpp

lego-client/CMakeFiles/lego-client.dir/main/src/controller/FigureController.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lego-client.dir/main/src/controller/FigureController.cpp.i"
	cd /mnt/d/Desktop/U/pi-redes-sistemas-operativos/build/lego-client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/Desktop/U/pi-redes-sistemas-operativos/lego-client/main/src/controller/FigureController.cpp > CMakeFiles/lego-client.dir/main/src/controller/FigureController.cpp.i

lego-client/CMakeFiles/lego-client.dir/main/src/controller/FigureController.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lego-client.dir/main/src/controller/FigureController.cpp.s"
	cd /mnt/d/Desktop/U/pi-redes-sistemas-operativos/build/lego-client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/Desktop/U/pi-redes-sistemas-operativos/lego-client/main/src/controller/FigureController.cpp -o CMakeFiles/lego-client.dir/main/src/controller/FigureController.cpp.s

lego-client/CMakeFiles/lego-client.dir/main/src/data/FigureRepository.cpp.o: lego-client/CMakeFiles/lego-client.dir/flags.make
lego-client/CMakeFiles/lego-client.dir/main/src/data/FigureRepository.cpp.o: ../lego-client/main/src/data/FigureRepository.cpp
lego-client/CMakeFiles/lego-client.dir/main/src/data/FigureRepository.cpp.o: lego-client/CMakeFiles/lego-client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/Desktop/U/pi-redes-sistemas-operativos/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object lego-client/CMakeFiles/lego-client.dir/main/src/data/FigureRepository.cpp.o"
	cd /mnt/d/Desktop/U/pi-redes-sistemas-operativos/build/lego-client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lego-client/CMakeFiles/lego-client.dir/main/src/data/FigureRepository.cpp.o -MF CMakeFiles/lego-client.dir/main/src/data/FigureRepository.cpp.o.d -o CMakeFiles/lego-client.dir/main/src/data/FigureRepository.cpp.o -c /mnt/d/Desktop/U/pi-redes-sistemas-operativos/lego-client/main/src/data/FigureRepository.cpp

lego-client/CMakeFiles/lego-client.dir/main/src/data/FigureRepository.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lego-client.dir/main/src/data/FigureRepository.cpp.i"
	cd /mnt/d/Desktop/U/pi-redes-sistemas-operativos/build/lego-client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/Desktop/U/pi-redes-sistemas-operativos/lego-client/main/src/data/FigureRepository.cpp > CMakeFiles/lego-client.dir/main/src/data/FigureRepository.cpp.i

lego-client/CMakeFiles/lego-client.dir/main/src/data/FigureRepository.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lego-client.dir/main/src/data/FigureRepository.cpp.s"
	cd /mnt/d/Desktop/U/pi-redes-sistemas-operativos/build/lego-client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/Desktop/U/pi-redes-sistemas-operativos/lego-client/main/src/data/FigureRepository.cpp -o CMakeFiles/lego-client.dir/main/src/data/FigureRepository.cpp.s

lego-client/CMakeFiles/lego-client.dir/main/src/model/Figure.cpp.o: lego-client/CMakeFiles/lego-client.dir/flags.make
lego-client/CMakeFiles/lego-client.dir/main/src/model/Figure.cpp.o: ../lego-client/main/src/model/Figure.cpp
lego-client/CMakeFiles/lego-client.dir/main/src/model/Figure.cpp.o: lego-client/CMakeFiles/lego-client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/Desktop/U/pi-redes-sistemas-operativos/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object lego-client/CMakeFiles/lego-client.dir/main/src/model/Figure.cpp.o"
	cd /mnt/d/Desktop/U/pi-redes-sistemas-operativos/build/lego-client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lego-client/CMakeFiles/lego-client.dir/main/src/model/Figure.cpp.o -MF CMakeFiles/lego-client.dir/main/src/model/Figure.cpp.o.d -o CMakeFiles/lego-client.dir/main/src/model/Figure.cpp.o -c /mnt/d/Desktop/U/pi-redes-sistemas-operativos/lego-client/main/src/model/Figure.cpp

lego-client/CMakeFiles/lego-client.dir/main/src/model/Figure.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lego-client.dir/main/src/model/Figure.cpp.i"
	cd /mnt/d/Desktop/U/pi-redes-sistemas-operativos/build/lego-client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/Desktop/U/pi-redes-sistemas-operativos/lego-client/main/src/model/Figure.cpp > CMakeFiles/lego-client.dir/main/src/model/Figure.cpp.i

lego-client/CMakeFiles/lego-client.dir/main/src/model/Figure.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lego-client.dir/main/src/model/Figure.cpp.s"
	cd /mnt/d/Desktop/U/pi-redes-sistemas-operativos/build/lego-client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/Desktop/U/pi-redes-sistemas-operativos/lego-client/main/src/model/Figure.cpp -o CMakeFiles/lego-client.dir/main/src/model/Figure.cpp.s

lego-client/CMakeFiles/lego-client.dir/main/src/net/HttpsClient.cpp.o: lego-client/CMakeFiles/lego-client.dir/flags.make
lego-client/CMakeFiles/lego-client.dir/main/src/net/HttpsClient.cpp.o: ../lego-client/main/src/net/HttpsClient.cpp
lego-client/CMakeFiles/lego-client.dir/main/src/net/HttpsClient.cpp.o: lego-client/CMakeFiles/lego-client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/Desktop/U/pi-redes-sistemas-operativos/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object lego-client/CMakeFiles/lego-client.dir/main/src/net/HttpsClient.cpp.o"
	cd /mnt/d/Desktop/U/pi-redes-sistemas-operativos/build/lego-client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lego-client/CMakeFiles/lego-client.dir/main/src/net/HttpsClient.cpp.o -MF CMakeFiles/lego-client.dir/main/src/net/HttpsClient.cpp.o.d -o CMakeFiles/lego-client.dir/main/src/net/HttpsClient.cpp.o -c /mnt/d/Desktop/U/pi-redes-sistemas-operativos/lego-client/main/src/net/HttpsClient.cpp

lego-client/CMakeFiles/lego-client.dir/main/src/net/HttpsClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lego-client.dir/main/src/net/HttpsClient.cpp.i"
	cd /mnt/d/Desktop/U/pi-redes-sistemas-operativos/build/lego-client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/Desktop/U/pi-redes-sistemas-operativos/lego-client/main/src/net/HttpsClient.cpp > CMakeFiles/lego-client.dir/main/src/net/HttpsClient.cpp.i

lego-client/CMakeFiles/lego-client.dir/main/src/net/HttpsClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lego-client.dir/main/src/net/HttpsClient.cpp.s"
	cd /mnt/d/Desktop/U/pi-redes-sistemas-operativos/build/lego-client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/Desktop/U/pi-redes-sistemas-operativos/lego-client/main/src/net/HttpsClient.cpp -o CMakeFiles/lego-client.dir/main/src/net/HttpsClient.cpp.s

# Object files for target lego-client
lego__client_OBJECTS = \
"CMakeFiles/lego-client.dir/main/src/LegoClient.cpp.o" \
"CMakeFiles/lego-client.dir/main/src/controller/FigureController.cpp.o" \
"CMakeFiles/lego-client.dir/main/src/data/FigureRepository.cpp.o" \
"CMakeFiles/lego-client.dir/main/src/model/Figure.cpp.o" \
"CMakeFiles/lego-client.dir/main/src/net/HttpsClient.cpp.o"

# External object files for target lego-client
lego__client_EXTERNAL_OBJECTS =

lego-client/lego-client: lego-client/CMakeFiles/lego-client.dir/main/src/LegoClient.cpp.o
lego-client/lego-client: lego-client/CMakeFiles/lego-client.dir/main/src/controller/FigureController.cpp.o
lego-client/lego-client: lego-client/CMakeFiles/lego-client.dir/main/src/data/FigureRepository.cpp.o
lego-client/lego-client: lego-client/CMakeFiles/lego-client.dir/main/src/model/Figure.cpp.o
lego-client/lego-client: lego-client/CMakeFiles/lego-client.dir/main/src/net/HttpsClient.cpp.o
lego-client/lego-client: lego-client/CMakeFiles/lego-client.dir/build.make
lego-client/lego-client: /usr/lib/x86_64-linux-gnu/libssl.so
lego-client/lego-client: /usr/lib/x86_64-linux-gnu/libcrypto.so
lego-client/lego-client: liblego-common.a
lego-client/lego-client: lego-client/CMakeFiles/lego-client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/Desktop/U/pi-redes-sistemas-operativos/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable lego-client"
	cd /mnt/d/Desktop/U/pi-redes-sistemas-operativos/build/lego-client && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lego-client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lego-client/CMakeFiles/lego-client.dir/build: lego-client/lego-client
.PHONY : lego-client/CMakeFiles/lego-client.dir/build

lego-client/CMakeFiles/lego-client.dir/clean:
	cd /mnt/d/Desktop/U/pi-redes-sistemas-operativos/build/lego-client && $(CMAKE_COMMAND) -P CMakeFiles/lego-client.dir/cmake_clean.cmake
.PHONY : lego-client/CMakeFiles/lego-client.dir/clean

lego-client/CMakeFiles/lego-client.dir/depend:
	cd /mnt/d/Desktop/U/pi-redes-sistemas-operativos/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/Desktop/U/pi-redes-sistemas-operativos /mnt/d/Desktop/U/pi-redes-sistemas-operativos/lego-client /mnt/d/Desktop/U/pi-redes-sistemas-operativos/build /mnt/d/Desktop/U/pi-redes-sistemas-operativos/build/lego-client /mnt/d/Desktop/U/pi-redes-sistemas-operativos/build/lego-client/CMakeFiles/lego-client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lego-client/CMakeFiles/lego-client.dir/depend

