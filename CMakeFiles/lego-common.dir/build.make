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
include CMakeFiles/lego-common.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lego-common.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lego-common.dir/flags.make

CMakeFiles/lego-common.dir/lego-common/main/src/concurrency/Semaphore.cpp.o: CMakeFiles/lego-common.dir/flags.make
CMakeFiles/lego-common.dir/lego-common/main/src/concurrency/Semaphore.cpp.o: lego-common/main/src/concurrency/Semaphore.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lego-common.dir/lego-common/main/src/concurrency/Semaphore.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lego-common.dir/lego-common/main/src/concurrency/Semaphore.cpp.o -c /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-common/main/src/concurrency/Semaphore.cpp

CMakeFiles/lego-common.dir/lego-common/main/src/concurrency/Semaphore.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lego-common.dir/lego-common/main/src/concurrency/Semaphore.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-common/main/src/concurrency/Semaphore.cpp > CMakeFiles/lego-common.dir/lego-common/main/src/concurrency/Semaphore.cpp.i

CMakeFiles/lego-common.dir/lego-common/main/src/concurrency/Semaphore.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lego-common.dir/lego-common/main/src/concurrency/Semaphore.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-common/main/src/concurrency/Semaphore.cpp -o CMakeFiles/lego-common.dir/lego-common/main/src/concurrency/Semaphore.cpp.s

CMakeFiles/lego-common.dir/lego-common/main/src/logging/Logger.cpp.o: CMakeFiles/lego-common.dir/flags.make
CMakeFiles/lego-common.dir/lego-common/main/src/logging/Logger.cpp.o: lego-common/main/src/logging/Logger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/lego-common.dir/lego-common/main/src/logging/Logger.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lego-common.dir/lego-common/main/src/logging/Logger.cpp.o -c /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-common/main/src/logging/Logger.cpp

CMakeFiles/lego-common.dir/lego-common/main/src/logging/Logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lego-common.dir/lego-common/main/src/logging/Logger.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-common/main/src/logging/Logger.cpp > CMakeFiles/lego-common.dir/lego-common/main/src/logging/Logger.cpp.i

CMakeFiles/lego-common.dir/lego-common/main/src/logging/Logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lego-common.dir/lego-common/main/src/logging/Logger.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-common/main/src/logging/Logger.cpp -o CMakeFiles/lego-common.dir/lego-common/main/src/logging/Logger.cpp.s

CMakeFiles/lego-common.dir/lego-common/main/src/net/ProtocolClient.cpp.o: CMakeFiles/lego-common.dir/flags.make
CMakeFiles/lego-common.dir/lego-common/main/src/net/ProtocolClient.cpp.o: lego-common/main/src/net/ProtocolClient.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/lego-common.dir/lego-common/main/src/net/ProtocolClient.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lego-common.dir/lego-common/main/src/net/ProtocolClient.cpp.o -c /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-common/main/src/net/ProtocolClient.cpp

CMakeFiles/lego-common.dir/lego-common/main/src/net/ProtocolClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lego-common.dir/lego-common/main/src/net/ProtocolClient.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-common/main/src/net/ProtocolClient.cpp > CMakeFiles/lego-common.dir/lego-common/main/src/net/ProtocolClient.cpp.i

CMakeFiles/lego-common.dir/lego-common/main/src/net/ProtocolClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lego-common.dir/lego-common/main/src/net/ProtocolClient.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-common/main/src/net/ProtocolClient.cpp -o CMakeFiles/lego-common.dir/lego-common/main/src/net/ProtocolClient.cpp.s

CMakeFiles/lego-common.dir/lego-common/main/src/net/ProtocolServer.cpp.o: CMakeFiles/lego-common.dir/flags.make
CMakeFiles/lego-common.dir/lego-common/main/src/net/ProtocolServer.cpp.o: lego-common/main/src/net/ProtocolServer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/lego-common.dir/lego-common/main/src/net/ProtocolServer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lego-common.dir/lego-common/main/src/net/ProtocolServer.cpp.o -c /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-common/main/src/net/ProtocolServer.cpp

CMakeFiles/lego-common.dir/lego-common/main/src/net/ProtocolServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lego-common.dir/lego-common/main/src/net/ProtocolServer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-common/main/src/net/ProtocolServer.cpp > CMakeFiles/lego-common.dir/lego-common/main/src/net/ProtocolServer.cpp.i

CMakeFiles/lego-common.dir/lego-common/main/src/net/ProtocolServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lego-common.dir/lego-common/main/src/net/ProtocolServer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-common/main/src/net/ProtocolServer.cpp -o CMakeFiles/lego-common.dir/lego-common/main/src/net/ProtocolServer.cpp.s

CMakeFiles/lego-common.dir/lego-common/main/src/net/SslServer.cpp.o: CMakeFiles/lego-common.dir/flags.make
CMakeFiles/lego-common.dir/lego-common/main/src/net/SslServer.cpp.o: lego-common/main/src/net/SslServer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/lego-common.dir/lego-common/main/src/net/SslServer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lego-common.dir/lego-common/main/src/net/SslServer.cpp.o -c /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-common/main/src/net/SslServer.cpp

CMakeFiles/lego-common.dir/lego-common/main/src/net/SslServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lego-common.dir/lego-common/main/src/net/SslServer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-common/main/src/net/SslServer.cpp > CMakeFiles/lego-common.dir/lego-common/main/src/net/SslServer.cpp.i

CMakeFiles/lego-common.dir/lego-common/main/src/net/SslServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lego-common.dir/lego-common/main/src/net/SslServer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-common/main/src/net/SslServer.cpp -o CMakeFiles/lego-common.dir/lego-common/main/src/net/SslServer.cpp.s

CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/IPv4SslSocket.cpp.o: CMakeFiles/lego-common.dir/flags.make
CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/IPv4SslSocket.cpp.o: lego-common/main/src/net/socket/IPv4SslSocket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/IPv4SslSocket.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/IPv4SslSocket.cpp.o -c /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-common/main/src/net/socket/IPv4SslSocket.cpp

CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/IPv4SslSocket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/IPv4SslSocket.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-common/main/src/net/socket/IPv4SslSocket.cpp > CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/IPv4SslSocket.cpp.i

CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/IPv4SslSocket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/IPv4SslSocket.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-common/main/src/net/socket/IPv4SslSocket.cpp -o CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/IPv4SslSocket.cpp.s

CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/IPv4UdpSocket.cpp.o: CMakeFiles/lego-common.dir/flags.make
CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/IPv4UdpSocket.cpp.o: lego-common/main/src/net/socket/IPv4UdpSocket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/IPv4UdpSocket.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/IPv4UdpSocket.cpp.o -c /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-common/main/src/net/socket/IPv4UdpSocket.cpp

CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/IPv4UdpSocket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/IPv4UdpSocket.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-common/main/src/net/socket/IPv4UdpSocket.cpp > CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/IPv4UdpSocket.cpp.i

CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/IPv4UdpSocket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/IPv4UdpSocket.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-common/main/src/net/socket/IPv4UdpSocket.cpp -o CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/IPv4UdpSocket.cpp.s

CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/SslCtxPtr.cpp.o: CMakeFiles/lego-common.dir/flags.make
CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/SslCtxPtr.cpp.o: lego-common/main/src/net/socket/SslCtxPtr.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/SslCtxPtr.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/SslCtxPtr.cpp.o -c /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-common/main/src/net/socket/SslCtxPtr.cpp

CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/SslCtxPtr.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/SslCtxPtr.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-common/main/src/net/socket/SslCtxPtr.cpp > CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/SslCtxPtr.cpp.i

CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/SslCtxPtr.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/SslCtxPtr.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-common/main/src/net/socket/SslCtxPtr.cpp -o CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/SslCtxPtr.cpp.s

CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/SslPtr.cpp.o: CMakeFiles/lego-common.dir/flags.make
CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/SslPtr.cpp.o: lego-common/main/src/net/socket/SslPtr.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/SslPtr.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/SslPtr.cpp.o -c /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-common/main/src/net/socket/SslPtr.cpp

CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/SslPtr.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/SslPtr.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-common/main/src/net/socket/SslPtr.cpp > CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/SslPtr.cpp.i

CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/SslPtr.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/SslPtr.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/lego-common/main/src/net/socket/SslPtr.cpp -o CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/SslPtr.cpp.s

# Object files for target lego-common
lego__common_OBJECTS = \
"CMakeFiles/lego-common.dir/lego-common/main/src/concurrency/Semaphore.cpp.o" \
"CMakeFiles/lego-common.dir/lego-common/main/src/logging/Logger.cpp.o" \
"CMakeFiles/lego-common.dir/lego-common/main/src/net/ProtocolClient.cpp.o" \
"CMakeFiles/lego-common.dir/lego-common/main/src/net/ProtocolServer.cpp.o" \
"CMakeFiles/lego-common.dir/lego-common/main/src/net/SslServer.cpp.o" \
"CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/IPv4SslSocket.cpp.o" \
"CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/IPv4UdpSocket.cpp.o" \
"CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/SslCtxPtr.cpp.o" \
"CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/SslPtr.cpp.o"

# External object files for target lego-common
lego__common_EXTERNAL_OBJECTS =

liblego-common.a: CMakeFiles/lego-common.dir/lego-common/main/src/concurrency/Semaphore.cpp.o
liblego-common.a: CMakeFiles/lego-common.dir/lego-common/main/src/logging/Logger.cpp.o
liblego-common.a: CMakeFiles/lego-common.dir/lego-common/main/src/net/ProtocolClient.cpp.o
liblego-common.a: CMakeFiles/lego-common.dir/lego-common/main/src/net/ProtocolServer.cpp.o
liblego-common.a: CMakeFiles/lego-common.dir/lego-common/main/src/net/SslServer.cpp.o
liblego-common.a: CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/IPv4SslSocket.cpp.o
liblego-common.a: CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/IPv4UdpSocket.cpp.o
liblego-common.a: CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/SslCtxPtr.cpp.o
liblego-common.a: CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/SslPtr.cpp.o
liblego-common.a: CMakeFiles/lego-common.dir/build.make
liblego-common.a: CMakeFiles/lego-common.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX static library liblego-common.a"
	$(CMAKE_COMMAND) -P CMakeFiles/lego-common.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lego-common.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lego-common.dir/build: liblego-common.a

.PHONY : CMakeFiles/lego-common.dir/build

CMakeFiles/lego-common.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lego-common.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lego-common.dir/clean

CMakeFiles/lego-common.dir/depend:
	cd /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/CMakeFiles/lego-common.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lego-common.dir/depend

