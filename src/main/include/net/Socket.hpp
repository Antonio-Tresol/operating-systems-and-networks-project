/**
 *  Establece la definición de la clase Socket para efectuar la comunicación
 *  de procesos que no comparten memoria, utilizando un esquema de memoria
 *  distribuida.  El desarrollo de esta clase se hará en varias etapas, primero
 *  los métodos necesarios para los clientes, en la otras etapas los métodos para el servidor,
 *  manejo de IPv6, conexiones seguras y otros
 *
 *  Universidad de Costa Rica
 *  ECCI
 *  CI0123 Proyecto integrador de redes y sistemas operativos
 *  2023-i
 *  Grupos: 2 y 3
 *
 * (versión Ubuntu)
 *
 **/

#pragma once

#include <unistd.h>
#include <stdio.h>    // for perror
#include <stdlib.h>    // for exit
#include <string.h>    // for memset
#include <netdb.h>
#include <arpa/inet.h>    // for inet_pton
#include <sys/types.h>    // for connect
#include <sys/socket.h>

class Socket {

 public:
  Socket(char, bool IPv6 = false);    // char == 's' => stream, char == 'd' => datagram
  Socket(int);                // int = socket descriptor
  ~Socket();
  int Connect(const char *host, int port);
  int Connect(const char *host, const char *service);
  int sendTo(const void *buffer, size_t bufferSize, void *address);
  int recvFrom(void *buffer, size_t bufferSize, void *address);
  void Close();
  int Read(void *buffer, size_t bufferSize);
  int Write(const void *buffer, size_t bufferSize);
  int Write(const char *buffer);    // size is calculated with strlen
  int Listen(int backlog);
  int Bind(int port);
  Socket *Accept();
  int Shutdown(int mode);        // mode = { SHUT_RD, SHUT_WR, SHUT_RDWR }
  void SetIDSocket(int newId);

 private:
  const int TCP_ID = 6;
  const int UDP_ID = 17;
  const int NONE = 0;

  int idSocket;
  int port;
  bool ipv6;
};

/**
  *  Class constructor
  *     use Unix socket system call
  *
  *  @param	char type: socket type to define
  *     's' for stream
  *     'd' for datagram
  *  @param	bool ipv6: if we need a IPv6 socket
  *
 **/
Socket::Socket(char type, bool IPv6) {
  int typeId;
  int protocolId;

  switch (type) {
    case 's':typeId = SOCK_STREAM;
      protocolId = TCP_ID;
      break;
    case 'd':typeId = SOCK_DGRAM;
      protocolId = UDP_ID;
      break;
  }

  int domain = IPv6 ? AF_INET6 : AF_INET;

  this->idSocket = socket(domain, typeId, protocolId);
  if (-1 == idSocket) {
    perror("Socket::Socket");
    exit(2);
  }

  this->ipv6 = IPv6;
}

/**
  * Class destructor
  *
 **/
Socket::~Socket() {
  Close();
}

/**
  * Close method
  *    use Unix close system call (once opened a socket is managed like a file in Unix)
  *
 **/
void Socket::Close() {
  close(idSocket);
}

/**
  * Connect method
  *   use "connect" Unix system call
  *
  * @param	char * host: host address in dot notation, example "10.1.104.187"
  * @param	int port: process address, example 80
  *
 **/
int Socket::Connect(const char *host, int port) {
  int st = -1;
  struct sockaddr *ha;

  if (ipv6) {
    struct sockaddr_in6 host6;
    size_t len;

    memset(&host6, 0, sizeof(host6));
    host6.sin6_family = AF_INET6;

    st = inet_pton(AF_INET6, host, &host6.sin6_addr);
    if (1 == st) {    // 0 means invalid address, -1 means address error
      perror("Socket::Connect, inet_pton");
      exit(2);
    }

    host6.sin6_port = htons(port);
    ha = (struct sockaddr *) &host6;
    len = sizeof(host6);

    st = connect(this->idSocket, ha, len);
    if (-1 == st) {
      perror("Socket::Connect, connect");
      exit(2);
    }
  } else {
    struct sockaddr_in host4;

    memset((char *) &host4, 0, sizeof(host4));
    host4.sin_family = AF_INET;

    inet_pton(AF_INET, host, &host4.sin_addr);
    host4.sin_port = htons(port);
    ha = (sockaddr *) &host4;

    st = connect(idSocket, ha, sizeof(host4));
    if (-1 == st) {    // check for errors
      perror("Socket::Connect");
      exit(2);
    }
  }

  return st;
}

/**
  * Connect method
  *
  * @param	char * host: host address in dot notation, example "163.178.104.187"
  * @param	char * service: service name, example "http"
  *
 **/
int Socket::Connect(const char *host, const char *service) {
  struct addrinfo hints, *result, *rp;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
  hints.ai_socktype = SOCK_STREAM; /* Stream socket */
  hints.ai_flags = 0;
  hints.ai_protocol = 0;          /* Any protocol */

  int st = getaddrinfo(host, service, &hints, &result);

  for (rp = result; rp; rp = rp->ai_next) {
    st = connect(idSocket, rp->ai_addr, rp->ai_addrlen);
    if (0 == st)
      break;
  }

  freeaddrinfo(result);

  return st;
}

/**
  * sendTo method
  *   use "sendto" Unix system call (man sendto)
  *
  * @param	void * text: buffer to store data write to socket
  * @param	int size: buffer capacity, number of bytes to write
  *
 **/
int Socket::sendTo(const void *text, size_t size, void *address) {
  socklen_t addr_len = ipv6 ? sizeof(sockaddr_in6) : sizeof(sockaddr_in);

  int st = sendto(idSocket, text, size, NONE, (const sockaddr *) address, addr_len);
  if (-1 == st) {
    perror("Socket::sendTo");
    exit(2);
  }

  return st;
}

/**
  * recvFrom method
  *   use "recvfrom" Unix system call (man recvfrom)
  *
  * @param	void * text: buffer to store data read from socket
  * @param	int size: buffer capacity, number of bytes to read (truncates)
  *
 **/
int Socket::recvFrom(void *text, size_t size, void *address) {
  socklen_t addr_len = ipv6 ? sizeof(sockaddr_in6) : sizeof(sockaddr_in);

  int st = recvfrom(idSocket, text, size, NONE, (sockaddr *) address, &addr_len);
  if (-1 == st) {
    perror("Socket::recvFrom");
    exit(2);
  }

  return st;
}

/**
  * Read method
  *   use "read" Unix system call (man 3 read)
  *
  * @param	void * text: buffer to store data read from socket
  * @param	int size: buffer capacity, read will stop if buffer is full
  *
 **/
int Socket::Read(void *text, size_t size) {
  int st = read(idSocket, text, size);
  if (-1 == st) {
    perror("Socket::Read");
    exit(2);
  }

  return st;
}

/**
  * Write method
  *   use "write" Unix system call (man 3 write)
  *
  * @param	void * buffer: buffer to store data write to socket
  * @param	size_t size: buffer capacity, number of bytes to write
  *
 **/
int Socket::Write(const void *text, size_t size) {
  int st = write(idSocket, text, size);
  if (-1 == st) {
    perror("Socket::Write");
    exit(2);
  }

  return st;
}

/**
  * Write method
  *
  * @param	char * text: string to store data write to socket
  *
  *  This method write a string to socket, use strlen to determine how many bytes
  *
 **/
int Socket::Write(const char *text) {
  int st = write(idSocket, text, strlen(text));
  if (-1 == st) {
    perror("Socket::Write");
    exit(2);
  }

  return st;
}

/**
  * Listen method
  *   use "listen" Unix system call (server mode)
  *
  * @param	int queue: max pending connections to enqueue
  *
  *  This method define how many elements can wait in queue
  *
 **/
int Socket::Listen(int queue) {
  int st = -1;

  return st;

}

/**
  * Bind method
  *    use "bind" Unix system call (man 3 bind) (server mode)
  *
  * @param	int port: bind a socket to a port defined in sockaddr structure
  *
  *  Links the calling process to a service at port
  *
 **/
int Socket::Bind(int port) {
  int st = -1;
  struct sockaddr *ha;

  if (ipv6) {
    struct sockaddr_in6 host6;
    socklen_t len;

    memset(&host6, 0, sizeof(host6));
    host6.sin6_family = AF_INET6;
    host6.sin6_port = htons(port);
    host6.sin6_addr = in6addr_any;

    ha = (sockaddr *) &host6;
    len = sizeof(host6);

    st = bind(idSocket, ha, len);
    if (-1 == st) {
      perror("Socket::Bind");
      exit(2);
    }

  } else {
    struct sockaddr_in host4;

    memset((char *) &host4, 0, sizeof(host4));
    host4.sin_family = AF_INET;
    host4.sin_port = htons(port);
    host4.sin_addr.s_addr = INADDR_ANY;

    ha = (sockaddr *) &host4;

    st = bind(idSocket, ha, sizeof(host4));
    if (-1 == st) {
      perror("Socket::Bind");
      exit(2);
    }
  }

  return st;

}

/**
  * Accept method
  *    use "accept" Unix system call (man 3 accept) (server mode)
  *
  *  @returns	a new class instance
  *
  *  Waits for a new connection to service (TCP  mode: stream)
  *
 **/
Socket *Socket::Accept() {

  return (Socket *) 0;

}

/**
  * Shutdown method
  *    use "shutdown" Unix system call (man 3 shutdown)
  *
  *  @param	int mode define how to cease socket operation
  *
  *  Partial close the connection (TCP mode)
  *
 **/
int Socket::Shutdown(int mode) {
  int st = -1;

  return st;

}

/**
  *  SetIDSocket
  *
  *  @param	int id assigns a new value to field
  *
 **/
void Socket::SetIDSocket(int id) {

  this->idSocket = id;

}