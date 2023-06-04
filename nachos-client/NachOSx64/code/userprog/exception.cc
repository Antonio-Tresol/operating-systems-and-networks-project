// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <openssl/ssl.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "copyright.h"
#include "system.h"
#include "syscall.h"
#include "socket.h"
#include "semtable.h"

using std::to_string;

void returnFromSystemCall() {
    int currentPC{machine->ReadRegister(PCReg)};
    machine->WriteRegister(PrevPCReg, currentPC);

    int nextPC{machine->ReadRegister(NextPCReg)};
    machine->WriteRegister(PCReg, nextPC);

    machine->WriteRegister(NextPCReg, nextPC + 4);
}

// Pass the user routine address as a parameter for this function
// This function is similar to "StartProcess" in "progtest.cc" file under "userprog"
// Requires a correct AddrSpace setup to work well
void NachosForkThread(void *p) { // for 64 bits version

    AddrSpace *space;

    space = currentThread->space;
    space->InitRegisters();             // set the initial register values
    space->RestoreState();              // load page table register
    space->fileTable->addThread();

// Set the return address for this thread to the same as the main thread
// This will lead this thread to call the exit system call and finish
    machine->WriteRegister(RetAddrReg, 4);

    machine->WriteRegister(PCReg, (long) p);
    machine->WriteRegister(NextPCReg, (long) p + 4);

    machine->Run();                     // jump to the user progam
    ASSERT(false);
}

void NachosStartProcess(void *filename) {
    syscallLock->Acquire();

    OpenFile *executable = fileSystem->Open(reinterpret_cast<char *>(filename));

    if (executable == NULL) {
        printf("Unable to open file %s\n", reinterpret_cast<char *>(filename));
        machine->WriteRegister(2, -1);
        syscallLock->Release();
        return;
    }

    AddrSpace *space = new AddrSpace(executable);
    space->fileTable->addThread();
    currentThread->space = space;

    delete executable;

    space->InitRegisters();
    space->RestoreState();

    syscallLock->Release();

    machine->Run();
    ASSERT(false);
}

int ipV4tcpConnect(int socketFd, const char *host, int port) {
    struct sockaddr_in hostIpv4;

    hostIpv4.sin_family = AF_INET;

    int status = inet_pton(AF_INET, host, &hostIpv4.sin_addr);

    if (status == 0) {
        printf("Invalid IPv4 address: %s\n", strerror(errno));
        return -1;
    } else if (status == -1) {
        printf("Invalid address family: %s\n", strerror(errno));
        return status;
    }

    hostIpv4.sin_port = htons(port);

    struct sockaddr *hostIpv4Ptr = reinterpret_cast<struct sockaddr *>(&hostIpv4);

    socklen_t hostIpv4Len = sizeof(hostIpv4);

    status = connect(socketFd, hostIpv4Ptr, hostIpv4Len);
    if (status == -1) {
        printf("Invalid IPv4 address: %s\n", strerror(errno));
    }

    return status;
}

int ipV6tcpConnect(int socketFd, const char *host, int port) {
    struct sockaddr_in6 hostIpv6;

    hostIpv6.sin6_family = AF_INET6;

    int status = inet_pton(AF_INET6, host, &hostIpv6.sin6_addr);

    if (status == 0) {
        printf("Invalid IPv6 address: %s\n", strerror(errno));
        return -1;
    } else if (status == -1) {
        printf("Invalid address family: %s\n", strerror(errno));
        return status;
    }

    hostIpv6.sin6_port = htons(port);

    struct sockaddr *hostIpv6Ptr = reinterpret_cast<struct sockaddr *>(&hostIpv6);

    socklen_t hostIpv6Len = sizeof(hostIpv6);

    status = connect(socketFd, hostIpv6Ptr, hostIpv6Len);
    if (status == -1) {
        printf("Invalid IPv6 address: %s\n", strerror(errno));
    }

    return status;
}

int tcpConnectByFamily(int socketFd, const char *host, int port, int family) {
    return family == AF_INET ? ipV4tcpConnect(socketFd, host, port) : ipV6tcpConnect(socketFd, host, port);
}

// Because size in memory is assumed as not including null terminator, buffer must be addr.size + 1
void readFromMemory(int addr, char *buffer, int size) {
    int pos{0};
    for (; pos < size; ++pos) {
        if (!machine->ReadMem(addr + pos, 1, reinterpret_cast<int *>(buffer + pos))) {
            printf("Error reading memory\n");
            delete[] buffer;
            ASSERT(false);
        }

        if (!*(buffer + pos)) {
            break;
        }
    }

    buffer[pos + 1] = '\0';
}

void writeToMemory(int addr, char *buffer, int size) {
    int pos{0};
    for (; pos < size && *(buffer + pos); ++pos) {
        if (!machine->WriteMem(addr + pos, 1, *(buffer + pos))) {
            printf("Error writing memory\n");
            delete[] buffer;
            ASSERT(false);
        }
    }
}

/*
 *  System call interface: Halt()
 */
void NachOS_Halt() {        // System call 0
    DEBUG('a', "Shutdown, initiated by user program.\n");
    currentThread->Finish();
    interrupt->Halt();
}


/*
 *  System call interface: void Exit( int )
 */
void NachOS_Exit() {        // System call 1
    syscallLock->Acquire();

    int returnValue{machine->ReadRegister(4)};

    processTable->release(currentThread->spaceId, returnValue);

    printf("Exited code %d\n", machine->ReadRegister(4));

    delete currentThread->space;

    syscallLock->Release();

    if (processTable->currentSize == 0) {
        interrupt->Halt();
    } else {
        currentThread->Yield();
        currentThread->Finish();
    }
}


/*
 *  System call interface: SpaceId Exec( char * )
 */
void NachOS_Exec() {        // System call 2
    syscallLock->Acquire();

    const int MAX_FILENAME_LEN{1024};

    int addr{machine->ReadRegister(4)};
    char *filename{new char[MAX_FILENAME_LEN]};

    readFromMemory(addr, filename, MAX_FILENAME_LEN);

    Thread *newT{new Thread("child to execute Fork code")};

    int spaceId{processTable->alloc(newT)};

    newT->spaceId = spaceId;

    newT->Fork(NachosStartProcess, filename);

    machine->WriteRegister(2, spaceId);

    syscallLock->Release();

    currentThread->Yield();

    returnFromSystemCall();
}


/*
 *  System call interface: int Join( SpaceId )
 */
void NachOS_Join() {        // System call 3
    SpaceId spaceId{machine->ReadRegister(4)};

    int retVal{processTable->wait(spaceId)};

    machine->WriteRegister(2, retVal);

    returnFromSystemCall();
}


/*
 *  System call interface: void Create( char * )
 */
void NachOS_Create() {        // System call 4
    syscallLock->Acquire();

    const int MAX_FILENAME_LEN{1024};

    int addr{machine->ReadRegister(4)};
    char *filename{new char[MAX_FILENAME_LEN]};

    readFromMemory(addr, filename, MAX_FILENAME_LEN);

    OpenFileId unixFileId{creat(filename, 0777)};

    if (0 >= unixFileId) {
        printf("Unable to create file: %s\n", strerror(errno));
    }

    delete[] filename;

    syscallLock->Release();

    returnFromSystemCall();        // Update the PC registers
}


/*
 *  System call interface: OpenFileId Open( char * )
 */
void NachOS_Open() {        // System call 5
    syscallLock->Acquire();

    const int MAX_FILENAME_LEN{1024};

    int addr{machine->ReadRegister(4)};
    char *filename{new char[MAX_FILENAME_LEN]};

    readFromMemory(addr, filename, MAX_FILENAME_LEN);

    OpenFileId unixFileId{open(filename, O_RDWR | O_APPEND)};

    if (0 >= unixFileId) {
        printf("Unable to open file: %s, %s\n", filename, strerror(errno));
        delete[] filename;
        machine->WriteRegister(2, -1);
        syscallLock->Release();
        returnFromSystemCall();
        return;
    }

    FileTable *fileTable{currentThread->space->fileTable};

    int nachosFileId{fileTable->Open(unixFileId)};
    if (-1 == nachosFileId) {
        printf("Unable to assign file to table: %s\n", filename);
        delete[] filename;
        machine->WriteRegister(2, -1);
        syscallLock->Release();
        returnFromSystemCall();
        return;
    }

    machine->WriteRegister(2, nachosFileId);

    delete[] filename;

    syscallLock->Release();

    returnFromSystemCall();        // Update the PC registers
}


/*
 *  System call interface: OpenFileId write( char *, int, OpenFileId )
 */
void NachOS_Write() {        // System call 6
    syscallLock->Acquire();

    int addr{machine->ReadRegister(4)};
    int size{machine->ReadRegister(5)};
    OpenFileId openFileId{machine->ReadRegister(6)};

    char *buffer{new char[size + 1]};

    readFromMemory(addr, buffer, size);

    switch (openFileId) {
        case ConsoleInput:    // User could not write to standard input
            machine->WriteRegister(2, -1);
            break;
        case ConsoleOutput:
            printf("%s\n", buffer);
            machine->WriteRegister(2, size);
            break;
        case ConsoleError:    // This trick permits to write integers to console
            printf("%d\n", machine->ReadRegister(4));
            break;
        default:
            FileTable *currentFileTable{currentThread->space->fileTable};

            if (!currentFileTable->isOpened(openFileId)) {
                machine->WriteRegister(2, -1);
            }

            int unixHandle{currentFileTable->getUnixHandle(openFileId)};

            // Is handle an SSL socket?
            auto it = socketTable->find(openFileId);
            if (it != socketTable->end() && socketTable->at(openFileId).isSsl) {
                int res{SSL_write(socketTable->at(openFileId).ssl, buffer, size)};
                if (0 >= res) {
                    uint64_t err{ERR_get_error()};
                    const char *buf{ERR_reason_error_string(err)};
                    printf("Failed to SSL write: %s\n", buf);
                    machine->WriteRegister(2, -1);
                    break;
                }
            } else {
                int res{static_cast<int>(write(unixHandle, buffer, size))};
                if (0 > res) {
                    printf("Unable to write to file: %d\n", unixHandle);
                    machine->WriteRegister(2, -1);
                    break;
                }
            }

            machine->WriteRegister(2, size);
    }

    delete[] buffer;

    syscallLock->Release();

    returnFromSystemCall();        // Update the PC registers
}


/*
 *  System call interface: OpenFileId read( char *, int, OpenFileId )
 */
void NachOS_Read() {        // System call 7
    syscallLock->Acquire();

    int addr{machine->ReadRegister(4)};
    int size{machine->ReadRegister(5)};
    OpenFileId openFileId{machine->ReadRegister(6)};

    char *buffer{new char[size + 1]};

    int res{-1};

    switch (openFileId) {
        case ConsoleInput:
            for (int i{0}; i < size; ++i) {
                read(ConsoleInput, &buffer[i], 1);

                if('\n' == buffer[i]) {
                    size = i + 1;
                }
            }

            writeToMemory(addr, buffer, size);
            break;
        case ConsoleOutput:
            machine->WriteRegister(2, -1);
            break;
        case ConsoleError:    // This trick permits to write integers to console
            printf("%d\n", machine->ReadRegister(4));
            break;
        default:
            FileTable *currentFileTable{currentThread->space->fileTable};

            if (!currentFileTable->isOpened(openFileId)) {
                machine->WriteRegister(2, -1);
            }

            int unixHandle{currentFileTable->getUnixHandle(openFileId)};


            auto it = socketTable->find(openFileId);
            if (it != socketTable->end() && socketTable->at(openFileId).isSsl) {
                res = SSL_read(socketTable->at(openFileId).ssl, buffer, size);
                if (0 >= res) {
                    uint64_t err{ERR_get_error()};
                    const char *buf{ERR_reason_error_string(err)};
                    printf("Failed to SSL read: %s\n", buf);
                    machine->WriteRegister(2, -1);
                    break;
                }
            } else {
                 res = static_cast<int>(read(unixHandle, buffer, size));
                if (0 > res) {
                    printf("Unable to read from file: %d\n", unixHandle);
                    machine->WriteRegister(2, -1);
                    break;
                }
            }

            writeToMemory(addr, buffer, size);

            machine->WriteRegister(2, res);
    }

    delete[] buffer;

    syscallLock->Release();

    returnFromSystemCall();        // Update the PC registers
}


/*
 *  System call interface: void Close( OpenFileId )
 */
void NachOS_Close() {        // System call 8
    syscallLock->Acquire();

    OpenFileId openFileId{machine->ReadRegister(4)};

    FileTable *fileTable{currentThread->space->fileTable};

    int unixHandle{fileTable->Close(openFileId)};

    if (unixHandle == -1) {
        printf("Unable to unassign file from table: %d\n", openFileId);
        machine->WriteRegister(2, -1);
        syscallLock->Release();
        returnFromSystemCall();
        return;
    }

    int res{close(unixHandle)};
    if (0 > res) {
        printf("Unable to close file: %d\n", unixHandle);
        machine->WriteRegister(2, -1);
        syscallLock->Release();
        returnFromSystemCall();
        return;
    }

    machine->WriteRegister(2, res);

    syscallLock->Release();

    returnFromSystemCall();        // Update the PC registers
}


/*
 *  System call interface: void Fork( void (*func)() )
 */
void NachOS_Fork() {        // System call 9
    syscallLock->Acquire();

    DEBUG('u', "Entering Fork System call\n");
    // We need to create a new kernel thread to execute the user thread
    Thread *newT = new Thread("child to execute Fork code");

    // We need to share the Open File Table structure with this new child

    // Child and father will also share the same address space, except for the stack
    // Text, init data and uninit data are shared, a new stack area must be created
    // for the new child
    // We suggest the use of a new constructor in AddrSpace class,
    // This new constructor will copy the shared segments (space variable) from currentThread, passed
    // as a parameter, and create a new stack for the new child
    newT->space = new AddrSpace(currentThread->space);

    // We (kernel)-Fork to a new method to execute the child code
    // Pass the user routine address, now in register 4, as a parameter
    // Note: in 64 bits register 4 need to be casted to (void *)
    newT->Fork(NachosForkThread, reinterpret_cast<void *>(machine->ReadRegister(4)));

    syscallLock->Release();

    returnFromSystemCall();    // This adjust the PrevPC, PC, and NextPC registers

    DEBUG('u', "Exiting Fork System call\n");
}


/*
 *  System call interface: void Yield()
 */
void NachOS_Yield() {        // System call 10
    currentThread->Yield();
    returnFromSystemCall();
}


/*
 *  System call interface: Sem_t SemCreate( int )
 */
void NachOS_SemCreate() {        // System call 11
    syscallLock->Acquire();

    int initialValue{machine->ReadRegister(4)};

    Sem_t semId{semaphoreTable->add({to_string(initialValue).c_str(), initialValue})};

    machine->WriteRegister(2, semId);

    syscallLock->Release();

    returnFromSystemCall();
}


/*
 *  System call interface: int SemDestroy( Sem_t )
 */
void NachOS_SemDestroy() {        // System call 12
    syscallLock->Acquire();

    Sem_t semId{machine->ReadRegister(4)};

    int res{semaphoreTable->remove(semId)};

    machine->WriteRegister(2, res);

    syscallLock->Release();

    returnFromSystemCall();
}


/*
 *  System call interface: int SemSignal( Sem_t )
 */
void NachOS_SemSignal() {        // System call 13
    syscallLock->Acquire();

    Sem_t semId{machine->ReadRegister(4)};

    Semaphore *sem{semaphoreTable->get(semId)};

    if (!sem) {
        machine->WriteRegister(2, -1);
    } else {
        sem->V();
        machine->WriteRegister(2, 1);
    }

    syscallLock->Release();

    returnFromSystemCall();
}


/*
 *  System call interface: int SemWait( Sem_t )
 */
void NachOS_SemWait() {        // System call 14
    syscallLock->Acquire();

    Sem_t semId{machine->ReadRegister(4)};

    Semaphore *sem{semaphoreTable->get(semId)};

    if (!sem) {
        machine->WriteRegister(2, -1);
    } else {
        sem->P();
        machine->WriteRegister(2, 1);
    }

    syscallLock->Release();

    returnFromSystemCall();
}


/*
 *  System call interface: Lock_t LockCreate( int )
 */
void NachOS_LockCreate() {        // System call 15
}


/*
 *  System call interface: int LockDestroy( Lock_t )
 */
void NachOS_LockDestroy() {        // System call 16
}


/*
 *  System call interface: int LockAcquire( Lock_t )
 */
void NachOS_LockAcquire() {        // System call 17
}


/*
 *  System call interface: int LockRelease( Lock_t )
 */
void NachOS_LockRelease() {        // System call 18
}


/*
 *  System call interface: Cond_t LockCreate( int )
 */
void NachOS_CondCreate() {        // System call 19
}


/*
 *  System call interface: int CondDestroy( Cond_t )
 */
void NachOS_CondDestroy() {        // System call 20
}


/*
 *  System call interface: int CondSignal( Cond_t )
 */
void NachOS_CondSignal() {        // System call 21
}


/*
 *  System call interface: int CondWait( Cond_t )
 */
void NachOS_CondWait() {        // System call 22
}


/*
 *  System call interface: int CondBroadcast( Cond_t )
 */
void NachOS_CondBroadcast() {        // System call 23
}


/*
 *  System call interface: Socket_t Socket( int, int, int )
 */
void NachOS_Socket() {            // System call 30
    syscallLock->Acquire();

    int family{machine->ReadRegister(4)};
    int sockType{machine->ReadRegister(5)};
    int isSsl{1};

    switch (family) {
        case AF_INET_NachOS:
            family = AF_INET;
            break;
        case AF_INET6_NachOS:
            family = AF_INET6;
            break;
        default:
            printf("Unsupported socket family: %d\n", family);
            machine->WriteRegister(2, -1);
            syscallLock->Release();
            returnFromSystemCall();
            return;
    }

    switch (sockType) {
        case SOCK_STREAM_NachOS:
            sockType = SOCK_STREAM;
            break;
        case SOCK_DGRAM_NachOS:
            sockType = SOCK_DGRAM;
            break;
        default:
            printf("Unsupported socket type: %d\n", sockType);
            machine->WriteRegister(2, -1);
            syscallLock->Release();
            returnFromSystemCall();
            return;
    }

    int unixHandle{socket(family, sockType, 0)};
    if (-1 == unixHandle) {
        printf("Failed to create unix socket: %s\n", strerror(errno));
        machine->WriteRegister(2, -1);
        syscallLock->Release();
        returnFromSystemCall();
        return;
    }

    Socket_t nachosHandle{currentThread->space->fileTable->Open(unixHandle)};
    if (-1 == nachosHandle) {
        printf("Failed to create nachos handle\n");
        machine->WriteRegister(2, -1);
        syscallLock->Release();
        returnFromSystemCall();
        return;
    }

    if (isSsl) {
        const SSL_METHOD *sslMethod{TLS_client_method()};

        SSL_CTX *sslCtx{SSL_CTX_new(sslMethod)};

        SSL *ssl{SSL_new(sslCtx)};

        socketTable->insert({nachosHandle, {family, sockType, ssl, sslCtx}});
    } else {
        socketTable->insert({nachosHandle, {family, sockType}});
    }

    machine->WriteRegister(2, nachosHandle);
    syscallLock->Release();
    returnFromSystemCall();
}


/*
 *  System call interface: Socket_t Connect( char *, int )
 */
void NachOS_Connect() {        // System call 31
    syscallLock->Acquire();

    Socket_t sockHandle{machine->ReadRegister(4)};
    int ipAddrAddr{machine->ReadRegister(5)};
    int port{machine->ReadRegister(6)};

    auto it = socketTable->find(sockHandle);
    if (it == socketTable->end()) {
        printf("Failed to retrieve socket by handle\n");
        machine->WriteRegister(2, -1);
        syscallLock->Release();
        returnFromSystemCall();
        return;
    }

    int unixHandle{currentThread->space->fileTable->getUnixHandle(sockHandle)};
    if (-1 == unixHandle) {
        printf("Failed to retrieve unix handle\n");
        machine->WriteRegister(2, -1);
        syscallLock->Release();
        returnFromSystemCall();
        return;
    }

    class Socket &socket{socketTable->at(sockHandle)};

    int size{socket.family == AF_INET ? 15 : 39};

    char *ipAddr{new char[size + 1]};

    readFromMemory(ipAddrAddr, ipAddr, size);

    int res{tcpConnectByFamily(unixHandle, ipAddr, port, socket.family)};
    if (-1 == res) {
        printf("Failed to tcp connect\n");
        delete[] ipAddr;
        machine->WriteRegister(2, -1);
        syscallLock->Release();
        returnFromSystemCall();
        return;
    }

    if (socket.isSsl) {
        res = SSL_set_fd(socket.ssl, unixHandle);
        if (!res) {
            uint64_t err{ERR_get_error()};
            const char *buf{ERR_reason_error_string(err)};
            printf("Failed to set SSL socket: %s\n", buf);
            delete[] ipAddr;
            machine->WriteRegister(2, -1);
            syscallLock->Release();
            returnFromSystemCall();
            return;
        }

        res = SSL_connect(socket.ssl);
        if (0 >= res) {
            uint64_t err{ERR_get_error()};
            const char *buf{ERR_reason_error_string(err)};
            printf("Failed to SSL connect socket: %s\n", buf);
            delete[] ipAddr;
            machine->WriteRegister(2, -1);
            syscallLock->Release();
            returnFromSystemCall();
            return;
        }
    }

    delete[] ipAddr;

    machine->WriteRegister(2, res);
    syscallLock->Release();
    returnFromSystemCall();
}


/*
 *  System call interface: int Bind( Socket_t, int )
 */
void NachOS_Bind() {        // System call 32
}


/*
 *  System call interface: int Listen( Socket_t, int )
 */
void NachOS_Listen() {        // System call 33
}


/*
 *  System call interface: int Accept( Socket_t )
 */
void NachOS_Accept() {        // System call 34
}


/*
 *  System call interface: int Shutdown( Socket_t, int )
 */
void NachOS_Shutdown() {    // System call 25
//    if (ssl) {
//        SSL_shutdown(ssl);
//        SSL_free(ssl);
//    }
//
//    if (sslCtx) {
//        SSL_CTX_free(sslCtx);
//    }
}


//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.
//----------------------------------------------------------------------

void
ExceptionHandler(ExceptionType which) {
    int type = machine->ReadRegister(2);

    switch (which) {

        case SyscallException:
            switch (type) {
                case SC_Halt:        // System call # 0
                    NachOS_Halt();
                    break;
                case SC_Exit:        // System call # 1
                    NachOS_Exit();
                    break;
                case SC_Exec:        // System call # 2
                    NachOS_Exec();
                    break;
                case SC_Join:        // System call # 3
                    NachOS_Join();
                    break;

                case SC_Create:        // System call # 4
                    NachOS_Create();
                    break;
                case SC_Open:        // System call # 5
                    NachOS_Open();
                    break;
                case SC_Read:        // System call # 6
                    NachOS_Read();
                    break;
                case SC_Write:        // System call # 7
                    NachOS_Write();
                    break;
                case SC_Close:        // System call # 8
                    NachOS_Close();
                    break;

                case SC_Fork:        // System call # 9
                    NachOS_Fork();
                    break;
                case SC_Yield:        // System call # 10
                    NachOS_Yield();
                    break;

                case SC_SemCreate:         // System call # 11
                    NachOS_SemCreate();
                    break;
                case SC_SemDestroy:        // System call # 12
                    NachOS_SemDestroy();
                    break;
                case SC_SemSignal:         // System call # 13
                    NachOS_SemSignal();
                    break;
                case SC_SemWait:           // System call # 14
                    NachOS_SemWait();
                    break;

                case SC_LckCreate:         // System call # 15
                    NachOS_LockCreate();
                    break;
                case SC_LckDestroy:        // System call # 16
                    NachOS_LockDestroy();
                    break;
                case SC_LckAcquire:         // System call # 17
                    NachOS_LockAcquire();
                    break;
                case SC_LckRelease:           // System call # 18
                    NachOS_LockRelease();
                    break;

                case SC_CondCreate:         // System call # 19
                    NachOS_CondCreate();
                    break;
                case SC_CondDestroy:        // System call # 20
                    NachOS_CondDestroy();
                    break;
                case SC_CondSignal:         // System call # 21
                    NachOS_CondSignal();
                    break;
                case SC_CondWait:           // System call # 22
                    NachOS_CondWait();
                    break;
                case SC_CondBroadcast:           // System call # 23
                    NachOS_CondBroadcast();
                    break;

                case SC_Socket:    // System call # 30
                    NachOS_Socket();
                    break;
                case SC_Connect:    // System call # 31
                    NachOS_Connect();
                    break;
                case SC_Bind:    // System call # 32
                    NachOS_Bind();
                    break;
                case SC_Listen:    // System call # 33
                    NachOS_Listen();
                    break;
                case SC_Accept:    // System call # 32
                    NachOS_Accept();
                    break;
                case SC_Shutdown:    // System call # 33
                    NachOS_Shutdown();
                    break;

                default:
                    printf("Unexpected syscall exception %d\n", type);
                    ASSERT(false);
                    break;
            }
            break;

        case PageFaultException: {
            break;
        }

        case ReadOnlyException:
            printf("read Only exception (%d)\n", which);
            ASSERT(false);
            break;

        case BusErrorException:
            printf("Bus error exception (%d)\n", which);
            ASSERT(false);
            break;

        case AddressErrorException:
            printf("Address error exception (%d)\n", which);
            ASSERT(false);
            break;

        case OverflowException:
            printf("Overflow exception (%d)\n", which);
            ASSERT(false);
            break;

        case IllegalInstrException:
            printf("Ilegal instruction exception (%d)\n", which);
            ASSERT(false);
            break;

        default:
            printf("Unexpected exception %d\n", which);
            ASSERT(false);
            break;
    }

}
