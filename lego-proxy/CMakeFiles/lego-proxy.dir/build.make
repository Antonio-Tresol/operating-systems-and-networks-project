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
CMAKE_SOURCE_DIR = /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos

# Include any dependencies generated for this target.
include lego-proxy/CMakeFiles/lego-proxy.dir/depend.make

# Include the progress variables for this target.
include lego-proxy/CMakeFiles/lego-proxy.dir/progress.make

# Include the compile flags for this target's objects.
include lego-proxy/CMakeFiles/lego-proxy.dir/flags.make

lego-proxy/CMakeFiles/lego-proxy.dir/main/src/LegoProxy.cpp.o: lego-proxy/CMakeFiles/lego-proxy.dir/flags.make
lego-proxy/CMakeFiles/lego-proxy.dir/main/src/LegoProxy.cpp.o: lego-proxy/main/src/LegoProxy.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lego-proxy/CMakeFiles/lego-proxy.dir/main/src/LegoProxy.cpp.o"
	cd /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-proxy && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lego-proxy.dir/main/src/LegoProxy.cpp.o -c /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-proxy/main/src/LegoProxy.cpp

lego-proxy/CMakeFiles/lego-proxy.dir/main/src/LegoProxy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lego-proxy.dir/main/src/LegoProxy.cpp.i"
	cd /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-proxy && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-proxy/main/src/LegoProxy.cpp > CMakeFiles/lego-proxy.dir/main/src/LegoProxy.cpp.i

lego-proxy/CMakeFiles/lego-proxy.dir/main/src/LegoProxy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lego-proxy.dir/main/src/LegoProxy.cpp.s"
	cd /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-proxy && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-proxy/main/src/LegoProxy.cpp -o CMakeFiles/lego-proxy.dir/main/src/LegoProxy.cpp.s

lego-proxy/CMakeFiles/lego-proxy.dir/main/src/controller/FigureController.cpp.o: lego-proxy/CMakeFiles/lego-proxy.dir/flags.make
lego-proxy/CMakeFiles/lego-proxy.dir/main/src/controller/FigureController.cpp.o: lego-proxy/main/src/controller/FigureController.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lego-proxy/CMakeFiles/lego-proxy.dir/main/src/controller/FigureController.cpp.o"
	cd /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-proxy && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lego-proxy.dir/main/src/controller/FigureController.cpp.o -c /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-proxy/main/src/controller/FigureController.cpp

lego-proxy/CMakeFiles/lego-proxy.dir/main/src/controller/FigureController.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lego-proxy.dir/main/src/controller/FigureController.cpp.i"
	cd /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-proxy && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-proxy/main/src/controller/FigureController.cpp > CMakeFiles/lego-proxy.dir/main/src/controller/FigureController.cpp.i

lego-proxy/CMakeFiles/lego-proxy.dir/main/src/controller/FigureController.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lego-proxy.dir/main/src/controller/FigureController.cpp.s"
	cd /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-proxy && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-proxy/main/src/controller/FigureController.cpp -o CMakeFiles/lego-proxy.dir/main/src/controller/FigureController.cpp.s

lego-proxy/CMakeFiles/lego-proxy.dir/main/src/net/FigureHttpsServer.cpp.o: lego-proxy/CMakeFiles/lego-proxy.dir/flags.make
lego-proxy/CMakeFiles/lego-proxy.dir/main/src/net/FigureHttpsServer.cpp.o: lego-proxy/main/src/net/FigureHttpsServer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object lego-proxy/CMakeFiles/lego-proxy.dir/main/src/net/FigureHttpsServer.cpp.o"
	cd /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-proxy && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lego-proxy.dir/main/src/net/FigureHttpsServer.cpp.o -c /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-proxy/main/src/net/FigureHttpsServer.cpp

lego-proxy/CMakeFiles/lego-proxy.dir/main/src/net/FigureHttpsServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lego-proxy.dir/main/src/net/FigureHttpsServer.cpp.i"
	cd /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-proxy && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-proxy/main/src/net/FigureHttpsServer.cpp > CMakeFiles/lego-proxy.dir/main/src/net/FigureHttpsServer.cpp.i

lego-proxy/CMakeFiles/lego-proxy.dir/main/src/net/FigureHttpsServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lego-proxy.dir/main/src/net/FigureHttpsServer.cpp.s"
	cd /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-proxy && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-proxy/main/src/net/FigureHttpsServer.cpp -o CMakeFiles/lego-proxy.dir/main/src/net/FigureHttpsServer.cpp.s

# Object files for target lego-proxy
lego__proxy_OBJECTS = \
"CMakeFiles/lego-proxy.dir/main/src/LegoProxy.cpp.o" \
"CMakeFiles/lego-proxy.dir/main/src/controller/FigureController.cpp.o" \
"CMakeFiles/lego-proxy.dir/main/src/net/FigureHttpsServer.cpp.o"

# External object files for target lego-proxy
lego__proxy_EXTERNAL_OBJECTS =

lego-proxy/lego-proxy: lego-proxy/CMakeFiles/lego-proxy.dir/main/src/LegoProxy.cpp.o
lego-proxy/lego-proxy: lego-proxy/CMakeFiles/lego-proxy.dir/main/src/controller/FigureController.cpp.o
lego-proxy/lego-proxy: lego-proxy/CMakeFiles/lego-proxy.dir/main/src/net/FigureHttpsServer.cpp.o
lego-proxy/lego-proxy: lego-proxy/CMakeFiles/lego-proxy.dir/build.make
lego-proxy/lego-proxy: /usr/lib/x86_64-linux-gnu/libssl.so
lego-proxy/lego-proxy: /usr/lib/x86_64-linux-gnu/libcrypto.so
lego-proxy/lego-proxy: liblego-common.a
lego-proxy/lego-proxy: /usr/lib/x86_64-linux-gnu/libssl.so
lego-proxy/lego-proxy: /usr/lib/x86_64-linux-gnu/libcrypto.so
lego-proxy/lego-proxy: lego-proxy/CMakeFiles/lego-proxy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable lego-proxy"
	cd /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-proxy && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lego-proxy.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lego-proxy/CMakeFiles/lego-proxy.dir/build: lego-proxy/lego-proxy

.PHONY : lego-proxy/CMakeFiles/lego-proxy.dir/build

lego-proxy/CMakeFiles/lego-proxy.dir/clean:
	cd /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-proxy && $(CMAKE_COMMAND) -P CMakeFiles/lego-proxy.dir/cmake_clean.cmake
.PHONY : lego-proxy/CMakeFiles/lego-proxy.dir/clean

lego-proxy/CMakeFiles/lego-proxy.dir/depend:
	cd /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-proxy /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-proxy /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-proxy/CMakeFiles/lego-proxy.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lego-proxy/CMakeFiles/lego-proxy.dir/depend

