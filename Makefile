# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/CMakeFiles /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/jean/IS2023/PI/grupo/pi-redes-sistemas-operativos/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named lego-common

# Build rule for target.
lego-common: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 lego-common
.PHONY : lego-common

# fast build rule for target.
lego-common/fast:
	$(MAKE) -f CMakeFiles/lego-common.dir/build.make CMakeFiles/lego-common.dir/build
.PHONY : lego-common/fast

#=============================================================================
# Target rules for targets named lego-client

# Build rule for target.
lego-client: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 lego-client
.PHONY : lego-client

# fast build rule for target.
lego-client/fast:
	$(MAKE) -f lego-client/CMakeFiles/lego-client.dir/build.make lego-client/CMakeFiles/lego-client.dir/build
.PHONY : lego-client/fast

#=============================================================================
# Target rules for targets named lego-server

# Build rule for target.
lego-server: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 lego-server
.PHONY : lego-server

# fast build rule for target.
lego-server/fast:
	$(MAKE) -f lego-server/CMakeFiles/lego-server.dir/build.make lego-server/CMakeFiles/lego-server.dir/build
.PHONY : lego-server/fast

lego-common/main/src/concurrency/Semaphore.o: lego-common/main/src/concurrency/Semaphore.cpp.o

.PHONY : lego-common/main/src/concurrency/Semaphore.o

# target to build an object file
lego-common/main/src/concurrency/Semaphore.cpp.o:
	$(MAKE) -f CMakeFiles/lego-common.dir/build.make CMakeFiles/lego-common.dir/lego-common/main/src/concurrency/Semaphore.cpp.o
.PHONY : lego-common/main/src/concurrency/Semaphore.cpp.o

lego-common/main/src/concurrency/Semaphore.i: lego-common/main/src/concurrency/Semaphore.cpp.i

.PHONY : lego-common/main/src/concurrency/Semaphore.i

# target to preprocess a source file
lego-common/main/src/concurrency/Semaphore.cpp.i:
	$(MAKE) -f CMakeFiles/lego-common.dir/build.make CMakeFiles/lego-common.dir/lego-common/main/src/concurrency/Semaphore.cpp.i
.PHONY : lego-common/main/src/concurrency/Semaphore.cpp.i

lego-common/main/src/concurrency/Semaphore.s: lego-common/main/src/concurrency/Semaphore.cpp.s

.PHONY : lego-common/main/src/concurrency/Semaphore.s

# target to generate assembly for a file
lego-common/main/src/concurrency/Semaphore.cpp.s:
	$(MAKE) -f CMakeFiles/lego-common.dir/build.make CMakeFiles/lego-common.dir/lego-common/main/src/concurrency/Semaphore.cpp.s
.PHONY : lego-common/main/src/concurrency/Semaphore.cpp.s

lego-common/main/src/logging/Logger.o: lego-common/main/src/logging/Logger.cpp.o

.PHONY : lego-common/main/src/logging/Logger.o

# target to build an object file
lego-common/main/src/logging/Logger.cpp.o:
	$(MAKE) -f CMakeFiles/lego-common.dir/build.make CMakeFiles/lego-common.dir/lego-common/main/src/logging/Logger.cpp.o
.PHONY : lego-common/main/src/logging/Logger.cpp.o

lego-common/main/src/logging/Logger.i: lego-common/main/src/logging/Logger.cpp.i

.PHONY : lego-common/main/src/logging/Logger.i

# target to preprocess a source file
lego-common/main/src/logging/Logger.cpp.i:
	$(MAKE) -f CMakeFiles/lego-common.dir/build.make CMakeFiles/lego-common.dir/lego-common/main/src/logging/Logger.cpp.i
.PHONY : lego-common/main/src/logging/Logger.cpp.i

lego-common/main/src/logging/Logger.s: lego-common/main/src/logging/Logger.cpp.s

.PHONY : lego-common/main/src/logging/Logger.s

# target to generate assembly for a file
lego-common/main/src/logging/Logger.cpp.s:
	$(MAKE) -f CMakeFiles/lego-common.dir/build.make CMakeFiles/lego-common.dir/lego-common/main/src/logging/Logger.cpp.s
.PHONY : lego-common/main/src/logging/Logger.cpp.s

lego-common/main/src/net/ProtocolClient.o: lego-common/main/src/net/ProtocolClient.cpp.o

.PHONY : lego-common/main/src/net/ProtocolClient.o

# target to build an object file
lego-common/main/src/net/ProtocolClient.cpp.o:
	$(MAKE) -f CMakeFiles/lego-common.dir/build.make CMakeFiles/lego-common.dir/lego-common/main/src/net/ProtocolClient.cpp.o
.PHONY : lego-common/main/src/net/ProtocolClient.cpp.o

lego-common/main/src/net/ProtocolClient.i: lego-common/main/src/net/ProtocolClient.cpp.i

.PHONY : lego-common/main/src/net/ProtocolClient.i

# target to preprocess a source file
lego-common/main/src/net/ProtocolClient.cpp.i:
	$(MAKE) -f CMakeFiles/lego-common.dir/build.make CMakeFiles/lego-common.dir/lego-common/main/src/net/ProtocolClient.cpp.i
.PHONY : lego-common/main/src/net/ProtocolClient.cpp.i

lego-common/main/src/net/ProtocolClient.s: lego-common/main/src/net/ProtocolClient.cpp.s

.PHONY : lego-common/main/src/net/ProtocolClient.s

# target to generate assembly for a file
lego-common/main/src/net/ProtocolClient.cpp.s:
	$(MAKE) -f CMakeFiles/lego-common.dir/build.make CMakeFiles/lego-common.dir/lego-common/main/src/net/ProtocolClient.cpp.s
.PHONY : lego-common/main/src/net/ProtocolClient.cpp.s

lego-common/main/src/net/ProtocolServer.o: lego-common/main/src/net/ProtocolServer.cpp.o

.PHONY : lego-common/main/src/net/ProtocolServer.o

# target to build an object file
lego-common/main/src/net/ProtocolServer.cpp.o:
	$(MAKE) -f CMakeFiles/lego-common.dir/build.make CMakeFiles/lego-common.dir/lego-common/main/src/net/ProtocolServer.cpp.o
.PHONY : lego-common/main/src/net/ProtocolServer.cpp.o

lego-common/main/src/net/ProtocolServer.i: lego-common/main/src/net/ProtocolServer.cpp.i

.PHONY : lego-common/main/src/net/ProtocolServer.i

# target to preprocess a source file
lego-common/main/src/net/ProtocolServer.cpp.i:
	$(MAKE) -f CMakeFiles/lego-common.dir/build.make CMakeFiles/lego-common.dir/lego-common/main/src/net/ProtocolServer.cpp.i
.PHONY : lego-common/main/src/net/ProtocolServer.cpp.i

lego-common/main/src/net/ProtocolServer.s: lego-common/main/src/net/ProtocolServer.cpp.s

.PHONY : lego-common/main/src/net/ProtocolServer.s

# target to generate assembly for a file
lego-common/main/src/net/ProtocolServer.cpp.s:
	$(MAKE) -f CMakeFiles/lego-common.dir/build.make CMakeFiles/lego-common.dir/lego-common/main/src/net/ProtocolServer.cpp.s
.PHONY : lego-common/main/src/net/ProtocolServer.cpp.s

lego-common/main/src/net/SslServer.o: lego-common/main/src/net/SslServer.cpp.o

.PHONY : lego-common/main/src/net/SslServer.o

# target to build an object file
lego-common/main/src/net/SslServer.cpp.o:
	$(MAKE) -f CMakeFiles/lego-common.dir/build.make CMakeFiles/lego-common.dir/lego-common/main/src/net/SslServer.cpp.o
.PHONY : lego-common/main/src/net/SslServer.cpp.o

lego-common/main/src/net/SslServer.i: lego-common/main/src/net/SslServer.cpp.i

.PHONY : lego-common/main/src/net/SslServer.i

# target to preprocess a source file
lego-common/main/src/net/SslServer.cpp.i:
	$(MAKE) -f CMakeFiles/lego-common.dir/build.make CMakeFiles/lego-common.dir/lego-common/main/src/net/SslServer.cpp.i
.PHONY : lego-common/main/src/net/SslServer.cpp.i

lego-common/main/src/net/SslServer.s: lego-common/main/src/net/SslServer.cpp.s

.PHONY : lego-common/main/src/net/SslServer.s

# target to generate assembly for a file
lego-common/main/src/net/SslServer.cpp.s:
	$(MAKE) -f CMakeFiles/lego-common.dir/build.make CMakeFiles/lego-common.dir/lego-common/main/src/net/SslServer.cpp.s
.PHONY : lego-common/main/src/net/SslServer.cpp.s

lego-common/main/src/net/socket/IPv4SslSocket.o: lego-common/main/src/net/socket/IPv4SslSocket.cpp.o

.PHONY : lego-common/main/src/net/socket/IPv4SslSocket.o

# target to build an object file
lego-common/main/src/net/socket/IPv4SslSocket.cpp.o:
	$(MAKE) -f CMakeFiles/lego-common.dir/build.make CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/IPv4SslSocket.cpp.o
.PHONY : lego-common/main/src/net/socket/IPv4SslSocket.cpp.o

lego-common/main/src/net/socket/IPv4SslSocket.i: lego-common/main/src/net/socket/IPv4SslSocket.cpp.i

.PHONY : lego-common/main/src/net/socket/IPv4SslSocket.i

# target to preprocess a source file
lego-common/main/src/net/socket/IPv4SslSocket.cpp.i:
	$(MAKE) -f CMakeFiles/lego-common.dir/build.make CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/IPv4SslSocket.cpp.i
.PHONY : lego-common/main/src/net/socket/IPv4SslSocket.cpp.i

lego-common/main/src/net/socket/IPv4SslSocket.s: lego-common/main/src/net/socket/IPv4SslSocket.cpp.s

.PHONY : lego-common/main/src/net/socket/IPv4SslSocket.s

# target to generate assembly for a file
lego-common/main/src/net/socket/IPv4SslSocket.cpp.s:
	$(MAKE) -f CMakeFiles/lego-common.dir/build.make CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/IPv4SslSocket.cpp.s
.PHONY : lego-common/main/src/net/socket/IPv4SslSocket.cpp.s

lego-common/main/src/net/socket/IPv4UdpSocket.o: lego-common/main/src/net/socket/IPv4UdpSocket.cpp.o

.PHONY : lego-common/main/src/net/socket/IPv4UdpSocket.o

# target to build an object file
lego-common/main/src/net/socket/IPv4UdpSocket.cpp.o:
	$(MAKE) -f CMakeFiles/lego-common.dir/build.make CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/IPv4UdpSocket.cpp.o
.PHONY : lego-common/main/src/net/socket/IPv4UdpSocket.cpp.o

lego-common/main/src/net/socket/IPv4UdpSocket.i: lego-common/main/src/net/socket/IPv4UdpSocket.cpp.i

.PHONY : lego-common/main/src/net/socket/IPv4UdpSocket.i

# target to preprocess a source file
lego-common/main/src/net/socket/IPv4UdpSocket.cpp.i:
	$(MAKE) -f CMakeFiles/lego-common.dir/build.make CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/IPv4UdpSocket.cpp.i
.PHONY : lego-common/main/src/net/socket/IPv4UdpSocket.cpp.i

lego-common/main/src/net/socket/IPv4UdpSocket.s: lego-common/main/src/net/socket/IPv4UdpSocket.cpp.s

.PHONY : lego-common/main/src/net/socket/IPv4UdpSocket.s

# target to generate assembly for a file
lego-common/main/src/net/socket/IPv4UdpSocket.cpp.s:
	$(MAKE) -f CMakeFiles/lego-common.dir/build.make CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/IPv4UdpSocket.cpp.s
.PHONY : lego-common/main/src/net/socket/IPv4UdpSocket.cpp.s

lego-common/main/src/net/socket/SslCtxPtr.o: lego-common/main/src/net/socket/SslCtxPtr.cpp.o

.PHONY : lego-common/main/src/net/socket/SslCtxPtr.o

# target to build an object file
lego-common/main/src/net/socket/SslCtxPtr.cpp.o:
	$(MAKE) -f CMakeFiles/lego-common.dir/build.make CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/SslCtxPtr.cpp.o
.PHONY : lego-common/main/src/net/socket/SslCtxPtr.cpp.o

lego-common/main/src/net/socket/SslCtxPtr.i: lego-common/main/src/net/socket/SslCtxPtr.cpp.i

.PHONY : lego-common/main/src/net/socket/SslCtxPtr.i

# target to preprocess a source file
lego-common/main/src/net/socket/SslCtxPtr.cpp.i:
	$(MAKE) -f CMakeFiles/lego-common.dir/build.make CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/SslCtxPtr.cpp.i
.PHONY : lego-common/main/src/net/socket/SslCtxPtr.cpp.i

lego-common/main/src/net/socket/SslCtxPtr.s: lego-common/main/src/net/socket/SslCtxPtr.cpp.s

.PHONY : lego-common/main/src/net/socket/SslCtxPtr.s

# target to generate assembly for a file
lego-common/main/src/net/socket/SslCtxPtr.cpp.s:
	$(MAKE) -f CMakeFiles/lego-common.dir/build.make CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/SslCtxPtr.cpp.s
.PHONY : lego-common/main/src/net/socket/SslCtxPtr.cpp.s

lego-common/main/src/net/socket/SslPtr.o: lego-common/main/src/net/socket/SslPtr.cpp.o

.PHONY : lego-common/main/src/net/socket/SslPtr.o

# target to build an object file
lego-common/main/src/net/socket/SslPtr.cpp.o:
	$(MAKE) -f CMakeFiles/lego-common.dir/build.make CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/SslPtr.cpp.o
.PHONY : lego-common/main/src/net/socket/SslPtr.cpp.o

lego-common/main/src/net/socket/SslPtr.i: lego-common/main/src/net/socket/SslPtr.cpp.i

.PHONY : lego-common/main/src/net/socket/SslPtr.i

# target to preprocess a source file
lego-common/main/src/net/socket/SslPtr.cpp.i:
	$(MAKE) -f CMakeFiles/lego-common.dir/build.make CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/SslPtr.cpp.i
.PHONY : lego-common/main/src/net/socket/SslPtr.cpp.i

lego-common/main/src/net/socket/SslPtr.s: lego-common/main/src/net/socket/SslPtr.cpp.s

.PHONY : lego-common/main/src/net/socket/SslPtr.s

# target to generate assembly for a file
lego-common/main/src/net/socket/SslPtr.cpp.s:
	$(MAKE) -f CMakeFiles/lego-common.dir/build.make CMakeFiles/lego-common.dir/lego-common/main/src/net/socket/SslPtr.cpp.s
.PHONY : lego-common/main/src/net/socket/SslPtr.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... lego-common"
	@echo "... lego-client"
	@echo "... lego-server"
	@echo "... lego-common/main/src/concurrency/Semaphore.o"
	@echo "... lego-common/main/src/concurrency/Semaphore.i"
	@echo "... lego-common/main/src/concurrency/Semaphore.s"
	@echo "... lego-common/main/src/logging/Logger.o"
	@echo "... lego-common/main/src/logging/Logger.i"
	@echo "... lego-common/main/src/logging/Logger.s"
	@echo "... lego-common/main/src/net/ProtocolClient.o"
	@echo "... lego-common/main/src/net/ProtocolClient.i"
	@echo "... lego-common/main/src/net/ProtocolClient.s"
	@echo "... lego-common/main/src/net/ProtocolServer.o"
	@echo "... lego-common/main/src/net/ProtocolServer.i"
	@echo "... lego-common/main/src/net/ProtocolServer.s"
	@echo "... lego-common/main/src/net/SslServer.o"
	@echo "... lego-common/main/src/net/SslServer.i"
	@echo "... lego-common/main/src/net/SslServer.s"
	@echo "... lego-common/main/src/net/socket/IPv4SslSocket.o"
	@echo "... lego-common/main/src/net/socket/IPv4SslSocket.i"
	@echo "... lego-common/main/src/net/socket/IPv4SslSocket.s"
	@echo "... lego-common/main/src/net/socket/IPv4UdpSocket.o"
	@echo "... lego-common/main/src/net/socket/IPv4UdpSocket.i"
	@echo "... lego-common/main/src/net/socket/IPv4UdpSocket.s"
	@echo "... lego-common/main/src/net/socket/SslCtxPtr.o"
	@echo "... lego-common/main/src/net/socket/SslCtxPtr.i"
	@echo "... lego-common/main/src/net/socket/SslCtxPtr.s"
	@echo "... lego-common/main/src/net/socket/SslPtr.o"
	@echo "... lego-common/main/src/net/socket/SslPtr.i"
	@echo "... lego-common/main/src/net/socket/SslPtr.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

