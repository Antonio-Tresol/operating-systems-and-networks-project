  /**
 *   CI0123 PIRO
 *   Clase para utilizar los "sockets" en Linux
 *
 **/

#include <stdio.h>	// for perror
#include <stdlib.h>	// for exit
#include <string.h>	// for memset
#include <arpa/inet.h>	// for inet_pton
#include <sys/types.h>	// for connect 
#include <sys/socket.h>
#include <unistd.h>
#include "../../../include/net/socket/clSocket.hpp"
#include <netdb.h>
#include <iostream>
#include <openssl/ssl.h>
#include <openssl/err.h>
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
Socket::Socket( char type, bool IPv6 ){
    ipv6 = IPv6;
    printf("Socket::Socket: ipv6 = %d\n", ipv6);
    int domain = AF_INET;

    if (IPv6) {
        domain = AF_INET6;
    }
    int typeS;
    if ('s' == type) {
        typeS = SOCK_STREAM;
    }
    else if ('d' == type) {
        typeS = SOCK_DGRAM;
    }
    idSocket = socket(domain, typeS, 0);
}

Socket::Socket( int sd ){
  this->idSocket = sd;
}

/**
  * Class destructor
  *
 **/
Socket::~Socket(){
    Close();
}


/**
  * Close method
  *    use Unix close system call (once opened a socket is managed like a file in Unix)
  *
 **/
void Socket::Close(){
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
int Socket::Connect( const char * host, int port ) {
   int st = -1;
   if (!this->ipv6) {
    struct sockaddr_in  host4;
    struct sockaddr * ha;
    memset( (char *) &host4, 0, sizeof( host4 ) );
    host4.sin_family = AF_INET;
    inet_pton( AF_INET, host, &host4.sin_addr );
    host4.sin_port = htons( port );
    ha = (struct sockaddr *) &host4;
    st = connect( idSocket, (sockaddr *) ha, sizeof( host4 ) );
    if ( -1 == st ) {	// check for errors
      perror( "Socket::Connect" );
      exit( 2 );
    }
   } else {
    struct sockaddr_in6  host6;
    struct sockaddr * ha;
    memset( (char *) &host6, 0, sizeof( host6 ) );
    host6.sin6_family = AF_INET6;
    inet_pton( AF_INET6, host, &host6.sin6_addr );
    host6.sin6_port = htons( port );
    ha = (struct sockaddr *) &host6;
    st = connect( idSocket, (sockaddr *) ha, sizeof( host6 ) );
    if ( -1 == st ) {	// check for errors
      perror( "Socket::Connect" );
      exit( 2 );
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
int Socket::Connect( const char *host, const char *service ) {
    struct addrinfo hints, *result, *rp;
    int st;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; /* Stream socket */
    hints.ai_flags = 0;
    hints.ai_protocol = 0;          /* Any protocol */

    st = getaddrinfo( host, service, &hints, &result );

    for ( rp = result; rp; rp = rp->ai_next ) {
    st = connect( idSocket, rp->ai_addr, rp->ai_addrlen );
    if ( 0 == st )
        return st;
    }

    freeaddrinfo( result );
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
int Socket::Read(  void * text, size_t size ) {
   int st = -1;
    st = read(idSocket, text, size);
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
int Socket::Write( const void *text, size_t size ) {
   int st = -1;
    st = write(idSocket, text, size);
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
int Socket::Write( const char *text ) {
   int st = -1;
    st = write(idSocket, text, strlen(text));
    if (-1 == st) {
        printf("Error en write char*");
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
int Socket::Listen( int queue ) {
    int st = -1;

    st = listen(idSocket, queue);
    if (-1 == st) {
        perror("Socket::Listen");
        exit(2);
    }
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
int Socket::Bind( int port ) {
   int st = -1;
  //  struct sockaddr * ha;
  //  host4.sin_family = AF_INET;
  //  host4.sin_port = htons(port);
  // printf("prueba");
  if (ipv6) {
    struct sockaddr_in6 host6;
    memset(&host6, 0, sizeof(host6));
    host6.sin6_family = AF_INET6;
    host6.sin6_port = htons(port);
    // ha->sa_family = AF_INET6;
    st = bind(idSocket, (struct sockaddr*) &host6, (socklen_t) sizeof(sockaddr_in6));
  }
  else {
    struct sockaddr_in host4;
    memset(&host4, 0, sizeof(host4));
    host4.sin_family = AF_INET;
    host4.sin_port = htons(port);
    // ha->sa_family = AF_INET;
    st = bind(idSocket, (struct sockaddr*) &host4, (socklen_t) sizeof(sockaddr_in));

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
Socket * Socket::Accept(){ 
  int st = -1;
  socklen_t lenSock4;
  socklen_t lenSock6;
  if (ipv6) {
    struct sockaddr_in6 host6;
    memset(&host6, 0, sizeof(host6));
    host6.sin6_family = AF_INET6;
    host6.sin6_port = htons(port);
    // ha->sa_family = AF_INET6;
    lenSock6 = sizeof(host6);
    host6.sin6_addr = in6addr_any;
    st = accept(idSocket, (struct sockaddr*) &host6, &lenSock6);
  }
  else {
    struct sockaddr_in host4;
    memset(&host4, 0, sizeof(host4));
    host4.sin_family = AF_INET;
    host4.sin_port = htons(port);
    // ha->sa_family = AF_INET;
    lenSock4 = sizeof(host4);
    host4.sin_addr.s_addr = INADDR_ANY;

    st = accept(idSocket, (struct sockaddr*) &host4, &lenSock4);

  }
  if (-1 == st) {
    perror("Socket::Accept");
    exit(2);
  }
  return new Socket(st);
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
int Socket::Shutdown( int mode ) {
   int st = -1;
    st = shutdown(idSocket, mode);
    if (-1 == st) {
        perror("Socket::Shutdown");
        exit(2);
    }
   return st;

}


/**
  *  SetIDSocket
  *
  *  @param	int id assigns a new value to field
  *  
 **/
void Socket::SetIDSocket(int id){

    this->idSocket = id;

}

ssize_t Socket::sendTo(const void *buffer /*message*/, size_t length, void* pDest_addr) {
    // ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
    //                   const struct sockaddr *dest_addr, socklen_t addrlen);
  ssize_t sent;
  int addr6len = sizeof(sockaddr_in6);
  if (!ipv6) {
    sent = sendto(idSocket, buffer, length, 0, (const struct sockaddr*) pDest_addr, (socklen_t) sizeof(sockaddr_in));
  } else { // ipv6 = true 
    sent = sendto(idSocket, buffer, length, 0, (const struct sockaddr*) pDest_addr, (socklen_t) addr6len);
  }

  if ( -1 == sent ) {	// check for errors
      perror( "Socket::sendTo" );
      exit( 2 );
   }
  return sent;
}

ssize_t Socket::recvFrom(void* buf, size_t len, void* addr) {
  int adrrlen = sizeof(sockaddr_in);
  int addr6len = sizeof(sockaddr_in6);
  ssize_t recvd;
  if (!ipv6) {
    recvd = recvfrom(idSocket, buf, len, 0, (struct sockaddr*) addr, (socklen_t*) &adrrlen);
  } else { // ipv6 = true 
    recvd = recvfrom(idSocket, buf, len, 0, (struct sockaddr*) addr, (socklen_t*) &addr6len);
  }
  if (-1 == recvd) {
    perror("Socket::recvFrom");
    exit(2);
  }
  return recvd;
}

void Socket::InitSSLContext() {
  // SSL_library_init();
  // SSL_load_error_strings();
  // OpenSSL_add_all_algorithms();
  // ctx = SSL_CTX_new(SSLv23_client_method());
  // if (ctx == NULL) {
  //   ERR_print_errors_fp(stderr);
  //   exit(1);
  // }
  const SSL_METHOD *method = TLS_client_method();
  if (method == NULL) {
    std::cerr << "Error creating SSL method" << std::endl;
    exit(2);
  }
  SSL_CTX* ctx = SSL_CTX_new(method);
  if (ctx == NULL) {
    std::cerr << "Error creating SSL context" << std::endl;
    exit(2);
  }
  this->SSLContext = ctx;
  
}

void Socket::InitSSL() { // Create a SSL socket, a new context must be created before
  this->InitSSLContext();
  SSL * ssl = SSL_new( (SSL_CTX *) this->SSLContext );
  if (ssl == NULL) {
    std::cerr << "Error creating SSL socket" << std::endl;
    exit(2);
  }
  this->SSLStruct = (void *) ssl;
}

/**
 *  Load certificates
 *    verify and load certificates
 *
 *  @param	const char * certFileName, file containing certificate
 *  @param	const char * keyFileName, file containing keys
 *
 **/
 void Socket::SSLLoadCertificates( const char * certFileName, const char * keyFileName ) {
   // SSL_CTX * context = instance variable
   SSL_CTX* context = (SSL_CTX*) this->SSLContext;
   int st;

   if ( SSL_CTX_use_certificate_file( context, certFileName, SSL_FILETYPE_PEM ) <= 0 ) {	 // set the local certificate from CertFile
      st = SSL_get_error( (SSL *) this->SSLStruct, st );
      ERR_print_errors_fp( stderr );
      abort();
   }

   if ( SSL_CTX_use_PrivateKey_file( context, keyFileName, SSL_FILETYPE_PEM ) <= 0 ) {	// set the private key from KeyFile (may be the same as CertFile)
      st = SSL_get_error( (SSL *) this->SSLStruct, st );
      ERR_print_errors_fp( stderr );
      abort();
   }

   if ( ! SSL_CTX_check_private_key( context ) ) {	// verify private key
      st = SSL_get_error( (SSL *) this->SSLStruct, st );
      ERR_print_errors_fp( stderr );
      abort();
   }

}


int Socket::SSLConnect(const char* host, int port) {
  // int st = -1;
  // if (this->SSLStruct == NULL) {
  //   std::cerr << "Error: SSL socket not initialized" << std::endl;
  //   exit(2);
  // }
  // SSL * ssl = (SSL *) this->SSLStruct;
  // st = SSL_set_fd(ssl, this->idSocket);
  // if (st == 0) {
  //   std::cerr << "Error setting SSL socket" << std::endl;
  //   exit(2);
  // }
  // st = SSL_connect(ssl);
  // if (st != 1) {
  //   std::cerr << "Error connecting SSL socket" << std::endl;
  //   exit(2);
  // }
  // return st;
  Connect(host, port);
  SSL_set_fd( (SSL *) this->SSLStruct, this->idSocket );
  int st = SSL_connect( (SSL *) this->SSLStruct );
  if (st != 1) {
    std::cerr << "Error connecting SSL socket" << std::endl;
    exit(2);
  }
  return st;
}

int Socket::SSLConnect( char* host, char* service ) {
  Connect(host, service);
  SSL_set_fd( (SSL *) this->SSLStruct, this->idSocket );
  int st = SSL_connect( (SSL *) this->SSLStruct );
  if (st != 1) {
    std::cerr << "Error connecting SSL socket" << std::endl;
    exit(2);
  }
  return st;
}

int Socket::SSLRead( void * buffer, int size ) {
  // int st = -1;
  // if (this->SSLStruct == NULL) {
  //   std::cerr << "Error: SSL socket not initialized" << std::endl;
  //   exit(2);
  // }
  // SSL * ssl = (SSL *) this->SSLStruct;
  // st = SSL_read(ssl, buffer, size);
  // if (st < 0) {
  //   std::cerr << "Error reading SSL socket" << std::endl;
  //   exit(2);
  // }
  // return st;
  int st = SSL_read( (SSL *) this->SSLStruct, buffer, size );
  if (st <= 0) {
    std::cerr << "Error reading SSL socket" << std::endl;
    exit(2);
  }
  return st;
}

int Socket::SSLWrite( const void * text, int size ) {
  // int st = -1;
  // if (this->SSLStruct == NULL) {
  //   std::cerr << "Error: SSL socket not initialized" << std::endl;
  //   exit(2);
  // }
  // SSL * ssl = (SSL *) this->SSLStruct;
  // st = SSL_write(ssl, buffer, size);
  // if (st < 0) {
  //   std::cerr << "Error writing SSL socket" << std::endl;
  //   exit(2);
  // }
  // return st;
  int st = SSL_write( (SSL *) this->SSLStruct, text, size );
  if (st <= 0) {
    std::cerr << "Error writing SSL socket" << std::endl;
    exit(2);
  }
  return st;
}

void Socket::SSLInitServerContext() {
  SSL_library_init();
  OpenSSL_add_all_algorithms();  /* load & register all cryptos, etc. */
  SSL_load_error_strings();   /* load all error messages */

  const SSL_METHOD* method = TLS_server_method();
  if (method == NULL) {
    std::cerr << "Error creating method in Socket::SSLInitServerContext()"
      << std::endl;
    exit(2);

  }
  this->SSLContext = SSL_CTX_new(method);
  if (this->SSLContext == NULL) {
    std::cerr << "Error creating a context in Socket::SSLInitServerContext()"
      << std::endl;
    exit(2);
  }

}

void Socket::SSLInitServer( const char * certFileName,
          const char * keyFileName) {
  SSLInitServerContext();
  SSL* ssl = SSL_new((SSL_CTX*) this->SSLContext);
  if (ssl == NULL) {
    std::cerr << "Error initializing server in Socket::SSLInitServer()"
      << std::endl;
    exit(2);
  }
  this->SSLStruct = ssl;
  SSLLoadCertificates(certFileName, keyFileName);
}

/**
 *   Show SSL certificates
 *
 **/
void Socket::SSLShowCerts() {
   X509 *cert;
   char *line;

   cert = SSL_get_peer_certificate( (SSL *) this->SSLStruct );		 // Get certificates (if available)
   if ( nullptr != cert ) {
      printf("Server certificates:\n");
      line = X509_NAME_oneline( X509_get_subject_name( cert ), 0, 0 );
      printf( "Subject: %s\n", line );
      free( line );
      line = X509_NAME_oneline( X509_get_issuer_name( cert ), 0, 0 );
      printf( "Issuer: %s\n", line );
      free( line );
      X509_free( cert );
   } else {
      printf( "No certificates.\n" );
   }

}

/**
 *   SSLCreate constructs a new SSL * variable from a previous created context
 *
 *  @param	Socket * original socket with a previous created context
 *
 **/
void Socket::SSLCreate( Socket * original ) {
  SSL* ssl = SSL_new((SSL_CTX*) original->SSLContext);
  if (ssl == NULL) {
    std::cerr << "Error initializing server in Socket::SSLInitServer()"
      << std::endl;
    exit(2);
  }

  this->SSLStruct = ssl;
  int st = SSL_set_fd((SSL*)this->SSLStruct, this->idSocket);
  if (0 == st) { // yes the comparison is with 0
    std::cerr << "Error in SSL_set_fd in Socket::SSLCreate()" << std::endl;
    exit(2);
  }

}

/**
 *   SSLAccept
 *
 *  waits for a TLS/SSL client to initiate the TLS/SSL handshake
 *
 **/
void Socket::SSLAccept() {
  int st = -1;
  st = SSL_accept((SSL*)this->SSLStruct);
  if (st != 1) {
    std::cerr << "Error in SSL_accept in Socket::SSLAccept()" << std::endl;
    exit(2);
  }
}


/**
 *   Get SSL ciphers
 *
 **/
const char * Socket::SSLGetCipher() {
  return SSL_get_cipher((SSL*)this->SSLStruct);
}
